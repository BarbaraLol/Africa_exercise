#include <iostream>
#include <vector>
#include <algorithm>

class SparseMatrix {
    protected:

    std::vector<double> values;
    //std::vector<int> rows;
    std::vector<int> columns;
    const int size = values.size();

    public:
    //Constructor

    /*SparseMatrix(const std::vector <double> input_values, const std::vector <int> input_rows, const std::vector <int> input_columns)  :  values(input_values),

    rows(input_rows), columns(input_columns) {*/
    SparseMatrix(const std::vector <double> input_values, const std::vector <int> input_columns)  :  values(input_values), columns(input_columns) {

 

    }

 

    int n_col( ){

        auto max = std::max_element(columns.begin(), columns.end());

        return *max; // qui ho messo un puntatore se no non funzionava. Perché?

        }

 

    int non_zeros(){

        return size;

        }

};


/* class SparseMatrixCOO: public SparseMatrix{    

    public:

    SparseMatrixCOO(const std::vector <double> input_values, const std::vector <int> input_rows, const std::vector <int> input_columns);

 

   

    int n_row( ){

        auto max = std::max_element(rows.begin(), rows.end());

        return *max; // qui ho messo un puntatore se no non funzionava. Perché?

        }




   double read(int n,int m){

        //throw an error

        if (n>n_row()){

            std::cout << "Index out of range";

        }

        //cose serie

        int numero;

        for (int i; i=0; i++){

            if( rows[i]==n){

                if( columns[i]==m){

                    numero= values[i];

                }

            }

            else{

                return 0;

            }

 

        }

    }

 



};*/

 

class SparseMatrixCSR: public SparseMatrix{    
    private:
    std::vector<int> row_idx;
    public:

    SparseMatrixCSR(const std::vector <double> input_values, const std::vector <int> input_rows, const std::vector <int> input_columns):SparseMatrix(input_values, input_columns), row_idx(input_rows){};   

    /*int n_row( ){


        return rows.size()-1; // qui ho messo un puntatore se no non funzionava. Perché?

        }*/

    void print(){
        std::cout<<"ciao"<<std::endl;
    }


};
 

int main(){

    std::vector<double> input_values= {3.1, 4, 5, 7.4, 2, 6};

    std::vector<int>  input_rows= { 0, 0, 1,   1, 3, 3};

    std::vector<int> input_columns={ 2, 4, 2,   4, 1, 3};
    SparseMatrixCSR M2(input_values, input_rows, input_columns);
    M2.print();

    //int x = M.n_col();
    //int x = M.n_row();
    //std::cout<< "Il numero di colonne è "<<x<<std::endl;

    //std::cout<< input_values.at(1)<<std::endl;

 

    return 0;

}