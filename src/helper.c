#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <sort.h>

// 辅助函数 生成随机数组
void generate_random_array(int *array, size_t num_elements) {
    for (size_t i = 0; i < num_elements; i++) {
        array[i] = rand() % 1000; // 生成0到999的随机数
    }
}

// 辅助函数 打印数组
void print_array(const int *array, size_t num_elements) {
    for (size_t i = 0; i < num_elements; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 辅助函数 测量排序算法的时间
double measure_sorting_time(void (*sort_func)(int *, size_t), int *array, size_t num_elements) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    sort_func(array, num_elements);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}
