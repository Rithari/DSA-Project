#ifndef EX1_MERGEBINSORTER_H
#define EX1_MERGEBINSORTER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Binary insertion sort function declaration
void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));

// Merge function declaration, used in merge sort algorithm
void merge(void *base, size_t split, size_t nitems, size_t size, int (*compar)(const void *, const void*));
// Merge sort function declaration, used to implement the merge sort algorithm
void merge_sort(void *base, void *temp, size_t left, size_t right, size_t size, size_t z, int (*compar)(const void *, const void *));

// Merge-binary insertion sort function declaration, combining merge sort and binary insertion sort
void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void*));

#endif //EX1_MERGEBINSORTER_H
