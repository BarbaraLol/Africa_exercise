#include "SparseMatrix.hpp"

/*COSA MANCA DA FARE:
- Switch da COO a CSR;
- Copy constructor;
- bash script
- Sistemare i commenti;
- input da terminale (?);
-parentesone
*/

//BASE CLASS CONSTRUCTOR
//SparseMatrix::SparseMatrix(const std::vector <double>& input_values,  const std::vector <int>& input_columns)  :  values(input_values), columns(input_columns) {}
//Destructor for total cleanup
SparseMatrix::~SparseMatrix(){}

//COO SUBCLASS CONSTRUCTOR
SparseMatrixCOO::SparseMatrixCOO(const std::vector <int>& input_rows, const std::vector <double>& input_values,  const std::vector <int>& input_columns): SparseMatrix(input_values, input_columns), rows(input_rows){
    values = new double[input_values.size()];
    columns = new int[input_columns.size()];
    std::copy(input_values.begin(), input_values.end(), values);
    std::copy(input_columns.begin(), input_columns.end(), columns);
}

//Destructor to deallocate memory when done
SparseMatrixCOO::~SparseMatrixCOO(){
    delete[] values;
    delete[] columns;
}

//READING OPERATOR
const double SparseMatrixCOO::operator()(const  int n, const  int m) const {
        int max_row=this->n_row();
        int max_col=this->n_col();

        //throw an error if the index are out of bound
        if (n>max_row || m>max_col){
            throw std::invalid_argument("Index out of bound"); 
        }

        //find the element
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

// WRITING OPERATOR
double &SparseMatrixCOO::operator()(const  int n, const  int m){
        int max_row=this->n_row();
        int max_col=this->n_col();

        //throw an error if the index are out of bound
        if (n>max_row || m>max_col){
            throw std::invalid_argument("Index out of bound");    
        }

        //find the element that has to be changed
        for (int i=0; i<size-1; i++){
            if( rows[i]==n){
                if( columns[i]==m){
                    return values[i];
                }
            }
        }
        throw std::invalid_argument("You can only modify the non-zero elements of the sparse matrix");
}

// MATRIX-VECTOR PRODUCT
std::vector<double> SparseMatrixCOO::operator *(const std::vector<double>& x){
    
        //throw an error if the dimensions doesn't match
        if (x.size() != n_col()){
            throw std::invalid_argument("Incompatible dimension ");
            return std::vector<double>();
        }

        std::vector<double> y(n_row(), 0.0);    //vector of the needed dimentions
    
        //execute the product
        for (int i = 0; i < size; i++){
            y[rows[i]] += values[i] * x[columns[i]];
        }
    
        //print the result
        for (unsigned int i =0; i<n_row(); i++){
            std::cout << y[i] << std::endl;
        }
        return y;
}

// PRINTING FUNCTION
void SparseMatrixCOO::PrintMatrix(){
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


//CSR SUBCLASS CONSTRUCTOR
SparseMatrixCSR::SparseMatrixCSR(const std::vector <int>& input_rows, const std::vector <double>& input_values,  const std::vector <int>& input_columns): SparseMatrix(input_values, input_columns), rows_idx(input_rows){
    values = new double[input_values.size()];
    columns = new int[input_columns.size()];
    std::copy(input_values.begin(), input_values.end(), values);
    std::copy(input_columns.begin(), input_columns.end(), columns);
}

//Destructor to deallocate memory when done
SparseMatrixCSR::~SparseMatrixCSR() {
    delete[] values;
    delete[] columns;
}

//NUMBER OF ROWS    
unsigned int SparseMatrixCSR::n_row()const{
        return rows_idx.size()-1; 
}

//PRINTING FUNCTION
void SparseMatrixCSR::PrintMatrix() {
    int numRows = n_row(); 

    //if the matrix is empty
    if (numRows <= 0) {
        std::cout << "Sparse matrix is empty" << std::endl;
        return;
    }
    int numCols = n_col();
    
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            int index = -1;
            for (int i = rows_idx[row]; i < rows_idx[row + 1]; ++i) {
                //repete the following instruction a number of time equal to the non zero element in the row 
                if (columns[i] == col) {
                    index = i;
                    // break;
                }
            }
            if (index != -1) {
                // Non zero element at the position (row,col)
                std::cout << values[index] << "\t";
            } else {
                // Zero element
                std::cout << "0\t";
            }
        }
        std::cout << std::endl;
    }
}

//READING OPERATOR
const double SparseMatrixCSR::operator()(const  int n, const  int m) const {
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
double &SparseMatrixCSR::operator()(const  int n, const  int m){
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
std::vector <double> SparseMatrixCSR::operator*(const std::vector<double> &x) {
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
        for (unsigned int i =0; i<n_row(); i++) {
            std::cout << y[i] << std::endl;
        };
        return y; 
}


// Following, two stand alone function that transform a COO object into a CSR one an vice versa

SparseMatrixCSR* NewCSR_SparseMatrix(const std::vector <int>& input_rowsCOO, const std::vector <double>& input_valuesCOO,  const std::vector <int>& input_columnsCOO){
    // Perform the conversion and create a CSR object
    // I need the number of the rows and the size of number of non-zero element inside the sparse matrix
    // Initialize the rows_idx vector with zeros.
    auto max = std::max_element(input_rowsCOO.begin(), input_rowsCOO.end());
    std::vector<int> rows_idx(*max+2, 0); 

    // Count the number of non-zero elements in each row.
    for (unsigned int i=0; i<input_rowsCOO.size(); i++) {
        rows_idx[input_rowsCOO[i] + 1]++;
    }

    // Calculate the cumulative sum to complete the rows_idx vector.
    for (int i=1; i<=input_rowsCOO.size(); i++) {
        rows_idx[i] += rows_idx[i - 1];
    }

    for(int i=0; i<rows_idx.size(); i++){
        std::cout<<rows_idx[i]<<"\t";
    }
    std::cout<<std::endl;

// Creation of a new CSR object by calling it's constructor
    SparseMatrixCSR* new_csr = new SparseMatrixCSR(rows_idx, input_valuesCOO, input_columnsCOO);
    return new_csr;
}

SparseMatrixCOO* NewCOO_SparseMatrix(const std::vector <int>& input_rowsCSR, const std::vector <double>& input_valuesCSR,  const std::vector <int>& input_columnsCSR){
    // Perform the conversion and create a COO object
    // Starting from creating a COO rows vector from a CSR one
    std::vector<int> rows;

    rows.resize(input_columnsCSR.size());
    unsigned int count=0, index=0, diff;

    for(unsigned int i=0; i<input_rowsCSR.size(); i++){
        if(input_rowsCSR[i]!=0 && input_rowsCSR[i]>input_rowsCSR[i-1]){
            diff=input_rowsCSR[i]-input_rowsCSR[i-1];
            for(unsigned int j=0; j<diff; j++){
                rows[index]=i-1;
                index++;
            }
        }
    }

    // Creation of a new COO object by calling it's constructor
    SparseMatrixCOO* new_coo = new SparseMatrixCOO(rows, input_valuesCSR, input_columnsCSR);
    return new_coo;
}
