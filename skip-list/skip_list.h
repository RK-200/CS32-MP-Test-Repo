#ifndef skip_list_H
#define skip_list_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "skip_list_node.h"

const uint32_t SEED = 1000; // Sets a fixed seed (set to 0 to let it be unseeded)
const uint32_t MAX_HEIGHT = 32; // Maximum number of layers the skip list can reach
const int P = 2; // Probability for element to be added to another layer is 1/P

typedef struct list {
    int size;
    node** heads; // Contains the heads of each layer
    node** tails; // Contains the tails of each layer
    int height; // Number of layers of the tallest element in the whole list
    bool reversed;
} list;

int generate_random_level(); // Randomly generates how many layers an element will be in
int size(list *l);
bool empty(list *l);
void push_left(list *l, int64_t v);
void push_right(list *l, int64_t v);
list *make(int n, int64_t *seq);
bool pop_left(list *l);
bool pop_right(list *l);
int64_t peek_left(list *l);
int64_t peek_right(list *l);
node* get_node_at_i(list* l, int i); // Returns a pointer to the node at index i
int64_t get(list *l, int i);
void set(list *l, int i, int64_t v);
void reverse(list *l);

#endif