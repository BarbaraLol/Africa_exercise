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

    int n_col( ) const{
        auto max = std::max_element(columns.begin(), columns.end());
        int n_col= *max+1;
        return n_col; // qui ho messo un puntatore se no non funzionava. Perché? 
        }

    int non_zeros() const{
        return size;
        }
};

class SparseMatrixCOO: public SparseMatrix{    
    private:
    std::vector<int> rows;

    public:
    SparseMatrixCOO(const std::vector <int> input_rows, const std::vector <double> input_values,  const std::vector <int> input_columns): 
    SparseMatrix(input_values, input_columns),    rows(input_rows){};
    

    int n_row() const{
        auto max = std::max_element(rows.begin(), rows.end());
        return *max+1; // qui ho messo un puntatore se no non funzionava. Perché? 
    }

    
    
    const double operator()(const  int n, const  int m) const {
        //throw an error
        int max_row=this->n_row();
        int max_col=this->n_col();

        if (n>max_row || m>max_col){
            throw std::invalid_argument("Index out of bound"); 
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
        int max_row=this->n_row();
        int max_col=this->n_col();
        if (n>max_row || m>max_col){
            throw std::invalid_argument("Index out of bound");    
        }
        //bool flag=false; //Probabilmente questo non serve 
        //read
        for (int i=0; i<size-1; i++){
            if( rows[i]==n){
                if( columns[i]==m){
                    return values[i];
                    //flag=true; //Probabilmente questo non serve 
                }
            }
        }
        //if(flag==false){ //Probabilmente questo non serve 
            throw std::invalid_argument("You can only modify the non-zero elements of the sparse matrix");
        //}
        
    }

    //Matrix vector product
    std::vector<double> operator *(const std::vector<double>& vettore) {
        if (vettore.size() != n_col()) {
            std::cerr << "Dimensioni incompatibili per il prodotto matrice-vettore." << std::endl;
            return std::vector<double>();
        }

        std::vector<double> risultato(n_row(), 0.0);

        for (unsigned  i = 0; i < size; i++) {
            risultato[rows[i]] += values[i] * vettore[columns[i]];
        }

        for (int i =0; i<n_row(); i++) {
            std::cout << risultato[i] << std::endl;
        }
        return risultato;
    };

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

    
    int n_row()const{
        return rows_idx.size()-1; 
        }

    void PrintMatrix() {
        int numRows = n_row(); 
        if (numRows <= 0) {
            //if  the matrix is empty
            std::cout << "Sparse matrix is empty" << std::endl;
            return;
        }

        int numCols = n_col();
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                int index = -1;
                // Trova l'indice in cui si trova il valore nella colonna corrente
                for (int i = rows_idx[row]; i < rows_idx[row + 1]; ++i) {
                    if (columns[i] == col) {
                        index = i;
                       // break;

                    }
                }
                if (index != -1) {
                    // Valore non nullo nella colonna
                    std::cout << values[index] << "\t";
                } else {
                    // Valore nullo
                    std::cout << "0\t";
                }
            }
            std::cout << std::endl;
        }
    }

    //reading operator
    const double operator()(const  int n, const  int m) const {
        int max_row=this->n_row();
        int max_col=this->n_col();
        if (n>max_row || m>max_col){
            throw std::invalid_argument("Index out of bound"); 
        }
        
        //read
        double num = 0;
        for (int i = rows_idx[n]; i < rows_idx[n + 1]; ++i) {
            if (columns[i] == m) {
                num=values[i];
            }
       
        }  
        return num;
    }

    //writing operator
    double &operator()(const  int n, const  int m) {
        int max_row=this->n_row();
        int max_col=this->n_col();
        if (n>max_row || m>max_col){
            throw std::invalid_argument("Index out of bound"); 
        }
        
        //read
        for (int i = rows_idx[n]; i < rows_idx[n + 1]; ++i) {
            if (columns[i] == m) {
                return values[i];
            }
       
        }

        throw std::invalid_argument("You can only modify the non-zero elements of the sparse matrix");
        }

    //matrix vector
    std::vector <double> operator *(std::vector<double> &x) const{
        const int numRows= this->n_row();

        std::vector<double> y;
        for (int row = 0; row < numRows; ++row) { 
            double elem=0.0;
                for (int i = rows_idx[row]; i < rows_idx[row + 1]; ++i) {
                        int col_index=columns[i];
                        elem+=values[i]*x[col_index];
                    }
                y.push_back(elem);
                }
        return y;
    }
    };



 
    
  


int main(){

    
    std::vector<double> input_values = {3.1, 4, 5, 7.4, 2, 6};
    std::vector<int>  input_rows = { 0, 0, 1,   1, 3, 3};
    std::vector<int> input_columns = {2, 4, 2, 4, 1, 3};
    SparseMatrixCOO M( input_rows, input_values, input_columns);


    M.PrintMatrix();
    int a=M.n_row();
    //std::cout << a << std::endl;
    //std::cout << M(0,2) << std::endl;


    std::vector<double> vettore = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> risultato = M*vettore;

    /*
    const SparseMatrixCSR &a_const = M;
    std::cout << a_const(20,4) << std::endl;
 
    //matrix printing function
    M.PrintMatrix();
    std::cout << "\n" << std::endl;
    //M.PrintMatrix(); */
    return 0;
}