#include "../headers/main_ex1.h"

// Returns the time difference between two timespec structs in seconds
double get_time_diff(struct timespec start, struct timespec end) {
    double elapsed = (end.tv_sec - start.tv_sec) * 1e9;
    elapsed += (end.tv_nsec - start.tv_nsec);
    return elapsed * 1e-9;
}

// Comparison function for field1 (char*)
int compare_field1(const void *a, const void *b) {
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    return strcmp(row_a->field1, row_b->field1);
}

// Comparison function for field2 (int)
int compare_field2(const void *a, const void *b) {
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    return row_a->field2 - row_b->field2;
}

// Comparison function for field3 (double)
int compare_field3(const void *a, const void *b) {
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    return (row_a->field3 < row_b->field3) ? -1 : (row_a->field3 > row_b->field3) ? 1 : 0;
}

// Reads a CSV file, sorts the records based on the specified field, and writes the sorted records to a new CSV file
void sort_records(const char *infile, const char *outfile, size_t k, size_t field) {
    int num_rows;
    struct Row *rows = read_csv(infile, &num_rows);
    if (rows == NULL) {
        printf("Failed to read the CSV file.\n");
        exit(1);
    }

    // Function pointer to the comparison function
    int (*compare_function)(const void *, const void *);

    // Choose the comparison function based on the specified field
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

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Sort the records using merge-binary-insertion sort
    merge_binary_insertion_sort(rows, num_rows, sizeof(struct Row), k, compare_function);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = get_time_diff(start, end);

    printf("Finished sorting in %f seconds\n", time_taken);

    // Save the sorted rows to a new CSV file
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
    // Ensure that the required arguments are provided
    if (argc < 5) {
        printf("Usage: %s <path_to_csv_file> <output_csv_file> <k> <field>\n", argv[0]);
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];
    size_t k = strtol(argv[3], NULL, 10);
    size_t field = strtol(argv[4], NULL, 10);

    // Check if input and output files are the same
    if (strcmp(infile, outfile) == 0) {
        printf("Input and output files must be different.\n");
        return 1;
    }

    // Sort the records in the input file and save them to the output file
    sort_records(infile, outfile, k, field);

    return 0;
}
