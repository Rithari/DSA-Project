#include "../headers/ReaderUtility.h"

void free_row(struct Row *row) {
    free(row->Name);
}

struct Row *read_csv(const char *filename, int *num_rows) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    int num_allocated = 32;
    int num_read = 0;
    struct Row *rows = malloc(num_allocated * sizeof(struct Row));

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Read each line from the file
    while (getline(&line, &len, fp) != -1) {
        // Expand the rows array if needed
        if (num_read >= num_allocated) {
            num_allocated *= 2;
            struct Row* new_rows = realloc(rows, num_allocated * sizeof(struct Row));
            if (new_rows == NULL) {
                perror("Error reallocating memory");
                free(rows);  // Free the previously allocated memory
                return NULL;
            }
            rows = new_rows;
        }

        // Parse the line into a Row struct
        char *token;
        token = strtok(line, ",");
        rows[num_read].ID = atoi(token);

        token = strtok(NULL, ",");
        rows[num_read].Name = malloc((strlen(token) + 1) * sizeof(char));
        if (rows[num_read].Name == NULL) {
            perror("Error allocating memory");
            return NULL;
        }
        strcpy(rows[num_read].Name, token);

        token = strtok(NULL, ",");
        rows[num_read].Number1 = atof(token);

        token = strtok(NULL, ",");
        rows[num_read].Number2 = atof(token);

        num_read++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
    // Set the output parameter to the number of rows read
    *num_rows = num_read;

    return rows;
}
