//
// Created by 刘鑫 on 2024/5/25.
//

#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "dancer.h"
#include "cblas.h"
#include "utils.h"

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int compare_double(const void *a, const void *b) {
    double arg1 = *(const double *) a;
    double arg2 = *(const double *) b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int compare_double_reverse(const void *a, const void *b) {
    double arg1 = *(const double *) a;
    double arg2 = *(const double *) b;
    if (arg1 > arg2) return -1;
    if (arg1 < arg2) return 1;
    return 0;
}

int compare_indexed_value(const void *a, const void *b) {
    IndexedDouble arg1 = *(const IndexedDouble *) a;
    IndexedDouble arg2 = *(const IndexedDouble *) b;
    if (arg1.value < arg2.value) return -1;
    if (arg1.value > arg2.value) return 1;
    return 0;
}

int compare_indexed_value_reverse(const void *a, const void *b) {
    IndexedDouble arg1 = *(const IndexedDouble *) a;
    IndexedDouble arg2 = *(const IndexedDouble *) b;
    if (arg1.value > arg2.value) return -1;
    if (arg1.value < arg2.value) return 1;
    return 0;
}

int compare_indexed(const void *a, const void *b) {
    IndexedDouble arg1 = *(const IndexedDouble *) a;
    IndexedDouble arg2 = *(const IndexedDouble *) b;
    if (arg1.index < arg2.index) return -1;
    if (arg1.index > arg2.index) return 1;
    return 0;
}

int compare_indexed_reverse(const void *a, const void *b) {
    IndexedDouble arg1 = *(const IndexedDouble *) a;
    IndexedDouble arg2 = *(const IndexedDouble *) b;
    if (arg1.index > arg2.index) return -1;
    if (arg1.index < arg2.index) return 1;
    return 0;
}

double mean_double(const double *matrix, int len) {
    double result = 0.0;
    for (int i = 0; i < len; i++) {
        result += matrix[i];
    }
    result /= len;
    return result;
}

double sum_double(const double *matrix, int start, int stop) {
    double result = 0.0;
    for (int i = start; i < stop; i++) {
        result += matrix[i];
    }
    return result;
}

void covariance_double(const double *matrix, double *covariance, int rows, int cols) {
    // Calculate the outer product sum for the covariance matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = j; k < cols; ++k) {
                covariance[j * cols + k] += matrix[i * cols + j] * matrix[i * cols + k];
            }
        }
    }

    // Normalize the covariance matrix
    double norm_factor = 1.0 / (rows - 1);
    for (int i = 0; i < cols * cols; ++i) {
        covariance[i] *= norm_factor;
    }


}

double square_frobenius_norm_double(const double *matrix, int len) {
    double accumulate = 0.0;
    for (int i = 0; i < len; ++i) {
        accumulate += matrix[i] * matrix[i];
    }
    return accumulate;
}

double frobenius_norm_double(const double *matrix, int len) {
    double accumulate = square_frobenius_norm_double(matrix, len);
    return sqrt(accumulate);
}


int max_index_double(const double *input, int start, int to) {
    assert(start < to);
    double value = input[start];
    int result = start;
    for (int i = start + 1; i < to; i++) {
        if (input[i] > value) {
            result = i;
            value = input[i];
        }
    }
    return result;
}

int min_index_double(const double *input, int start, int to) {
    assert(start < to);
    double value = input[start];
    int result = start;
    for (int i = start + 1; i < to; i++) {
        if (input[i] < value) {
            result = i;
            value = input[i];
        }
    }
    return result;
}

void top_k_indexes(const double *input, int len, int *indexes, int k, enum TOP_K mode) {
    int (*cmp)(const void *, const void *);
    int (*cmp_double)(const void *, const void *);
    if (mode == TOP_K_MIN) {
        cmp = &compare_indexed_value;
        cmp_double = &compare_double;
    } else {
        cmp = &compare_indexed_value_reverse;
        cmp_double = &compare_double_reverse;
    }

    IndexedDouble *buffer = malloc(k * sizeof(IndexedDouble));
    for (int i = 0; i < k; i++) {
        buffer[i].index = i;
        buffer[i].value = input[i];
    }

    qsort(buffer, k, sizeof(IndexedDouble), cmp);

    int pos = k - 1;
    for (int i = k; i < len; i++) {
        int check = cmp_double(&input[i], &(buffer[pos].value));
        if (check == -1) {
            buffer[pos].index = i;
            buffer[pos].value = input[i];
            qsort(buffer, k, sizeof(IndexedDouble), cmp);
        }
    }

    qsort(buffer, k, sizeof(IndexedDouble), compare_indexed);
    for (int i = 0; i < k; i++) {
        indexes[i] = buffer[i].index;
    }

    free(buffer);
}

double norm_of_range(const double *input, int start, int stop) {
    double acc = sum_double(input, start, stop);
    double diff = stop - start;
    return acc / diff;
}

void dim_reduce(const double *input, int len, double *output, int reduce_to) {
    double rate = reduce_to * 1.0 / len;
    double *edges = malloc((len - 1) * sizeof(double));
    int breaks_k = reduce_to - 1;
    int *breaks = malloc(breaks_k * sizeof(int));
    for (int i = 0; i < len - 2; i++) {
        edges[i] = input[i] - input[i + 1];
    }

    top_k_indexes(edges, len - 1, breaks, breaks_k, TOP_K_MAX);
    int start = 0;
    for (int i = 0; i < breaks_k; i++) {
        int stop = breaks[i] + 1;
        double value = rate * norm_of_range(input, start, stop);
        output[i] = value;
        start = stop;
    }
    if (start < len - 1) {
        start = breaks[breaks_k];
        int stop = len - 1;
        double value = rate * norm_of_range(input, start, stop);
        output[breaks_k] = value;
    }
    free(breaks);
    free(edges);
}
