# Dynamic Array Details
## 1. Dynamic Array Rationale

O(1) indexing 
insert theoretical basis of dynamic array
  - resize when asjcoaijc
  - mention memory complexity
  - mention na this allows for all operations to be performed in O(1)
  - the deque behind the slaughter
  - A circular-deque-based dynamic array is essential in making it function as a dynamic list. For example, given an array of two elements occupying indices 0 and 1 of an array, executing a `pop_left()` then a `push_left()` may work if the array keeps track of a left index. However, without a circular deque implementation, a lone `push_left()` call would yield undefined behaviour as there is technically no index to the left of the leftmost index which is 0.
## 2. make(*n*, *seq*) and *dynamic_array.h* 
  - enumerate members
  - briefly describe functions (they just reallocate)
  -   allude to the earlier mentioned amortized concept (doubling every n, halving every n makes everything balance out to O(n))
  - resizing is a secret tool thatll help us later

## 3. size(*l*), empty(*l*), and reverse(*l*)
The previously mentioned members of the `list` struct allows for simple and efficient implementations of the `size()`, `empty()`, and `reverse()` functions of a dynamic list. The first two functions reference the `occupied_size` variable while the `reverse()` function simply flips the value of the `is_reversed` boolean member.

This does imply that our `reverse()` implementation runs in constant time. This efficiency is traded for more complexity in the code for the data structure itself as most other functions now require an implementation for the regular case and the reversed case of the dynamic array. Note that while this approach complicates the programming process, it does not affect the efficiency of the affected functions.

## 4. Capacity doubling, push_left(*l*, *v*), and push_right(*l*, *v*)

## 5. Capacity halving, pop_left(*l*), and pop_right(*l*)

## 6. Efficient indexing, get(*l*, *i*), and set(*l*, *i*, *v*)
As mentioned in section 1, one of the greatest strengths of the dynamic array implementation is its constant-time indexing. The `get()` and `set()` functions are simplified due to the innate constant-time indexing of the underlying array. They simply have to calculate for the "real" index, access its address using the backing array, then either return or modify its value.

The calculation for the offset index is very simple and is only complicated by the existence of a reverse case. The following figure illustrates these steps using the `get()` function as an example.

## References
