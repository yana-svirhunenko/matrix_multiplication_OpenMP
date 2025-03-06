#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <vector>
using namespace std;

struct UserInput {
    int a1, b1, a2, b2;  
    int num_threads;     
    bool display;        
    bool useOnesMatrix;
};

UserInput getUserInput();
vector<vector<int>> generateRandomMatrix(int rows, int cols);
vector<vector<int>> fillMatrix(int rows, int cols, bool useOnesMatrix);
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2, int num_threads);
void printMatrix(const vector<vector<int>>& matrix);

#endif
