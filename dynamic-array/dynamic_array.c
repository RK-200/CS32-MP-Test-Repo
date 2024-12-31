#include "dynamic_array.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

// O(len(seq)) worst-case
list *make(int n, int64_t *seq) {
    // allocates d in the heap then initializes its values using init_deque() and the for loop
    // note that the initial capacity of the backing array is twice the number of input elements

    list* d = (list*) malloc(sizeof(list));
    assert(d != 0);

    init_deque(d, n * 2);

    // no need to use push right since were copying from a "true" 0-indexed array instead of a deque
    for(int i = 0; i < n; i++) {
        d->data[i] = seq[i];
        d->occupied_size += 1;
    }
    return d;
}

// O(1) amortized
void push_left(list *l, int64_t v) {
    // expands the deque when we push to a full backing array
    if(l->occupied_size == l->capacity) {
        expand_deque(l);
    }

    if(l->is_reversed) {
        l->is_reversed = false;
        push_right(l, v);
        l->is_reversed = true;
        return;
    }

    // non-reversed logic moves the index one space to the left and inserts v at that index
    if(!l->is_reversed) {
        l->front -= 1;  

        if(l->front < 0) {
            l->front += l->capacity;
        }

        l->data[l->front] = v;
        l->occupied_size++;
        return;
    }
}

// O(1) amortized
void push_right(list *l, int64_t v) {
    // expands the deque when we push to a full backing array
    if(l->occupied_size == l->capacity) {
        expand_deque(l);
    }

    if(l->is_reversed) {
        l->is_reversed = false;
        push_left(l, v);
        l->is_reversed = true;
        return;
    }

    // non-reversed logic simply puts the new value at the calculated back index then increments occupied size
    // note that back does not need to be set as our list does not have a back variable
    if(!l->is_reversed) {
        int back = (l->front + l->occupied_size) % l->capacity;
        l->data[back] = v;
        l->occupied_size++;
        return;
    }
}

// O(1) amortized
bool pop_left(list *l) {
    if(l->occupied_size == 0) {
        return false;
    }

    // shrinks when popping from a list that contains less than (as of 2024.12.29) a third of the max capacity
    if(l->occupied_size < l->capacity / HYSTERESIS_FACTOR) {
        shrink_deque(l);
    }

    if(l->is_reversed) {
        l->is_reversed = false;
        pop_right(l);
        l->is_reversed = true;
        return true;
    }

    if(!l->is_reversed) {
        l->front = (l->front + 1) % l->capacity;        // unsure abt this formula
        l->occupied_size -= 1;
        return true;
    }
}

// once size is less than 1/3 of capacity, the next pop will resize the deque
// O(1) amortized
bool pop_right(list *l) {
    if(l->occupied_size == 0) {
        return false;
    }
    
    // shrinks when popping from a list that contains less than (as of 2024.12.29) a third of the max capacity
    if(l->occupied_size < l->capacity / HYSTERESIS_FACTOR) {
        shrink_deque(l);
    }

    if(l->is_reversed) {
        l->is_reversed = false;
        pop_left(l);
        l->is_reversed = true;
        return true;
    }

    if(!l->is_reversed) {
        int back = (l->front + l->occupied_size) % l->capacity - 1;         // the -1 is important since this operation lands the back index to the index to the right of the last occupied index
        l->data[back] = -1;
        l->occupied_size -= 1;
        return true;
    }
}

// O(1) worst-case
int64_t peek_left(list *l) {
    if(l->occupied_size == 0) {
        printf("ERROR: cannot peek from list of size 0");
        assert(0 != 0);
        return -1;
    }

    if(l->is_reversed) {
        l->is_reversed = false;
        int64_t ret = peek_right(l);
        l->is_reversed = true;
        return ret;
    }

    if(!l->is_reversed) {
        return l->data[l->front];
    }
}

// O(1) worst-case
int64_t peek_right(list *l) {
    if(l->occupied_size == 0) {
        printf("ERROR: cannot peek from list of size 0");
        assert(0 != 0);
        return -1;
    }
    
    if(l->is_reversed) {
        l->is_reversed = false;
        int64_t ret = peek_left(l);
        l->is_reversed = true;
        return ret;
    }

    if(!l->is_reversed) {
        // the modulo calculation lands the right index as the index to the right of the last occupied index (meaning it points to an empty index)
        return l->data[((l->front + l->occupied_size) % l->capacity) - 1];
    }
}

// O(1) worst-case
int size(list *l) {
    return l->occupied_size;
}

// O(1) worst-case
bool empty(list *l) {
    return (l->occupied_size == 0) ? true : false;
}

// O(1) worst-case
int64_t get(list *l, int i) {
    int index; 

    if(!l->is_reversed) {
        index = (l->front + i) % l->capacity;

        // OOB check UNSURE
        if(index + 1 > (l->front + l->occupied_size) % l->capacity) {
            printf("get index is out of bounds");
            assert(0 != 0);
            return -1;
        }

        // if in bounds
        return l->data[index];
    }

    if(l->is_reversed) {
        index = (l->front + l->occupied_size - 1 - i) % l->capacity;        //unsure abt this formula
        
        // OOB check UNSURE
        if(index < l->front) {
            printf("get index is out of bounds");
            assert(0 != 0);
            return -1;
        }

        //if in bounds
        return l->data[index];
    }
}

// O(1) worst-case
void set(list *l, int i, int64_t v) {
    int index;

    if(!l->is_reversed) {
        index = (l->front + i) % l->capacity;
        
        // CHECK FOR OOB
        if(index + 1 > (l->front + l->occupied_size) % l->capacity) {
            printf("set index is out of bounds");
            assert(0 != 0);
            return -1;
        }

        // if in bounds
        l->data[index] = v;
        return;
    }

    if(l->is_reversed) {
        index = (l->front + l->occupied_size - 1 - i) % l->capacity;        //unsure abt this formula
        
        // OOB check UNSURE
        if(index < l->front) {
            printf("set index is out of bounds");
            assert(0 != 0);
            return -1;
        }

        // if in bounds
        l->data[index] = v;
        return;
    }
}

// O(1) worst-case
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
    pop_right(l);       // [0, 1, 2, -1, -1, -1, -1, -1, -1, -1]
    pop_right(l);       // [0, 1, -1, -1, -1, -1, -1, -1, -1, -1]
    pop_right(l);       // [0, -1, -1, -1, -1]
    pop_right(l);       // [-1, -1, -1, -1, -1]
    pop_right(l);       // [-1, -1, -1, -1, -1]

    push_right(l, 10);  // [10, -1, -1, -1, -1]
    push_right(l, 11);  // [10, 11, -1, -1, -1]
    push_right(l, 12);  // [10, 11, 12, -1, -1]
    push_right(l, 13);  // [10, 11, 12, 13, -1]
    push_right(l, 14);  // [10, 11, 12, 13, 14]
    push_right(l, 15);  // [10, 11, 12, 13, 14 ,15, 0, 0, 0, 0]
    push_right(l, 16);  // [10, 11, 12, 13, 14 ,15, 16, 0, 0, 0]
    temp = get(l, 5);   // 15
    temp = get(l, 6);   // 16
    temp = get(l, 7);   // should error
    temp = get(l, 8);   // should error
    return 0;
}
