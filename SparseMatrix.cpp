#include "SparseMatrix.hpp"

/*COSA MANCA DA FARE:
- Switch da COO a CSR;
- Copy constructor;
- bash script
- Sistemare i commenti;
- input da terminale (?);
*/

SparseMatrix::SparseMatrix (
    const std::vector <double> input_values,  const std::vector <int> input_columns)  :  values(input_values), 
    columns(input_columns){};

SparseMatrixCOO::SparseMatrixCOO(const std::vector <int> input_rows, const std::vector <double> input_values,  const std::vector <int> input_columns): 
    SparseMatrix(input_values, input_columns), rows(input_rows){};
    
const double SparseMatrixCOO::operator()(const  int n, const  int m) const {
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
double &SparseMatrixCOO::operator()(const  int n, const  int m) {
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

//Matrix-vector product
std::vector<double> SparseMatrixCOO::operator *(const std::vector<double>& x) {
        if (x.size() != n_col()) {
            throw std::invalid_argument("Incompatible dimension ");
            return std::vector<double>();
        }

        std::vector<double> y(n_row(), 0.0);

        for (int i = 0; i < size; i++) {
            y[rows[i]] += values[i] * x[columns[i]];
        }

        for (unsigned int i =0; i<n_row(); i++) {
            std::cout << y[i] << std::endl;
        }
        return y;
    };

//matrix printing function
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

SparseMatrixCSR SparseMatrix::switch_toCSR(){
    std::vector<int> rows_coordinates;

        rows_idx.resize(values.size());
        unsigned int count=0, index=0, diff;

        for(unsigned int i=0; i<rows_idx.size(); i++){
            if(rows_idx[i]!=0 && rows_idx[i]>rows_idx[i-1]){
                diff=rows_idx[i]-rows_idx[i-1];
                for(unsigned int j=0; j<diff; j++){
                    rows_coordinates[index]=i-1;
                    index++;
                }
            }
        }

        for(int i=0; i<rows_coordinates.size(); i++){
            std::cout<<rows_coordinates[i]<<"\t";
        }

        return SparseMatrixCSR(rows_coordinates, values, columns);
};
    };

SparseMatrixCOO SparseMatrix::switchtoCOO(){
    std::vector<int> row_idx;
        //I need the number of the rows and the size of number of non-zero element inside the sparse amtrix
        const int numRows=this->n_row();

        row_idx.resize(numRows+1);
        
        row_idx[0]=0;
        unsigned int count=0;

        for(unsigned int i=0; i<size; i++){
            for(unsigned int j=0; j<size; j++){
                if(rows[j]==i){
                    count++;
                    row_idx[i+1]=count;
                }
                //case in which the row has all zero elements
                else if(rows[j]!=i){
                    row_idx[i+1]=count;
                }
            }
        }

        for(int i=0; i<numRows+1; i++){
            std::cout<<row_idx[i]<<"\t";
        }
        std::cout<<std::endl;
        return SparseMatrixCOO(row_idx, values, columns);
}


SparseMatrixCSR::SparseMatrixCSR(const std::vector <int> input_rows, const std::vector <double> input_values,  const std::vector <int> input_columns): 
    SparseMatrix(input_values, input_columns),    rows_idx(input_rows){};

    
unsigned int SparseMatrixCSR::n_row()const{
        return rows_idx.size()-1; 
        }

void SparseMatrixCSR::PrintMatrix() {
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
double &SparseMatrixCSR::operator()(const  int n, const  int m) {
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
        
    };
