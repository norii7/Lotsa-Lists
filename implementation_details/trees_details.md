## Sequence of Trees Implementation

This implementation uses a tree-based deque to represent the dynamic list.

```C
struct tree_root {
    int64_t val;
    int64_t type; //(2^(type+1)) - 1 amount of nodes, how many times it has been merged
    struct tree_root *left;
    struct tree_root *right;
    struct tree_root *left_child;
    struct tree_root *right_child;
    int64_t left_most_value;
    int64_t right_most_value;
    struct tree_root *parent;
}typedef tree_root;

struct list{
    tree_root *head;
    tree_root *tail;
    int orientation;
    int size;
}typedef list;
```
The ```tree_root``` struct represents a binary tree node with the following variables:

* ```val```: Value stored in the node.
* ```type```: Represents the depth of the tree (used for balancing).
* Pointers to children (```left_child```, ```right_child```) and tree nodes (```left```, ```right```).
* ```left_most_value``` and ```right_most_value```: Track values at the leftmost and rightmost ends of the subtree for efficient querying.
* ```parent```: Pointer to the parent node for backtracking during updates.

The ```list``` structure is the deque itself and has the following variables:

* ```head and tail```: Pointers to the start and end of the list.
* ```orientation```: Determines the logical direction of the deque (normal or reversed).
* ```size```: Tracks the number of elements

### Functions and Operations

#### Make

The ```make()``` function is responsible for constructing the initial structure of the deque. It initializes the doubly linked list and sets up the foundation for all subsequent operations.

#### Push

The functions ```absolute_push_left()``` and ```absolute_push_right()``` add a new element by creating a ```tree_root``` node with ```type = 0```. If no merging is required (i.e., the new node's neighbor has a different type), the new node is simply linked to the list.

If the new node's neighbor has the same ```type``` (both are balanced trees of the same depth), a merging process occurs. A new internal node is created with a ```type``` that is one greater than the ```type``` of the child nodes. The ```left_most_value``` and ```right_most_value``` of the new root are set accordingly. The old nodes are then replaced with the merged tree in the list. This merging process continues up the list until nodes of different ```types``` are encountered or the end of the list is reached.

Both ```push_left()``` and ```push_right()``` maintain the ```orientation``` of the list and call the appropriate absolute push function accordingly.

#### Pop

The functions ```absolute_pop_left()``` and ```absolute_pop_right()``` remove the node at the head or tail of the list. If the node is a leaf (```type = 0```), it is simply unlinked and freed.

If the node is an internal node, it is decomposed back into its two smaller subtrees (```left_child``` and ```right_child```). These smaller trees are then reinserted into the list. This process of decomposition and reinsertion continues until only a leaf node remains, which can then be removed.

Both ```pop_left()``` and ```pop_right()``` maintain the ```orientation``` of the list and call the appropriate absolute pop function based on the direction of the pop operation.

#### Peek

Absolute peek operations (```absolute_peek_left()``` and ```absolute_peek_right()```) return the left_most_value or right_most_value of the head or tail node, respectively.

Logical peek operations (```peek_left()``` and ```peek_right()```) maintain the ```orientation``` of the list and call the appropriate absolute peek function based on the direction of the peek operation.

#### Get and Set

The access operation ```get()``` utilizes the ```type``` attribute of nodes to efficiently traverse the structure. At each node encountered during the traversal, the size of the subtree ($2^{type}$) is checked. If the desired index lies outside the range of this subtree, the entire subtree can be skipped, significantly improving the efficiency of the search. This process continues until a leaf node is reached, which contains the desired value.

The ```set()``` traverses to the target node using the same logic as the ```get()``` funciton. Once the target leaf node is reached, the value stored at that node is updated. Following this update, the modification operation propagates changes upward through the tree structure, updating the metadata (```left_most_value``` and ```right_most_value```) in all affected parent nodes to ensure the structure remains consistent and accurate.

#### Reverse

The ```reverse()``` function toggles the ```orientation``` attribute of the ```list```. The logical left and right operations (```push```, ```pop```, ```peek```, ```get```, ```set```) are swapped without physically modifying the structure.