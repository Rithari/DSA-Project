#ifndef EX1_READERUTILITY_H
#define EX1_READERUTILITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Row {
    int ID;
    char *Name;
    double Number1;
    double Number2;
};

void free_row(struct Row *row);
struct Row *read_csv(const char *filename, int *num_rows);

#endif //EX1_READERUTILITY_H
