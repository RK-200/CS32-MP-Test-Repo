#include "dll_node.h"
#include "doubly_linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <inttypes.h>   // for printing  int64_t's

// REMINDER: when adding functionality to the operations, keep in mind na reversed is a thing, most operations would require a regular and reversed implementation to maintain O(1) reversal
// REMINDER: dont forget to update size
// REMINDER: dont forget to free()

// O(list size)
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

// O(1)
void push_left(list *l, int64_t v) {
    //empty behaviour
    if(l->size == 0) {
        node* new_node = createNode(v);
        l->left = new_node;
        l->right = new_node;
        l->size += 1;
        return;
    }

    //not reversed behaviour
    if(!l->is_reversed) {
        node* new_node = createNode(v);
        new_node->next = l->left;
        l->left->prev = new_node;
        l->left = new_node;
        l->size += 1;
        return;
    }
    //reversed behaviour
    if(l->is_reversed) {
        node* new_node = createNode(v);
        new_node->prev = l->right;
        l->right->next = new_node;
        l->right = new_node;
        l->size += 1;
        return;
    }
}

// O(1)
void push_right(list *l, int64_t v) {
    //empty behaviour
    if(l->size == 0) {
        node* new_node = createNode(v);
        l->left = new_node;
        l->right = new_node;
        l->size += 1;
        return;
    }

    //reversed behaviour
    if(l->is_reversed) {
        node* new_node = createNode(v);
        new_node->next = l->left;
        l->left->prev = new_node;
        l->left = new_node;
        l->size += 1;
        return;
    }
    //not reversed behaviour
    if(!l->is_reversed) {
        node* new_node = createNode(v);
        new_node->prev = l->right;
        l->right->next = new_node;
        l->right = new_node;
        l->size += 1;
        return;
    }
}

// O(1)
bool pop_left(list *l) {
    // if size is 0, return false
    if(l->size == 0) {
        return false;
    }
    
    // if size is 1, left and right are set to NULL
    if(l->size == 1) {
        node* to_pop = l->left;
        l->left = NULL;
        l->right = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    // regular logic
    if(!l->is_reversed) {
        node* to_pop = l->left;
        l->left = l->left->next;
        l->left->prev = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    // reversed logic
    if(l->is_reversed) {            //unnecessary conditional but im keeping it for readability
        node* to_pop = l->right;
        l->right = l->right->prev;
        l->right->next = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }
}

// O(1)
bool pop_right(list *l) {
    // if size is 0, return false
    if(l->size == 0) {
        return false;
    }
    
    // if size is 1, left and right are set to NULL
    if(l->size == 1) {
        node* to_pop = l->left;
        l->left = NULL;
        l->right = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    // reversed logic
    if(l->is_reversed) {
        node* to_pop = l->left;
        l->left = l->left->next;
        l->left->prev = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    // regular logic
    if(!l->is_reversed) {            //unnecessary conditional but im keeping it for readability
        node* to_pop = l->right;
        l->right = l->right->prev;
        l->right->next = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }
}

// O(1)
int64_t peek_left(list *l) {
    if(l->size == 0) {
        printf("ERROR: cannot peek from empty list");
        return -1;
    }
    return (l->is_reversed) ? l->right->data : l->left->data;
}

// O(1)
int64_t peek_right(list *l) {
    if(l->size == 0) {
        printf("ERROR: cannot peek from empty list");
        return -1;
    }
    return (l->is_reversed) ? l->left->data : l->right->data;
}

// O(1)
int size(list *l) {
    return l->size;
}

// O(1)
bool empty(list *l) {
    return (l->size == 0) ? true : false;
}


// O(n) worst case
int64_t get(list *l, int i) {
    // error if list is empty
    if(l->size == 0) {
        printf("ERROR: cannot get element from empty list\n");
        return -1;
    }

    // error if index is bigger than list
    if(l->size <= i) {
        printf("ERROR: get index exceeds list size\n");
        return -1;
    }

    node* currNode = l->left;
    // regular logic
    if(!l->is_reversed) {
        for(int counter = 0; counter < i; counter++) {
            currNode = currNode->next;
        }
    }

    // reversed logic
    else {
        i = l->size - i - 1;
        for(int counter = 0; counter < i; counter++) {
            currNode = currNode->next;
        }
    }
    
    return currNode->data;
}

// O(n)
void set(list *l, int i, int64_t v) {
    // error if list is empty
    if(l->size == 0) {
        printf("ERROR: cannot set element in empty list\n");
        return -1;
    }

    // error if index is bigger than list
    if(l->size <= i) {
        printf("ERROR: set index exceeds list size\n");
        return -1;
    }

    node* currNode = l->left;
    // regular logic
    if(!l->is_reversed) {
        for(int counter = 0; counter < i; counter++) {
            currNode = currNode->next;
        }
    }

    // reversed logic
    else {
        i = l->size - i - 1;
        for(int counter = 0; counter < i; counter++) {
            currNode = currNode->next;
        }
    }
    
    currNode->data = v;
    
    return;
}

// O(1)
void reverse(list *l) {
    l->is_reversed = !l->is_reversed;
}

void print_list(list* l) {
    printf("size: %d || reversed? %d \ncontains: ", l->size, l->is_reversed);
    for(int i = 0; i < l->size; i++) {
        printf("%"PRId64, get(l, i));
        printf(" ");
    }
    printf("\n");
    return;
}

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
