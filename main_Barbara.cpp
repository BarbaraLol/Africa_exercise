#include <iostream>
#include <vector>
#include <algorithm>


class SparseMatrix {
    protected:
    std::vector<double> values;
    std::vector<int> columns;
    const int size = values.size();

    public:
    //Constructor
    SparseMatrix( const std::vector <double> input_values,  const std::vector <int> input_columns)  :  values(input_values), 
    columns(input_columns) {

    }

    int n_col( ){
        auto max = std::max_element(columns.begin(), columns.end());
        int n_col= *max+1;
        return n_col; // qui ho messo un puntatore se no non funzionava. Perché? 
        }

    int non_zeros(){
        return size;
        }
};

class SparseMatrixCOO: public SparseMatrix{    
    private:
    std::vector<int> rows;

    public:
    SparseMatrixCOO(const std::vector <int> input_rows, const std::vector <double> input_values,  const std::vector <int> input_columns): 
    SparseMatrix(input_values, input_columns),    rows(input_rows){};
    

    int n_row(){
        auto max = std::max_element(rows.begin(), rows.end());
        return *max+1; // qui ho messo un puntatore se no non funzionava. Perché? 
    }

    
    
    const double operator()(const  int n, const  int m) const {

        //throw an error
        auto max_row = std::max_element(rows.begin(), rows.end());
        auto max_col = std::max_element(columns.begin(), columns.end());

        if (n>*max_row || m>*max_col){
            std::cout << "Index out of range";
        }
        

        //read
        double num = 0;
        for (int i=0; i<size-1; i++){
            if( rows[i]==n){
                if( columns[i]==m){
                    num=values[i];
                }
            }
        }

        return num;
    }

    // Writing operator.
    double &operator()(const  int n, const  int m) {
        auto max_row = std::max_element(rows.begin(), rows.end());
        auto max_col = std::max_element(columns.begin(), columns.end());

        if (n>*max_row || m>*max_col){
            throw std::invalid_argument("Index out of range");    
        }
        
        //read
        for (int i=0; i<size-1; i++){
            if( rows[i]==n){
                if( columns[i]==m){
                    return values[i];
                }
            }
        }
    }

    //Matrix-vector product
    std::vector <double> operator *(std::vector<double> &x) const{
        std::vector<double> y;
            int diff, i=0, size=rows.size();
            double elem;
            while(i<size){
                if(i==0){
                    elem=x[columns[i]]*values[i];
                }
                else if(rows[i]==rows[i-1]){
                    elem+=x[columns[i]]*values[i];
                }                
                elseif(rows[i]!=rows[i-1]){
                    y.push_back(elem);
                    if(rows[i]<rows[i-1]){
                        elem=(x[columns[i]]*values[i])+(y.at(rows[i]));
                        y.at(rows[i])=elem;                 
                    }
                    else if(rows[i]>rows[i-1]){
                        diff=rows[i]-(rows[i-1]+1);
                        elem=0.0;
                        for(int i=0; i<diff; i++){
                            y.push_back(elem);
                        }
                        elem+=x[columns[i]]*values[i];
                        diff=0;
                    }
                }
                i++;
            }
            y.push_back(elem);
        return y;
    }  

    //matrix printing function
    void PrintMatrix(){
        int i=0, num_rows=n_row(), num_cols=n_col();
        std::vector<int> cols_value;  
        
        //Rows from 0 to n-1
        while(i<num_rows-1){
            //I search for the colum value of the elemnts at the i row
            for(int j=0; j<size; j++){
                if(rows[j]==i){
                    cols_value.push_back(columns[j]);
                }
                else{
                cols_value.push_back(-1);
                }
            }

            //For cycle to print all the j columns
            for(int j=0; j<num_cols; j++){
                auto to_find=std::find(cols_value.begin(), cols_value.end(), j);
                if (to_find!=cols_value.end()){
                    int position = std::distance(cols_value.begin(), to_find);
                    std::cout<<values[position]<<"\t";
                }
                else if (to_find==cols_value.end()){
                    std::cout<<"0\t";
                }      
            }
            std::cout<<""<<std::endl;
            cols_value.clear();
            i++;
        }

        //Case: last row
        if(i==num_rows-1){

            //I search for the colum value of the elemnts at the bootom row
            for(int j=0; j<size; j++){
                if(rows[j]==i){
                    cols_value.push_back(columns[j]);
                }
                else{
                    cols_value.push_back(-1);
                }
            }

            //For cycle to print all the j columns 
            for(int j=0; j<num_cols; j++){
                auto to_find=std::find(cols_value.begin(), cols_value.end(), j);
                if (to_find!=cols_value.end()){
                    int position = std::distance(cols_value.begin(), to_find);
                    std::cout<<values[position]<<"\t";
                }
                else if (to_find==cols_value.end()){
                    std::cout<<"0\t";
                }
            }
            std::cout<<""<<std::endl;
            cols_value.clear();
        }
    }
};





class SparseMatrixCSR: public SparseMatrix{ 
    private:
    std::vector<int> rows_idx;   
    public:
    SparseMatrixCSR(const std::vector <int> input_rows, const std::vector <double> input_values,  const std::vector <int> input_columns): 
    SparseMatrix(input_values, input_columns),    rows_idx(input_rows){};

    
    int n_row(){
        return rows_idx.size()-1; // qui ho messo un puntatore se no non funzionava. Perché? 
        }

};

  


int main(){
    std::vector<double> input_values = {3.1, 4, 5, 7.4, 2, 6, 6, 0.2};
    std::vector<int>  input_rows = {0, 0, 1, 1, 3, 5, 2, 0};
    std::vector<int> input_columns = {2, 4, 2, 4, 1, 3, 1, 1};
    SparseMatrixCOO M( input_rows, input_values, input_columns);

    const SparseMatrixCOO &a_const = M;
    std::cout << a_const(10,2) << std::endl;
    
    int x = M.n_col();
    std::cout<< "Il numero di col è "<<x<<std::endl;


    int y = M.n_row();
    std::cout<< "Il numero di righe è "<<y<<std::endl;

    //matrix-vector product
    std::vector<double> x_vector = {1.0, 2.2, 3.1, 4.0, 5.0};
    std::vector<double> y_vector = M * x_vector;
    for(int i=0; i<y; i++){
        std::cout<<y_vector[i]<<std::endl;
    }

    //matrix printing function
    M.PrintMatrix();
    
    return 0;
}