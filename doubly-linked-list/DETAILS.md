# Doubly Linked List Details
## 1. Doubly linked list rationale

The doubly linked list implementation leverages O(1) creation and deletion of elements at the left and right ends of the list to provide dynamic sizing without the need for a resizing scheme.

List elements are represented as nodes which are created and deleted on demand. This means that it only takes up exactly the amount of space it needs, with no excess.

## 2. General structure, make(*n*, *seq*) and *dll_node.h* 



## 3. size(*l*), empty(*l*), and reverse(*l*)
Since the *list* struct keeps track of the *size* and *is_reversed* variables, all three of these functions simply read the concerned values and return in O(1) time.

## 4. push_left(*l*, *v*), push_right(*l*, *v*), pop_left(*l*), and pop_right(*l*)
The `push()` and `pop()` functions benefit from O(1) the largely self-encapsulating nature of its nodes. Nodes can be added and deleted in O(1) time with little regard to total size, direction of the list, or any concept larger than the node itself. This means that our `push()` and `pop()` implementations can focus on handling a few edge cases instead of maintaining a complicated system.

The most pertinent edge case is when insertion or deletion commands are executed on an empty list and, for the case of the `pop()` functions, a list of size 1. These cases are handled through their own conditional branches while reversed and regular case conditionals handle the rest.

![dll_push_pop](https://github.com/user-attachments/assets/7511235e-1765-4bb1-b9d8-002d461879e7)

## 5. O(n) indexing, get(*l*, *i*), and set(*l*, *i*, *v*)
A disadvantage of the doubly linked list structure is that indexing takes O(n) time in the worst case with the exception of the leftmost and rightmost elements.

`get()` and `set()` calls iterate through the list one node at a time before returning or setting the value once a certain number of nodes have been iterated through. The number of increments from the leftmost index is equal to the target index *i* when the list is not reversed. It is equal to the *size* - *i* - *1* when the list is reversed.
