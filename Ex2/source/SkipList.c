#include "../headers/SkipList.h"

void new_skiplist(struct SkipList **list, size_t max_height, int (*compar)(const void *, const void *)) {
    *list = (struct SkipList *)malloc(sizeof(struct SkipList));
    (*list)->max_height = max_height;
    (*list)->compare = compar;
    (*list)->heads = (struct Node **)calloc(max_height, sizeof(struct Node *));
    (*list)->max_level = 1;
}

void clear_skiplist(struct SkipList **list) {
    struct Node *current = (*list)->heads[0];
    struct Node *temp;

    while (current) {
        temp = current->next[0];
        free(current->next);
        free(current);
        current = temp;
    }

    free((*list)->heads);
    free(*list);
    *list = NULL;
}


size_t random_level(size_t max_height) {
    size_t level = 1;
    while ((rand() / ((double)RAND_MAX + 1) < 0.5) && (level < max_height)) {
        level++;
    }
    return level;
}

struct Node *create_node(void *item, size_t size) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->next = (struct Node **)calloc(size, sizeof(struct Node *));
    new_node->size = size;
    new_node->item = item;
    return new_node;
}

void insert_skiplist(struct SkipList *list, void *item) {
    struct Node *new = create_node(item, random_level(list->max_height));
    if (new->size > list->max_level) {
        list->max_level = new->size;
    }

    struct Node **x = list->heads;
    for (int k = list->max_level; k >= 1; k--) {
        while (x[k - 1] != NULL && list->compare(x[k - 1]->item, item) < 0) {
            x = x[k - 1]->next;
        }
        if (k <= new->size) {
            new->next[k - 1] = x[k - 1];
            x[k - 1] = new;
        }
    }
}

const void *search_skiplist(struct SkipList *list, void *item) {
    struct Node **x = list->heads;

    for (int i = list->max_level; i >= 1; i--) {
        while (x[i - 1] != NULL && list->compare(x[i - 1]->item, item) < 0) {
            x = x[i - 1]->next;
        }
    }

    if (x[0] != NULL && list->compare(x[0]->item, item) == 0) {
        return x[0]->item;
    } else {
        return NULL;
    }
}
