#include <iostream>
#include <vector>
#include <algorithm>

class SparseMatrix {
public:
    //Constructor
    SparseMatrix(const  std::vector<double> input_values, const std::vector<int> input_columns) 
     : values(input_values), columns(input_columns) {}

    int n_col( ){
    
        auto max = std::max_element(columns.begin(), columns.end());
        return *max; // qui ho messo un puntatore se no non funzionava. Perché? 

    }
    

    int non_zeros(){
        return size;
    }

   /* double read(int n,int m){
        //throw an error
        if (n>n_row()){
            std::cout << "Index out of range";
        }
        //cose serie
        double numero;
        for (int i; i=0; i++){
            if( rows[i]==n){
                if( columns[i]==m){
                    numero= values[i];
                }
            }
            else{
                return 0;
            }
        return numero;
        }
    }*/

    protected:
    std::vector<double> values;
    std::vector<int> columns;
    const int size = values.size();

};

class SparseMatrixCOO: public SparseMatrix{    

protected: 
    std::vector<int> rows;

public:

    SparseMatrixCOO(const std::vector<double> input_values, const std::vector<int> input_columns, const std::vector<int> input_rows) : SparseMatrix(values, columns), rows(input_rows) {};

    int n_row( ){
        auto max = std::max_element(rows.begin(), rows.end());
        return *max; // qui ho messo un puntatore se no non funzionava. Perché?
    }

 

};

class SparseMatrixCSR: public SparseMatrix{    

    protected:
    std::vector<int> rows_idx;
    public:

    SparseMatrixCSR(const std::vector<double> input_values, const std::vector<int> input_columns, const std::vector<int> input_rows) : SparseMatrix(values, columns), rows_idx(input_rows) {};

    int n_row( ){
        /*int max= rows;
        for (int i=0; i<size; i++){
            if (&rows[i]<&rows[i+1]){
                max= rows[i+1];
            }
        }
        return max;*/
        return rows_idx.size()-1; // qui ho messo un puntatore se no non funzionava. Perché?
        }

 

};

int main() {

    std::vector<double> input_values = {1.0, 9.1, 3.2, 4.5};
    std::vector<int> input_columns = {0, 9, 2, 7};
    std::vector<int> input_rows = {0, 9, 2, 7};
    std::vector<int> input_rowsidx = {0, 1, 3, 3, 5};
   
    SparseMatrixCOO A(input_values, input_columns, input_rows);
    SparseMatrixCSR B(input_values, input_columns, input_rowsidx); 


    // double x = A.read(2,2);
    int n_colonne = A.n_col();
    int n_righe = A.n_row(); 
    int nonzero_elements = A.non_zeros();

    int n_cols = B.n_col();
    int n_rows = B.n_row();
    int nonzeros = B.non_zeros();

    std::cout<< "Il numero di colonne di A è "<<n_colonne<< std::endl;
    std::cout<< "Il numero di righe di A è "<<n_righe<< std::endl;
    std::cout<< "Il numero di elementi non nulli di A è "<<nonzero_elements<< std::endl;

    std::cout<< "Il numero di colonne di B è "<<n_cols<< std::endl;
    std::cout<< "Il numero di righe di A è "<<n_rows<< std::endl;
    std::cout<< "Il numero di elementi non nulli di A è "<<nonzeros<< std::endl;


    return 0;

}

