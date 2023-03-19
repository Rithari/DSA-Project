#include <time.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdbool.h>
#include "../headers/main_ex1.h"

int compare_name(const void *a, const void *b) {
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    return strcmp(row_a->Name, row_b->Name);
}

int compare_number1(const void *a, const void *b) {
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    return row_a->Number1 - row_b->Number1;
}

int compare_number2(const void *a, const void *b) {
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    if (row_a->Number2 < row_b->Number2) {
        return -1;
    } else if (row_a->Number2 > row_b->Number2) {
        return 1;
    } else {
        return 0;
    }
}

int compare(const void *a, const void *b) {
    const struct Row *row_a = (const struct Row *)a;
    const struct Row *row_b = (const struct Row *)b;

    int name_cmp = strcmp(row_a->Name, row_b->Name);

    if (name_cmp == 0) {
        int number1_cmp = row_a->Number1 - row_b->Number1;
        if (number1_cmp == 0) {
            if (row_a->Number2 < row_b->Number2) {
                return -1;
            } else if (row_a->Number2 > row_b->Number2) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return number1_cmp;
        }
    } else {
        return name_cmp;
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <path_to_csv_file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    struct Row *rows;
    int num_rows;

    rows = read_csv(filename, &num_rows, false); // Set the has_header parameter to false if there's no header row
    if (rows == NULL) {
        perror("Failed to read CSV file");
        exit(1);
    }

    // Time the sorting algorithm
    struct tms start, end;
    times(&start);
    merge_binary_insertion_sort(rows, num_rows, sizeof(struct Row), 42, compare);
    //qsort(rows, num_rows, sizeof(struct Row), compare_field);
    times(&end);
    printf("Finished sorting in %f seconds\n", (double) (end.tms_utime - start.tms_utime) / sysconf(_SC_CLK_TCK));

    // Save the sorted rows back to a new CSV file
    char *output_filename = "../sorted.csv";
    if (write_csv(output_filename, rows, num_rows)) {
        perror("Failed to write sorted data to file");
        exit(1);
    }

    printf("Sorted data written to file '%s'\n", output_filename);

    // Free the memory allocated for the rows array
    for (int i = 0; i < num_rows; i++) {
        free_row(&rows[i]);
    }

    free(rows);

    return 0;
}
