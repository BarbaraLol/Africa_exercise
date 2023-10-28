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
    SparseMatrix(const std::vector <double>& input_values,  const std::vector <int>& input_columns) : values(input_values), columns(input_columns){};
    
    //Destructor for total cleanup
    virtual ~SparseMatrix();

    //Copy Constructor
    SparseMatrix( SparseMatrix &other){
        values = other.values;
        columns = other.columns;
    } 

    // Number of columns
    unsigned int n_col( ) const{
        auto max = std::max_element(columns.begin(), columns.end());
        int n_col= *max+1;
        return n_col;
    }

    // Number of nonzero elements
    int non_zeros() const {
        return size;
    }

    virtual unsigned int n_row() const { 
        return 0;
    }

    virtual const double operator()(const int n, const int m) const {
        return 0.0;
    }

    virtual double &operator ()(const int n, const int m){
        return values[0];
    }

    virtual std::vector <double> operator*(const std::vector<double>& x){
        return values;
    }

    virtual void PrintMatrix(){};
};


class SparseMatrixCOO: public SparseMatrix{    
    private:
    std::vector<int> rows;
    double* values;
    int* columns;

    public:
    // Constructor for SparseMatrix COO
    SparseMatrixCOO(const std::vector <int>& input_rows, const std::vector <double>& input_values,  const std::vector <int>& input_columns);

    // Destructor to deallocate memory when done
    ~SparseMatrixCOO();

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
    private:
    std::vector<int> rows_idx;
    double* values;
    int* columns;

    public:
    //Constructor for SparseMatrix CSR
    SparseMatrixCSR(const std::vector <int>& input_rows, const std::vector <double>& input_values,  const std::vector <int>& input_columns);

    //Destructor to deallocate memory when done
    ~SparseMatrixCSR();

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

SparseMatrixCSR* NewCSR_SparseMatrix(const std::vector <int>& input_rowsCOO, const std::vector <double>& input_valuesCOO,  const std::vector <int>& input_columnsCOO);

SparseMatrixCOO* NewCOO_SparseMatrix(const std::vector <int>& input_rowsCSR, const std::vector <double>& input_valuesCSR,  const std::vector <int>& input_columnsCSR);

#endif
