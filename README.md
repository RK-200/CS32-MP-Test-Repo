# CS32 MP - Calinawan, Fan, Montiero

## User Manual
This repo contains four different implementations of a dynamic list along with suitable unit tests for each of them. Our code is organized into five folders. 

The four implementation folders are identical in structure, containing source code written in c and assisted by header files, a `DETAILS.md` file dicussing the implementation details of each dynamic list strategy, and a `PROOFS.md` file justifying the time complexities of their respective implementations.

The unit-tests folder contains tools and written unit tests in order to verify the functionality and correctness of the written code.

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
The dynamic array approach combines regular C arrays with a circular deque to provide constant time operations with dynamic behaviour through a reallocation system. 

The defining trait of this approach is that it uses fixed-capacity arrays which, strictly speaking, should not have dynamic behaviour. It functions as a dynamic list as the array is encapsulated in a `list` struct which can be thought of as a circular deque that tracks properties such as size and the front index.

This struct is defined in the `dynamic_array.h` header file along with the `expand_deque()` and `shrink_deque()` functions which changes the `list`'s `data` reference to a new array with the same contents but with double or half capacity respectively. 

These functions are triggered whenever the `list`'s size goes beyond the capacity (for `expand_deque()`) or goes below one third capacity (for `shrink_deque()`). The one third constant can be changed in the mentioned header file.

Aside from those functions, the rest of the implementation, defined in the `dynamic_array.c` file, simply leverages O(1) indexing to implement dynamic list functions in an efficient manner.

### Skip list
The skip list is a probabilistic data structure which uses multiple doubly-linked lists as 'layers' to provide logarithmic expected running time for indexing operations.

The defining trait of this approach is the use of probability to randomly promote elements to different layers in the list, which evenly distributes each element at random heights in the list. This creates 'express lanes', as each layer has more elements than the one below it, and traversing this express lane skips elements from the layers below it, allowing for more efficient get and set operations.

Each operation runs in O(1) time, excluding the `get` and `set` operations, which run in O($\log n$) time. The `list` and `node` structs are defined in the `skip_list.h` and `skip_list_node.h` header files. Additionally, the constants `SEED`, `P`, and `MAX_HEIGHT` are defined in the `skip_list.c` file and can be modified by the user.

### Sequence of trees

## Unit Test System
Our unit testing suite thoroughly tests the various list implementations by covering a wide range of edge cases and scenarios. The suite includes several test files, each targeting different scenarios for the lists. These tests encompass operations on empty or zero-sized lists, the creation of multiple lists with varying inputs, and the verification of implementation-specific list properties after each operation. 

Additionally, the suite can generate large sequences sequences of random list operations to test the capabilities of the implementations through brute-force. While these tests do not target particular edge cases, they do run a massive quantity of commands (around 1.5 million lines).

This brute-force randomness can be used to verify the correctness of the different implementations by feeding the same randomly generated set of commands for all four implementations and comparing their outputs to find discrepancies. If at least one of the implementations' outputs are different, then at least one of the implementations is likely wrong. 

Having all four implementations in agreeance does not necessarily mean that all four are correct as they can simply be wrong in all the same ways. However, through repeated iterations of brute-force comparison testing, a good level of confidence may be achieved. When combined with the curated edge case test suite, we can be fairly confident that our implementations are correct.

### Running Unit Tests
To run tests, execute ./test.sh [name of txt file].
The results will be written in the folder "res" and will be overwritten in every excecution of test.sh

The seed for test.py + number of total ops can be changed by the user via the variables in the python file

### Adding More Unit Tests
| Function  | Associated letter command |
| ------------- | ------------- |
| `make()`  | omitted |
| `push_left()`  | a |
| `push_right()`  | b |
| `pop_left()`  | c |
| `pop_right()`  | d |
| `peek_left()`  | e |
| `peek_right()`  | f |
| `size()`  | g |
| `empty()`  | h |
| `get()`  | i |
| `set()`  | j |
| `reverse()`  | k |
| `print_list()` | l |

go guys woo

## References
Chumbley, A., Williams, C., Branco, J., Khim, J., & Ross, E. (n.d.). *Skip list*. Brilliant. https://brilliant.org/wiki/skip-lists/ 


Wikipedia contributors. (2024, December 30). *Skip list*. Wikipedia, The Free Encyclopedia. Retrieved 09:01, January 3, 2025, from https://en.wikipedia.org/w/index.php?title=Skip_list&oldid=1266213396
