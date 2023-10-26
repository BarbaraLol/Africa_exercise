#ifndef SPARSEMATRIX_HPP_
#define SPARSEMATRIX_HPP_

#include <iostream>
#include <vector>
#include <algorithm>

class SparseMatrix {
    protected:
    std::vector<double> values;
    std::vector<int> columns;
    int size = values.size();

    public:
    //Constructor
    SparseMatrix( const std::vector <double> &input_values,  const std::vector <int> &input_columns);

    //Copy Constructor
    SparseMatrix( SparseMatrix &other){
        values = other.values;
        columns = other.columns;
    };

    //NO destructor; I'M THE DESTRUCTOR. MUAHAHAHAAHAH. 

    // Number of columns
    unsigned int n_col( ) const{
        auto max = std::max_element(columns.begin(), columns.end());
        int n_col= *max+1;
        return n_col;
    };

    // Number of nonzero elements
    int non_zeros() const {
        return size;
    };

    virtual unsigned int n_row() const { 
        return 0;
    };

    virtual const double operator()(const int n, const int m) const {
        return 0.0;
    };

    virtual double &operator ()(const int n, const int m){
        return values[0];
    };

    virtual std::vector <double> operator*(const std::vector<double>& x){
        return values;
    };

    virtual void PrintMatrix(){};

    SparseMatrixCOO switch_toCOO(){
    };

    SparseMatrixCSR switch_toCSR(){};



};


class SparseMatrixCOO: public SparseMatrix{    
    private:
    std::vector<int> rows;

    public:
    SparseMatrixCOO(const std::vector <int> &input_rows, const std::vector <double> &input_values,  const std::vector <int> &input_columns);
    
    // Number of rows 
    unsigned int n_row() const override {
        auto max = std::max_element(rows.begin(), rows.end());
        return *max+1; // qui ho messo un puntatore se no non funzionava. Perché? 
    };

    // Reading operator
    const double operator() (const  int n, const  int m) const override;

    // Writing operator.
    double &operator()(const  int n, const  int m) override;

    // Matrix-vector product
    std::vector<double> operator*(const std::vector<double>& x) override;

    // Matrix printing function
    void PrintMatrix() override;
             
};


class SparseMatrixCSR: public SparseMatrix{ 
    protected:
    std::vector<int> rows_idx; 

    public:
    SparseMatrixCSR(const std::vector <int> &input_rows, const std::vector <double> &input_values,  const std::vector <int> &input_columns);

    // Number of rows
    unsigned int n_row()const override;

    // Matrix printing function
    void PrintMatrix() override;

    // Reading operator
    const double operator()(const  int n, const  int m) const override;

    // Writing operator
    double &operator()(const  int n, const  int m) override;

    // Matrix-vector product
    std::vector <double> operator*(const std::vector<double> &x) override;

};

#endif
