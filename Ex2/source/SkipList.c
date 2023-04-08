#include "../headers/SkipList.h"

void new_skiplist(struct SkipList **list, size_t max_height, int (*compar)(const void *, const void *)) {
    *list = (struct SkipList *)malloc(sizeof(struct SkipList));
    (*list)->max_height = max_height;
    (*list)->compare = compar;
    (*list)->head = (struct Node *)malloc(sizeof(struct Node));
    (*list)->head->next = (struct Node **)calloc(max_height, sizeof(struct Node *));
    (*list)->head->size = max_height;
    (*list)->max_level = 1;
}

void clear_skiplist(struct SkipList **list) {
    struct Node *current = (*list)->head;
    struct Node *temp;

    while (current) {
        temp = current->next[0];
        free(current->next);
        free(current);
        current = temp;
    }

    free(*list);
    *list = NULL;
}

size_t random_level(size_t max_height) {
    size_t level = 1;
    while ((random() / ((double)RAND_MAX + 1) < 0.5) && (level < max_height)) {
        level++;
    }
    return level;
}


void insert_skiplist(struct SkipList *list, void *item) {
    struct Node *update[list->max_height];
    struct Node *current = list->head;

    for (int i = list->max_level - 1; i >= 0; i--) {
        while (current->next[i] && list->compare(current->next[i]->item, item) < 0) {
            current = current->next[i];
        }
        update[i] = current;
    }

    size_t new_level = random_level(list->max_height);
    if (new_level > list->max_level) {
        for (int i = list->max_level; i < new_level; i++) {
            update[i] = list->head;
        }
        list->max_level = new_level;
    }

    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->next = (struct Node **)calloc(new_level, sizeof(struct Node *));
    new_node->size = new_level;
    new_node->item = item;

    for (int i = 0; i < new_level; i++) {
        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
    }
}

const void *search_skiplist(struct SkipList *list, void *item) {
    struct Node *current = list->head;

    for (int i = list->max_level - 1; i >= 0; i--) {
        while (current->next[i] && list->compare(current->next[i]->item, item) < 0) {
            current = current->next[i];
        }
    }

    current = current->next[0];

    if (current && list->compare(current->item, item) == 0) {
        return current->item;
    } else {
        return NULL;
    }
}
