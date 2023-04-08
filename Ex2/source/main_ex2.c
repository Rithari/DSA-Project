#include "../headers/main_ex2.h"

int compare_strings(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

bool is_word_separator(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == ',' || c == '.' || c == ';' || c == ':' || c == '!';
}

void find_errors(const char *dictfile, const char *textfile, size_t max_height) {
    struct SkipList *list;
    new_skiplist(&list, max_height, compare_strings);

    FILE *dict = fopen(dictfile, "r");
    if (!dict) {
        perror("Error opening dictionary file");
        return;
    }

    char word[256];
    while (fgets(word, sizeof(word), dict)) {
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n') {
            word[len - 1] = '\0';
            len--;
        }
        if (len > 0) {
            insert_skiplist(list, strdup(word));
        }
    }
    fclose(dict);

    FILE *text = fopen(textfile, "r");
    if (!text) {
        perror("Error opening text file");
        return;
    }

    char c;
    size_t word_pos = 0;
    while (1) {
        c = fgetc(text);
        if (is_word_separator(c) || c == EOF) {
            if (word_pos > 0) {
                word[word_pos] = '\0';
                if (!search_skiplist(list, word)) {
                    printf("Error: %s\n", word);
                }
                word_pos = 0;
            }
            if (c == EOF) {
                break;
            }
        } else {
            word[word_pos++] = c;
        }
    }


    if (word_pos > 0) {
        word[word_pos] = '\0';
        if (!search_skiplist(list, word)) {
            printf("Error: %s\n", word);
        }
    }

    fclose(text);
    clear_skiplist(&list);
}

// TODO: Remove max_height from arguments after determining it automatically
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <dictionary_file> <text_file> <max_height>\n", argv[0]);
        return 1;
    }

    srandom(time(NULL));
    find_errors(argv[1], argv[2], strtol(argv[3], NULL, 10));

    return 0;
}