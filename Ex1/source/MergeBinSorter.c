#include "../headers/MergeBinSorter.h"

void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *)) {
    void *temp = malloc(size);

    for (size_t i = 1; i < nitems; i++) {
        void *key = (char *)base + i * size;
        memcpy(temp, key, size);

        size_t low = 0;
        size_t high = i;

        while (low < high) {
            size_t mid = (low + high) / 2;
            if (compar(temp, (char *)base + mid * size) < 0) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        memmove((char *)base + (low + 1) * size, (char *)base + low * size, (i - low) * size);
        memcpy((char *)base + low * size, temp, size);
    }

    free(temp);
}



void merge(void *base, void *temp, size_t left, size_t middle, size_t right, size_t size, int (*compar)(const void *, const void *)) {
    size_t left_size = middle - left + 1;
    size_t right_size = right - middle;

    memcpy(temp, (char *)base + left * size, left_size * size);
    memcpy((char *)temp + left_size * size, (char *)base + (middle + 1) * size, right_size * size);

    size_t i = 0;
    size_t j = left_size;
    size_t k = left;

    while (i < left_size && j < left_size + right_size) {
        if (compar((char *)temp + i * size, (char *)temp + j * size) <= 0) {
            memcpy((char *)base + k * size, (char *)temp + i * size, size);
            i++;
        } else {
            memcpy((char *)base + k * size, (char *)temp + j * size, size);
            j++;
        }
        k++;
    }

    while (i < left_size) {
        memcpy((char *)base + k * size, (char *)temp + i * size, size);
        i++;
        k++;
    }

    while (j < left_size + right_size) {
        memcpy((char *)base + k * size, (char *)temp + j * size, size);
        j++;
        k++;
    }
}

void merge_sort_recursive(void *base, void *temp, size_t left, size_t right, size_t size, int (*compar)(const void *, const void *)) {
    if (left >= right) {
        return;
    }

    size_t middle = left + (right - left) / 2;
    merge_sort_recursive(base, temp, left, middle, size, compar);
    merge_sort_recursive(base, temp, middle + 1, right, size, compar);
    merge(base, temp, left, middle, right, size, compar);
}


void merge_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *)) {
    if (nitems <= 1) {
        return;
    }

    void *temp = malloc(nitems * size);
    merge_sort_recursive(base, temp, 0, nitems - 1, size, compar);
    free(temp);
}


void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void *)) {
    if (k == 0) {
        merge_sort(base, nitems, size, compar);
        return;
    }

    if (nitems <= k) {
        binary_insertion_sort(base, nitems, size, compar);
        return;
    }

    // Sort subarrays
    for (size_t i = 0; i < nitems; i += k) {
        size_t subarray_size = (i + k > nitems) ? (nitems - i) : k;

        if (subarray_size <= k) {
            binary_insertion_sort((char *)base + i * size, subarray_size, size, compar);
        } else {
            merge_sort((char *)base + i * size, subarray_size, size, compar);
        }
    }

    void *temp = malloc(nitems * size);

    for (size_t width = k; width < nitems; width *= 2) {
        for (size_t i = 0; i < nitems; i += 2 * width) {
            size_t left = i;
            size_t middle = i + width - 1;
            size_t right = i + 2 * width - 1;

            if (middle >= nitems) {
                middle = nitems - 1;
            }

            if (right >= nitems) {
                right = nitems - 1;
            }

            if (left < nitems && middle < nitems && right < nitems) {
                merge(base, temp, left, middle, right, size, compar);
            }
        }
    }

    free(temp);
}
