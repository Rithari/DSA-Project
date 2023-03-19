#ifndef EX1_MERGEBINSORTER_H
#define EX1_MERGEBINSORTER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));
void merge(void *src, void *dst, size_t mid, size_t nitems, size_t size, int (*compar)(const void *, const void *));
void merge_sort(void *base, void *buffer, size_t nitems, size_t size, int (*compar)(const void *, const void *));
void merge_binary_insertion_sort(void *base, size_t num, size_t size, size_t k, int (*compare)(const void *, const void *));

#endif //EX1_MERGEBINSORTER_H
