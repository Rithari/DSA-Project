#ifndef EX1_MERGEBINSORTER_H
#define EX1_MERGEBINSORTER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compare(const void *a, const void *b, int(*cast)(const void*, const void*));
int cast_int(const void *a, const void*b);
int cast_float(const void *a, const void *b);
int cast_string(const void *a, const void *b);

void merge_binary_insertion_sort(void *base, size_t num, size_t size, size_t threshold, int (*compare)(const void *, const void *));
void merge_sort(void *base, size_t start, size_t end, size_t size, int (*compar)(const void *, const void*));
void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

#endif //EX1_MERGEBINSORTER_H
