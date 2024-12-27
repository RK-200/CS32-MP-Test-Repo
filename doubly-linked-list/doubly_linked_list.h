#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINED_LIST_H

#include "dll_node.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct list {
    node* left;
    node* right;
    int size;
    bool is_reversed;
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