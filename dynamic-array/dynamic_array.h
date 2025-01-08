#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/* This const exists to provide stability to the resizing system. 
While a deque of capacity 5 doubles in capacity once it needs to contain 6 elements, 
it should not halve its capacity when its size falls back to 5 since another push would cause it to expand again (inefficient).
Instead, the deque halves in size once the contents go below 1/HYSTERESIS_FACTOR.*/
const int HYSTERESIS_FACTOR = 3;

// Scales the capacity of the deque by this const when resized
const int RESIZE_FACTOR = 2;



/* Only the essential variables are kept in this struct.
Note that there is no variable for back as we can calculate it using occupied_size and front*/
typedef struct list {
    int64_t* data;
    int front;
    int occupied_size;
    int capacity;
    bool is_reversed;
} list;

/* Initializes the contents of a list (allocation of the list itself is done in the make() function).
This function is called during deque resizes.
The is_reversed parameter is needed to maintain the list's state between resizes*/
void init_deque(list* d, int capacity, bool is_reversed) {
    if(capacity <= 0) {
        printf("ERROR: cannot initialize deque with 0 capacity");
        assert(0 != 0);
        return;
    }

    // reset values
    d->front = 0;
    d->occupied_size = 0;
    d->is_reversed = is_reversed; 
    d->capacity = capacity;
    
    d->data = (int64_t*) malloc(sizeof(int64_t) * capacity);
    assert(d->data != 0);
    
    return;
} 

// Keeps the same list but expands the backing array
void expand_deque(list* d) {
    int64_t* data_copy = d->data;
    int old_front = d->front;
    int old_capacity = d->capacity;
    bool old_reverse = d->is_reversed;

    init_deque(d, d->capacity * RESIZE_FACTOR, old_reverse);

    // transfer old data to new deque 
    // O(n)
    for(int i = old_front; i < old_front + old_capacity; i++) {
        push_right(d, data_copy[i % old_capacity]);
    }
    
    free(data_copy);
}

// Keeps the same list but expands the backing array
void shrink_deque(list* d) {
    int64_t* data_copy = d->data;
    int old_front = d->front;
    int old_capacity = d->capacity;
    int old_size = d->occupied_size;
    bool old_reverse = d->is_reversed;

    init_deque(d, d->capacity / RESIZE_FACTOR, old_reverse);

    // transfer old data to new deque 
    // O(n)
    for(int i = old_front; i < old_front + old_size; i++) {
        push_right(d, data_copy[i % old_capacity]);
    }
    free(data_copy);
}

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