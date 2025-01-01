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

    init_deque(d, n * 2, false);

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

    if(l->is_reversed) {
        l->is_reversed = false;
        pop_right(l);
        l->is_reversed = true;

    }

    if(!l->is_reversed) {
        l->data[l->front] = -1;
        l->front = (l->front + 1) % l->capacity;        // unsure abt this formula
        l->occupied_size -= 1;
    }

    // im putting this in the end now so it can properly put the index at i = 0 after a pop,, not that it really matters
    // shrinks when popping from a list that contains less than (as of 2024.12.29) a third of the max capacity
    if(l->occupied_size < l->capacity / HYSTERESIS_FACTOR) {
        shrink_deque(l);
    }

    return true;
}

// once size is less than 1/3 of capacity, the next pop will resize the deque
// O(1) amortized
bool pop_right(list *l) {
    if(l->occupied_size == 0) {
        return false;
    }

    if(l->is_reversed) {
        l->is_reversed = false;
        pop_left(l);
        l->is_reversed = true;
    }

    if(!l->is_reversed) {
        int back = (l->front + l->occupied_size) % l->capacity - 1;         // the -1 is important since this operation lands the back index to the index to the right of the last occupied index
        l->data[back] = -1;
        l->occupied_size -= 1;
    }

    // im putting this in the end now so it can properly put the index at i = 0 after a pop,, not that it really matters
    // shrinks when popping from a list that contains less than (as of 2024.12.29) a third of the max capacity
    if(l->occupied_size < l->capacity / HYSTERESIS_FACTOR) {
        shrink_deque(l);
    }

    return true;
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
        // if index is greater than rear index and list is not full
        if(index + 1 > (l->front + l->occupied_size) % l->capacity && l->occupied_size != l->capacity) {
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
        // if index is less than the front index and list is not full
        if(index < l->front && l->occupied_size != l->capacity) {
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
        // if index is greater than rear index and list is not full
        if(index + 1 > (l->front + l->occupied_size) % l->capacity && l->occupied_size != l->capacity) {
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
        // if index is less than the front index and list is not full
        if(index < l->front && l->occupied_size != l->capacity) {
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
    //temp = get(l, 7);   // should error
    //temp = get(l, 8);   // should error

    pop_right(l);       // [10, 11, 12, 13, 14 ,15, -1, 0, 0, 0]
    pop_left(l);        // [-1, 11, 12, 13, 14 ,15, -1, 0, 0, 0]
    pop_left(l);        // [-1, -1, 12, 13, 14 ,15, -1, 0, 0, 0]
    pop_left(l);        // [-1, -1, -1, 13, 14 ,15, -1, 0, 0, 0]
    pop_right(l);       // [-1, -1, -1, 13, 14 ,-1, -1, 0, 0, 0]
    pop_left(l);        // [14, 0, 0, 0, 0]
    pop_left(l);        // [0, 0]
    pop_right(l);       // [0, 0]
    pop_right(l);       // [0, 0]

    push_left(l, 10);   // [0, 10]
    push_right(l, 11);  // [11, 10]
    push_left(l, 12);   // [10, 11, 0, 12] note na it doesnt have to be represented as [12, 11, 10, 0] in memory 
    push_left(l, 13);   // [10, 11, 13, 12]
    push_left(l, 14);   // [13, 12, 10, 11, 0, 0, 0, 14]
    push_right(l, 15);  // [13, 12, 10, 11, 15, 0, 0, 14]
    push_left(l, 16);   // [13, 12, 10, 11, 15, 0, 16, 14]
    push_right(l, 17);  // [13, 12, 10, 11, 15, 17, 16, 14]
    push_right(l, 18);  // [16, 14, 13, 12, 10, 11, 15, 17, 18, 0, 0, 0, 0, 0, 0, 0]

    temp = get(l, 0);   // 16
    temp = get(l, 8);   // 18
    temp = get(l, 2);   // 13
    temp = get(l, 6);   // 15
    //temp = get(l, 10);  // should error 

    push_left(l, 19);   // [16, 14, 13, 12, 10, 11, 15, 17, 18, 0, 0, 0, 0, 0, 0, 19]
    push_left(l, 20);   // [16, 14, 13, 12, 10, 11, 15, 17, 18, 0, 0, 0, 0, 0, 20, 19]
    push_left(l, 21);   // [16, 14, 13, 12, 10, 11, 15, 17, 18, 0, 0, 0, 0, 21, 20, 19] index 13 front
    reverse(l);         // [16, 14, 13, 12, 10, 11, 15, 17, 18, 0, 0, 0, 0, 21, 20, 19] is_reversed = true
    push_left(l, 22);   // [16, 14, 13, 12, 10, 11, 15, 17, 18, 22, 0, 0, 0, 21, 20, 19] 
    push_left(l, 23);   // [16, 14, 13, 12, 10, 11, 15, 17, 18, 22, 23, 0, 0, 21, 20, 19]
    push_right(l, 24);  // [16, 14, 13, 12, 10, 11, 15, 17, 18, 22, 23, 0, 24, 21, 20, 19]  index 12 front
    push_right(l, 25);  // [16, 14, 13, 12, 10, 11, 15, 17, 18, 22, 23, 25, 24, 21, 20, 19] index 11 front (25) but its reversed so 25 is technically the back
    temp = get(l, 15);  // 25
    temp = get(l, 0);   // 23
    temp = get(l, 1);   // 22

    for(int i = 0; i < size(l); i++) {          
        set(l, i, i);                   // [10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11]
    }

    reverse(l);

    for(int i = 0; i < size(l); i++) {
        set(l, i, i);                   // [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4]
    }

    

    return 0;
}
