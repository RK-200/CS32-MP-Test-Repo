# Dynamic Array Proof Sketch

## 0. Introduction and Summary of Time Complexities

This file is a compilation of brief proofs for the asymptotic behaviour of our dynamic array implementation of a dynamic list. The following table summarizes the expected time complexities based on the specifications of our MP.

| Function  | Time complexity |
| ------------- | ------------- |
| `make()`  | O(*l*) worst-case |
| `push_left()`  | O(1) amortized |
| `push_right()`  | O(1) amortized |
| `pop_left()`  | O(1) amortized |
| `pop_right()`  | O(1) amortized |
| `peek_left()`  | O(1) worst-case |
| `peek_right()`  | O(1) worst-case |
| `size()`  | O(1) worst-case |
| `empty()`  | O(1) worst-case |
| `get()`  | O(1) worst-case |
| `set()`  | O(1) worst-case |
| `reverse()`  | O(1) worst-case |

Additionally, this dynamic array implementation is expected to have a **worst-case memory complexity of O(n)**

<insert general outline here>

It is important to keep in mind while perusing these proofs that the constant time `reverse()` is achieved by writing a regular and reversed implementation for most of the functions. This means that there will be at least two cases for most of the proofs in this file.

Lastly, we will be analyzing similar functions in pairs or groups to keep the proofs concise.

## 1. push_left(*l*, *v*), push_right(*l*, *v*)

The first of these logical pairs are the `push_left()` and `push_right()` functions.

They have similar implementations which are each divided into three cases: a regular case, a reversed case, and a full list case.

```c
// Non-reversed logic moves the front index one space to the left and inserts v at that index
if(!l->is_reversed) {
    l->front -= 1;  

    if(l->front < 0) {
        l->front += l->capacity;
    }

    l->data[l->front] = v;
    l->occupied_size++;
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
