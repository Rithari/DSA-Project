#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
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
    while ((c = fgetc(text)) != EOF) {
        if (is_word_separator(c)) {
            if (word_pos > 0) {
                word[word_pos] = '\0';
                if (!search_skiplist(list, word)) {
                    printf("Error: %s\n", word);
                }
                word_pos = 0; // Reset word_pos to 0
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

struct WorkerArgs {
    const char *dictfile;
    const char *textfile;
    size_t max_height;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool done;
};

void *find_errors_worker(void *args) {
    struct WorkerArgs *params = (struct WorkerArgs *)args;

    find_errors(params->dictfile, params->textfile, params->max_height);

    pthread_mutex_lock(&params->mutex);
    params->done = true;
    pthread_cond_signal(&params->cond);
    pthread_mutex_unlock(&params->mutex);

    return NULL;
}

void find_errors_timeout(const char *dictfile, const char *textfile) {
    for (size_t height = 17; height <= 20; height++) {
        printf("Trying max_height: %zu\n", height);

        pthread_t worker;
        pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
        pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
        struct WorkerArgs params = {dictfile, textfile, height, mutex, cond, false};

        struct timespec start_time;
        clock_gettime(CLOCK_REALTIME, &start_time);
        pthread_create(&worker, NULL, find_errors_worker, &params);

        struct timespec timeout;
        clock_gettime(CLOCK_REALTIME, &timeout);
        timeout.tv_sec += 45; // 45-second timeout

        pthread_mutex_lock(&params.mutex);
        while (!params.done && pthread_cond_timedwait(&params.cond, &params.mutex, &timeout) != ETIMEDOUT) {}
        bool timed_out = !params.done;
        pthread_mutex_unlock(&params.mutex);

        if (timed_out) {
            printf("Timed out for max_height: %zu\n", height);
            pthread_cancel(worker);
        } else {
            struct timespec end_time;
            clock_gettime(CLOCK_REALTIME, &end_time);
            double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
            printf("Finished for max_height: %zu in %.2f seconds\n", height, time_taken);
        }

        pthread_join(worker, NULL);
        pthread_mutex_destroy(&params.mutex);
        pthread_cond_destroy(&params.cond);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <dictionary_file> <text_file>\n", argv[0]);
        return 1;
    }

    srandom(time(NULL));
    find_errors_timeout(argv[1], argv[2]);

    return 0;
}
