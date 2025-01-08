# Doubly Linked List Details
## 1. Doubly linked list rationale

The doubly linked list implementation leverages O(1) creation and deletion of elements at the left and right ends of the list to provide dynamic behaviour without the need for a resizing scheme.

List elements are represented as `node`s which are created and deleted efficiently on demand. This means that it does not waste any space as `node`s are created only when necessary and freed when removed from the list.

## 2. General structure, make(*n*, *seq*) and *dll_node.h* 
A header file, `dll_node.h`, underpins the entire implementation as it houses the details for the `node` struct. `node`s are the individual elements that link together to form a doubly linked list. Each node tracks three pieces of information: the address of the node to its *left*, the node to its *right*, and the *data* that the node itself stores.

These `node`s are initialized using the `make()` function but can be created or deleted using the `push()` and `pop()` functions once an initial list is made. 

The `make()` function itself intializes the members of the `list` struct. This includes crucial list-level information such as the list's *leftmost* node, its *rightmost* node, its *size*, and whether or not it *is reversed*. After initializing the struct, it iteratively calls the `push_right()` function to insert each element frpm the input *seq* into the list. 

## 3. size(*l*), empty(*l*), and reverse(*l*)
Since the `list` struct keeps track of the *size* and *is_reversed* variables, all three of these functions simply read the concerned values and return in O(1) time. There functions are absolutely bereft of logic as there are no edge cases to consider.

## 4. push_left(*l*, *v*), push_right(*l*, *v*), pop_left(*l*), and pop_right(*l*)
The `push()` and `pop()` functions benefit from the largely self-encapsulating nature of the list's nodes. Nodes can be easily added and deleted in O(1) time. The only complicating factor to these functions are the various edge cases that arise from the list-levelvalues we maintain.

The most pertinent edge case is when insertion or deletion commands are executed on an empty list and, for the case of the `pop()` functions, a list of size 1. These cases are handled through their own conditional branches while reversed and regular case conditionals handle the rest.

![dll_push_pop](https://github.com/user-attachments/assets/7511235e-1765-4bb1-b9d8-002d461879e7)

## 5. O(n) indexing, get(*l*, *i*), and set(*l*, *i*, *v*)
A disadvantage of the doubly linked list structure is that indexing takes O(n) time in the worst case with the exception of the leftmost and rightmost elements.

`get()` and `set()` calls iterate through the list one node at a time before returning or setting the value once the correct number of nodes have been iterated through. The number of increments from the leftmost index is equal to the target index *i* when the list is not reversed while it is equal to the *size - i - 1* when the list is reversed.
