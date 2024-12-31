#include "skip_list_node.h"
#include "skip_list.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

const uint32_t SEED = 1000; // fixed seed for testing (can be removed)
const uint32_t MAX_HEIGHT = 32; // sets maximum number of layers the skip list can reach
const int P = 2; // probability for element to be added to another layer is 1/P

int generate_random_level(){ // randomly generates how many layers an element will be in
    int level = 0;
    while (rand() % P == 0 && level < MAX_HEIGHT - 1){
        level++;
    }
    return level;
}

int size(skip_list *l){
    return l->size;
}

bool empty(skip_list *l){
    return (l->size == 0);
}

void push_left(skip_list *l, int64_t v){
    if (l->reversed){
        l->reversed = false;
        push_right(l, v);
        l->reversed = true;
        return;
    }

    int level = generate_random_level(); // randomly generate number of layers of this element
    int current_level = level;

    if (level > l->height){
        l->height = level;
    }

    int index;
    if (empty(l)){
        index = 0;
    }
    else{
        index = l->heads[0]->index - 1; // sets index to the next index minus 1
    }

    // initialize the new node
    node* new_node = create_node(v, level, index);
    
    l->size++;
    
    node* node_above = new_node;
    
    while (current_level >= 0){
        // case if node is the first in this layer
        if (l->heads[current_level] == NULL && l->tails[current_level] == NULL){
            l->heads[current_level] = new_node;
            l->tails[current_level] = new_node;
        }
        else{
            new_node->next = l->heads[current_level];
            l->heads[current_level]->prev = new_node;
            l->heads[current_level] = new_node;
        }

        if (current_level > 0){
            new_node = create_node(v, level, index);
            node_above->below = new_node;
            node_above = new_node;
        }
        current_level--;
    }
}

void push_right(skip_list *l, int64_t v){
    if (l->reversed){
        l->reversed = false;
        push_left(l, v);
        l->reversed = true;
        return;
    }

    int level = generate_random_level(); // randomly generate number of layers of this element
    int current_level = level;

    if (level > l->height){
        l->height = level;
    }
    int index;
    if (empty(l)){
        index = 0;
    }
    else{
        index = l->tails[0]->index + 1; // sets index to 1 plus the previous index
    }

    // initialize the new node
    node* new_node = create_node(v, level, index);

    l->size++;
    
    node* node_above = new_node;

    while (current_level >= 0){
        // case if node is the first in this layer
        if (l->heads[current_level] == NULL && l->tails[current_level] == NULL){
            l->heads[current_level] = new_node;
            l->tails[current_level] = new_node;
        }
        else{
            new_node->prev = l->tails[current_level];
            l->tails[current_level]->next = new_node;
            l->tails[current_level] = new_node;
        }

        if (current_level > 0){
            new_node = create_node(v, level, index);
            node_above->below = new_node;
            node_above = new_node;
        }
        current_level--;
    }
}

skip_list *make(int n, int64_t *seq){
    skip_list* l = (skip_list*) malloc(sizeof(skip_list));
    l->size = 0;
    l->height = 0;
    l->heads = calloc(sizeof(node*), MAX_HEIGHT);
    l->tails = calloc(sizeof(node*), MAX_HEIGHT);
    l->reversed = false;

    srand(SEED);

    for (int i = 0; i < n; i++){
        push_right(l, seq[i]);
    }
    return l;
}

bool pop_left(skip_list *l){
    if (empty(l)){
        return false;
    }
    else{
        if (l->reversed){
            l->reversed = false;
            bool ret = pop_right(l);
            l->reversed = true;
            return ret;
        }

        node* current = l->heads[l->heads[0]->level]; // start at the topmost node
        int current_level = current->level;
       
        while (current_level >= 0){
            if (current->next){
                current->next->prev = NULL;
                l->heads[current_level] = current->next;
            }
            else if (current->prev == NULL){ // layer is now empty
                l->height--;
                l->heads[current_level] = NULL;
                l->tails[current_level] = NULL;
            }
            
            node* node_below = current->below;
            free(current);
            current = node_below;

            current_level--;
        }

        l->size--;
        return true;
    }
}

bool pop_right(skip_list *l){
    if (empty(l)){
        return false;
    }
    else{
        if (l->reversed){
            l->reversed = false;
            bool ret = pop_left(l);
            l->reversed = true;
            return ret;
        }

        node* current = l->tails[l->tails[0]->level]; // start at the topmost node
        int current_level = current->level;

        while (current_level >= 0){
            if (current->prev){
                current->prev->next = NULL;
                l->tails[current_level] = current->prev;
            }
            else if (current->next == NULL){ // layer is empty after popping
                l->height--;
                l->heads[current_level] = NULL;
                l->tails[current_level] = NULL;
            }

            node* node_below = current->below;
            free(current);
            current = node_below;

            current_level--;
        }

        l->size--;
        return true;
    }
}

int64_t peek_left(skip_list *l){
    if (l->reversed){
        l->reversed = false;
        int64_t ret = peek_right(l);
        l->reversed = true;
        return ret;
    }
    return l->heads[0]->val;
}

int64_t peek_right(skip_list *l){
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

node* get_node_at_i(skip_list* l, int i){ // returns node at index i
    if (0 <= i && i < l->size){
        node* current = l->heads[l->height];

        int _i = l->heads[0]->index + i; // adjust index being searched for to stored index

        bool left_checked = false;
        bool right_checked = false;

        while (_i != current->index){
            if (_i < current->index){ // element must be to its left
                if (current->prev){ // move to the left element, if it exists
                    current = current->prev;
                    left_checked = true;
                }
                else{ // if there is no element to its left, keep going down layers until there is
                    while(current->prev == NULL){
                        current = current->below;
                        left_checked = false;
                        right_checked = false;
                    }
                }
            }
            else if (_i > current->index){ // otherwise, it must be to the right
                if (current->next){ // move to the right element, if it exists
                    current = current->next;
                    right_checked = true;
                }
                else{ // if there is no element to the right, go down a layer
                    while(current->next == NULL){
                        current = current->below;
                        left_checked = false;
                        right_checked = false;
                    }
                }
            }
            if (right_checked && left_checked){ // element is not in this layer, go down
                current = current->below;
                left_checked = false;
                right_checked = false;
            }
        }
        return current;
    }

    printf("ERROR: index is out of bounds!");
    return NULL;
}

int64_t get(skip_list *l, int i){
    if (l->reversed){
        return get_node_at_i(l, l->size - i - 1)->val;
    }
    else{
        return get_node_at_i(l, i)->val;
    }
}

void set(skip_list *l, int i, int64_t v){
    node* current = NULL;
    if (l->reversed){
        current = get_node_at_i(l, l->size - i - 1);
    }
    else{
        current = get_node_at_i(l, i);
    }
    while (current){ // change node values starting from the top
        current->val = v;
        current = current->below;
    }
}

void reverse(skip_list *l){
    l->reversed = !l->reversed;
}

//for debugging (doesn't print in reversed btw)
void print_list(skip_list* l){
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

// temporary testing code
int main(void){
    int n = 64;
    int64_t* arr = (int64_t*) malloc(sizeof(int64_t) * n);
    for (int i = 0; i < n; i++){
        arr[i] = i;
    }

    skip_list* l = make(n, arr);
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
}