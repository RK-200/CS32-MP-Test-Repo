#include "dynamic_array.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



list *make(int n, int64_t *seq) {
    list* d = (list*) malloc(sizeof(list));
    assert(d != 0);

    init_deque(d, n * 2);

    // no need to use push right since were copying from a "true" 0-indexed array instead of a deque
    for(int i = 0; i < n; i++) {
        d->data[i] = seq[i];
    }
    return d;

    //TODO: TEST THIS
}

void push_left(list *l, int64_t v) {
    if(l->occupied_size == l->capacity) {
        expand_deque(l);
    }

    l->front -= 1;
    
    if(l->front < 0) {
        l->front += l->capacity;
    }

    l->data[l->front] = v;
    l->occupied_size++;

    // TODO: ADD REVERSE LOGIC
}

void push_right(list *l, int64_t v) {
    if(l->occupied_size == l->capacity) {
        expand_deque(l);
    }

    int back = (l->front + l->occupied_size) % l->capacity;
    l->data[back] = v;
    l->occupied_size++;

    //TODO: add reverse logic
}

bool pop_left(list *l);

bool pop_right(list *l);

int64_t peek_left(list *l) {
    return l->data[l->front];
}

int64_t peek_right(list *l) {
    // the modulo calculation lands the right index as the index to the right of the last occupied index (meaning it points to an empty index)
    return l->data[((l->front + l->occupied_size) % l->capacity) - 1];
}

int size(list *l) {
    return l->occupied_size;
}

bool empty(list *l) {
    return (l->occupied_size == 0) ? true : false;
}

int64_t get(list *l, int i) {
    
}

void set(list *l, int i, int64_t v);

void reverse(list *l) {
    l->is_reversed = !l->is_reversed;
}