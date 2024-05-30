#include <iostream>
#include <cassert>
#include "dancer.h"
#include <random>

void print_matrix(double *matrix, int rows, int cols) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int idx = r * cols + c;
            std::cout << matrix[idx] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    const int len = 32;
    int rows = 2;
    int cols = 16;
    assert(rows * cols == len);

    auto *matrix = new double(len);
    std::cout << "test zero " << std::endl;

    memset(matrix, 0, len * sizeof(double));
    for (int idx = 0; idx < len; idx++) {
        assert(matrix[idx] == 0);
    }
    print_matrix(matrix, rows, cols);

    std::cout << "test mean " << std::endl;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 256);
    auto dice = std::bind(distribution, generator);
    for (int idx = 0; idx < len; idx++) {
        matrix[idx] = dice();
    }
    std::cout << "matrix: " << std::endl;
    print_matrix(matrix, rows, cols);
    double mean = mean_double(matrix, len);
    std::cout << "matrix mean: " << mean << std::endl;

    std::cout << "test l2 norm" << std::endl;
    double square_l2 = square_frobenius_norm_double(matrix, len);
    std::cout << "l2^2 = " << square_l2 << std::endl;

    delete matrix;
    return 0;
}
