#ifndef EX1_MERGEBINSORTER_H
#define EX1_MERGEBINSORTER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));
void merge(void *base, void *temp, size_t left, size_t middle, size_t right, size_t size, size_t z, int (*compar)(const void *, const void *));
void merge_sort_recursive(void *base, void *temp, size_t left, size_t right, size_t size, size_t z, int (*compar)(const void *, const void *));
void merge_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void *));
void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void*));
#endif //EX1_MERGEBINSORTER_H
