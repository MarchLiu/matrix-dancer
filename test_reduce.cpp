//
// Created by 刘鑫 on 2024/5/29.
//

#include <cassert>
#include "utils.h"
#include "dancer.h"
#include <iostream>

int main(int argc, char **argv) {
    const int len = 32;
    const int rows = 2;
    const int cols = 16;
    const int k = 8;
    assert(rows * cols == len);

    double *matrix = (double *)malloc(len * sizeof(double));
    double *reduced = (double *) malloc(k*sizeof(double ));

    rand_c_matrix(matrix, len);
    dim_reduce(matrix, len, reduced, k);

    std::cout<< "vector dim " << len << std::endl;
    print_c_matrix(matrix, 1, len);

    std::cout<< "reduce to  " << k << std::endl;
    print_c_matrix(reduced, 1, k);

    free(reduced);
    free(matrix);
    return 0;
}