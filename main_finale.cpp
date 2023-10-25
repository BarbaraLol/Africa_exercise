#include "SparseMatrix.hpp"



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
