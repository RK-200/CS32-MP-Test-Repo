#include "dll_node.h"
#include "doubly_linked_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// REMINDER: when adding functionality to the operations, keep in mind na reversed is a thing, most operations would require a regular and reversed implementation to maintain O(1) reversal
// REMINDER: dont forget to update size
// REMINDER: dont forget to free()

list *make(int n, int64_t *seq) {
    
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
    if(l->size == 0) {
        return false;
    }
    
    if(l->size == 1) {
        node* to_pop = l->left;
        l->left = NULL;
        l->right = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    if(!l->is_reversed) {
        node* to_pop = l->left;
        l->left = l->left->next;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    if(l->is_reversed) {            //unnecessary conditional but im keeping it for readability
        node* to_pop = l->right;
        l->right = l->right->prev;
        l->size -= 1;
        free(to_pop);
        return true;
    }
}

// O(1)
bool pop_right(list *l) {
    if(l->size == 0) {
        return false;
    }
    
    if(l->size == 1) {
        node* to_pop = l->left;
        l->left = NULL;
        l->right = NULL;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    if(l->is_reversed) {
        node* to_pop = l->left;
        l->left = l->left->next;
        l->size -= 1;
        free(to_pop);
        return true;
    }

    if(!l->is_reversed) {            //unnecessary conditional but im keeping it for readability
        node* to_pop = l->right;
        l->right = l->right->prev;
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
        printf("ERROR: index exceeds list size\n");
        return -1;
    }

    // iterate through list until specified index
    node* currNode = l->left;
    for(int counter = 0; counter < i; counter++) {
        currNode = currNode->next;
    }
    
    return currNode->data;
}

void set(list *l, int i, int64_t v);

// O(1)
void reverse(list *l) {
    l->is_reversed = !l->is_reversed;
}