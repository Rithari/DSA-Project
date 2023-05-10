#include "../headers/ReaderUtility.h"

// Frees the memory allocated for field1 in the Row structure
void free_row(struct Row *row) {
    free(row->field1);
}

// Checks if the given string represents a valid number
bool is_number(const char *str) {
    // Ignore leading whitespace
    while (*str && isspace(*str)) {
        str++;
    }

    // Check for a sign (+ or -)
    if (*str == '+' || *str == '-') {
        str++;
    }

    bool has_decimal_point = false;
    bool has_digit = false;
    while (*str) {
        if (*str == '.') {
            if (has_decimal_point) {
                return false; // Multiple decimal points are not allowed
            }
            has_decimal_point = true;
        } else if (isdigit(*str)) {
            has_digit = true;
        } else {
            return false; // Non-digit characters are not allowed
        }
        str++;
    }

    return has_digit; // Ensure there is at least one digit in the number
}

// Reads the CSV file and returns an array of Row structs
struct Row *read_csv(FILE *fp, int *num_rows) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read_bytes;
    int num_allocated = 32;
    int num_read = 0;
    struct Row *rows = malloc(num_allocated * sizeof(struct Row));
    if (rows == NULL) {
        perror("Error allocating memory for rows");
        return NULL;
    }

    if (fp == NULL) {
        perror("Error opening file");
        free(rows);
        return NULL;
    }

    // Read each line from the file
    while ((read_bytes = getline(&line, &len, fp)) != -1) {
        // Remove newline character if present
        if (line[read_bytes - 1] == '\n') {
            line[read_bytes - 1] = '\0';
        }

        // Expand the rows array if needed
        if (num_read >= num_allocated) {
            num_allocated *= 2;
            struct Row *new_rows = realloc(rows, num_allocated * sizeof(struct Row));
            if (new_rows == NULL) {
                perror("Error reallocating memory for rows");
                for (int i = 0; i < num_read; i++) {
                    free_row(&rows[i]);
                }
                free(rows);
                fclose(fp);
                free(line);
                return NULL;
            }
            rows = new_rows;
        }

        // Parse the line into a Row struct
        char *token;
        char *next_ptr;
        int field = 0;

        token = strtok_r(line, ",", &next_ptr);
        while (token != NULL) {
            switch (field) {
                case 0:
                    if (!is_number(token)) {
                        fprintf(stderr, "Error parsing ID field\n");
                        goto next_line;
                    }
                    rows[num_read].ID = atoi(token);
                    break;
                case 1:
                    rows[num_read].field1 = strdup(token);
                    if (rows[num_read].field1 == NULL) {
                        perror("Error allocating memory for field1\n");
                        for (int i = 0; i < num_read; i++) {
                            free_row(&rows[i]);
                        }
                        free(rows);
                        fclose(fp);
                        free(line);
                        return NULL;
                    }
                    break;
                case 2:
                    if (!is_number(token)) {
                        fprintf(stderr, "Error parsing field2\n");
                        goto next_line;
                    }
                    rows[num_read].field2 = atoi(token);
                    break;
                case 3:
                    if (!is_number(token)) {
                        fprintf(stderr, "Error parsing field3\n");
                        goto next_line;
                    }
                    rows[num_read].field3 = strtod(token, NULL);
                    break;
                default:
                    fprintf(stderr, "Error: too many fields in the row\n");
                    goto next_line;
            }
            field++;
            token = strtok_r(NULL, ",", &next_ptr);
        }

        if (field != 4) {
            fprintf(stderr, "Error: not enough fields in the row\n");
            goto next_line;
        }

        num_read++; // Increment the number of rows read because this line was valid

        next_line:
        continue;
    }

    fclose(fp);
    if (line) free(line);

    *num_rows = num_read;
    return rows;
}
// Writes the given array of Row structs to a CSV file
int write_csv(FILE *fp, const struct Row *rows, int num_rows) {
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }
    // Iterate through the rows and write each row to the file
    for (int i = 0; i < num_rows; i++) {
        fprintf(fp, "%d,%s,%d,%5lf\n",
                rows[i].ID,
                rows[i].field1,
                rows[i].field2,
                rows[i].field3);
    }

    fclose(fp);
    return 0;
}