# Skip List Proof Sketch

## 0. Introduction and Summary of Time Complexities

This file is a compilation of brief proofs for the asymptotic behaviour of our dynamic array implementation of a dynamic list. The following table summarizes the expected time complexities based on the specifications of our MP.

| Function  | Time complexity |
| ------------- | ------------- |
| `make()`  | O(*l*) expected |
| `push_left()`  | O(1) expected |
| `push_right()`  | O(1) expected |
| `pop_left()`  | O(1) expected |
| `pop_right()`  | O(1) expected |
| `peek_left()`  | O(1) worst-case |
| `peek_right()`  | O(1) worst-case |
| `size()`  | O(1) worst-case |
| `empty()`  | O(1) worst-case |
| `get()`  | O(log n) expected |
| `set()`  | O(log n) expected |
| `reverse()`  | O(1) worst-case |

Additionally, this skip list implementation has a **expected memory complexity of O(n)**

## 1. push_left(*l*, *v*), push_right(*l*, *v*)
First, $`push\_left()`$ and $`push\_right()`$ both make a call to $`generate\_random\_level()`$ to randomly generate the number of layers the given element will appear in. The probability that an element has a node at the level $i$ is $p^{i-1}$. Thus, the expected height $l$ of an element in a skip list is:
```math
E[l] = \sum_{i=1}^{\infty} p^{i-1}
```
This converges to:
```math
E[l] = \frac{1}{1-p}
```
For $p = \frac{1}{2}$, $E[l] = 2$. Additionally, since there is a set constant $`MAXIMUM\_LEVEL`$, $`generate\_random\_level()`$ will always run at a constant $O(1)$ time.
The $push()$ operations then loop a number of times equivalent to the value of the generated level, allocating memory for the new node, and changing its pointers and the pointers of the node adjacent to it, which all take an expected constant amount of time (since the adjacent node will also have a constant height). Thus, both push operations run in O(1) time.
## 2. make(*n*, *seq*)
The $make()$ function first allocates memory for a $`skip\_list`$ pointer and
sets each of its fields to a default value, which takes a constant $O(1)$ time. Then, for each element of the input list $seq$, it calls $`push\_right()`$, pushing that element into the skip list. Since there are $l$ elements in $seq$, and $`push\_right()`$ runs at a constant $O(1)$ time, the total time complexity of the loop is
```math
l\cdot O(1)=O(l)
```
The total time complexity of $make()$ is therefore
```math
O(l)+O(1)=O(l)
```
## 3. pop_left(*l*), pop_right(*l*)
Since each element has a constant expected number of layers, freeing all nodes of the leftmost\rightmost element will also take a constant expected time. Additionally, pointers to the leftmost and rightmost element are stored in the first element of the $heads$ and $tails$ arrays, respectively, and accessing them also takes a constant time. Thus, the expected time complexity of both $pop()$ operations is O(1). 
## 4. get(*l*, *i*)
The $get()$ function calls the function $`get\_node\_at\_i()`$, which runs in $O(\log n)$ time.


$Proof:$\
There are $n$ nodes in layer 0 of the skip list, since all elements must be present here. On layer 1, there are $n\cdot p^1$ elements, since each element has probability $p$ to have a node in this layer. On layer 2, there are $n\cdot p^2$. In general, for each layer i, there are $n\cdot p^{i}$ elements. Let $h$ be the height of the skip list. At layer h, there must be at least 1 element:
```math
n\cdot p^{h}\geq1
```
Solving for $h$:
```math
p^{h}\geq \frac{1}{n}
```
Taking the logarithm of both sides and flipping the inequality (since $p < 1$):
```math
\begin{gather*} h\leq \log_p (\frac{1}{n})\\
h\leq \log_p(1)-\log_p(n)\\
h\leq -log_p(n)\\
h\leq log_{\frac{1}{p}}(n)\end{gather*}
```
Therefore, the expected maximum height is $\log_{\frac{1}{p}} n$ or $\lg n$ for $p = \frac{1}{2}$


The $`get\_node\_at\_i()`$ function works by starting at the first node at the highest layer of the list, comparing its index to the index $i$ being searched for, and either: 
1. returns the node if its index is equal to $i$ 
2. moves to the left node if $i$ is less than its index
3. moves to the right node if $i$ is greater than its index
4. moves to the node below if the conditions in 2 or 3 are met, but the left/right node does not exist in the current layer.
Each of the above steps takes $O(1)$ time, since it only involves changing pointers to the appropriate node. The expected search time is then the expected number of steps taken to go down or go horizontally (left or right). Let $S_d$ be the number of steps going down and $S_h$ be the number of steps going down:
```math
E[S] = E[S_d] + E[S_h]
```
On average, each layer in the skip list has $p$ less nodes than the one below it. So, moving horizontally in the list skips $\frac{1}{p}$ nodes on average. Since the expected height of the list is $\log_{\frac{1}{p}} n$, $E[S_h] = \log_{\frac{1}{p}}n\cdot \frac{1}{p}$. Additionally, the number of downward steps is bounded above by the height of the list. Thus we have:
```math
E[S] = \log_{\frac{1}{p}}n + \log_{\frac{1}{p}}n\cdot \frac{1}{p}
```
For $p=\frac{1}{2}$, $E[S] = 3\lg n$. Since each step takes O(1) time, the total time complexity of $`get\_node\_at\_i()`$ is $O(\log n)$.

Since $get()$ just takes the $value$ field of the returned node, its time complexity is also $O(\log n)$
## 5. set(*l*, *i*)
The $set()$ function also calls the $`get\_node\_at\_i()`$ function, which has been shown earlier to run in $O(\log n)$ time. Since the number of nodes each element can have is bounded above by a constant number, traversing down layers of each element and changing their $value$ fields will also take constant time. As such, the total time complexity of $set()$ is the time it takes to search, plus the time it takes to change each value:
```math
O(\log n)+O(1) = O(\log n)
```
## 5. peek_left(*l*), peek_right(*l*)
Both $peek()$ functions return the $value$ field of the node pointed to by the first element of the $heads$ or $tails$ field of the input list $l$. This takes $O(1)$ time. 
## 6. size(*l*), empty(*l*)
Both $size()$ and $empty()$ run in $O(1)$ time since they only return/check the $size$ field of the input list $l$, which is maintained by the $push()$ and $pop()$ operations.
## 7. reverse(*l*)
Calling $reverse()$ simply sets the $reversed$ field of the skip list to the opposite value, which takes $O(1)$ time. The reversed behaviors of each function are handled by the functions themselves, calling the function on the opposite side in the case of $push()$ and $pop()$, or starting the index count from the opposite side, in the case of $set()$ and $get()$.
## 8. Expected Space Complexity
As shown earlier, the probability that an element exists at layer $i$ is $p^{i-1}$. For $n$ elements, the number of nodes at layer $i$ is $np^{i-1}$. Therefore, the total number of nodes in the entire list among all layers is the geometric series
```math
\sum_{i=1}^{\infty} np^{i-1}=\frac{n}{1-p}
```
For the set probability $p=\frac{1}{2}$, the number of nodes is $2n$, which is in $O(n)$
