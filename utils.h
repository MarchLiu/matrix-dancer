//
// Created by 刘鑫 on 2024/5/29.
//

#ifndef MATRIX_DANCER_UTILS_H
#define MATRIX_DANCER_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

void print_c_matrix(const double *matrix, int rows, int cols);

void rand_c_matrix(double *matrix, int len);

#ifdef __cplusplus
};
#endif

#endif //MATRIX_DANCER_UTILS_H
