#include "../headers/main_ex2.h"

int compare_strings(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

void find_errors(const char *dictfile, const char *textfile, size_t max_height) {
    struct SkipList *list;
    new_skiplist(&list, max_height, compare_strings);

    // Load dictionary file into the skip list
    FILE *dict = fopen(dictfile, "r");
    if (!dict) {
        perror("Error opening dictionary file");
        return;
    }

    char word[256];
    while (fgets(word, sizeof(word), dict)) {
        strtok(word, "\n"); // Remove newline character
        to_lowercase(word); // Convert to lowercase

        char *insert_word = strdup(word);
        if (!insert_word) {
            printf("Memory allocation failed\n");
            exit(1);
        }

        insert_skiplist(list, insert_word);
    }
    fclose(dict);

    // Process text file to find errors
    FILE *text = fopen(textfile, "r");
    if (!text) {
        perror("Error opening text file");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), text)) {
        char *token = strtok(line, " \t\n\r.,;:!-");
        while (token) {
            to_lowercase(token); // Convert to lowercase
            if (!search_skiplist(list, token)) {
                printf("Error: %s\n", token);
            }
            token = strtok(NULL, " \t\n\r.,;:!-");
        }
    }
    fclose(text);
    clear_skiplist(&list);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <dictionary_file> <text_file> <max_height>\n", argv[0]);
        return 1;
    }

    size_t height = strtoul(argv[3], NULL, 10);

    srandom(time(NULL));
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    find_errors(argv[1], argv[2], height);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Finished for max_height: %zu in %.2f seconds\n", height, elapsed_time);

    return 0;
}