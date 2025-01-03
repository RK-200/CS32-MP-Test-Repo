# Skip List Details
## 1. Skip List Structure
The skip list implementation works essentially like multiple "layers" of doubly-linked lists stacked on top of each other. However, not every element is present in every layer of the skip list. Instead,
the number of layers each element has a corresponding node in is determined randomly, with a 50% chance for another node containing that element to be added to another layer, excluding the bottommost layer 0, where all elements can be found.

![Example of a skip list](/images/skip_list_example.png)

Each `node` in the skip list has three pointers: next, prev, and below, each of which points to the node after, before, and under it, respectively, or to NULL if it does not exist. Additionally, the `skip_list` struct contains two `node*` arrays:
`heads` and `tails`, which contain pointers to the first and last nodes of each layer, respectively.

## 2. push_left(*l*, *v*), push_right(*l*, *v*)
The `push_left` and `push_right` operations both insert the input value *v* to the leftmost\rightmost side of the input list *l*. This is done by first generating a random level for the new element using the function
`generate_random_level`. Note that there is a set constant `MAX_HEIGHT`, which limits the number of layers in the list. The leftmost and rightmost positions of the generated level can be easily accessed through the `heads` and `tails` arrays of the list. Then, new nodes are created and added from the top layer
of the new element, and each additional node is built downwards until the bottom-most layer is reached. The `size` and `height` fields of the input list are also maintained properly for each call to `push`. Additionally, the indices for each new
element are 0 if the list was empty before pushing, the index of the previous element plus 1 for `push_right`, or the index of the next element minus 1 for `push_left`. Lastly, the reversed behaviors of `push_left` and `push_right` instead call the opposite function if the `reversed` field of the list is `true`

![Example of the push operation](/images/push_right_example.png)

## 3. make(*n*, *seq*)
The `make` function initializes and returns a skip list containing the *n* elements of the input array *seq* in order. This is done by first allocating memory for the list and initializing each of its fields to default values. 
Each element in *seq* is then added by calling `push_right`, until every element is added. Additionally, a fixed seed is set upon calling `make` if the constant `SEED` is set to a non-zero value.

## 4. pop_left(*l*), pop_right(*l*)
The `pop_left` and `pop_right` operations remove the leftmost\rightmost value of the input list *l*. Similarly to the `push` operations, popping an element starts at its top-most node, which is accessed through the
heads\tails array of the list, and using the `level` field of the node to start at the correct layer. The steps are as follows:
While the element to be popped is still in the list:
1. Change the head\tail pointer at the current level to point to the node after\before the current node.
2. Change the prev\next pointer of the new head\tail to `NULL`
3. Free the current node and decrement the `size` field of the list by 1.
4. If the current layer is now empty after popping, set the head and tail pointers to `NULL` and decrement the `height` field of the list by 1.
5. Set the current node to the node below the popped node.
The function then returns `true` if the `pop` operation was successful, and `false` if the list was empty. Lastly, the reversed behaviors of `pop_left` and `pop_right` call the opposing operation if the `reversed` field of the list is `true`.

## 5. peek_left(*l*), peek_right(*l*)
The `peek_left` and `peek_right` operations return the value of the leftmost and rightmost elements of the input list $l$, respectively. This is done by accessing the 0th index of the `heads` or `tails` arrays, since all elements
are present in the first layer of the list, and returning the `value` field of the node at that pointer. If instead, the list is empty, it prints an error message and returns immediately. Lastly, the reversed behaviors of `peek_left` and `peek_right` call the opposing function if the `reversed` field of the list is `true`.

## 6. get(*l*, *i*), set(*l*, *i*, *v*)
For the input list *l*, the `get` operation returns the value of the element at index *i*, while the `set` operation sets the value of the element at index *i* to the value *v*. Both `get` and `set` function similarly, as they first call the helper function `get_node_at_i` with the same inputs *i* and *i*. Calling `get_node_at_i`
returns the topmost node of the element at *i*. This function gets the required node through the following steps:
1. Adjust the index being searched for to the stored index in the list by adding the index of the first element to it.
2. Start at the first node at the topmost layer.
3. Check its index. There are 4 possibilities:
  1. Its index is the same as the index being searched for. In this case, the node has been found.
  2. Its index is less than the index being searched for. In this case, the node must be to the left of the current node. Move to the left node if it exists, or move to the node below if not.
  3. Its index is greater than the index being searched for. In this case, the node must be to the right of the current node. Move to the right node if it exists, or move to the node below if not.
  4. If the above two steps have been repeated consecutively, the node must not be in this layer. Move to the node below.
5. Repeat step 3 until the node is found.
6. Return the node.
For example, searching for the node at index 3: 
