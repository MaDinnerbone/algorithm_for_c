#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// #include <sort.h>

void generate_random_array(int *array, size_t num_elements);

void print_array(const int *array, size_t num_elements);

double measure_sorting_time(void (*sort_func)(int *, size_t), int *array, size_t num_elements);

#endif

// helper.h