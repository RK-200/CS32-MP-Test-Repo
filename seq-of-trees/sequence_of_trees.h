#ifndef SEQUENCE_OF_TREES_H
#define SEQUENCE_OF_TREES_H

#include "st_node.h"
#include <stdbool.h>
#include <assert.h>

typedef struct list {
    node* left_head;
    node* right_head;
    int64_t size;
    int64_t nodes;
    int64_t leftmost;
    int64_t rightmost;
    bool reverse;
} list;

list *make(int n, int64_t *seq);
void push_left(list *l, int64_t v);
void push_right(list *l, int64_t v);
bool pop_left(list *l);
bool pop_right(list *l);
int64_t peek_left(list *l);
int64_t peek_right(list *l);
int size(list *l);
bool empty(list *l);
int64_t get(list *l, int i);
void set(list *l, int i, int64_t v);
void reverse(list *l);

#endif