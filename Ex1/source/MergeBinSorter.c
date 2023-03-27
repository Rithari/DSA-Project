#include "../headers/MergeBinSorter.h"

void binary_insertion_sort(void *base, size_t nitems, size_t size, size_t *comparison_count, size_t *data_move_count, int (*compar)(const void *, const void *, size_t *)) {
    void *temp = malloc(size);

    for (size_t i = 1; i < nitems; i++) {
        void *key = (char *)base + i * size;
        memcpy(temp, key, size);
        (*data_move_count)++;

        size_t low = 0;
        size_t high = i;

        while (low < high) {
            size_t mid = (low + high) / 2;
            (*comparison_count)++;
            if (compar(temp, (char *)base + mid * size, comparison_count) < 0) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        memmove((char *)base + (low + 1) * size, (char *)base + low * size, (i - low) * size);
        (*data_move_count) += (i - low);
        memcpy((char *)base + low * size, temp, size);
        (*data_move_count)++;
    }

    free(temp);
}

void merge(void *base, void *temp, size_t left, size_t middle, size_t right, size_t size, size_t *comparison_count, size_t *data_move_count, int (*compar)(const void *, const void *, size_t *)) {
    if (middle < right && compar((char *)base + middle * size, (char *)base + (middle + 1) * size, comparison_count) <= 0) {
        return;
    }
    size_t left_size = middle - left + 1;
    size_t right_size = right - middle;

    memcpy(temp, (char *)base + left * size, left_size * size);
    (*data_move_count) += left_size;
    memcpy((char *)temp + left_size * size, (char *)base + (middle + 1) * size, right_size * size);
    (*data_move_count) += right_size;

    size_t i = 0;
    size_t j = left_size;
    size_t k = left;

    while (i < left_size && j < left_size + right_size) {
        if (compar((char *)temp + i * size, (char *)temp + j * size, comparison_count) <= 0) {
            memcpy((char *)base + k * size, (char *)temp + i * size, size);
            (*data_move_count)++;
            i++;
        } else {
            memcpy((char *)base + k * size, (char *)temp + j * size, size);
            (*data_move_count)++;
            j++;
        }
        k++;
    }

    while (i < left_size) {
        memcpy((char *)base + k * size, (char *)temp + i * size, size);
        (*data_move_count)++;
        i++;
        k++;
    }

    while (j < left_size + right_size) {
        memcpy((char *)base + k * size, (char *)temp + j * size, size);
        (*data_move_count)++;
        j++;
        k++;
    }
}

void merge_sort_recursive(void *base, void *temp, size_t left, size_t right, size_t size, size_t *comparison_count, size_t *data_move_count, int (*compar)(const void *, const void *, size_t *)) {
    if (left >= right) {
        return;
    }

    size_t middle = left + (right - left) / 2;
    merge_sort_recursive(base, temp, left, middle, size, comparison_count, data_move_count, compar);
    merge_sort_recursive(base, temp, middle + 1, right, size, comparison_count, data_move_count, compar);
    merge(base, temp, left, middle, right, size, comparison_count, data_move_count, compar);
}

void merge_sort(void *base, size_t nitems, size_t size, size_t *comparison_count, size_t *data_move_count, int (*compar)(const void *, const void *, size_t *)) {
    if (nitems <= 1) {
        return;
    }

    void *temp = malloc(nitems * size);
    merge_sort_recursive(base, temp, 0, nitems - 1, size, comparison_count, data_move_count, compar);
    free(temp);
}

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, size_t *comparison_count, size_t *data_move_count, int (*compar)(const void *, const void *, size_t *)) {
    if (k == 0) {
        merge_sort(base, nitems, size, comparison_count, data_move_count, compar);
        return;
    }

    if (nitems <= k) {
        binary_insertion_sort(base, nitems, size, comparison_count, data_move_count, compar);
        return;
    }

    void *temp = malloc(nitems * size);

    size_t run_start = 0;
    size_t run_end;

    while (run_start < nitems) {
        run_end = run_start + 1;
        while (run_end < nitems && compar((char *)base + (run_end - 1) * size, (char *)base + run_end * size, comparison_count) <= 0) {
            run_end++;
        }

        size_t run_size = run_end - run_start;

        if (run_size <= k) {
            binary_insertion_sort((char *)base + run_start * size, run_size, size, comparison_count, data_move_count, compar);
        } else {
            merge_sort((char *)base + run_start * size, run_size, size, comparison_count, data_move_count, compar);
        }

        run_start = run_end;
    }

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
                merge(base, temp, left, middle, right, size, comparison_count, data_move_count, compar);
            }
        }
    }

    free(temp);
}
