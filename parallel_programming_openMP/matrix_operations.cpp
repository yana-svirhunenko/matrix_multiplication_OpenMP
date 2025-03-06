#include "matrix_operations.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;


UserInput getUserInput() {

    UserInput input;
    cout << "Введіть розміри першої матриці (a1 * b1): " << endl;
    cout << "a1 (Ряди): ";
    cin >> input.a1;
    cout << "b1 (Стовпці): ";
    cin >> input.b1;

    cout << "Введіть розміри другої матриці (a2 * b2): " << endl;
    cout << "a2 (Ряди): ";
    cin >> input.a2;
    cout << "b2 (Стовпці): ";
    cin >> input.b2;

    cout << "Введіть кількість потоків: ";
    cin >> input.num_threads;

    if (input.b1 != input.a2) {
        cout << "Неможливо помножити матриці з такими розмірами: \n";
        cout << "Перша матриця: (" << input.a1 << "*" << input.b1 << ") \n";
        cout << "Друга матриця: (" << input.a2 << "*" << input.b2 << ") \n" << endl;
        exit(1); 
    }

    char useOnesChoice;
    cout << "Використовувати матриці заповнені одиницями для тестування? [y/n]: ";
    cin >> useOnesChoice;

    if (useOnesChoice == 'y' || useOnesChoice == 'Y') {
        input.useOnesMatrix = true;
    } else if (useOnesChoice == 'n' || useOnesChoice == 'N') {
        input.useOnesMatrix = false;
    } else {
        cout << "Невірний символ. За замовчуванням встановлено 'n'." << endl;
        input.useOnesMatrix = false;
    }

    char displayChoice;
    cout << "Відобразити результат множення матриць? [y/n]: ";
    cin >> displayChoice;

    if (displayChoice == 'y' || displayChoice == 'Y') {
        input.display = true;
    } else if (displayChoice == 'n' || displayChoice == 'N') {
        input.display = false;
    } else {
        cout << "Невірний символ. За замовчуванням встановлено 'n'." << endl;
        input.display = false;
    }

    return input;
}


vector<vector<int>> generateRandomMatrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 9 + 1;
        }
    }
    return matrix;
}


vector<vector<int>> fillMatrix(int rows, int cols, bool useOnesMatrix) {
    if (useOnesMatrix) {
        return vector<vector<int>>(rows, vector<int>(cols, 1));
    } else {
        return generateRandomMatrix(rows, cols);
    }
}


vector<vector<int>> multiplyMatrices(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2, int num_threads) {
    int a1 = mat1.size();
    int b1 = mat1[0].size();
    int b2 = mat2[0].size();
    vector<vector<int>> result(a1, vector<int>(b2, 0));

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        int rows_per_thread = a1 / total_threads;
        int start_row = thread_id * rows_per_thread;
        int end_row = (thread_id == total_threads - 1) ? a1 : start_row + rows_per_thread;

        for (int i = start_row; i < end_row; ++i) {
            for (int j = 0; j < b2; ++j) {
                for (int k = 0; k < b1; ++k) {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
    }

    return result;
}


void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}
