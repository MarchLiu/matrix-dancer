//
// Created by 刘鑫 on 2024/5/28.
//

#include <stdio.h>
#include <stdlib.h>
#include "dancer.h"

int main(int argc, char** argv) {
    int array[] = {64, 34, 25, 12, 22, 11, 90};
    size_t n = sizeof(array) / sizeof(array[0]);

    // 使用 qsort 对数组进行排序
    qsort(array, n, sizeof(int), compare_ints);

    // 输出排序后的数组
    for (size_t i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
