#include <iostream>
#include <chrono>
#include <iomanip>
#include <omp.h>  
#include "matrix_operations.h"

using namespace std;
using namespace std::chrono;


int main() {

    srand(time(0));
    UserInput input = getUserInput();
    vector<vector<int>> matrix1 = fillMatrix(input.a1, input.b1, input.useOnesMatrix);
    vector<vector<int>> matrix2 = fillMatrix(input.a2, input.b2, input.useOnesMatrix);

    if (input.display) {
        cout << "\nМатриця 1:" << endl;
        printMatrix(matrix1);

        cout << "\nМатриця 2:" << endl;
        printMatrix(matrix2);
    }

    auto start = high_resolution_clock::now();
    vector<vector<int>> result = multiplyMatrices(matrix1, matrix2, input.num_threads);

    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;

    if (input.display) {
        cout << "\nОтримана матриця після множення:" << endl;
        printMatrix(result);
    }

    cout << fixed << setprecision(3);
    cout << "\nЧас, витрачений на множення: " << elapsed.count() << " секунд" << endl;

    return 0;
}
