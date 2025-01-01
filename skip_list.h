#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "skip_list_node.h"

typedef struct skip_list {
    int size;
    node** heads; // Contains the heads of each layer
    node** tails; // Contains the tails of each layer
    int height; // Number of layers of the tallest element in the whole list
    bool reversed;
} skip_list;

int generate_random_level(); // Randomly generates how many layers an element will be in
int size(skip_list *l);
bool empty(skip_list *l);
void push_left(skip_list *l, int64_t v);
void push_right(skip_list *l, int64_t v);
skip_list *make(int n, int64_t *seq);
bool pop_left(skip_list *l);
bool pop_right(skip_list *l);
int64_t peek_left(skip_list *l);
int64_t peek_right(skip_list *l);
node* get_node_at_i(skip_list* l, int i); // Returns a pointer to the node at index i
int64_t get(skip_list *l, int i);
void set(skip_list *l, int i, int64_t v);
void reverse(skip_list *l);

#endif