# Doubly Linked List Proof Sketch

## 0. Introduction and Summary of Time Complexities

This file is a compilation of brief proofs for the asymptotic behaviour of our doubly linked list implementation of a dynamic list. The following table summarizes the expected time complexities based on the specifications of our MP.

| Function  | Worst-case time complexity |
| ------------- | ------------- |
| `make()`  | O(*l*)  |
| `push_left()`  | O(1)  |
| `push_right()`  | O(1)  |
| `pop_left()`  | O(1)  |
| `pop_right()`  | O(1)  |
| `peek_left()`  | O(1)  |
| `peek_right()`  | O(1)  |
| `size()`  | O(1)  |
| `empty()`  | O(1)  |
| `get()`  | O(n)  |
| `set()`  | O(n)  |
| `reverse()`  | O(1)  |

Additionally, this doubly linked list implementation is expected to have a **worst-case memory complexity of O(n)**

It is important to keep in mind while perusing these proofs that the constant time `reverse()` is achieved by writing a regular and reversed implementation for most of the functions. This means that there will be at least two cases for most of the proofs in this file.

## 1. push_left(*l*, *v*), push_right(*l*, *v*)

`push_left()` and `push_right()` smth smth similar implementations
Their implementations are divided into three cases: a reversed case, 
```c
// Non-reversed behaviour creates a new node, sets it as the left to the current leftmost node, then sets it as the new leftmost node
if(!l->is_reversed) {
    node* new_node = createNode(v);
    new_node->next = l->left;
    l->left->prev = new_node;
    l->left = new_node;
    l->size += 1;
    return;
}
```

## 2. make(*n*, *seq*)

## 3. pop_left(*l*), pop_right(*l*)

## 4. peek_left(*l*), peek_right(*l*)

## 5. size(*l*), empty(*l*), reverse(*l*)

## 6. get(*l*, *i*)

## 7. set(*l*, *i*, *v*)

## 8. Expected Space Complexity
