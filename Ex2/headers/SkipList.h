#ifndef EX2_SKIPLIST_H
#define EX2_SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    struct Node **next;
    size_t size;
    void *item;
};

struct SkipList {
    struct Node **heads;
    size_t max_level;
    size_t max_height;
    int (*compare)(const void *, const void *);
};

void new_skiplist(struct SkipList **list, size_t max_height, int (*compar)(const void *, const void *));
void clear_skiplist(struct SkipList **list);
size_t random_level(size_t max_height);
struct Node *create_node(void *item, size_t size);
void insert_skiplist(struct SkipList *list, void *item);
const void *search_skiplist(struct SkipList *list, void *item);


#endif //EX2_SKIPLIST_H
