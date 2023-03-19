#include "../headers/MergeBinSorter.h"

void insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *)) {
    char *buffer = (char *)malloc(size);
    char *array = (char *)base;

    for (size_t i = 1; i < nitems; i++) {
        memcpy(buffer, array + i * size, size);
        size_t j = i;
        while (j > 0 && compar(array + (j - 1) * size, buffer) > 0) {
            memcpy(array + j * size, array + (j - 1) * size, size);
            j--;
        }
        memcpy(array + j * size, buffer, size);
    }

    free(buffer);
}

void merge(void *src, void *dst, size_t mid, size_t nitems, size_t size, int (*compar)(const void *, const void *)) {
    char *left_ptr = (char *)src;
    char *right_ptr = (char *)src + mid * size;
    char *dst_ptr = (char *)dst;

    size_t left_index = 0, right_index = 0;

    while (left_index < mid && right_index < nitems - mid) {
        if (compar(left_ptr + left_index * size, right_ptr + right_index * size) <= 0) {
            memcpy(dst_ptr, left_ptr + left_index * size, size);
            left_index++;
        } else {
            memcpy(dst_ptr, right_ptr + right_index * size, size);
            right_index++;
        }
        dst_ptr += size;
    }

    memcpy(dst_ptr, left_ptr + left_index * size, (mid - left_index) * size);
    memcpy(dst_ptr, right_ptr + right_index * size, (nitems - mid - right_index) * size);
}

void merge_sort(void *base, void *buffer, size_t nitems, size_t size, int (*compar)(const void *, const void *)) {
    if (nitems <= 1) {
        return;
    }

    size_t mid = nitems / 2;

    merge_sort(buffer, base, mid, size, compar);
    merge_sort(buffer + mid * size, base + mid * size, nitems - mid, size, compar);

    merge(buffer, base, mid, nitems, size, compar);
}

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void *)) {
    if (nitems <= k) {
        insertion_sort(base, nitems, size, compar);
        return;
    }

    void *buffer = malloc(nitems * size);
    memcpy(buffer, base, nitems * size);

    merge_sort(base, buffer, nitems, size, compar);

    free(buffer);
}

