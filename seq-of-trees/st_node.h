#ifndef ST_NODE_H
#define ST_NODE_H

#include <stdlib.h>
#include <stdint.h>

typedef struct Node{
    int degree;
    int64_t val;
    struct Node* left_child;
    struct Node* right_child;
    struct Node* left;
    struct Node* right;

}node;
node* new_node(int64_t val);


#endif