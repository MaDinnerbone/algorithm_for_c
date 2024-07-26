#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// void swap(int *array, int index_a, int index_b);

void insertion_sort(int *array, size_t num_elements);

void shell_sort(int *array, size_t num_elements);

void selection_sort(int *array, size_t num_elements);

// static void heapify(int *array, size_t num_elements, size_t node_idx);
void heap_sortA(int *array, size_t num_elements);
void heap_sortB(int *array, size_t num_elements);

void bubble_sort(int *array, size_t num_elements);

// static void quick_sort_helper(int *array, size_t low, size_t high);
// static size_t partition(int *array, size_t low, size_t high);
void quick_sort(int *array, size_t num_elements);

// static void merge_sort_helper(int *array, size_t left, size_t right);
void merge_sort(int *array, size_t num_elements);

void sort_testA();
void sort_testB();

#endif 
// SORT_H