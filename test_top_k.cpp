//
// Created by 刘鑫 on 2024/5/29.
//

#include "utils.h"
#include "dancer.h"
#include <cassert>
#include <iostream>
#include <random>

// extern "C" void print_c_matrix(double *, int, int);

int main(int argc, char **argv) {
    const int len = 32;
    const int rows = 2;
    const int cols = 16;
    const int k = 8;
    assert(rows * cols == len);

    auto *matrix = new double(len);
    auto *top = new double(k);
    auto *indexes = (int *) malloc(k * sizeof(int));

    std::cout << "init matrix " << rows << "*" << cols << std::endl;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0, 256);
    auto dice = std::bind(distribution, generator);
    for (int idx = 0; idx < len; idx++) {
        matrix[idx] = dice();
    }

    print_c_matrix(matrix, rows, cols);

    top_k_indexes(matrix, len, indexes, k, TOP_K_MAX);

    for (int i = 0; i < k; i++) {
        top[i] = matrix[indexes[i]];
    }
    std::cout << "top max " << k << " items is " << std::endl;
    print_c_matrix(top, 1, 8);
    //clean
    delete matrix;
    delete top;
    free(indexes);

    return 0;
}