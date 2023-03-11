#include "../headers/MergeBinSorter.h"

// Comparison function that takes a function pointer to a cast function
int compare(const void *a, const void *b, int (*cast)(const void*, const void*)) {
    return cast(a, b);
}

// Cast function for integers
int cast_int(const void *a, const void *b) {
    const int *num1 = (const int*) a;
    const int *num2 = (const int*) b;
    if (*num1 < *num2) {
        return -1;
    }
    else if (*num1 > *num2) {
        return 1;
    }
    else {
        return 0;
    }
}

// Cast function for floats
int cast_float(const void *a, const void *b) {
    const float *num1 = (const float*) a;
    const float *num2 = (const float*) b;
    if (*num1 < *num2) {
        return -1;
    }
    else if (*num1 > *num2) {
        return 1;
    }
    else {
        return 0;
    }
}

// Cast function for strings
int cast_string(const void *a, const void *b) {
    const char **str1 = (const char**) a;
    const char **str2 = (const char**) b;
    return strcmp(*str1, *str2);
}

void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)) {
    char *arr = (char*) base;
    char temp[size];
    int i, j;
    for (i = 1; i < nitems; i++) {
        memcpy(temp, &arr[i * size], size);
        j = i - 1;
        while (j >= 0 && compar(&arr[j * size], temp) > 0) {
            memcpy(&arr[(j + 1) * size], &arr[j * size], size);
            j--;
        }
        memcpy(&arr[(j + 1) * size], temp, size);
    }
}

void merge_sort(void *base, size_t start, size_t end, size_t size, int (*compar)(const void *, const void*)) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        merge_sort(base, start, mid, size, compar);
        merge_sort(base, mid + 1, end, size, compar);

        char temp[(end - start + 1) * size];
        char *arr = (char *) base;
        int i = start, j = mid + 1, k = 0;

        while (i <= mid && j <= end) {
            if (compar(&arr[i * size], &arr[j * size]) <= 0) {
                memcpy(&temp[k * size], &arr[i * size], size);
                i++;
            } else {
                memcpy(&temp[k * size], &arr[j * size], size);
                j++;
            }
            k++;
        }

        while (i <= mid) {
            memcpy(&temp[k * size], &arr[i * size], size);
            i++;
            k++;
        }

        while (j <= end) {
            memcpy(&temp[k * size], &arr[j * size], size);
            j++;
            k++;
        }

        memcpy(&arr[start * size], temp, (end - start + 1) * size);
    }
}

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void*)) {
    if (nitems <= k) {
        binary_insertion_sort(base, nitems, size, compar);
    }
    else {
        int mid = nitems / 2;
        merge_binary_insertion_sort(base, mid, size, k, compar);
        merge_binary_insertion_sort((char*)base + mid * size, nitems - mid, size, k, compar);
        merge_sort(base, 0, nitems - 1, size, compar);
    }
}

