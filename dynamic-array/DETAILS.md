# Dynamic Array Details
## 1. Dynamic Array Rationale

O(1) indexing 
insert theoretical basis of dynamic array
  - resize when asjcoaijc
  - mention memory complexity
  - mention na this allows for all operations to be performed in O(1)
  - the deque behind the slaughter
  - A circular-deque-based dynamic array is essential in making it function as a dynamic list. For example, given an array of two elements occupying indices 0 and 1 of an array, executing a `pop_left()` then a `push_left()` may work if the array keeps track of a left index. However, without a circular deque implementation, a lone `push_left()` call would yield undefined behaviour as there is technically no index to the left of the leftmost index which is 0.
## 2. make(*n*, *seq[]*) and *dynamic_array.h* 
  - enumerate members
  - briefly describe functions (they just reallocate)
  -   allude to the earlier mentioned amortized concept (doubling every n, halving every n makes everything balance out to O(n))
  - resizing is a secret tool thatll help us later

## 3. size(*l*), empty(*l*), and reverse(*l*)
These struct members allow us to create simple yet efficient implementations for the `size()`, `empty()`, and `reverse()` functions of a dynamic list

## 4. Capacity doubling, push_left(*l*, *v*), and push_right(*l*, *v*)

## 5. Capacity halving, pop_left(*l*), and pop_right(*l*)

## 6. Efficient indexing, get(*l*, *i*), and set(*l*, *i*, *v*)

## References
