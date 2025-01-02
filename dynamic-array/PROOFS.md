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

### 1.1 The three cases
The first of these logical pairs are the `push_left()` and `push_right()` functions.

They have similar implementations which are each divided into three cases: a regular case, a reversed case, and a full list case. Due to the analogous nature of their implementations, we will use `push()` to refer to both `push_left()` and `push_right()` in this proof.

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

1.) establish na the regular and reversed cases take O(1)
2.) amortize that shit

### 1.2 Amortized analysis via the aggregate method
Let us assume that the initial array capacity is a power of 2. This simplifies our calculations as the array capacity will remain a power of 2 after each doublying. 

In line with the analysis above, the cost for the *i*<sup>th</sup> `push()` call can be formally expressed as:

$`
\begin{equation} 
c(i) = 
    \begin{cases}
        i, & \text{when i - 1 is an exact power of 2} \\
        1, & \text{otherwise}
    \end{cases}
\end{equation}
`$

$`
\begin{equation} 
\begin{split}
    \text{cost of n pushes:} \\ \\
    &\sum^{n}_{i = 1} \text c(i) \\
    &=n+\sum^{\lfloor j=log_2(n - 1)\rfloor}_{j=0} 2^j &&\text{j is equal to the number of times the array would have doubled in size given i pushes} \\
    &=n+\frac{2^{log_2(n - 1) + 1} - 1}{2-1} &&\text{standard summation formula}\\
    &=n+2^{\lfloor log_2(2(n-1))\rfloor}  \\
    &=n+2(n-1) &&\text{simplify using log rules} \\
    &=3n-2 \\
    &=3n-2<3n \\
    &=O(n)
\end{split}
\end{equation}
`$


Therefore, the cost for n `push()` calls is O(n). Recall that

$`
\begin{equation} 
\begin{split}
    &\text{amortized cost per operation = }
    &\frac{\text{total cost for all operations}}{\text{number of operations}} \\
    &\text{thus, we have:} \\
    &\frac{O(n)}{n}
    =O(1) \text{ amortized}
\end{split}
\end{equation}
`$

## 2. make(*n*, *seq*)


## 3. pop_left(*l*), pop_right(*l*)

## 4. peek_left(*l*), peek_right(*l*)

## 5. size(*l*), empty(*l*), reverse(*l*)

## 6. get(*l*, *i*)

## 7. set(*l*, *i*, *v*)

## 8. Expected Space Complexity
