#include "../headers/MergeBinSorter.h"

// Binary insertion sort function
// Sorts an array using binary search to find the correct position for insertion
// Params:
// - base: pointer to the first element of the array
// - nitems: number of elements in the array
// - size: size of each element in bytes
// - compar: comparison function to determine the order of the elements
void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *)) {
    void *temp = malloc(size);

    for (size_t i = 1; i < nitems; i++) {
        void *key = (char *)base + i * size;
        memcpy(temp, key, size);

        // Perform binary search to find the correct position for the key
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

        // Move elements to make space for the key at the correct position
        memmove((char *)base + (low + 1) * size, (char *)base + low * size, (i - low) * size);
        memcpy((char *)base + low * size, temp, size);
    }

    free(temp);
}

// Merge function for the merge sort algorithm
// Merges two sorted subarrays within the main array
// Params:
// - base: pointer to the first element of the array
// - temp: temporary buffer for storing elements during merging
// - left: index of the first element of the left subarray
// - middle: index of the last element of the left subarray
// - right: index of the last element of the right subarray
// - size: size of each element in bytes
// - z: threshold (k) for using binary insertion sort for merging
// - compar: comparison function to determine the order of the elements
void merge(void *base, void *temp, size_t left, size_t middle, size_t right, size_t size, size_t z, int (*compar)(const void *, const void *)) {
    // If the subarray size is less than or equal to z, use binary insertion sort
    if(right - left + 1 <= z) {
        binary_insertion_sort((char *)base + left * size, right - left + 1, size, compar);
        return;
    }

    size_t left_size = middle - left + 1;
    size_t right_size = right - middle;

    // Copy the left and right subarrays into the temporary buffer
    memcpy(temp, (char *)base + left * size, left_size * size);
    memcpy((char *)temp + left_size * size, (char *)base + (middle + 1) * size, right_size * size);

    // Merge the subarrays back into the main array
    size_t i = 0;
    size_t j = left_size;
    size_t k = left;

    while (i < left_size && j < left_size + right_size) {
        if (compar((char *)temp + i * size, (char *)temp + j * size) <= 0) {
            memcpy((char *)base + k * size, (char
            *)temp + i * size, size);
            i++;
        } else {
            memcpy((char *)base + k * size, (char *)temp + j * size, size);
            j++;
        }
        k++;
    }

    // Copy any remaining elements from the left and right subarrays
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

// Recursive merge sort function
// Params:
// - base: pointer to the first element of the array
// - temp: temporary buffer for storing elements during merging
// - left: index of the first element of the current subarray
// - right: index of the last element of the current subarray
// - size: size of each element in bytes
// - k: threshold for using binary insertion sort for merging
// - compar: comparison function to determine the order of the elements
void merge_sort_recursive(void *base, void *temp, size_t left, size_t right, size_t size, size_t k, int (*compar)(const void *, const void *)) {
    if (left >= right) {
        return;
    }

    size_t middle = left + (right - left) / 2;
    merge_sort_recursive(base, temp, left, middle, size, k, compar);
    merge_sort_recursive(base, temp, middle + 1, right, size, k, compar);

    // Merge the two subarrays only if they are out of order
    if (compar((char *)base + middle * size, (char *)base + (middle + 1) * size) > 0) {
        merge(base, temp, left, middle, right, size, k, compar);
    }
}

// Merge sort function
// Params:
// - base: pointer to the first element of the array
// - nitems: number of elements in the array
// - size: size of each element in bytes
// - k: threshold for using binary insertion sort for merging
// - compar: comparison function to determine the order of the elements
void merge_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void *)) {
    if (nitems <= 1) {
        return;
    }

    void *temp = malloc(nitems * size);
    merge_sort_recursive(base, temp, 0, nitems - 1, size, k, compar);
    free(temp);
}

// Merge sort combined with binary insertion sort
// Params:
// - base: pointer to the first element of the array
// - nitems: number of elements in the array
// - size: size of each element in bytes
// - k: threshold for using binary insertion sort for merging
// - compar: comparison function to determine the order of the elements
void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void *)) {
    if (k == 0) {
        merge_sort(base, nitems, size, k, compar);
        return;
    }

    if (nitems <= k) {
        binary_insertion_sort(base, nitems, size, compar);
        return;
    }

    void *temp = malloc(nitems * size);

    // First, sort chunks of size 'k' using binary_insertion_sort
    for (size_t i = 0; i < nitems; i += k) {
        size_t chunk_size = (i + k < nitems) ? k : (nitems - i);
        binary_insertion_sort((char *)base + i * size, chunk_size, size, compar);
    }

    // Then, merge the chunks together iteratively
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
                merge(base, temp, left, middle, right, size, k, compar);
            }
        }
    }

    free(temp);
}
