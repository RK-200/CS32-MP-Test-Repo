#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

const int HYSTERESIS_FACTOR = 3;
const int RESIZE_FACTOR = 2;

typedef struct list {
    int64_t* data;
    int front;
    int occupied_size;
    int capacity;
    bool is_reversed;
} list;

void init_deque(list* d, int capacity) {
    d->front = 0;
    d->occupied_size = 0;
    d->is_reversed = false;                 // BIG NOTE: THIS MIGHT NEED TO RETAIN THE REVERSED STATUS OF THE DEQUE THAT CAME BEFORE IT,, HTINK ABT IT

    assert(capacity > 0);
    d->capacity = capacity;
    
    d->data = (int64_t*) malloc(sizeof(int64_t) * capacity);
    assert(d->data != 0);
    
    return;
} 

// keeps the same deque but expands the backing array
void expand_deque(list* d) {
    int64_t* data_copy = d->data;
    int old_front = d->front;
    int old_capacity = d->capacity;
    init_deque(d, d->capacity * RESIZE_FACTOR);

    // transfer old data to new deque 
    // O(n)
    for(int i = old_front; i < old_front + old_capacity; i++) {
        push_right(d, data_copy[i % old_capacity]);
    }
    
}

//shrink deque

void shrink_deque(list* d) {
    int64_t* data_copy = d->data;
    int old_front = d->front;
    int old_capacity = d->capacity;
    int old_size = d->occupied_size;

    init_deque(d, d->capacity / RESIZE_FACTOR);

    // transfer old data to new deque 
    // O(n)
    // WARNIGN: THIS DOESNT WORK KASI BY DEFINITION, NOT ALL OF THESE INDICES ARE OCCUPIED,, FIND ANOTHER WAY
    for(int i = old_front; i < old_front + old_size; i++) {
        push_right(d, data_copy[i % old_capacity]);
    }
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