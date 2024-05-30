//
// Created by 刘鑫 on 2024/5/25.
//

#ifndef MATRIX_DANCER_DANCER_H
#define MATRIX_DANCER_DANCER_H

#ifdef __cplusplus
extern "C" {
#endif

enum TOP_K {
    TOP_K_MIN = 0,
    TOP_K_MAX = 1,
};

typedef struct {
    int index;
    double value;
} IndexedDouble;

int compare_ints(const void *a, const void *b);

double mean_double(const double *matrix, int len);
double sum_double(const double *matrix, int start, int stop);

void covariance_double(const double *matrix, double *covariance, int rows, int cols);
double square_frobenius_norm_double(const double *matrix, int len);
double frobenius_norm_double(const double *matrix, int len);
void top_k_indexes(const double *input, int len, int *indexes, int k, enum TOP_K mode);
void dim_reduce(const double *input, int len, double *output, int reduce_to);

#ifdef __cplusplus
};
#endif

#endif //MATRIX_DANCER_DANCER_H
