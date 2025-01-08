#include "skip_list_node.h"
#include "skip_list.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

// Randomly generates how many layers an element will be in
int generate_random_level(){ 
    int level = 0;
    while (rand() % P == 0 && level < MAX_HEIGHT - 1){
        level++;
    }
    return level;
}

// Returns how many elements are in the list
int size(list *l){
    return l->size;
}

// Returns if the list if empty or not
bool empty(list *l){
    return (l->size == 0);
}

// Inserts the input value v to the left of the list with a random number of layers
void push_left(list *l, int64_t v){
    // Reversed behavior instead inserts on the right
    if (l->reversed){
        l->reversed = false;
        push_right(l, v);
        l->reversed = true;
        return;
    }
    
    // Randomly generate number of layers of this element
    int level = generate_random_level(); 
    int current_level = level;

    // Set new height for the list if this element is now the tallest
    if (level > l->height){
        l->height = level;
    }

    int index;
    if (empty(l)){
        index = 0; // Index starts at zero for the first element
    }
    else{
        index = l->heads[0]->index - 1; // Index is the next index minus 1
    }

    // Initialize the new node
    node* new_node = create_node(v, level, index);
    node* node_above = new_node;
    l->size++;
    
    while (current_level >= 0){
        // Case if node is the first in this layer
        if (l->heads[current_level] == NULL && l->tails[current_level] == NULL){
            l->heads[current_level] = new_node;
            l->tails[current_level] = new_node;
        }
        // 
        else{
            new_node->next = l->heads[current_level];
            l->heads[current_level]->prev = new_node;
            l->heads[current_level] = new_node;
        }

        // Generate a node below if not in the bottommost layer
        if (current_level > 0){
            new_node = create_node(v, level, index);
            node_above->below = new_node;
            node_above = new_node;
        }
        current_level--;
    }

    return;
}

void push_right(list *l, int64_t v){
    // Reversed behavior instead inserts on the right
    if (l->reversed){
        l->reversed = false;
        push_left(l, v);
        l->reversed = true;
        return;
    }

    // Randomly generate number of layers of this element
    int level = generate_random_level(); 
    int current_level = level;

    // Set new height for the list if this element is now the tallest    
    if (level > l->height){
        l->height = level;
    }


    int index;
    if (empty(l)){
        index = 0;
    }
    else{
        index = l->tails[0]->index + 1; // Index is the previous index plus 1
    }

    // Initialize the new node
    node* new_node = create_node(v, level, index);

    l->size++;
    
    node* node_above = new_node;

    while (current_level >= 0){
        // Case if node is the first in this layer
        if (l->heads[current_level] == NULL && l->tails[current_level] == NULL){
            l->heads[current_level] = new_node;
            l->tails[current_level] = new_node;
        }
        else{
            new_node->prev = l->tails[current_level];
            l->tails[current_level]->next = new_node;
            l->tails[current_level] = new_node;
        }

        // Generate a node below if not in the bottommost layer
        if (current_level > 0){
            new_node = create_node(v, level, index);
            node_above->below = new_node;
            node_above = new_node;
        }
        current_level--;
    }
}

// Initializes a new skip list from the given input sequence
list *make(int n, int64_t *seq){
    list* l = (list*) malloc(sizeof(list));
    l->size = 0;
    l->height = 0;
    l->heads = calloc(sizeof(node*), MAX_HEIGHT);
    l->tails = calloc(sizeof(node*), MAX_HEIGHT);
    l->reversed = false;

    // Sets a seed for randomization if SEED is non-zero
    if (SEED){
        srand(SEED);
    }

    // Push each element in seq in order
    for (int i = 0; i < n; i++){
        push_right(l, seq[i]);
    }
    return l;
}

// Remove the leftmost element from the list; Returns false if the list is empty
bool pop_left(list *l){
    if (empty(l)){
        return false;
    }
    else{
        // Pop from the right if list is reversed
        if (l->reversed){
            l->reversed = false;
            bool ret = pop_right(l);
            l->reversed = true;
            return ret;
        }
        // Start at the topmost node of the leftmost element
        node* current = l->heads[l->heads[0]->level]; 
        int current_level = current->level;

        while (current_level >= 0){
            // If there is an element to the right
            if (current->next){
                current->next->prev = NULL;
                l->heads[current_level] = current->next;
            }
            // Otherwise, this layer will be empty after popping
            else{ 
                l->height--;
                l->heads[current_level] = NULL;
                l->tails[current_level] = NULL;
            }
            
            // Move to the node below it
            node* node_below = current->below;
            free(current);
            current = node_below;

            current_level--;
        }

        l->size--;
        return true;
    }
}

// Remove the rightmost element from the list; Returns false if the list is empty
bool pop_right(list *l){
    if (empty(l)){
        return false;
    }
    else{
        // Pop from the right if list is reversed
        if (l->reversed){
            l->reversed = false;
            bool ret = pop_left(l);
            l->reversed = true;
            return ret;
        }

        node* current = l->tails[l->tails[0]->level]; // Start at the topmost node of the rightmost element
        int current_level = current->level;

        while (current_level >= 0){
            // If there is an element to the right
            if (current->prev){
                current->prev->next = NULL;
                l->tails[current_level] = current->prev;
            }
            // Otherwise, this layer will be empty after popping
            else{ 
                l->height--;
                l->heads[current_level] = NULL;
                l->tails[current_level] = NULL;
            }

            // Move to the node below it
            node* node_below = current->below;
            free(current);
            current = node_below;

            current_level--;
        }
        l->size--;
        return true;
    }
}

// Returns the value of the leftmost element
int64_t peek_left(list *l){
    if (empty(l)){
        printf("ERROR: list is empty!");
        assert(0 != 0);
        return -1;
    }
    // Instead returns the rightmost value if list is reversed
    if (l->reversed){
        l->reversed = false;
        int64_t ret = peek_right(l);
        l->reversed = true;
        return ret;
    }
    return l->heads[0]->val;
}

// Returns the value of the leftmost element
int64_t peek_right(list *l){
    if (empty(l)){
        printf("ERROR: list is empty!");
        assert(0 != 0);
        return -1;
    }
    // Instead returns the leftmost value if list is reversed
    if (l->reversed){
        l->reversed = false;
        int64_t ret = peek_left(l);
        l->reversed = true;
        return ret;
    }
    else{
        return l->tails[0]->val;
    }   
}

// Returns the topmost node of the element at index i
node* get_node_at_i(list* l, int i){
    if (0 <= i && i < l->size){
        node* current = l->heads[l->height];

        int _i = l->heads[0]->index + i; // Adjust index being searched for to stored index

        // Used to prevent looping if index is between two elements in the same layer
        bool left_checked = false;
        bool right_checked = false;

        while (_i != current->index){
            // Element must be to its left
            if (_i < current->index){ 
                if (current->prev){ // Move to the left element, if it exists
                    current = current->prev;
                    left_checked = true;
                }
                // If there is no element to the right, go down a layer
                else{ 
                    while(current->prev == NULL){
                        current = current->below;
                        left_checked = false;
                        right_checked = false;
                    }
                }
            }
            // Otherwise, it must be to the right
            else if (_i > current->index){ 
                // Move to the right element, if it exists
                if (current->next){ 
                    current = current->next;
                    right_checked = true;
                }
                // If there is no element to the right, go down a layer
                else{ 
                    while(current->next == NULL){
                        current = current->below;
                        left_checked = false;
                        right_checked = false;
                    }
                }
            }
            // Element is not in this layer, go down
            if (right_checked && left_checked){ 
                current = current->below;
                left_checked = false;
                right_checked = false;
            }
        }
        return current;
    }
    
    return NULL;
}

// Returns the value of the node at index i
int64_t get(list *l, int i){
    node* node_at_i;
    if (l->reversed){
        // Index counting starts from the right if list is reversed
        node_at_i = get_node_at_i(l, l->size - i - 1);
    }
    else{
        node_at_i = get_node_at_i(l, i);
    }
    if (node_at_i){
        return node_at_i->val;
    }
    else{
        printf("ERROR: index is out of bounds!");
        assert(0 != 0);
        return -1;
    }
}

// Sets the value of all nodes at index i to v
void set(list *l, int i, int64_t v){
    node* node_at_i = NULL;
    if (l->reversed){
        node_at_i = get_node_at_i(l, l->size - i - 1);
    }
    else{
        node_at_i = get_node_at_i(l, i);
    }

    if (node_at_i){
        while (node_at_i){ // Change node values starting from the top
            node_at_i->val = v;
            node_at_i = node_at_i->below;
        }
        return;
    }
    else{
        printf("ERROR: index is out of bounds!");
        assert(0 != 0);
        return;
    }
}

// Reverses the list
void reverse(list *l){
    l->reversed = !l->reversed;
}

// For debugging (doesn't print in reversed btw)
void print_list(list* l){
    if (empty(l)){
        printf("list is empty\n");
        return;
    }
    printf("list: \n");

    for (int i = l->height; i >= 0; i--){
        if (l->heads[i]->prev == NULL) printf("NULL -> ");
        node* current = l->heads[i];
        while (current){
            printf("%lld -> ", current->val);
            current = current->next;
        }
        if (current == NULL) printf("NULL");
        printf("\n");
    }

    node* current = l->heads[0];
    printf("indices: ");
    for (int i = 0; i < size(l); i++){
        
        printf("%d ", current->index);
        current = current->next;
    }
    printf("\n \n");
}

// Temporary testing code
int main(void){
    int n = 64;
    int64_t* arr = (int64_t*) malloc(sizeof(int64_t) * n);
    for (int i = 0; i < n; i++){
        arr[i] = i;
    }

    list* l = make(n, arr);
    print_list(l);
    assert(peek_left(l) == 0);
    pop_left(l);
    print_list(l);
    assert(peek_right(l) == 63);
    assert(peek_left(l) == 1);

    pop_right(l);
    print_list(l);

    assert(get(l, 0) == 1);
    pop_left(l);
    pop_left(l);
    pop_left(l);
    pop_left(l);

    for (int i = 0; i < 13; i++){
        pop_left(l);
    }

    print_list(l);
    assert(l->height == 3);
    assert(peek_left(l) == 18);
    assert(peek_right(l) == 62);
    assert(get(l, 0) == 18);
    assert(get(l, 1) == 19);
    assert(get(l, 2) == 20);
    assert(get(l, 16) == 34);
    set(l, 8, 26);

    print_list(l);

    for (int i = 0; i < 37; i++){
        pop_right(l);
    }

    print_list(l);

    assert(get(l, 3) == 21);
    for (int i = 0; i < 8; i++){
        pop_right(l);
    }

    assert(empty(l));

    for (int i = 0; i < 20; i++){
        if (i % 2 == 0){
            push_left(l, i);
        }
        else{
            push_right(l, i);
        }
    }

    print_list(l);

    reverse(l);
    assert(peek_left(l) == 19);
    assert(peek_right(l) == 18);
    
    for (int i = 0; i < 4; i++){
        pop_right(l);
    }

    print_list(l);
    
    assert(peek_right(l) == 10);
    assert(get(l, 15) == 10);
    assert(get(l, 14) == 8);
    assert(get(l, 13) == 6);
    assert(get(l, 12) == 4);

    reverse(l);
    assert(peek_left(l) == 10);
    assert(size(l) == 16);
    assert(!empty(l));
    
    for (int i = 0; i < 16; i++){
        assert(pop_left(l));
    }

    assert(empty(l));
    assert(size(l) == 0);
    print_list(l);

    int64_t q[] = {1};
    list* a = make(0, q);
    for (int i = 0; i < 10; i++){
        push_left(a, i);
    }
    for (int i = 0; i < 3; i++){
        pop_right(a);
    }
    assert(get(a, 2) == 7);
    print_list(a);
}