#include "dll_node.h"
#include "doubly_linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>

/* Initializes a dynamic list with a doubly linked list backing.
O(len(seq)) worst-case */
list* make(int n, int64_t *seq) {
    list* ptr_list = (list*) malloc(sizeof(list));
    ptr_list->left = NULL;
    ptr_list->right = NULL;
    ptr_list->is_reversed = false;
    ptr_list->size = 0;

    for(int i = 0; i < n; i++) {
        push_right(ptr_list, seq[i]);
    }
    return ptr_list;
}

/* Inserts the value v to the left, so that it becomes the leftmost value. 
O(1) worst-case */
void push_left(list *l, int64_t v) {
    // Special handling for an empty list
    if(l->size == 0) {
        node* new_node = createNode(v);
        l->left = new_node;
        l->right = new_node;
        l->size += 1;
        return;
    }

    // Non-reversed behaviour creates a new node, sets it as the left to the current leftmost node, then sets it as the new leftmost node
    if(!l->is_reversed) {
        node* new_node = createNode(v);
        new_node->next = l->left;
        l->left->prev = new_node;
        l->left = new_node;
        l->size += 1;
        return;
    }

    // Reversed logic uses the non-reversed implementation of push_right()
    if(l->is_reversed) {
        l->is_reversed = false;
        push_right(l, v);
        l->is_reversed = true;
        return;
    }
}

/* Inserts the value v to the right, so that it becomes the rightmost value. 
O(1) worst-case */
void push_right(list *l, int64_t v) {
    // Special handling for an empty list
    if(l->size == 0) {
        node* new_node = createNode(v);
        l->left = new_node;
        l->right = new_node;
        l->size += 1;
        return;
    }

    // Reversed logic uses the non-reversed implementation of push_left()
    if(l->is_reversed) {
        l->is_reversed = false;
        push_left(l, v);
        l->is_reversed = true;
        return;
    }
    
    // Non-reversed behaviour creates a new node, sets it as the right to the current rightmost node, then sets it as the new rightmost node
    if(!l->is_reversed) {
        node* new_node = createNode(v);
        new_node->prev = l->right;
        l->right->next = new_node;
        l->right = new_node;
        l->size += 1;
        return;
    }
}

/* Sets the new leftmost node as the node to the right of the old leftmost then frees the old leftmost node. Has a special case for a list of size 1.
Returns whether the operation was successful or not. 
O(1) worst-case */
bool pop_left(list *l) {
    // If size is 0, return false
    if(l->size == 0) {
        return false;
    }
    
    // If size is 1, left and right are set to NULL
    if(l->size == 1) {
        node* to_pop = l->left;
        l->left = NULL;
        l->right = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    // Non-reversed logic
    if(!l->is_reversed) {
        node* to_pop = l->left;
        l->left = l->left->next;
        l->left->prev = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    // Reversed logic uses the non-reversed implementation of pop_right()
    if(l->is_reversed) {            
        l->is_reversed = false;
        pop_right(l);
        l->is_reversed = true;
    }
}

/* Sets the new rightmost node as the node to the left of the old rightmost then frees the old rightmost node. Has a special case for a list of size 1.
Returns whether the operation was successful or not. 
O(1) worst-case */
bool pop_right(list *l) {
    // If size is 0, return false
    if(l->size == 0) {
        return false;
    }
    
    // If size is 1, left and right are set to NULL
    if(l->size == 1) {
        node* to_pop = l->left;
        l->left = NULL;
        l->right = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    // Reversed logic uses the non-reversed implementation of pop_left()
    if(l->is_reversed) {
        l->is_reversed = false;
        pop_left(l);
        l->is_reversed = true;
        return true;
    }

    // regular logic
    if(!l->is_reversed) {    
        node* to_pop = l->right;
        l->right = l->right->prev;
        l->right->next = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }
}

/*  Returns the value at the leftmost index. Prints an error message, fails an assertion, and returns -1 if there is no leftmost element. 
O(1) worst-case*/
int64_t peek_left(list *l) {
    if(l->size == 0) {
        printf("ERROR: cannot peek from empty list");
        assert(0 != 0);
        return -1;
    }
    return (l->is_reversed) ? l->right->data : l->left->data;
}

/* Returns the value at the rightmost index. Prints an error message, fails an assertion, and returns -1 if there is no rightmost element. 
O(1) worst-case*/
int64_t peek_right(list *l) {
    if(l->size == 0) {
        printf("ERROR: cannot peek from empty list");
        assert(0 != 0);
        return -1;
    }
    return (l->is_reversed) ? l->left->data : l->right->data;
}

/* Returns the number of elements currently in the list. 
O(1) worst-case */
int size(list *l) {
    return l->size;
}

/* Returns whether the list is currently empty or not. 
O(1) worst-case */
bool empty(list *l) {
    return (l->size == 0) ? true : false;
}


/* Returns the element at index i provided that 0 <= i < occupied_size. If i is out of bounds, prints an error, fails an assertion, and returns -1.
O(n) worst-case */
int64_t get(list *l, int i) {
    // Error if list is empty
    if(l->size == 0) {
        printf("ERROR: cannot get element from empty list\n");
        assert(0 != 0);
        return -1;
    }

    // Error if index is bigger than list
    if(l->size <= i) {
        printf("ERROR: get index exceeds list size\n");
        assert(0 != 0);
        return -1;
    }

    node* currNode = l->left;

    // Regular logic increments i times from the left
    if(!l->is_reversed) {
        for(int counter = 0; counter < i; counter++) {
            currNode = currNode->next;
        }
    }

    // Reversed logic increments size - i - 1 times from the left
    else {
        i = l->size - i - 1;
        for(int counter = 0; counter < i; counter++) {
            currNode = currNode->next;
        }
    }
    
    return currNode->data;
}

/* Sets the element at index i to v provided that 0 <= i < occupied_size. If i is out of bounds, prints an error, fails an assertion, and does nothing.
O(n) worst-case */
void set(list *l, int i, int64_t v) {
    // Error if list is empty
    if(l->size == 0) {
        printf("ERROR: cannot set element in empty list\n");
        assert(0 != 0);
        return;
    }

    // Error if index is bigger than list
    if(l->size <= i) {
        printf("ERROR: set index exceeds list size\n");
        assert(0 != 0);
        return;
    }

    node* currNode = l->left;
    // Regular logic increments i times from the left
    if(!l->is_reversed) {
        for(int counter = 0; counter < i; counter++) {
            currNode = currNode->next;
        }
    }

    // Reversed logic increments size - i - 1 times from the left
    else {
        i = l->size - i - 1;
        for(int counter = 0; counter < i; counter++) {
            currNode = currNode->next;
        }
    }
    
    currNode->data = v;
    return;
}

/* Reverses the list. 
O(1) worst-case */
void reverse(list *l) {
    l->is_reversed = !l->is_reversed;
}

/*
int main()
{
    int64_t input[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list* l = make(10, input);
    // [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    for(int i = 0; i < 5; i++) {    
        pop_left(l);
    }
    // [5, 6, 7, 8, 9]


    for(int i = 0; i < 5; i++) {    
        pop_left(l);
    }
    // [5, 6, 7, 8, 9]

    for(int i = 10; i < 15; i++) {
        push_right(l, i);
    }
    // [10, 11, 12, 13, 14]

    for(int i = 9; i > 4; i--) {
        push_left(l, i);
    }
    // [5, 6, 7, 8, 9, 10, 11, 12, 13, 14]

    for(int i = 0; i < 8; i++) {
        (i % 2 == 0) ? pop_left(l) : pop_right(l);
    }
    // [9, 10]
    int64_t temp;
    temp = peek_left(l);    // 9
    temp = peek_right(l);   // 10
    temp = size(l);         // 2
    temp = empty(l);        // 0

    for(int i = 99; i < 111; i++) {
        (i % 2 != 0) ? push_left(l, i) : push_right(l, i);
    }
    // [109, 107, 105, 103, 101, 99, 9, 10, 100, 102, 104, 106, 108, 110]

    temp = peek_left(l);    // 109
    temp = peek_right(l);   // 110
    temp = size(l);         // 14
    temp = empty(l);        // 0

    temp = get(l, 9); // 102
    temp = get(l, 3); // 103

    set(l, 1, 50);          // [109, 50, 105, 103, 101, 99, 9, 10, 100, 102, 104, 106, 108, 110]
    set(l, 8, 51);          // [109, 102, 105, 103, 101, 99, 9, 10, 51, 102, 104, 106, 108, 110]
    set(l, 9, 52);          // [109, 102, 105, 103, 101, 99, 9, 10, 51, 52, 104, 106, 108, 110]
    set(l, 3, 53);          // [109, 102, 105, 53, 101, 99, 9, 10, 51, 102, 104, 106, 108, 110]


    return 0;
}
*/