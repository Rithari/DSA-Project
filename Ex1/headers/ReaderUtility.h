#ifndef EX1_READERUTILITY_H
#define EX1_READERUTILITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Data types as specified in the exercise brief
struct Row {
    int ID;
    char *field1;
    int field2;
    double field3;
};

void free_row(struct Row *row);
bool is_number(const char *str);
struct Row *read_csv(const char *filename, int *num_rows, bool has_header);
int write_csv(const char *filename, const struct Row *rows, int num_rows);

#endif //EX1_READERUTILITY_H
