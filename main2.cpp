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
    

    int n_row( ){
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
    
   

    };





class SparseMatrixCSR: public SparseMatrix{ 
    private:
    std::vector<int> rows_idx;   
    public:
    SparseMatrixCSR(const std::vector <int> input_rows, const std::vector <double> input_values,  const std::vector <int> input_columns): 
    SparseMatrix(input_values, input_columns),    rows_idx(input_rows){};

    
    int n_row( ){

        return rows_idx.size()-1; // qui ho messo un puntatore se no non funzionava. Perché? 
        }

};

  


int main(){
    std::vector<double> input_values= {3.1, 4, 5, 7.4, 2, 6};
    std::vector<int>  input_rows= { 0, 0, 1,   1, 3, 3};
    std::vector<int> input_columns={ 2, 4, 2,   4, 1, 3};
    SparseMatrixCOO M( input_rows, input_values, input_columns);

    const SparseMatrixCOO &a_const = M;
    std::cout << a_const(10,2) << std::endl;
    
        int x = M.n_col();
    std::cout<< "Il numero di col è "<<x<<std::endl;


        int y = M.n_row();
    std::cout<< "Il numero di righe è "<<y<<std::endl;



    //    double a=M(0,2);
    //std::cout<< "leggi l'elemento M(0,2)"<<a<std::endl;
    return 0;
}