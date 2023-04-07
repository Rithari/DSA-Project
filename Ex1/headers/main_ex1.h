#ifndef EX1_MAIN_EX1_H
#define EX1_MAIN_EX1_H

#include "MergeBinSorter.h"
#include "ReaderUtility.h"
#include <time.h>

// Calculate the time difference between two timespec structures
double get_time_diff(struct timespec start, struct timespec end);

// Comparison functions for sorting by field1, field2, and field3
int compare_field1(const void *a, const void *b);
int compare_field2(const void *a, const void *b);
int compare_field3(const void *a, const void *b);

// Sort the records in the input CSV file and save the sorted records to an output CSV file
void sort_records(const char *infile, const char *outfile, size_t k, size_t field);

#endif //EX1_MAIN_EX1_H
