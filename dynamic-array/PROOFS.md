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

They have similar implementations which are each divided into three cases: a regular case, a reversed case, and a full list case. Due to the analogous nature of their implementations, we will use `push()` to refer to both `push_left()` and `push_right()` in this proof.

### 1.1 The regular case
The regular (non-reversed) logic simply moves the front index one space to the left and inserts v at that index.

```c
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

Seeing as this is simply a series of O(1) operations, we can conclude that the regular case runs in O(1) time.

### 1.2 The reversed case
The reversed case uses the non-reversed implementation of the opposite function (i.e. `push_left()` calls `push_right()` and vice versa).

```c
if(l->is_reversed) {
    l->is_reversed = false;
    push_right(l, v);
    l->is_reversed = true;
    return;
}
```

As established above, the regular case runs in O(1). The reversed case simply adds two more O(1) operations, retaining the linear time complexity of `push()`.

### 1.3 Amortized analysis via the aggregate method
For the full list case, let us assume that the initial array capacity is a power of 2. This simplifies our calculations as the array capacity will remain a power of 2 after each doublying. 

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

This is because `push()` calls take constant time in the regular and reversed cases as established in subsections 1.1 and 1.2.

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

Put simply, `push()` takes O(n) time every n calls and O(1) otherwise. One O(n) operation every n calls is O(1) amortized.

## 2. make(*n*, *seq*)


## 3. pop_left(*l*), pop_right(*l*)

## 4. peek_left(*l*), peek_right(*l*)
The `peek()` functions have three cases: regular, reversed, and empty. Both functions have similar implementations. Let us take `peek_left()` as our example.

### 4.1 Empty case
```c
if(l->occupied_size == 0) {
    printf("ERROR: cannot peek from list of size 0");
    assert(0 != 0);
    return -1;
}
```
The empty case returns after performing an O(1) `printf()` and an `assert()`. This makes the empty case run in O(1) worst-case.


### 4.2 Regular case
```c
if(!l->is_reversed) {
        return l->data[l->front];
    }
```
The regular case returns the value of an indexing operation. This operation runs in constant time since `l->data` refers to the address of the initial element of a default C array. Indexing arrays in C takes constant time, thus, the regular case runs in O(1) worst-case.

### 4.3 Reverse case
```c
// Reversed logic uses the non-reversed implementation of peek_right()
if(l->is_reversed) {
    l->is_reversed = false;
    int64_t ret = peek_right(l);
    l->is_reversed = true;
    return ret;
}
```
The reverse case flips the value of `l->is_reversed` twice and calls the regular case of the other `peek()` function. All of these steps run in O(1) time, thus, the reverse case also runs in O(1) time.

Since all three cases run in O(1) time, the `peek_left()` and `peek_right()` functions both run in O(1) in the worst-case.

## 5. size(*l*), empty(*l*), reverse(*l*)
These functions all execute a single O(1) operation before terminating as can be seen in the snippet below. This means they all have O(1) time complexity in the worst-case.

```c
int size(list *l) {
    return l->occupied_size;
}

bool empty(list *l) {
    return (l->occupied_size == 0) ? true : false;
}

void reverse(list *l) {
    l->is_reversed = !l->is_reversed;
    return;
}
```

## 6. get(*l*, *i*)

## 7. set(*l*, *i*, *v*)

## 8. Expected Space Complexity
Since the backing dynamic array doubles and halves in size when the array goes above full and below 1/3 capacity respectively, then the space occupied by an array of n elements, $`s(n)`$ can be expressed as follows:

$`\begin{equation} 
\begin{split}
    n\leq s(n) \leq 3n
\end{split}
\end{equation}`$

The array **wastes the most space** when its size is at 1/3 of its capacity, taking up thrice the amount of space as its number of elements. This is expressed as $`3n`$. 

The array **wastes the least space** when its size is equal to its capacity, taking up exactly $`n`$ space. 

Since these bounds hold as $`n`$ grows to infinity, we can use these bounds to make conclusions about the dynamic array's asymptotic behaviour. We can say that the space complexity is bound above by O(3n) and below by O(n).

As it is bound above and below by linear space complexities, the space complexity of our dynamic array is O(n).
