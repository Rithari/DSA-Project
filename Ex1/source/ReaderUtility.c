#include "../headers/ReaderUtility.h"

void free_row(struct Row *row) {
    free(row->Name);
}

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
    while (*str) {
        if (*str == '.') {
            if (has_decimal_point) {
                return false; // Multiple decimal points are not allowed
            }
            has_decimal_point = true;
        } else if (!isdigit(*str)) {
            return false; // Non-digit characters are not allowed
        }
        str++;
    }

    return true;
}

struct Row *read_csv(const char *filename, int *num_rows, bool has_header) {
    FILE *fp;
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

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        free(rows);
        return NULL;
    }

    // If CSV has a header row, skip the first line
    if (has_header) {
        getline(&line, &len, fp);
    }

    // Read each line from the file
    while ((read_bytes = getline(&line, &len, fp)) != -1) {
        // Remove newline character if present
        if (line[read_bytes - 1] == '\n') {
            line[read_bytes - 1] = '\0';
            read_bytes--;
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
                    rows[num_read].Name = strdup(token);
                    if (rows[num_read].Name == NULL) {
                        perror("Error allocating memory for Name field");
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
                        fprintf(stderr, "Error parsing Number1 field\n");
                        goto next_line;
                    }
                    rows[num_read].Number1 = atoi(token);
                    break;
                case 3:
                    if (!is_number(token)) {
                        fprintf(stderr, "Error parsing Number2 field\n");
                        goto next_line;
                    }
                    rows[num_read].Number2 = strtof(token, NULL);
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

        num_read++;

        next_line:
        continue;
    }

    fclose(fp);
    if (line) free(line);

    *num_rows = num_read;
    return rows;
}

int write_csv(const char *filename, const struct Row *rows, int num_rows) {
    FILE *fp;

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    for (int i = 0; i < num_rows; i++) {
        fprintf(fp, "%d,%s,%d,%.2lf\n",
                rows[i].ID,
                rows[i].Name,
                rows[i].Number1,
                rows[i].Number2);
    }

    fclose(fp);
    return 0;
}
