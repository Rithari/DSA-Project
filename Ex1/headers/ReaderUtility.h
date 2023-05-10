#ifndef EX1_READERUTILITY_H
#define EX1_READERUTILITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Row structure representing a single row of data in the CSV file
struct Row {
    int ID;
    char *field1;
    int field2;
    double field3;
};

// Frees the memory allocated for field1 in the Row structure
void free_row(struct Row *row);

// Checks if the given string represents a valid number
bool is_number(const char *str);

// Reads the CSV file and returns an array of Row structs
struct Row *read_csv(FILE *filename, int *num_rows);

// Writes the given array of Row structs to a CSV file
int write_csv(FILE *filename, const struct Row *rows, int num_rows);

#endif //EX1_READERUTILITY_H
