#ifndef DLL_NODE_H
#define DLL_NODE_H

#include <stdlib.h>
#include <stdint.h>

// These nodes are linked together to form a doubly linked list.
typedef struct node {
    int64_t data;
    struct node* next;
    struct node* prev;
} node;

// Returns a node initialized with data and with both sides pointing to NULL.
node* createNode(int64_t data) {
    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

#endif