#include <sstream>
#include "SparseMatrix.hpp"


int main() {



while (true) {
std::string choose;
std::cout << "Choose the way you want to implement your SparseMatrix. Type COO or CSR: ";
std::cin >> choose;
std::cin.ignore();
if (choose == "COO" || choose == "coo") {

    // Enter the values
    std::cout
        << "Enter a set of numbers separated by spaces: ";
    std::string input;
    std::getline(std::cin, input);

    std::vector<double> input_values;
    std::istringstream iss(input);
    double num;
    while (iss >> num){
      input_values.push_back(num);
    };

    
    // Enter the columns

    std::cout << "Insert the indexes of the columns nonzero elements separated by spaces: ";
    std::string input_col;
    std::getline(std::cin, input_col);

    std::vector<int> input_columns;
    std::istringstream isscol(input_col);
    int numcol;
    while (isscol >> numcol) {
        input_columns.push_back(numcol);
    };

    // Enter the rows

    std::cout << "Insert the indexes of the rows of nonzero elements separated by spaces: ";
    std::string input_row;
    std::getline(std::cin, input_row);

    std::vector<int> input_rows;
    std::istringstream issrow(input_row);
    int numrow;
    while (issrow >> numrow) {
        input_rows.push_back(numrow);
    };

    SparseMatrixCOO* M_COO = new SparseMatrixCOO(input_rows, input_values, input_columns);

    M_COO->PrintMatrix();

    // Number of columns
    std::cout << "The number of columns is " << M_COO->n_col()<< std::endl;

    // Number of rows
    std::cout << "The number of rows is " <<M_COO->n_row()<< std::endl;

    // Read operator
    const SparseMatrixCOO* MCOO_const = M_COO;
    std::cout << "The element in (0,2) is " << (*MCOO_const)(0,2) << std::endl;

    // Write operator 
    (*M_COO)(0,2) = 3;
    M_COO->PrintMatrix();
    std::cout<< "\n";

    // Matrix-vector product
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y_COO = (*M_COO)*x;
    std::cout << "\n";

    delete M_COO;

    // Switching from COO to CSR
    SparseMatrixCSR* new_csr = NewCSR_SparseMatrix(input_rows, input_values, input_columns);
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

    break;
}

else if (choose == "CSR" || choose == "csr") {
    // Enter the values
    std::cout
        << "Enter a set of numbers separated by spaces: ";
    std::string input;
    std::getline(std::cin, input);

    std::vector<double> input_values;
    std::istringstream iss(input);
    double num;
    while (iss >> num) {
      input_values.push_back(num);
    };


    // Enter the columns

    std::cout << "Insert the indexes of the columns nonzero elements separated by spaces: ";
    std::string input_col;
    std::getline(std::cin, input_col);

    std::vector<int> input_columns;
    std::istringstream isscol(input_col);
    int numcol;
    while (isscol >> numcol) {
        input_columns.push_back(numcol);
    };

    // Enter the rows

    std::cout << "Insert the cumulative numbers of nonzero elements in every row: ";
    std::string input_row;
    std::getline(std::cin, input_row);

    std::vector<int> input_rows;
    std::istringstream issrow(input_row);
    int numrow;
    while (issrow >> numrow) {
        input_rows.push_back(numrow);
    };

    SparseMatrixCSR* M_CSR = new SparseMatrixCSR(input_rows, input_values, input_columns);

    M_CSR->PrintMatrix();

    // Number of columns
    std::cout << "The number of columns is " <<M_CSR->n_col()<< std::endl;

    // Number of rows
    std::cout << "The number of rows is " << M_CSR->n_row()<< std::endl;

    // Read operator
    const SparseMatrixCSR* MCSR_const = M_CSR;
    std::cout << "The element in (0,2) is " << (*MCSR_const)(0,2) << std::endl;

    // Write operator
    (*M_CSR)(0,2) = 3;
    M_CSR->PrintMatrix();
    std::cout << "\n";

    // Matrix-vector product
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y_CSR = (*M_CSR)*x;

    delete M_CSR;

    SparseMatrixCOO* new_coo = NewCOO_SparseMatrix(input_rows, input_values, input_columns);

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


    break;
}

else {
    std::cout<< "You have to choose between CSR and COO."<< "\n";
}

};
    return 0;
}
