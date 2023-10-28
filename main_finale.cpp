#include "SparseMatrix.hpp"

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

    // Print function
    M_COO->PrintMatrix();
    std::cout<<"\n";
    M_CSR->PrintMatrix();

    // Number of columns
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
    (*M_CSR)(0,2) = 3;
    M_CSR->PrintMatrix();

    // Matrix-vector product

    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};

    std::vector<double> y_COO = (*M_COO)*x;

    std::cout << "\n";
    std::vector<double> y_CSR = (*M_CSR)*x;

    delete M_COO;
    delete M_CSR;

    SparseMatrixCSR* new_csr = NewCSR_SparseMatrix(input_rowsCOO, input_valuesCOO, input_columnsCOO);
    SparseMatrixCOO* new_coo = NewCOO_SparseMatrix(input_rowsCSR, input_valuesCSR, input_columnsCSR);

    // new_csr
    std::vector<double> y1_CSR = (*new_csr)*x;
    (*new_csr)(0,2)=90;
    new_csr->PrintMatrix();
    std::cout << "The number of columns is " << new_csr->n_col()<< std::endl;
    std::cout << "The number of rows is " << new_csr->n_row()<< std::endl;
    const SparseMatrixCSR* csr_const = new_csr;
    // Read
    (*new_csr)(0,2);
    std::cout << "The element in (0,2) is " << (*new_csr)(0,2) << std::endl;

    // new_coo
    std::vector<double> y1_COO = (*new_coo)*x;
    (*new_coo)(0,2)=90; //write
    new_coo->PrintMatrix();
    std::cout << "The number of columns is " << new_coo->n_col()<< std::endl;
    std::cout << "The number of rows is " << new_coo->n_row()<< std::endl;
    const SparseMatrixCOO* coo_const = new_coo;
    // Read
    (*new_coo)(0,2);
    std::cout << "The element in (0,2) is " << (*new_coo)(0,2) << std::endl;
    
    //delete new_csr;
    //delete new_coo;

    return 0;
}
