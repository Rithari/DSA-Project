#include "../headers/unity.h"
#include "../headers/MergeBinSorter.h"

// Comparison function for integer sorting
static int int_compare(const void *a, const void *b) {
    const int int_a = *(const int *) a;
    const int int_b = *(const int *) b;

    return (int_a > int_b) - (int_a < int_b);
}

// Setup function for Unity testing framework
void setUp(void) {
}

// Teardown function for Unity testing framework
void tearDown(void) {
}

// Test sorting a basic unsorted array
void test_merge_binary_insertion_sort_basic(void) {
    int data[] = {10, 2, 8, 6, 7, 9, 4, 1, 3, 5};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t n = sizeof(data) / sizeof(data[0]);
    size_t k = 4;

    merge_binary_insertion_sort(data, n, sizeof(int), k, int_compare);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, data, n);
}

// Test sorting an array that is already sorted
void test_merge_binary_insertion_sort_already_sorted(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t n = sizeof(data) / sizeof(data[0]);
    size_t k = 4;

    merge_binary_insertion_sort(data, n, sizeof(int), k, int_compare);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, data, n);
}

// Test sorting an array that is sorted in reverse order
void test_merge_binary_insertion_sort_reversed(void) {
    int data[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t n = sizeof(data) / sizeof(data[0]);
    size_t k = 4;

    merge_binary_insertion_sort(data, n, sizeof(int), k, int_compare);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, data, n);
}

// Test sorting an array with a single element
void test_merge_binary_insertion_sort_single_element() {
    int arr[] = {5};
    merge_binary_insertion_sort(arr, 1, sizeof(int), 3, int_compare);
    TEST_ASSERT_EQUAL_INT(5, arr[0]);
}

// Test sorting an array where all elements have the same value
void test_merge_binary_insertion_sort_same_values() {
    int arr[] = {2, 2, 2, 2, 2};
    int expected[] = {2, 2, 2, 2, 2};
    merge_binary_insertion_sort(arr, 5, sizeof(int), 3, &int_compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 5);
 }

// Test sorting an array with negative values
void test_merge_binary_insertion_sort_negative_values(void) {
    int arr[] = {-3, 5, -1, 10, -7, 4};
    int expected[] = {-7, -3, -1, 4, 5, 10};
    merge_binary_insertion_sort(arr, 6, sizeof(int), 3, int_compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 6);
}

// Test sorting an array where k is greater than the number of elements
void test_merge_binary_insertion_sort_k_greater_than_n(void) {
    int arr[] = {6, 2, 4, 1, 3, 5};
    int expected[] = {1, 2, 3, 4, 5, 6};
    merge_binary_insertion_sort(arr, 6, sizeof(int), 10, int_compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 6);
}

// Test sorting an array where k is equal to the number of elements
void test_merge_binary_insertion_sort_k_equal_to_n(void) {
    int arr[] = {5, 3, 1, 2, 4, 6};
    int expected[] = {1, 2, 3, 4, 5, 6};
    merge_binary_insertion_sort(arr, 6, sizeof(int), 6, int_compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 6);
}

// Test sorting an array where k equals 1
void test_merge_binary_insertion_sort_k_equals_one(void) {
    int arr[] = {9, 7, 2, 5, 6, 1, 8, 4, 3};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    merge_binary_insertion_sort(arr, 9, sizeof(int), 1, int_compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 9);
}

// Test sorting an array where all elements are sorted except one
void test_merge_binary_insertion_sort_all_but_one_sorted(void) {
    int arr[] = {1, 3, 5, 7, 9, 2};
    int expected[] = {1, 2, 3, 5, 7, 9};
    merge_binary_insertion_sort(arr, 6, sizeof(int), 3, int_compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 6);
}

// Test sorting an array with duplicates and negative values
void test_merge_binary_insertion_sort_duplicates_and_negatives(void) {
    int arr[] = {-5, 2, 2, -5, 3, 0, 0};
    int expected[] = {-5, -5, 0, 0, 2, 2, 3};
    merge_binary_insertion_sort(arr, 7, sizeof(int), 4, int_compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 7);
}

// Test sorting an array with ascending and descending parts
void test_merge_binary_insertion_sort_ascending_descending(void) {
    int arr[] = {1, 2, 3, 4, 5, 10, 9, 8, 7, 6};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    merge_binary_insertion_sort(arr, 10, sizeof(int), 5, int_compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 10);
}

// Test sorting an array with descending and ascending parts
void test_merge_binary_insertion_sort_descending_ascending(void) {
    int arr[] = {5, 4, 3, 2, 1, 6, 7, 8, 9, 10};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    merge_binary_insertion_sort(arr, 10, sizeof(int), 5, int_compare);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, arr, 10);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_merge_binary_insertion_sort_basic);
    RUN_TEST(test_merge_binary_insertion_sort_already_sorted);
    RUN_TEST(test_merge_binary_insertion_sort_reversed);
    RUN_TEST(test_merge_binary_insertion_sort_single_element);
    RUN_TEST(test_merge_binary_insertion_sort_same_values);
    RUN_TEST(test_merge_binary_insertion_sort_negative_values);
    RUN_TEST(test_merge_binary_insertion_sort_k_greater_than_n);
    RUN_TEST(test_merge_binary_insertion_sort_k_equal_to_n);
    RUN_TEST(test_merge_binary_insertion_sort_k_equals_one);
    RUN_TEST(test_merge_binary_insertion_sort_all_but_one_sorted);
    RUN_TEST(test_merge_binary_insertion_sort_duplicates_and_negatives);
    RUN_TEST(test_merge_binary_insertion_sort_ascending_descending);
    RUN_TEST(test_merge_binary_insertion_sort_descending_ascending);

    return UNITY_END();
}


