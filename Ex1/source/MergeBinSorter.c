#include "../headers/MergeBinSorter.h"


int binary_search(void *elem, void *base, int nitems, int size, int (*compar)(const void *, const void*)) {
    int low = 0;
    int high = nitems;

    while (low < high) {
        size_t mid = low + (high - low) / 2;
        if (compar((char *)base + mid * size, elem) < 0) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}

// Binary insertion sort function
// Sorts an array using binary search to find the correct position for insertion
// Params:
// - base: pointer to the first element of the array
// - nitems: number of elements in the array
// - size: size of each element in bytes
// - compar: comparison function to determine the order of the elements
void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)) {

    void *tmp = malloc(size);
    for (size_t i = 1; i < nitems; ++i) {
        size_t pos = binary_search((char *)base + i * size, base, i, size, compar);
        memcpy(tmp, (char *)base + i * size, size);
        memmove((char *)base + (pos + 1) * size, (char *)base + pos * size, (i - pos) * size);
        memcpy((char *)base + pos * size, tmp, size);
    }
    free(tmp);
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
void merge(void *base, size_t split, size_t nitems, size_t size, int (*compar)(const void *, const void*)) {
    void* copy = malloc(nitems*size);
    memcpy(copy, base, nitems*size);
    char* L = (char*)copy;
    char* Lend = L + split*size;
    char* R = Lend;
    char* Rend = L + nitems*size;

    char* p = (char*)base;
    for (int i=0; i<nitems; ++i) {
        if (L == Lend) {
            memcpy(p, R, size);
            R += size;
        } else if (R == Rend) {
            memcpy(p, L, size);
            L += size;
        } else if (compar(L, R) < 0) {
            memcpy(p, L, size);
            L += size;
        } else {
            memcpy(p, R, size);
            R += size;
        }
        p += size;
    }
    free(copy);
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
void merge_sort(void *base, void *temp, size_t left, size_t right, size_t size, size_t z, int (*compar)(const void *, const void *)) {
    if (left >= right) {
        return;
    }

    size_t middle = left + (right - left) / 2;
    merge_sort(base, temp, left, middle, size, z, compar);
    merge_sort(base, temp, middle + 1, right, size, z, compar);

    // Merge the two subarrays only if they are out of order
    void *middle_element = (char *)base + middle * size;
    void *middle_plus_one_element = (char *)base + (middle + 1) * size;
    if (compar(middle_element, middle_plus_one_element) > 0) {
        size_t split = middle - left + 1;
        size_t nitems = right - left + 1;
        merge(base, split, nitems, size, compar);
    }
}

// Merge sort combined with binary insertion sort
// Params:
// - base: pointer to the first element of the array
// - nitems: number of elements in the array
// - size: size of each element in bytes
// - k: threshold for using binary insertion sort for merging
// - compar: comparison function to determine the order of the elements
void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void*)) {
    if (nitems <= 1) {
        return;
    }

    if (nitems <= k) {
        binary_insertion_sort(base, nitems, size, compar);
        return;
    }

    size_t split = nitems / 2;
    merge_binary_insertion_sort(base, split, size, k, compar);
    merge_binary_insertion_sort(((char *)base) + split * size, nitems - split, size, k, compar);
    merge(base, split, nitems, size, compar);
}
