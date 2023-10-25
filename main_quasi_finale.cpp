#include <iostream>
#include <vector>
#include <algorithm>

/*COSA MANCA DA FARE:
- Switch da COO a CSR;
- Copy constructor;
- Sistemare i commenti;
- virtual e override;
- tre file: cpp, hpp, main;
- input da terminale (?);
*/

class SparseMatrix {
    protected:
    std::vector<double> values;
    std::vector<int> columns;
    int size = values.size();

    public:
    //Constructor
    SparseMatrix( const std::vector <double> input_values,  const std::vector <int> input_columns)  :  values(input_values), 
    columns(input_columns) {

    }

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
    std::vector<int> rows;

    public:
    SparseMatrixCOO(const std::vector <int> input_rows, const std::vector <double> input_values,  const std::vector <int> input_columns): 
    SparseMatrix(input_values, input_columns),    rows(input_rows){};
    

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

    std::vector<int> COOtoCSR_converter(){
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
    
            /*for(int i=0; i<numRows+1; i++){
                std::cout<<row_idx[i]<<"\t";
            }
            std::cout<<std::endl;*/
            return row_idx;
        }
};






class SparseMatrixCSR: public SparseMatrix{ 
    private:
    std::vector<int> rows_idx;   
    public:
    SparseMatrixCSR(const std::vector <int> input_rows, const std::vector <double> input_values,  const std::vector <int> input_columns): 
    SparseMatrix(input_values, input_columns),    rows_idx(input_rows){};

    
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
        for (unsigned int i =0; i<n_row(); i++) {
            std::cout << y[i] << std::endl;
        };
        return y;
        
    }

    std::vector<int> CSRtoCOO_converter(){
        std::vector<int> rows_coordinates;

        rows_coordinates.resize(values.size());
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

        /*for(int i=0; i<rows_coordinates.size(); i++){
            std::cout<<rows_coordinates[i]<<"\t";
        }*/

        return rows_coordinates;
    }
};



 
    
  


int main(){

    //input of COO
    std::vector<double> input_valuesCOO = {3.1, 4, 5, 7.4, 2, 6};
    std::vector<int>  input_rowsCOO = { 0, 0, 1,   1, 3, 3};
    std::vector<int> input_columnsCOO = {2, 4, 2, 4, 1, 3};

    SparseMatrixCOO M_COO( input_rowsCOO, input_valuesCOO, input_columnsCOO);

    //input of CSR

    std::vector<double> input_valuesCSR = {3.1, 4, 5, 7.4, 2, 6};
    std::vector<int>  input_rowsCSR = { 0, 2, 4,   4, 6};
    std::vector<int> input_columnsCSR = {2, 4, 2, 4, 1, 3};

    SparseMatrixCSR M_CSR(input_rowsCSR, input_valuesCSR, input_columnsCSR);

    //Print function
    M_COO.PrintMatrix();
    std::cout<<"\n";
    M_CSR.PrintMatrix();

    // Number of columns
    std::cout << "The number of columns is " << M_COO.n_col()<< std::endl;
    std::cout << "The number of columns is " <<M_CSR.n_col()<< std::endl;

    // Number of rows
    std::cout << "The number of rows is " <<M_COO.n_row()<< std::endl;
    std::cout << "The number of rows is " << M_CSR.n_row()<< std::endl;

    // Read operator
    const SparseMatrixCOO &MCOO_const = M_COO;
    std::cout << "The element in (0,2) is " << MCOO_const(0,2) << std::endl;

    const SparseMatrixCSR &MCSR_const = M_CSR;
    std::cout << "The element in (0,2) is " << MCSR_const(0,2) << std::endl;

    // Write operator 
    M_COO(0,2) = 3;
    M_COO.PrintMatrix();
    std::cout<< "\n";
    M_CSR(0,2) = 3;
    M_CSR.PrintMatrix();

    // Matrix-vector product

    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};

    std::vector<double> y_COO = M_COO*x;
    std::cout << "\n";
    std::vector<double> y_CSR = M_CSR*x;

    return 0;
}
