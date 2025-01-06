# Dynamic Array Details
## 1. Dynamic Array Rationale

The array data structure is a natural choice for the dynamic list as it offers a linear arrangement of elements while offering an O(1) indexing operation. This provides an easy path for implementing efficient `get()` and `set()` functions.

Our implementation combines a circular deque with a reallocation scheme to create a functional dynamic list. This allows for all dynamic list functions to run in O(1) time with the exception of `make()`.

The circular deque base is essential in making the array function as a dynamic list as it lets us handle insertions and deletions on both the front and the rear of the array while the reallocation functions give it dynamic properties. 

The array doubles in size when attempting to add an element to a full array; it halves in size when attempting to remove an element from an array whose size is equal to a third of its capacity. Two distinct constants are needed in order to prevent inefficient behaviour when performing additions and deletions at the boundary of the resizing factor. This resizing scheme ensures 

For example, given an array of two elements occupying indices 0 and 1 of an array, executing a `pop_left()` then a `push_left()` may work if the array keeps track of only the left index. However, without a circular deque implementation, a lone `push_left()` call would yield undefined behaviour as there is technically no index to the left of the leftmost index which is 0.

Our implementation solves this issue by keeping track of key array properties and storing them as members of a struct.

## 2. make(*n*, *seq*) and *dynamic_array.h* 
  - enumerate members
  - briefly describe functions (they just reallocate)
  -   allude to the earlier mentioned amortized concept (doubling every n, halving every n makes everything balance out to O(n))
  - resizing is a secret tool thatll help us later

## 3. size(*l*), empty(*l*), and reverse(*l*)
The previously mentioned members of the `list` struct allows for simple and efficient implementations of the `size()`, `empty()`, and `reverse()` functions of a dynamic list. The first two functions reference the `occupied_size` variable while the `reverse()` function simply flips the value of the `is_reversed` boolean member.

This does imply that our `reverse()` implementation runs in constant time. This efficiency is traded for more complexity in the code for the data structure itself as most other functions now require an implementation for the regular case and the reversed case of the dynamic array. Note that while this approach complicates the programming process, it does not affect the efficiency of the affected functions.

## 4. Capacity doubling, push_left(*l*, *v*), and push_right(*l*, *v*)
The array doubles in capacity whenever `push()` is called on a full array.
![dynamic_array_rationale](https://github.com/user-attachments/assets/56b97669-ce63-4ff4-9d7c-5a6c80c4a811)

## 5. Capacity halving, pop_left(*l*), and pop_right(*l*)
The array halves in capacity whenever `pop()` is called on an array whose size is equal to a third of its capacity. As explained in section 1, the system has hysteresis in that the array does not halve when it goes below half capacity. This is to avoid inefficient behaviour where the array frequently doubles and halves in size when performing operations near half capacity.

The following figure illustrates this inefficient behaviour.
![dynamic_array_hysteresis](https://github.com/user-attachments/assets/d1bd2b31-5c4e-4ccf-8f31-ead37d5edd65)

## 6. Efficient indexing, get(*l*, *i*), and set(*l*, *i*, *v*)
As mentioned in section 1, one of the greatest strengths of the dynamic array implementation is its constant-time indexing. The `get()` and `set()` functions are simplified due to the innate constant-time indexing of the underlying array. They simply have to calculate for the "real" index, access its address using the backing array, then either return or modify its value.

The calculation for the offset index is very simple and is only complicated by the existence of a reverse case. The following figure illustrates these steps using the `set()` function as an example. Note that the `reverse()` call does not actually change the value of `front`. Concerned functions simply have a case handling reverse logic.
![dynamic_array_set](https://github.com/user-attachments/assets/34134746-afa7-4f13-8fd0-e62956289b43)



## References
