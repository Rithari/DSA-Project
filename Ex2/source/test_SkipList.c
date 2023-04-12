#include "../headers/unity.h"
#include "../headers/SkipList.h"

static struct SkipList *list;

// Comparison function for integer sorting
static int int_compare(const void *a, const void *b) {
    int a_val = *((int *)a);
    int b_val = *((int *)b);

    return a_val - b_val;
}

void setUp(void) {
    new_skiplist(&list, 10, int_compare);
}

void tearDown(void) {
    if(list) {
        clear_skiplist(&list);
    }
}

void test_insert_skiplist(void) {
    int value = 42;
    insert_skiplist(list, &value);

    const void *result = search_skiplist(list, &value);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(&value, result);
}

void test_search_skiplist_not_found(void) {
    int value = 42;
    int search_value = 24;

    insert_skiplist(list, &value);

    const void *result = search_skiplist(list, &search_value);
    TEST_ASSERT_NULL(result);
}

void test_skiplist_multiple_inserts(void) {
    int values[] = {42, 24, 7, 66, 10};
    size_t len = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < len; i++) {
        insert_skiplist(list, &values[i]);
    }

    for (size_t i = 0; i < len; i++) {
        const void *result = search_skiplist(list, &values[i]);
        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_PTR(&values[i], result);
    }
}

void test_insert_skiplist_duplicate(void) {
    int value = 42;
    insert_skiplist(list, &value);
    insert_skiplist(list, &value);

    const void *result = search_skiplist(list, &value);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_PTR(&value, result);
}

void test_clear_skiplist(void) {
    int value = 42;
    insert_skiplist(list, &value);
    clear_skiplist(&list);
    list = NULL;

    TEST_ASSERT_NULL(list);
}

void test_search_skiplist_empty_list(void) {
    int value = 42;
    const void *result = search_skiplist(list, &value);
    TEST_ASSERT_NULL(result);
}

void test_insert_skiplist_min_max_values(void) {
    int min_value = INT_MIN;
    int max_value = INT_MAX;

    insert_skiplist(list, &min_value);
    insert_skiplist(list, &max_value);

    const void *min_result = search_skiplist(list, &min_value);
    const void *max_result = search_skiplist(list, &max_value);

    TEST_ASSERT_NOT_NULL(min_result);
    TEST_ASSERT_EQUAL_PTR(&min_value, min_result);
    TEST_ASSERT_NOT_NULL(max_result);
    TEST_ASSERT_EQUAL_PTR(&max_value, max_result);
}

void test_insert_skiplist_negative_values(void) {
    int values[] = {-1, -2, -3, -4, -5};
    size_t len = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < len; i++) {
        insert_skiplist(list, &values[i]);
    }

    for (size_t i = 0; i < len; i++) {
        const void *result = search_skiplist(list, &values[i]);
        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_PTR(&values[i], result);
    }
}

void test_insert_skiplist_non_existing_value(void) {
    int values[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < len; i++) {
        insert_skiplist(list, &values[i]);
    }

    int non_existing_value = 42;
    const void *result = search_skiplist(list, &non_existing_value);
    TEST_ASSERT_NULL(result);
}

void test_insert_skiplist_random_values(void) {
    size_t len = 20;
    int *values = (int *)malloc(len * sizeof(int));

    srand(time(NULL));

    for (size_t i = 0; i < len; i++) {
        values[i] = rand();
        insert_skiplist(list, &values[i]);
    }

    for (size_t i = 0; i < len; i++) {
        const void *result = search_skiplist(list, &values[i]);
        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_PTR(&values[i], result);
    }

    free(values);
}



int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_insert_skiplist);
    RUN_TEST(test_search_skiplist_not_found);
    RUN_TEST(test_skiplist_multiple_inserts);
    RUN_TEST(test_insert_skiplist_duplicate);
    RUN_TEST(test_clear_skiplist);
    RUN_TEST(test_search_skiplist_empty_list);
    RUN_TEST(test_insert_skiplist_min_max_values);
    RUN_TEST(test_insert_skiplist_negative_values);
    RUN_TEST(test_insert_skiplist_non_existing_value);
    RUN_TEST(test_insert_skiplist_random_values);
    return UNITY_END();
}