# CS32 MP - Calinawan, Fan, Montiero

## User Manual
This repo contains four different implementations of a dynamic list along with suitable unit tests for each of them. Our code is organized into five folders. 

The four implementation folders are identical in structure, containing source code written in c and assisted by header files, a `DETAILS.md` file dicussing the implementation details of each dynamic list strategy, and a `PROOFS.md` file justifying the time complexities of their respective implementations.

The fifth folder contains unit testing shit idfk what its gonna contain honestly AHAHHAHAHAHAHAHAHHA

These folders, with the exception of the `unit-tests` folder are standalone and the programs within them make no reference to files of other implementations.

<insert instructions on how to use unit tests and how to use the implementations>

## Code Structure
### Doubly linked list
The doubly linked list approach is composed of four files including a `main.c` file for unit testing purposes. 

The implementation itself is spread across two header files and a `doubly_linked_list.c` file tying their functionalities together. The `dll_node.h` file houses information on the `node`s that compose the doubly linked list structure including the function that creates these `node`s.

The `doubly_linked_list.h` file contains the list-level information tracked by the implementation such as list size and its left and rightmost nodes. It also declares the functions required of a dynamic list which are then defined in the `doubly_linked_list.c` file which imports the two aforementioned header files.

As a brief overview, the doubly linked list approach represents dynamic lists as a doubly linked list. This data structure is a nautral choice as it implements dynamic behaviour with ease; creation and deletion of elements is efficient at the ends and `node`s can be added without concern as there is no maximum size limitation. 

All operations run in constant time except for operations which involve indexing nodes that are on neither end of the list, in which case it takes O(n) time in the worst case. The implementation uses no other data structure; all operations are performed on the `list` struct which stores references to `node`s which reference each other.
### Dynamic array


### Skip list
### Sequence of trees

## Unit Test System
go jelo woo

## resources ig lmao
