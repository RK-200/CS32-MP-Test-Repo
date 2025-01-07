# Doubly Linked List Details
## 1. Doubly linked list rationale

The doubly linked list implementation leverages O(1) creation and deletion of elements at the left and right ends of the list to provide dynamic sizing without the need for a resizing scheme.

List elements are represented as nodes which are created and deleted on demand. This means that it only takes up exactly the amount of space it needs, with no excess.

## 2. General structure, make(*n*, *seq*) and *dll_node.h* 

## 3. size(*l*), empty(*l*), and reverse(*l*)

## 4. push_left(*l*, *v*), push_right(*l*, *v*), pop_left(*l*), and pop_right(*l*)
  - mention na its mostly just edge case handling, mention all the general cases

![dll_push_pop](https://github.com/user-attachments/assets/7511235e-1765-4bb1-b9d8-002d461879e7)

## 5. O(n) indexing, get(*l*, *i*), and set(*l*, *i*, *v*)

