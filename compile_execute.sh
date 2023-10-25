#!/bin/bash
# Compile the C++ files
g++ -std=c++17 -Wall -Wpedantic main.cpp sparsematrix.cpp -o sparse_matrix
# Run the resulting executable
./sparse_matrix
