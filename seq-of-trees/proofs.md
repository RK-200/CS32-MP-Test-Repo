# Proofs

# Dynamic Array Proof Sketch

## 0. Introduction and Summary of Time Complexities

This file is a compilation of brief proofs for the asymptotic behaviour of our sequence of trees implementation of a dynamic list. The following table summarizes the expected time complexities based on the specifications of our MP.

|Function|Time complexity|
| ----------| ---------------------|
|​`make()`​|O(*l*) worst-case|
|​`push_left()`​|O(1og n) worst-case|
|​`push_right()`​|O(1og n) worst-case|
|​`pop_left()`​|O(1og n) worst-case|
|​`pop_right()`​|O(1og n) worst-case|
|​`peek_left()`​|O(1) worst-case|
|​`peek_right()`​|O(1) worst-case|
|​`size()`​|O(1) worst-case|
|​`empty()`​|O(1) worst-case|
|​`get()`​|O(1og n) worst-case|
|​`set()`​|O(1og n) worst-case|
|​`reverse()`​|O(1) worst-case|

Additionally, this dynamic array implementation is expected to have a **worst-case memory complexity of O(n)**

<insert general outline here>

It is important to keep in mind while perusing these proofs that the constant time `reverse()`​ is achieved by calling the opposite side implementation for most of the functions. The functions `get()`​ and `set()`​ achieve constant time reverse using different means. This means that there will be at least two cases for most of the proofs in this file.

Lastly, we will be analyzing similar functions in pairs or groups to keep the proofs concise.

## 1 push_left(*l*, *v*), push_right(*l*, *v*)

The first of the logical pairs are the `push_left()`​ and `push_right()`​ functions.

They have similar implementations which are each divided into two cases: `push_left()`​, and `push_right()`​. The function `n_union()`​ will also be discussed here as it is a helper function used only for the `push()`​ operations.

### 1.1 n_union()

The function is an O(1) operation that returns a node of a higher degree with its left and right children being the two nodes that were passed.

### 1.2 push()

```c
if(l->reverse){
        l->reverse = false;
        push_right(l,v);
        l->reverse = true;
        return; 
    }
    node* new = new_node(v);
    l->leftmost = v;

    if(l->size == 0){
        l->left_head = new;
        l->right_head = new;
        l->rightmost = v;
    }
    else{
        node* tmp = l->left_head;
        l->left_head = new;
        l->left_head->right = tmp;
        tmp->left = new;
    }
    l->size++;
    l->nodes++;
    merge(l,'l');
```

The function begins by creating a degree 0 node and appending it at the start of the list. The values of `size`​ and `nodes`​ are incremented by `1`​ since a single node is added. In order to follow the additional requirement, a check is made to verify that the resulting subsequence of tree degrees are increasing/decreasing, which is handled by the `merge()`​ function.

This is done by checking if the degree of the following tree is the same as the current tree. If they are the same, which implies the degrees are not strictly increasing/decreasing, `n_union()`​ is called in order to merge the trees with same degrees together. Since it is possible that a sequence of degrees increases by 1 step each eg.(`[1,2,3]`​), the loop only stops when the degrees of the current `left_head/right_head`​ and the `right/left`​ node respectively are different or nonexistent. This guarantees that no matter how long the 1 step increasing sequence lasts, the resulting sequence of degrees will follow the additional requirement.

While this implementation may have monotonic sequences of degrees, all the given time complexities would still be valid since we avoid the degenerate representation of a sequence of trees where the worst-case time complexity is O(n). We can prove this since for any decimal representation of the number of elements in the list, there is a corresponding binary representation. This binary representation is a monotonic sequence and for n>1 there will always be less trees than elements which fulfils the requirement of avoiding the degenerate case. Thus still allowing us to perform operations in O(log n) time.

### 1.3 merge()

```c
void merge(list* l,char start){
    if(start == 'l'){
        if(l->size > 1){
            while(l->size > 1 && l->left_head->degree == l->left_head->right->degree){
                node* r_temp = NULL;
                if(l->left_head->right->right != NULL){
                    r_temp = l->left_head->right->right;
                }
                l->left_head = n_union(l->left_head,l->left_head->right);
                l->left_head->right = r_temp;
                l->size--;
                if(l->size > 1){
                    l->left_head->right->left = l->left_head; 
                }
            }
        }
        if(l->size == 1){
            l->right_head = l->left_head;
        }
        return;
    }
    else{
        if(l->size > 1){
            while(l->size > 1 && l->right_head->degree == l->right_head->left->degree){
                node* l_temp = NULL;
                if(l->right_head->left->left != NULL){
                    l_temp = l->right_head->left->left;
                }
                l->right_head = n_union(l->right_head->left,l->right_head);
                l->right_head->left = l_temp;
              
                l->size--;
                if(l->size > 1){
                    l->right_head->left->right = l->right_head; 
                }
            }
        }
        if(l->size == 1){
            l->left_head = l->right_head;
        }
        return;
    }
}
```

From the definition of `n_union()`​ we can see that it is possible for `push()`​ to run in constant time (when appending a node of degree 0 and having no unions). However, whenever there are unions involved, there will be at least more than one operation being done. Wherein the worst case is a sequence of degrees that increase by 1 step each. Meanwhile, we see that due to the strictly increasing/decreasing degree property of the list, there will only be at most lg(n) unions, or lg(n)+1 operations. This falls under the O(log n) time complexity since at a large enough n, $1\leq operations \leq lg(n)$. Thus, we show that `push()`​ runs in O(log n) worst-case time.

### 2.4 Amortized analysis via the aggregate method

We also need to show that while the worst case running time of `push()`​ is O(log n), the amortized cost is actually O(1). This will be important in proving that `make()`​ runs in linear time O(n). From the condition of the `merge()`​ function, we can see that merge will happen at most once every 2 pushes. And since at the smallest degree, `merge()`​ of two degree 0 takes 2 operations, one insert and one `merge()`​ can be re

## 2. make(*n*, *seq*)

The `make()`​ function allocates a `list`​ in the heap then initializes its values through a series of O(1) assignment operations.

Since

It then runs the `push_right()`​ operation `l`​ times:

```c
list *make(int n, int64_t *seq){
    list* ret = malloc(sizeof(list));
    ret->left_head = NULL;
    ret->right_head = NULL;
    ret->size = 0;
    ret->nodes = 0;
    ret->leftmost = 0;
    ret->rightmost = 0;
    ret->reverse = false;
    for(int i=0;i<n;i++){
        push_right(ret,seq[i]);
    }
    return ret;
}
```

Since the loop iterates through the entirety of the array `seq`​, we can conclude that it runs in O(*l*) time if *l* is the length of the `seq`​ array.

## 3. pop_left(*l*), pop_right(*l*)

Similar to the implementation of `push()`​, `pop()`​ also makes use of a helper function called `split()`​. This function takes an existing node of degree > 0 and correctly places the resulting nodes while taking into consideration the prior connection of nodes in the doubly linked list of trees. The `pop()`​ functions run in O(log n) worst-case time, and both have similar implementations, with an additional check to know if the array is empty before popping.  

### 3.1 split()

The function `split()`​ runs in O(log n) time, since the head/tail node can possibly be of a degree>1. Therefore, multiple splits may occur.

```c
void split(list *l, char start){
    if(start == 'l'){
        while(l->left_head->degree > 0){
            //split
            if(l->size == 1){
                node* lh= l->left_head;
                l->left_head = lh->left_child;
                l->right_head = lh->right_child;
                l->left_head->right = l->right_head;
                l->right_head->left = l->left_head;
                l->left_head->left = NULL;
                l->right_head->right= NULL;
            }
            else{
                node* lh= l->left_head;
                l->left_head = lh->left_child;
                l->left_head->left = NULL;
                l->left_head->right = lh->right_child;
                l->left_head->right->left = l->left_head;
                l->left_head->right->right = lh->right;
                lh->right->left = l->left_head->right;
  
            }
            l->size++;
        }
    }else{
        while(l->right_head->degree != 0){
            //split
            if(l->size == 1){
                node* lh= l->right_head;
                l->right_head = lh->right_child;
                l->left_head = lh->left_child;
                l->right_head->left = l->left_head;
                l->left_head->right = l->right_head;
                l->left_head->left = NULL;
                l->right_head->right= NULL;
            }
            else{
                node* lh= l->right_head;
                l->right_head = lh->right_child;
                l->right_head->right = NULL;
                l->right_head->left = lh->left_child;
                l->right_head->left->right = l->right_head;
                l->right_head->left->left = lh->left;
                lh->left->right = l->right_head->left;
  
            }
            l->size++;
        }
    }
}
```

Once the head or tail tree is split until it is of degree 0, that specific node is then removed from the sequence of trees and the memory is freed. Because of the splitting, there is a chance that the property of the sequence of trees will be violated. For example `[2,1]`​, `pop_left()`​, `-> [0,1,1]`​. In order to guarantee that a strictly increasing/decreasing subsequence of degrees are still followed, `merge()`​ is called on both sides of the list. Since `merge()`​ runs in O(log n) time, at worst `pop()`​ will still run at O(log n) time.

Since the maintenance steps of keeping the relations of the doubly linked list of trees can be done in O(1) time, the only operations that dominate the `pop()`​ function are `split()`​ and `merge()`​, therefore `pop()`​ runs in O(log n) time.

## 4. peek_left(*l*), peek_right(*l*)

The `peek()`​ functions have three cases: peek_left, peek_right, and empty. Both functions have similar implementations. The function is made execute in O(1) time by maintaining a variable leftmost/rightmost. The correctness of the function is then left to the implementation of `push()`​ and `pop()`​ and with how it maintains the leftmost/rightmost variable.

The implementation of `push()`​ shows that at the start of the start of the function, the variable `leftmost/rightmost`​ is maintained to have the new value being added to the list. There is also a check to make sure that if a value is pushed to an empty list, both the `leftmost`​ and `rightmost`​ values are maintained.

### push()

```c
//snippet of push_left()
node* new = new_node(v);
    l->leftmost = v;

    if(l->size == 0){
        l->left_head = new;
        l->right_head = new;
        l->rightmost = v;
    }

//snippet of push_right()
node* new = new_node(v);
    l->rightmost = v;

    if(l->size == 0){
        l->left_head = new;
        l->right_head = new;
        l->leftmost = v;
    }
```

‍

### pop()

```c
//snippet of pop_left()
if(l->size >1){
        l->left_head = l->left_head->right;
        merge(l,'l');
        merge(l,'r');  
    }
    else{l->left_head=l->right_head;l->right_head = l->left_head;}
  
    l->leftmost = get(l,0);

//snippet of pop_right()
if(l->size >1){
        l->right_head = l->right_head->left;
        merge(l,'l');
        merge(l,'r');
    }
    else{l->right_head=l->left_head;l->left_head = l->right_head;}
  
    l->rightmost = get(l,l->nodes-1);
    return ret;
```

Since the maintenance steps are done outside of the `peek()`​ functions, we are able to keep the O(1) runtime even though some maintenance operations are in O(log n) time.

The function returns the maintained variable `leftmost`​ or `rightmost`​ when reversed. An error is returned whenever `peek()`​ is called on an empty list.

### peek_left()

```c
int64_t peek_left(list *l){
    if(l->size == 0 ){
        printf("empty");
        assert(0!=0);
    }
    if(l->reverse){
        return l->rightmost;
    }
    return l->leftmost;
}
```

‍

## 5. size(*l*), empty(*l*), reverse(*l*)

These functions all execute a single O(1) operation before terminating as can be seen in the snippet below. This means they all have O(1) time complexity in the worst-case.

```c
int size(list *l){
    return l->nodes;
}
bool empty(list *l){
    return (l->nodes == 0) ? true : false;
}
void reverse(list *l){
    l->reverse ^= true;
}
```

## 6. get(*l*, *i*) and set(*l*, *i*, *v*)

The `get()`​ and `set()`​ functions are implemented similarly in the way they `traverse()`​ the sequence of trees to arrive at the node of a specific index `i`​. At the start of the function, basic checks are done in order to see if `i`​ is within the bounds of the array. The `traverse()`​ function contains the bulk of the implementation of `get()`​ and `set()`​.

### 6.1 traverse()

In order to achieve the expected time complexity of O(log n) or more specifically $O(t\ +\ k_j)$, `traverse()`​ makes use of the fact that the number of leaves of each tree is 2^k. To find which tree `i`​ is at, an integer `s`​ (that is offset by -1 to account for 0 indexing) is maintained that sums up $2^k$ where k is the degree of the current tree. The value of `s`​ lets us know the maximum index that the current tree would contain. Thus, we are able to select which tree contains `i`​ in O(t) time.

In order to find which leaf `i`​ is at, we first need to know at which "index" `i`​ is at on the specific tree. The "index" of the tree is calculated by offsetting `i`​ with the `s`​ calculated before accounting for the current tree. This gives us information on which nth leaf `i`​ is at. Now, to traverse to the right leaf at O(k_j) time, we must find the right leaf in j steps. We can do this by making use of the fact that every tree contains $2^k$ leaves. Trivially, if k=0 then we simply return the root of the current tree. For any k>0 though, we can see that there will always be 2 children. By having the information of "index" calculated beforehand, in our traversal, we can perform a comparison `k/2 >= i2`​ to see whether we choose the left child or the right child. We know this will always be correct since for every level of the tree traversed, the number of traversable nodes halve. It is also important to note that when we select the right child, we must properly set the offset of `i2`​ since i2 is based on the degree. As we keep traversing the tree, we will eventually end up in our trivial case of k=0 where we can then return the node that we end up at. Thus completing the traversal in O(k_j) time.

```c
node* traverse(list *l,int i){
    int64_t s = -1,res;
    node* n = l->left_head;
    while(s<i){
        if(s!=-1){n=n->right;}
        res = (1 << n->degree);
        s += res;
      
    }
    int64_t i2 = i - (s - (1 << n->degree));
    int64_t k = 1 << n->degree;
    while (n->degree!= 0){
        if (k/2 >= i2){
            n = n->left_child;
            k = k/2;
        }else{
            n = n->right_child;
            k = k/2;
            i2 -= k;
        }
    }
    return n;
}
```

### 6.2 get() and set()

Since both `get()`​ and `set()`​ are simple functions relying on `traverse()`​, we instead place our focus on the implementation of the reverse indexing. When the list is reversed, in order to find the reversed index in O(1) time, we simply subtract the highest possible index and subtract `i`​ to it, giving us the reversed index (similar to counting in reverse). The functions  `get()`​ and `set()`​ run in O(log n) time since it is bound by the most costly function `traverse()`​ which also runs in O(log n) time. Modifying or accessing the returned node only runs in O(1) time, thus showing that `get()`​ and `set()`​ runs in O(log n) time.

```c
int64_t get(list *l, int i){ 
    if(l->size == 0 || i >= l->nodes || i < 0){
        printf("index error");
        assert(0!=0);
    }

    if(l->reverse){
        i = l->nodes-i-1;
    }

    node* ret = traverse(l,i);
  
    return ret->val;

}
void set(list *l, int i, int64_t v){
    if(l->size == 0 || i >= l->nodes || i < 0){
        printf("index error");
        assert(0!=0);
    }

    if(l->reverse){
        i = l->nodes-i-1;
    }

    node* ret = traverse(l,i);
    ret->val = v;
}
```

## 7. Expected Space Complexity

The sequence of trees grows in constant size O(1) whenever a node of degree 0 is added. In order to fulfil the increasing/decreasing degree property, we will have trees of degree > 0. For these trees, non-leaf nodes contain no meaningful data even though they still take up space. We know that a tree will always be a perfect binary tree, and that perfect binary trees have 2^(k+1)-1 nodes. In order to relate the number of elements to the nodes of the perfect binary tree, we consider increasing/decreasing degree property. We can see that the number of nodes increase linearly as n grows. This is because `union()`​ is only called whenever two nodes are of the same degree. Which means that there must be at least 2 nodes before each `union()`​, thus the amortized space complexity is O(1) for each node. Since there are n nodes in the sequence of trees, we have shown that it has O(n) memory complexity.
