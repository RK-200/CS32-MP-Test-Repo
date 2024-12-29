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
        d->occupied_size += 1;
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

bool pop_right(list *l) {
    if(l->occupied_size == 0) {
        return false;
    }

    if(l->occupied_size < l->capacity / HYSTERESIS_FACTOR) {
        shrink_deque(l);
    }

    int back = (l->front + l->occupied_size) % l->capacity - 1;         // the -1 is important since this operation lands the back index to the index to the right of the last occupied index
    l->data[back] = -1;
    l->occupied_size -= 1;
    return true;

    //TODO: implement reverse logic
}

int64_t peek_left(list *l) {
    return l->data[l->front];
    //TODO: implement reverse logic
}

int64_t peek_right(list *l) {
    // the modulo calculation lands the right index as the index to the right of the last occupied index (meaning it points to an empty index)
    return l->data[((l->front + l->occupied_size) % l->capacity) - 1];
    //TODO: implement reverse logic
}

int size(list *l) {
    return l->occupied_size;
}

bool empty(list *l) {
    return (l->occupied_size == 0) ? true : false;
}

int64_t get(list *l, int i) {
    return l->data[(i + l->front + l->occupied_size) % l->capacity];
    //TODO: add reverse logic
}

void set(list *l, int i, int64_t v) {
    l->data[(i + l->front + l->occupied_size) % l->capacity] = v;
    //TODO: add reverse logic
    return;
}

void reverse(list *l) {
    l->is_reversed = !l->is_reversed;
    return;
}

int main()
{
    int64_t seq[5] = {0, 1, 2, 3, 4};
    list* l = make(5, seq);

    int temp = 0;
    temp = size(l); //5
    temp = empty(l); //0
    
    push_right(l, 10);  // [0, 1, 2, 3, 4, 10, 0, 0, 0, 0]
    push_right(l, 10);  // [0, 1, 2, 3, 4, 10, 10, 0, 0, 0]
    push_right(l, 10);  // [0, 1, 2, 3, 4, 10, 10, 10, 0, 0]
    push_right(l, 10);  // [0, 1, 2, 3, 4, 10, 10, 10, 10, 0]
    push_right(l, 10);  // [0, 1, 2, 3, 4, 10, 10, 10, 10, 10]
    push_right(l, 11);  // [0, 1, 2, 3, 4, 10, 10, 10, 10, 10, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    push_right(l, 11);  // [0, 1, 2, 3, 4, 10, 10, 10, 10, 10, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    push_right(l, 11);  // [0, 1, 2, 3, 4, 10, 10, 10, 10, 10, 11, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0]
    push_right(l, 11);  // [0, 1, 2, 3, 4, 10, 10, 10, 10, 10, 11, 11, 11, 11, 0, 0, 0, 0, 0, 0, 0]
    
    pop_right(l);       // [0, 1, 2, 3, 4, 10, 10, 10, 10, 10, 11, 11, 11, -1, 0, 0, 0, 0, 0, 0, 0]
    pop_right(l);       // [0, 1, 2, 3, 4, 10, 10, 10, 10, 10, 11, 11, -1, -1, 0, 0, 0, 0, 0, 0, 0]
    pop_right(l);       // [0, 1, 2, 3, 4, 10, 10, 10, 10, 10, 11, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0]
    pop_right(l);       // [0, 1, 2, 3, 4, 10, 10, 10, 10, 10, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0]
    pop_right(l);       // [0, 1, 2, 3, 4, 10, 10, 10, 10, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0]
    pop_right(l);       // [0, 1, 2, 3, 4, 10, 10, 10, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0]
    pop_right(l);       // [0, 1, 2, 3, 4, 10, 10, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0]
    pop_right(l);       // [0, 1, 2, 3, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0]
    pop_right(l);       // [0, 1, 2, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0]
    pop_right(l);       // [0, 1, 2, 3, -1, -1, -1, -1, -1, -1]
    return 0;
}
