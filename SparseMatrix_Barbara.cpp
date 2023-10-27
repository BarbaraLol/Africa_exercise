#include <iostream>
#include <vector>
#include <algorithm>

class SparseMatrixCSR;
class SparseMatrixCOO;

class SparseMatrix {
    protected:
    std::vector<double> values;
    std::vector<int> columns;
    int size = values.size();

    public:
    //Constructor
    SparseMatrix(const std::vector <double>& input_values,  const std::vector <int>& input_columns)  :  values(input_values), 
    columns(input_columns) {}

    //Destructor for total cleanup
    virtual ~SparseMatrix() {}

    unsigned int n_col( ) const{
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
    //int* rows;
    std::vector<int> rows;
    // !!!NEW!!!
    double* values;
    int* columns;

    public:
    //Constructor for SparseMatrix COO
    SparseMatrixCOO(const std::vector <int>& input_rows, const std::vector <double>& input_values,  const std::vector <int>& input_columns): 
    SparseMatrix(input_values, input_columns), /*rows(new int[input_rows.size()])*/ rows(input_rows){
        // !!!NEW!!!
        values = new double[input_values.size()];
        columns = new int[input_columns.size()];
        std::copy(input_values.begin(), input_values.end(), values);
        std::copy(input_columns.begin(), input_columns.end(), columns);
        //Volendo definire in maniera dinamica anche rows, per poi deallocare anche la sua memoria, bisogna cambiare l'implementazione di n_row()
        //std::copy(input_columns.begin(), input_columns.end(), rows);
    }

    //Destructor to deallocate memory when done
    // !!!NEW!!!
    ~SparseMatrixCOO() {
        delete[] values;
        delete[] columns;
        //delete[] rows;
    }
    
    unsigned int n_row() const{
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
    std::vector<double> operator *(const std::vector<double>& x) {
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
    //int* rows_idx;
    std::vector<int> rows_idx;
    // !!!NEW!!!
    double* values;
    int* columns;

    public:
    //Constructor for SparseMatrix CSR
    SparseMatrixCSR(const std::vector <int>& input_rows, const std::vector <double>& input_values,  const std::vector <int>& input_columns): 
    SparseMatrix(input_values, input_columns), /*rows_idx(new int[input_rows.size()])*/ rows_idx(input_rows){
        // !!!NEW!!!
        values = new double[input_values.size()];
        columns = new int[input_columns.size()];
        std::copy(input_values.begin(), input_values.end(), values);
        std::copy(input_columns.begin(), input_columns.end(), columns);
        //Volendo definire in maniera dinamica anche rows, per poi deallocare anche la sua memoria, bisogna cambiare l'implementazione di n_row()
        //std::copy(input_rows.begin(), input_rows.end(), rows_idx);
    }

    //Destructor to deallocate memory when done
    // !!!NEW!!!
    ~SparseMatrixCSR() {
        delete[] values;
        delete[] columns;
        //delete[] rows_idx;
    }
    
    unsigned int n_row()const{
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
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
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
        for (int i = rows_idx[n]; i < rows_idx[n + 1]; i++) {
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
        for (unsigned int i =0; i<n_row(); i++) {
            std::cout << y[i] << std::endl;
        };
        return y;  
    }

    
};

// !!!NEW!!!
SparseMatrixCSR* NewCSR_SparseMatrix(const std::vector <int>& input_rowsCOO, const std::vector <double>& input_valuesCOO,  const std::vector <int>& input_columnsCOO){
    // Perform the conversion and create a CSR object
    // I need the number of the rows and the size of number of non-zero element inside the sparse matrix
    // Initialize the rows_idx vector with zeros.
    std::vector<int> rows_idx(input_rowsCOO.size()+1, 0); 

    // Count the number of non-zero elements in each row.
    for (unsigned int i = 0; i < input_rowsCOO.size(); i++) {
        rows_idx[input_rowsCOO[i] + 1]++;
    }

    // Calculate the cumulative sum to complete the rows_idx vector.
    for (int i = 1; i <= input_rowsCOO.size(); i++) {
        rows_idx[i] += rows_idx[i - 1];
    }

    SparseMatrixCSR* new_csr = new SparseMatrixCSR(rows_idx, input_valuesCOO, input_columnsCOO);
    return new_csr;
}

// !!!NEW!!!
SparseMatrixCOO* NewCOO_SparseMatrix(const std::vector <int>& input_rowsCSR, const std::vector <double>& input_valuesCSR,  const std::vector <int>& input_columnsCSR){
    // Perform the conversion and create a COO object
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

    SparseMatrixCOO* new_coo = new SparseMatrixCOO(rows, input_valuesCSR, input_columnsCSR);
    return new_coo;
}

int main(){

    //input of COO
    std::vector<double> input_valuesCOO = {3.1, 4, 5, 7.4, 2, 6};
    std::vector<int>  input_rowsCOO = { 0, 0, 1, 1, 3, 3};
    std::vector<int> input_columnsCOO = {2, 4, 2, 4, 1, 3};

    SparseMatrixCOO* M_COO = new SparseMatrixCOO( input_rowsCOO, input_valuesCOO, input_columnsCOO);

    //input of CSR
    std::vector<double> input_valuesCSR = {3.1, 4, 5, 7.4, 2, 6};
    std::vector<int>  input_rowsCSR = { 0, 2, 4,  4, 6};
    std::vector<int> input_columnsCSR = {2, 4, 2, 4, 1, 3};

    SparseMatrixCSR* M_CSR = new SparseMatrixCSR(input_rowsCSR, input_valuesCSR, input_columnsCSR);

    //Print function
    //M_COO->PrintMatrix();
    std::cout<<"\n";
    //M_CSR->PrintMatrix();

    /*// Number of columns
    std::cout << "The number of columns is " << M_COO->n_col()<< std::endl;
    std::cout << "The number of columns is " <<M_CSR->n_col()<< std::endl;

    // Number of rows
    std::cout << "The number of rows is " <<M_COO->n_row()<< std::endl;
    std::cout << "The number of rows is " << M_CSR->n_row()<< std::endl;

    // Read operator
    const SparseMatrixCOO* MCOO_const = M_COO;
    std::cout << "The element in (0,2) is " << (*MCOO_const)(0,2) << std::endl;

    const SparseMatrixCSR* MCSR_const = M_CSR;
    std::cout << "The element in (0,2) is " << (*MCSR_const)(0,2) << std::endl;

    // Write operator 
    (*M_COO)(0,2) = 3;
    M_COO->PrintMatrix();
    std::cout<< "\n";
    (*M_CSR)(0,2) = 3;*/
    //M_CSR->PrintMatrix();

    // Matrix-vector product*/

    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};

    //std::vector<double> y_COO = (*M_COO)*x;

    std::cout << "\n";
    //std::vector<double> y_CSR = (*M_CSR)*x;

    // !!!NEW!!!
    //delete M_COO;
    //delete M_CSR;

    SparseMatrixCSR* new_csr = NewCSR_SparseMatrix(input_rowsCOO, input_valuesCOO, input_columnsCOO);
    SparseMatrixCOO* new_coo = NewCOO_SparseMatrix(input_rowsCSR, input_valuesCSR, input_columnsCSR);

    //new_csr
    std::vector<double> y1_CSR = (*new_csr)*x;
    (*new_csr)(0,2)=90;
    new_csr->PrintMatrix();
    std::cout << "The number of columns is " << new_csr->n_col()<< std::endl;
    std::cout << "The number of rows is " << new_csr->n_row()<< std::endl;
    const SparseMatrixCSR* csr_const = new_csr;
    //Read
    (*new_csr)(0,2);
    std::cout << "The element in (0,2) is " << (*new_csr)(0,2) << std::endl;

    //new_coo
    std::vector<double> y1_COO = (*new_coo)*x;
    (*new_coo)(0,2)=90; //write
    new_coo->PrintMatrix();
    std::cout << "The number of columns is " << new_coo->n_col()<< std::endl;
    std::cout << "The number of rows is " << new_coo->n_row()<< std::endl;
    const SparseMatrixCOO* coo_const = new_coo;
    //Read
    (*new_coo)(0,2);
    std::cout << "The element in (0,2) is " << (*new_coo)(0,2) << std::endl;
    delete new_csr;
    delete new_coo;

    return 0;
}
