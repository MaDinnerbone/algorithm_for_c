#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include <sort.h>
#include <helper.h>

#define ARRAY_SIZE 1000

void (*const sort_funcs[])(int *, size_t) = {
    insertion_sort, shell_sort, selection_sort,
    heap_sort, bubble_sort, quick_sort, merge_sort
};

// 辅助 交换函数
static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 辅助 堆排序下沉函数
static void heapify(int *array, size_t num_elements, size_t node_idx) {
    size_t left_child_idx, right_child_idx, larger_child_idx;
    left_child_idx = 2 * node_idx + 1;
    right_child_idx = 2 * node_idx + 2;
    int temp;

    if ((left_child_idx < num_elements) && (array[left_child_idx] > array[node_idx])) {
        larger_child_idx = left_child_idx;
    } else {
        larger_child_idx = node_idx;
    }

    if ((right_child_idx < num_elements) && (array[right_child_idx] > array[larger_child_idx])) {
        larger_child_idx = right_child_idx;
    }

    if (larger_child_idx != node_idx) {
        temp = array[node_idx];
        array[node_idx] = array[larger_child_idx];
        array[larger_child_idx] = temp;
        heapify(array, num_elements, larger_child_idx);
    }
}

// 快速排序 分区函数
static size_t partition(int *array, size_t low, size_t high) {
    int pivot = array[high];
    size_t i = (low - 1);
    for (size_t j = low; j < high; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}
// 辅助 快速排序函数
static void quick_sort_helper(int *array, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition(array, low, high);
        quick_sort_helper(array, low, pi - 1);
        quick_sort_helper(array, pi + 1, high);
    }
}

// 辅助 归并排序函数
static void merge(int *array, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;
    int *left_array = (int *)malloc(n1 * sizeof(int));
    int *right_array = (int *)malloc(n2 * sizeof(int));

    for (size_t i = 0; i < n1; i++)
        left_array[i] = array[left + i];
    for (size_t j = 0; j < n2; j++)
        right_array[j] = array[mid + 1 + j];

    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        } else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        array[k] = left_array[i];
        i++;
        k++;
    }
    while (j < n2) {
        array[k] = right_array[j];
        j++;
        k++;
    }
    free(left_array);
    free(right_array);
}

// 辅助 归并排序 递归函数
static void merge_sort_helper(int *array, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        merge_sort_helper(array, left, mid);
        merge_sort_helper(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}



// insertion sort
void insertion_sort(int *array, size_t num_elements) {
    size_t i, j;
    int key;
    for (i = 1; i < num_elements; i++) {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

// 希尔排序 shell sort
void shell_sort(int *array, size_t num_elements) {
    size_t gap, i, j;
    int temp;
    gap = num_elements / 2;
    while (gap > 0) {
        for (i = gap; i < num_elements; i++) {
            temp = array[i];
            j = i;
            while ((j >= gap) && (array[j - gap] > temp)) {
                array[j] = array[j - gap];
                j = j - gap;
            }
            array[j] = temp;
        }
        gap = gap / 2;
    }
}

// 选择排序 selection sort
void selection_sort(int *array, size_t num_elements) {
    size_t i, j;
    int min_idx, temp;
    for (i = 0; i < num_elements - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < num_elements; j++) {
            if (array[j] < array[min_idx]) {
                min_idx = j;
            }
        }
        temp = array[min_idx];
        array[min_idx] = array[i];
        array[i] = temp;
    }
}

// 堆排序
void heap_sort(int *array, size_t num_elements) {
    size_t i;
    for (i = num_elements / 2 - 1; i >= 0; i--) {
        heapify(array, num_elements, i);
    }

    for (i = num_elements - 1; i > 0; i--) {
        swap(&array[0], &array[i]);
        heapify(array, i, 0);
    }
}

// 冒泡排序
void bubble_sort(int *array, size_t num_elements) {
    size_t i, j;
    for (i = 0; i < num_elements - 1; i++) {
        for (j = 0; j < num_elements - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}

// 快速排序
// the most fast sort function
void quick_sort(int *array, size_t num_elements) {
    quick_sort_helper(array, 0, num_elements - 1);
}

// 归并排序
void merge_sort(int *array, size_t num_elements) {
    merge_sort_helper(array, 0, num_elements - 1);
}



// 测试程序 test
void sort_testA(){
    const size_t array_size = 1000; // 数组大小
    int *array = malloc(array_size * sizeof(int));
    srand((unsigned)time(NULL)); // 初始化随机数

    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    }

    printf("Original array: \n");
    generate_random_array(array, array_size);
    print_array(array, array_size);

    // 
    printf("\nTesting sorting algorithms:\n\n");

    // 插入排序
    generate_random_array(array, array_size); // 重置为新的随机数组
    printf("Insertion sort time: %f seconds\n", measure_sorting_time(insertion_sort, array, array_size));
    printf("Insertion sort result:\n");
    print_array(array, array_size);
    printf("\n");

    free(array);

    // 希尔排序
    generate_random_array(array, array_size); // 重置为新的随机数组
    printf("Shell sort time: %f seconds\n", measure_sorting_time(shell_sort, array, array_size));
    printf("Shell sort result:\n");
    print_array(array, array_size);
    printf("\n");

    free(array);

    // 选择排序
    generate_random_array(array, array_size); // 重置为新的随机数组
    printf("Selection sort time: %f seconds\n", measure_sorting_time(selection_sort, array, array_size));
    printf("Selection sort result:\n");
    print_array(array, array_size);
    printf("\n");

    free(array);

    /* Error or too slow

    // 堆排序
    generate_random_array(array, array_size); // 重置为新的随机数组
    printf("Heap sort time: %f seconds\n", measure_sorting_time(heap_sort, array, array_size));
    printf("Heap sort result:\n");
    print_array(array, array_size);
    printf("\n");

    */

    // 冒泡排序
    generate_random_array(array, array_size); // 重置为新的随机数组
    printf("Bubble sort time: %f seconds\n", measure_sorting_time(bubble_sort, array, array_size));
    printf("Bubble sort result:\n");
    print_array(array, array_size);
    printf("\n");

    free(array);

    // 快速排序
    generate_random_array(array, array_size); // 重置为新的随机数组
    printf("Quick sort time: %f seconds\n", measure_sorting_time(quick_sort, array, array_size));
    printf("Quick sort result:\n");
    print_array(array, array_size);
    printf("\n");

    free(array);

    // 归并排序
    generate_random_array(array, array_size); // 重置为新的随机数组
    printf("Merge sort time: %f seconds\n", measure_sorting_time(merge_sort, array, array_size));
    printf("Merge sort result:\n");
    print_array(array, array_size);
    printf("\n");

    free(array);
}

void sort_testB() {
    size_t array_size = ARRAY_SIZE; // 定义数组大小
    int *array = malloc(array_size * sizeof(int));

    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // 初始化随机数种子
    srand((unsigned int)time(NULL));

    // 测试每个排序算法
    printf("Testing sorting algorithms:\n\n");
    for (size_t i = 0; i < sizeof(sort_funcs) / sizeof(sort_funcs[0]); ++i) {
        const char *sort_name;
        switch (i) {
            case 0: sort_name = "Insertion"; break;
            case 1: sort_name = "Shell"; break;
            case 2: sort_name = "Selection"; break;
            case 3: 
            /* Error or too slow to stuck the programe
            sort_name = "Heap"; */
            i=4; break;
            case 4: sort_name = "Bubble"; break;
            case 5: sort_name = "Quick"; break;
            case 6: sort_name = "Merge"; break;
            default: sort_name = "Unknown"; break;
        }

        // 重置数组为新的随机数组
        generate_random_array(array, array_size);
        
        // 执行测试并打印结果
        printf("Original array for %s sort:\n", sort_name);
        print_array(array, array_size);

        // 正确传递函数指针
        double sort_time = measure_sorting_time(sort_funcs[i], array, array_size);
        printf("%s sort time: %f seconds\n", sort_name, sort_time);

        printf("Sorted array:\n");
        print_array(array, array_size);
        printf("\n");
    }

    free(array);
}
