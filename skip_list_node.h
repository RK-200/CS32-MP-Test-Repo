#ifndef SKIP_LIST_NODE_H
#define SKIP_LIST_NODE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct node{
    int64_t val;
    struct node* prev;
    struct node* next;
    struct node* below;
    int level; // stores how many layers this element is in
    int index;
} node;

node* create_node(int64_t v, int l, int i);

// returns a node with value v
node* create_node(int64_t v, int l, int i){ 
    node* new_node = (node*) malloc(sizeof(node));
    new_node->val = v;
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->below = NULL;
    new_node->level = l;
    new_node->index = i;

    return new_node;
}

#endif