#include "../headers/main_ex1.h"

int compare_field(const void *a, const void *b) {
    struct Row *rowA = (struct Row *) a;
    struct Row *rowB = (struct Row *) b;
    if (rowA->Number1 < rowB->Number1) {
        return -1;
    } else if (rowA->Number1 > rowB->Number1) {
        return 1;
    } else {
        return 0;
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

    rows = read_csv(filename, &num_rows);
    if (rows == NULL) {
        perror("Failed to read CSV file");
        exit(1);
    }

    // Sort the rows array using Merge-BinaryInsertion Sort algorithm
    merge_binary_insertion_sort(rows, num_rows, sizeof(struct Row), 1, compare_field);

    // Save the sorted rows back to a new CSV file
    char *output_filename = "../sorted.csv";
    FILE *fp = fopen(output_filename, "w");
    if (fp == NULL) {
        perror("Failed to open output file");
        exit(1);
    }

    // Write the header row to the file
    fprintf(fp, "ID,Name,Number1,Number2\n");

    // Write each row to the file
    for (int i = 0; i < num_rows; i++) {
        struct Row row = rows[i];
        fprintf(fp, "%d,%s,%.2f,%.2f\n", row.ID, row.Name, row.Number1, row.Number2);
    }

    fclose(fp);

    printf("Sorted data written to file '%s'\n", output_filename);

    // Free the memory allocated for the rows array
    for (int i = 0; i < num_rows; i++) {
        free_row(&rows[i]);
    }

    free(rows);

    return 0;
}
