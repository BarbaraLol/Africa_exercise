#include "SparseMatrix.hpp"
#include <string>
#include <sstream>


int main() {



while (true) {
std::string choose;
std::cout << "Choose the way you want to implement your SparseMatrix. Type COO or CSR: ";
std::cin >> choose;
std::cin.ignore();
if (choose == "COO") {

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

    std::cout << "Insert the indexes of the rows of nonzero elements separated by spaces: ";
    std::string input_row;
    std::getline(std::cin, input_row);

    std::vector<int> input_rows;
    std::istringstream issrow(input_row);
    int numrow;
    while (issrow >> numrow) {
        input_rows.push_back(numrow);
    };

    SparseMatrixCOO M_COO(input_rows, input_values, input_columns);

    M_COO.PrintMatrix();

    break;
}

else if (choose == "CSR") {
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

    SparseMatrixCSR M_CSR(input_rows, input_values, input_columns);

    M_CSR.PrintMatrix();

    break;

}

else {
    std::cout<< "You have to choose between CSR and COO."<< "\n";
}

};
    return 0;
}
