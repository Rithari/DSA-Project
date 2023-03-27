#include <sys/times.h>
#include <stdbool.h>
#include <float.h>
#include <time.h>
#include "../headers/main_ex1.h"

double get_time_diff(struct timespec start, struct timespec end) {
    double elapsed = (end.tv_sec - start.tv_sec) * 1e9;
    elapsed += (end.tv_nsec - start.tv_nsec);
    return elapsed * 1e-9;
}

int compare_field1(const void *a, const void *b, size_t *comparison_count) {
    (*comparison_count)++;
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    return strcmp(row_a->field1, row_b->field1);
}

int compare_field2(const void *a, const void *b, size_t *comparison_count) {
    (*comparison_count)++;
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    return row_a->field2 - row_b->field2;
}

int compare_field3(const void *a, const void *b, size_t *comparison_count) {
    (*comparison_count)++;
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    return (row_a->field3 < row_b->field3) ? -1 : (row_a->field3 > row_b->field3) ? 1 : 0;
}

void sort_records(const char *infile, const char *outfile, size_t k, size_t field) {
    int num_rows;
    struct Row *rows = read_csv(infile, &num_rows, false);
    if (rows == NULL) {
        printf("Failed to read the CSV file.\n");
        exit(1);
    }

    int (*compare_function)(const void *, const void *, size_t *);

    switch (field) {
        case 1:
            compare_function = compare_field1;
            break;
        case 2:
            compare_function = compare_field2;
            break;
        case 3:
            compare_function = compare_field3;
            break;
        default:
            printf("Invalid field value. Must be 1, 2, or 3.\n");
            exit(1);
    }

    int best_k_time = 0;
    double best_time = DBL_MAX;

    int best_k_operations = 0;
    size_t best_operations = SIZE_MAX;

    int best_k_data_moves = 0;
    size_t best_data_moves = SIZE_MAX;

    int best_k_overall = 0;
    double best_score = DBL_MAX;

    // Define the weights for the criteria
    double time_weight = 1.0;
    double operations_weight = 1.0;
    double data_moves_weight = 1.0;

    int min_k = 1;
    int max_k = 100;

    for (int current_k = min_k; current_k <= max_k; current_k++) {
        struct Row *rows_copy = malloc(num_rows * sizeof(struct Row));
        memcpy(rows_copy, rows, num_rows * sizeof(struct Row));

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        size_t comparison_count = 0;
        size_t data_move_count = 0;
        merge_binary_insertion_sort(rows_copy, num_rows, sizeof(struct Row), current_k, &comparison_count, &data_move_count, compare_function);

        clock_gettime(CLOCK_MONOTONIC, &end);
        double current_time = get_time_diff(start, end);

        printf("Finished sorting with k=%d, comparison_count=%zu, data_move_count=%zu in %f seconds\n", current_k, comparison_count, data_move_count, current_time);

        if (current_time < best_time) {
            best_time = current_time;
            best_k_time = current_k;
        }

        if (comparison_count < best_operations) {
            best_operations = comparison_count;
            best_k_operations = current_k;
        }

        if (data_move_count < best_data_moves) {
            best_data_moves = data_move_count;
            best_k_data_moves = current_k;
        }

        double current_score = time_weight * current_time + operations_weight * comparison_count + data_moves_weight * data_move_count;

        if (current_score < best_score) {
            best_score = current_score;
            best_k_overall = current_k;
        }

        free(rows_copy);
    }

    printf("Optimal k value for time: %d, with a sorting time of %f seconds\n", best_k_time, best_time);
    printf("Optimal k value for operations: %d, with a count of %zu comparisons\n", best_k_operations, best_operations);
    printf("Optimal k value for data moves: %d, with a count of %zu data moves\n", best_k_data_moves, best_data_moves);
    printf("Optimal k value overall: %d, with a combined score of %f\n", best_k_overall, best_score);

    // Sort and save the sorted rows with the best overall k value to a new CSV file
    size_t comparison_count_final = 0;
    size_t data_move_count_final = 0;
    merge_binary_insertion_sort(rows, num_rows, sizeof(struct Row), best_k_overall, &comparison_count_final, &data_move_count_final, compare_function);
    if (write_csv(outfile, rows, num_rows) != 0) {
        perror("Failed to write CSV file");
        exit(1);
    }
    printf("Sorted CSV file saved to '%s'\n", outfile);

    // Free the memory allocated for the rows array
    for (int i = 0; i < num_rows; i++) {
        free_row(&rows[i]);
    }
    free(rows);
}


int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <path_to_csv_file> <output_csv_file> <k> <field>\n", argv[0]);
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];
    size_t k = atoi(argv[3]);
    size_t field = atoi(argv[4]);

    if (strcmp(infile, outfile) == 0) {
        printf("Input and output files must be different.\n");
        return 1;
    }

    sort_records(infile, outfile, k, field);

    return 0;
}

