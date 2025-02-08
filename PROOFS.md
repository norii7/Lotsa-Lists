# Dynamic Array Time Complexity

As mention in the ```DETAILS.md``` file, a cirlucar deque was utilized for the Dynamic Array implementation to keep the list operations time-efficient. Below is the struct to represent the deque:

```C
typedef struct list {
    int elem;
    int capacity;
    int head;
    int tail;
    bool is_reversed;
    int64_t *arr;
} list;
```

## Auxiliary Functions

To keep the proof more streamlined, we will start with the helper functions first.

```C
void inflate(list *l);
void deflate(list *l);
void help_push_left(list *l, int64_t v);
void help_push_right(list *l, int64_t v);
bool help_pop_left(list *l);
bool help_pop_right(list *l);
```

### Inflate and Deflate

```C
void inflate(list *l) {
    int new_capacity = l->capacity * 2;
    int64_t *new_arr = (int64_t *)malloc(sizeof(int64_t) * new_capacity);

    for (int i = 0; i < l->elem; i++) {
        new_arr[i] = (l->arr)[(l->head + i) % l->capacity];
    }

    free(l->arr);
    l->capacity = new_capacity;
    l->arr = new_arr;
    l->head = 0;
    l->tail = l->elem;
}

void deflate(list *l) {
    int new_capacity = l->capacity / 2;
    int64_t *new_arr = (int64_t *)malloc(sizeof(int64_t) * new_capacity);

    for (int i = 0; i < l->elem; i++) {
        new_arr[i] = (l->arr)[(l->head + i) % l->capacity];
    }

    free(l->arr);
    l->capacity = new_capacity;
    l->arr = new_arr;
    l->head = 0;
    l->tail = l->elem;
}
```

For both functions, the block of code that we are most interested in is the ```for``` loop. We can ignore the rest of the lines as they all run in $O(1)$ time and have no significant effect on the worst-case running time.

```C
for (int i = 0; i < l->elem; i++) {
        new_arr[i] = (l->arr)[(l->head + i) % l->capacity];
    }
```

Since the code inside the ```for``` loop is only an assignment operation, it runs in $O(1)$ time. The ```for``` loop runs the aforementioned operation $n$ times, with $n$ representing the current number of elements in the list. This means that the total running time is $O(n)$. Therefore, both ```inflate()``` and ```deflate``` have a time complexity of $O(n)$.

### Push Helpers

```C
void help_push_left(list *l, int64_t v) {
    if (l->elem == l->capacity) {
        inflate(l);
    }

    l->head = (l->head - 1 + l->capacity) % l->capacity;
    l->arr[l->head] = v;
    l->elem++;
}

void help_push_right(list *l, int64_t v) {
    if (l->elem == l->capacity) {
        inflate(l);
    }

    l->arr[l->tail] = v;
    l->tail = (l->tail + 1) % l->capacity;
    l->elem++;
}
```

* **Case 1:** *The list is not full.* If there is sufficient capacity in the list, both functions simply insert the input value in the front or back of the list and updates a couple of variables. This all takes $O(1)$ time. Thus, the cost of a single push operation is $O(1)$ when no resizing is required.

* **Case 2:** *The list is full.* If the list is already full, the ```inflate()``` function is called to resize the list, which we know have a running time of $O(n)$. After the list has been resized, the funtions simply perform the same operation in *Case 1,* which runs in $O(1)$.

Note that resizing the list (for ```push``` operations) means doubling its capacity. For a list of capacity $C$, resizing happens only after  $C$ insertions. During resizing, $C$ elements are copied, which takes $O(C)$ time. This cost can be distributed over $C$ insertions, giving an amortized cost per ```push``` of $O(1)$.

### Pop Helpers

```C
bool help_pop_left(list *l) {
    if (l->elem == 0) {
        return false;
    }
    
    l->head = (l->head + 1) % l->capacity;
    l->elem--;

    if (l->elem == l->capacity / 2 && l->capacity > 1) {
        deflate(l);
    }

    return true;
}

bool help_pop_right(list *l) {
    if (l->elem == 0) {
        return false;
    }

    l->tail = (l->tail - 1 + l->capacity) % l->capacity;
    l->elem--;

    if (l->elem == l->capacity / 2 && l->capacity > 1) {
        deflate(l);
    }

    return true;
}
```

* **Case 1:** *More than half of the list is filled.* If there are sufficient elements in the list, both functions simply update ```list``` parameters. This all takes $O(1)$ time. Thus, the cost of a single pop operation is $O(1)$ when no resizing is required.

* **Case 2:** *Less than or half of the list is filled.* If the list is half-full *(or half-empty)*, the ```deflate()``` function is called to resize the list, which we know have a running time of $O(n)$. After the list has been resized, the funtions simply perform the same operation in *Case 1,* which runs in $O(1)$.

For ```pop``` operations, resizing means cutting the capacity of the list in half. If a list has a capacity of $C$, then resizing occurs after only $C/2$ removals. During resizing, $C/2$ elements are copied, which takes $O(C/2)$ time. This cost can be distributed over $C/2$ removals, giving an amortized cost per ```pop``` of $O(1)$.

## Main Functions

The main functions are more straightforward as the bulk of the list operations are performed by the helper functions.

```C
list *make(int n, int64_t *seq);
void push_left(list *l, int64_t v);
void push_right(list *l, int64_t v);
bool pop_left(list *l);
bool pop_right(list *l);
int64_t peek_left(list *l);
int64_t peek_right(list *l);
int size(list *l);
bool empty(list *l);
int64_t get(list *l, int i);
void set(list *l, int i, int64_t v);
void reverse(list *l);
```

#### Make

```C
list *make(int n, int64_t *seq) {
    list *d_arr = (list *)malloc(sizeof(list));
    d_arr->elem = d_arr->capacity = n;
    d_arr->head = 0;
    d_arr->tail = n;
    d_arr->is_reversed = false;
    d_arr->arr = (int64_t *)malloc(sizeof(int64_t) * n);
    for(int i = 0; i < n; i++) {
        (d_arr->arr)[i] = seq[i];
    }
    return d_arr;
}
```

The greatest contributor to the running time of this function is the ```for``` loop. The code inside the loop is an assignment operation which means it runs in $O(1)$ time. This operation is repeated $\ell$ times, where $\ell$ is the length of the sequence passed to the function, giving a a total running time of $O(\ell)$. The rest of the function are just assignment operations running in $O(1)$ time. Therefore, the running time of ```make()``` is $O(\ell)$.

#### Reverse

```C
void reverse(list *l) {
    if(l->is_reversed) {
        l->is_reversed = false;
    } else {
        l->is_reversed = true;
    }
}
```

The ```reverse()``` function simply "inverts" the current value of the ```reversed``` parameter of the ```list``` struct. This takes $O(1)$ time. The actual "reversing" is handled individually by the main functions. This is so that the actual "reversing" operation itself takes $O(1)$ time.

#### Push and Pop

```C
void push_left(list *l, int64_t v) {
    if (!l->is_reversed) {
        help_push_left(l, v);
    } else {
        help_push_right(l, v);
    }
}

void push_right(list *l, int64_t v) {
    if (!l->is_reversed) {
        help_push_right(l, v);
    } else {
        help_push_left(l, v);
    }
}

bool pop_left(list *l) {
    if (!l->is_reversed) {
        return help_pop_left(l);
    } else {
        return help_pop_right(l);
    }
}

bool pop_right(list *l) {
    if (!l->is_reversed) {
        return help_pop_right(l);
    } else {
        return help_pop_left(l);
    }
}
```

As previously mentioned, the actual "pushing" and "pulling" is done by the helper functions which we already know have an amortized cost of $O(1)$. The main funtions simply makes it so that the cases where the list is reversed are handled properly. This is done using a simple conditional statement that takes $O(1)$ time.

### Peek

```C
int64_t peek_left(list *l) {
    if (l->elem == 0) {
        printf("Error. List is empty.\n");
        return -1;
    }

    if (!l->is_reversed) {
        return l->arr[l->head];
    } else {
        return l->arr[(l->tail - 1 + l->capacity) % l->capacity];
    }
}

int64_t peek_right(list *l) {
    if (l->elem == 0) {
        printf("Error. List is empty.");
        return -1;
    }

    if (!l->is_reversed) {
        return l->arr[(l->tail - 1 + l->capacity) % l->capacity];
    } else {
        return l->arr[l->head];
    }
}
```

The ```peek``` functions first check whether the list is empty. This takes $O(1)$ time. Then, they directly access the front or rear elements accordingly and outputs them all in $O(1)$ time. Thus, the running time of the ```peek``` functions is $O(1)$.

### Size and Empty

```C
int size(list *l) {
    return l->elem;
}

bool empty(list *l) {
    if(l->elem == 0) {return true;}
    return false;
}
```

Both of these functions simply return ```list``` parameters. Thus, they both run in $O(1)$ time.

#### Get and Set

```C
int64_t get(list *l, int i) {
    if(i >= 0 && i < l->elem) {
        if (!l->is_reversed) {
            return (l->arr)[(l->head + i) % l->capacity];
        } else {
            return (l->arr)[(l->tail - 1 - i + l->capacity) % l->capacity];
        }
    } else {
        printf("Index Error\n");
        return -1;
    }

}
void set(list *l, int i, int64_t v) {
    if(i >= 0 && i < l->elem) {
        if (!l->is_reversed) {
            (l->arr)[(l->head + i) % l->capacity] = v;
        } else {
            (l->arr)[(l->tail - 1 - i + l->capacity) % l->capacity] = v;
        }
    } else {
        printf("Index Error\n");
    }
}
```

Both of these functions access the element located in the input index the same way, that is, they use the circular deque indexing formula which changes "directions" depending on whether the list is currently reversed or not. Since the element is directly accessible, it only takes $O(1)$ time to perform both functions.

<br>

# Skip List Time Complexity

### push()
Creating a node takes O(1) time. Each time we call ```push()``` we flip a coin to see whether or not we add an extra node on the layer above the current node. The probability of adding a node on the layer above the bottom most layer is 1/2, the probability for the layer above that is 1/4, then 1/8, and so on. Meaning that if we call ```push()``` $l$ times, the expected amount of created nodes is $n + \frac{1}{2}l + \frac{1}{4}l + \frac{1}{8}l...$. This infinite series converges to $2l$. Meaning we expect to create $2l$ amount of nodes. If we divide this $2l$ among the $l$ times we call the push, we get 2. Meaning per ```push()``` call we expect to create 2 nodes. This makes the time complexity $O(1)$ expected.
### make()
Our implementation of ```make()``` simply calls the ```push_right()``` function for each element in the sequnce given. It was proven the ```push()``` functions take $O(1)$ expected time. If $l$ is the amount of elements in the sequence, the time complexity becomes $l*O(1)$. This results in $O(l)$ expected time complexity.

### pop()
Using the same thought process as discussed in the ```push()``` function, we can say that for each ```pop()``` call we can expect to pop 2 nodes on average. This makes the time complexity of the ```pop()``` function $O(1)$ expected.

### peek()
This function simply looks at a value that is directly accessible. It takes $O(1)$ worst-case.
### size()
The ```size()``` function accesses the ```size``` attribute of the list (i.e., ```l->size```). This value is updated everytime ```push()``` and ```pop()``` are called. Hence making it a readily accessed value. This function takes $O(1)$ worst-case.

### get()
Since the probability of making a new node on a layer is multiplied by $\frac{1}{2}$ for each succeeding node, we can say that the expected height of a skip list is $log(n)$. Therefore, if we were to travel from the top most to the bottom most layer it should on average $log(n)$ steps. Since the probability of a successful coin flip is $\frac{1}{2}$, we can say that its expected value is 1. Meaning, on average we need to make 1 failed attempt to make a successful coin flip. This means that per layer, we expect to travel 1 step horizontally before making a vertical move. Therefore the time complexity is $O(1)*O(log(n))$ expected, which is $O(log(n))$ expected.

### set()
When calling ```set()``` you are essentially calling get ```get()``` but doing extra steps. (Let us call the function of doing ```get()``` without returning a value ```get_to()```) These extra steps include changing the value of the node you arrive to when you do ```get_to()``` , then also changing the value of each consequent node below it. We know that the average height of a skip list is $log(n)$, upon arriving at the node upon calling ```get_to()``` you wouldn't have to travel more than $log(n)$ steps vertically as that you would have already done vertical steps before getting there. Worst case is that you arrive at the node at height $log(n)$. We know that ```get_to()``` takes $O(log(n))$, and on average we need not take more than $log(n)$ steps. Hence the time complexity is $O(log(n)) + O(log(n))$, giving $O(log(n))$ expected.

### reverse()
The following is the code for the ```reverse()``` function:

```C
void reverse(list *sl){
    if (sl->orientation == 0){
        sl->orientation = 1;
    }
    else {
        sl->orientation = 0;
    }
}
```

It simply changes the state of the list, where 0 represents a normal direction while 1 represents the reverse direction. This takes $O(1)$ worst-case time.

The work in reversing the list, or at least making it "functionally reverse" is when calling functions when the state is in reverse. The utility of functions are switched when the state is in reverse. For example:

```C
void push_left(list *sl, int64_t v){
    if (sl->orientation == 0){
        absolute_push_left(sl, v);
    }
    else{
        absolute_push_right(sl,v);
    }
}
```
```C
bool pop_right(list *sl){
    if (sl->orientation==0){
        absolute_pop_right(sl);
    }
    else{
        absolute_pop_left(sl);
    }
}
```

In the code above we can see that the program simply reverses the utility of each function depending on the state. Hence calling the ```reverse()``` function takes $O(1)$ worst-case time.

<br>

# Sequence of Trees Time Complexity
    Below are the proofs for each function in the Sequence of Trees Implementation of the Dynamic List data structure.

## Main Functions

### make
```C
list *make(int n, int64_t *seq){

    list * l= (list*)malloc(sizeof(list));
    l->size = 0;
    l->orientation = 0;
    if (n==0){
        l->head = NULL;
        l->tail = NULL;
        return l;
    }
    
    for (int i = 0; i<n; i++){
        push_right(l, seq[i]);
    }
    return l;
}
```
>To make the tree, we call ```push_right``` as many times as the size $l$ of the input sequence in order to push the sequence values to the list. Half of the time: these ```push``` calls take constant time, since they only push a $k=0$ tree with the needed value. The other half of the ```push``` calls achieve the worst case for the ```push``` function and take $O(log(l))$ time. 

>So, we can write the total time complexity as 
<br>$ \frac{l}{2} * O(1) + \frac{l}{2} * O(log(l)) = O(l) + O(log(l))$
<br> Note that $l > log(l)$ So, 
<br> $O(l) + O(log(l)) = O(l)$
<br>**Q.E.D.**

### push_*
```C
void absolute_push_left(list *l, int64_t v){
    tree_root *new_root = create_root(v);
    if (l->size == 0){
        l->head = new_root;
        l->tail = new_root;
        l->size++;
        return;
    }
    new_root->right = l->head;
    l->head->left = new_root;
    l->head = new_root;

    while (l->head->type == l->head->right->type){
        combine_trees_left(l);
        if (l->head->right == NULL){
            break;
        }
    }
    l->size++;
}

void absolute_push_right(list *l, int64_t v){
    tree_root *new_root = create_root(v);
    if (l->size == 0){
        l->head = new_root;
        l->tail = new_root;
        l->size++;
        return;
    }
    new_root->left = l->tail;
    l->tail->right = new_root;
    l->tail = new_root;

    while (l->tail->type == l->tail->left->type){
        combine_trees_right(l);
        if (l->tail->left == NULL){
            break;
        }
    }
    l->size++;
}  

void push_left(list *l, int64_t v){
    if (l->orientation == 0){
        absolute_push_left(l, v);
    }
    else{
        absolute_push_right(l, v);
    }
}

void push_right(list *l, int64_t v){
    if (l->orientation == 0){
        absolute_push_right(l, v);
    }
    else{
        absolute_push_left(l, v);
    }
}
```
>To push a new value to the list, we simply push a new tree with $k=0$ to the needed side of the doubly linked list of trees - this takes $O(1)$ time. However, following that consecutive trees must have non-equal $k$ values, we combine consecutive trees - which we can do in $O(1)$ time -  whenever a push breaks that rule. This process is done in the ```absolute_push_*``` functions called by the ```push_*``` functions appropriately based on the ```orientation``` of the list.

>Now, the worst-case time complexity would be $O(1) + m * O(1)$ where $m$ is the number of times we need to merge. In the worst case, $m$ is maximized. This is when $k_i = k_{i-1} + 1$ for ```absolute_push_left``` and $k_i = k_{i+1} + 1$ for ```absolute_push_right```, where $0 \leq i \leq t$ with $t$ as the number of trees in the list.

>With this condition, we would then need to combine as many times as the height of the perfect binary tree needed to store all $n + 1$ leaves, where $n$ is the current number of leaves. Note that the height of this tree would be $O(log_2(n+1)) = O(log(n+1)) = O(log(n))$.
<br> So, the worst-case time complexity would then be 
<br>$O(1) + O(log(n)) * O(1) = O(1) + O(log(n)) = O(log(n))$ 
<br> **Q.E.D.**

### pop_*
```C
bool absolute_pop_left(list *l){
    if (l->size == 0){
        printf("Size is 0 cannot pop");
        return false;
    }

    if (l->size == 1){
        tree_root *temp = l->head;
        l->head = NULL;
        l->tail = NULL;
        l->size--;
        free(temp);
        return true;
    }
    if (l->head->type == 0){
        tree_root *temp = l->head;
        l->head = temp->right;
        l->head->left = NULL;
        l->size--;
        free(temp);
        return true;
    }
    while(l->head->type!=0){
        decompose_left(l);
    }
    tree_root *temp = l->head;
    l->head = temp->right;
    l->head->left = NULL;
    l->size--;
    free(temp);
    return true;
}
bool absolute_pop_right(list *l){
    if (l->size == 0){
        printf("Size is 0 cannot pop");
        return false;
    }

    if (l->size == 1){
        tree_root *temp = l->tail;
        l->head = NULL;
        l->tail = NULL;
        l->size--;
        free(temp);
        return true;
    }
    if (l->tail->type == 0){
        tree_root *temp = l->tail;
        l->tail = temp->left;
        l->tail->right = NULL;
        l->size--;
        free(temp);
        return true;
    }
    while(l->tail->type!=0){
        decompose_right(l);
    }
    tree_root *temp = l->tail;
    l->tail = temp->left;
    l->tail->right = NULL;
    l->size--;
    free(temp);
    return true;
}

bool pop_left(list *l){
    if (l->orientation == 0){
        return absolute_pop_left(l);
    }
    else{
        return absolute_pop_right(l);
    }
}

bool pop_right(list *l){
    if (l->orientation == 0){
        return absolute_pop_right(l);
    }
    else{
        return absolute_pop_left(l);
    }
}
```
>To pop a value from the list, we simply pop the leftmost or rightmost $k = 0$ tree from the doubly linked list of trees - which takes $O(1)$ time. If the tree at the needed side has $k > 0$, we simply decompose - which can be done in $O(1)$ time - the tree until the needed side now has a tree of $k = 0$. This process is done in the ```absolute_pop_*``` functions called by the ```pop_*``` functions appropriately based on the ```orientation``` of the list.

>Now, the worst-case time complexity would be $O(1) + d * O(1)$ where $d$ is the number of times we need to decompose to have a $k = 0$ tree to pop. In the worst case, $d$ is maximized. This is when all the values are stored in the leaves of a single tree.

>When this is the case, we simply want to decompose - that is cut the tree in half - until we get to a tree with a single node. So, this is the same as having $log_2(n)$ where $n$ is the number of leaves in the current tree. $d$ can then be taken as $O(log_2(n)) = O(log(n))$ and the worst-case time complexity as 
<br> $O(1) + O(log(n)) * O(1) = O(1) + O(log(n)) = O(log(n))$
<br> **Q.E.D.**

### peek_*
```C
int64_t absolute_peek_left(list *l){
    if (l->size == 0){
        printf("Size 0 CANNOT PEEK");
        return -1;
    }
    else{
        return l->head->left_most_value;
    }
}
int64_t absolute_peek_right(list *l){
    if (l->size == 0){
        printf("Size 0 CANNOT PEEK");
        return -1;
    }
    else{
        return l->tail->right_most_value;
    }
}
int64_t peek_left(list *l){
    if (l->orientation == 0){
        return absolute_peek_left(l);
    }
    else{
        return absolute_peek_right(l);
    }
}
int64_t peek_right(list *l){
    if (l->orientation == 0){
        return absolute_peek_right(l);
    }
    else{
        return absolute_peek_left(l);
    }
}
```
>Since the leftmost and rightmost values are being kept track of in the ```list``` class, the function only needs to return whichever is needed. So, it only takes $O(1)$ time.
<br>**Q.E.D.**

### size
```C
int size(list *l){
    return l->size;
}
```
>Since all the function does is to return the existing ```size``` value from the ```list``` class, it runs in $O(1)$ time.
<br>**Q.E.D.**

### empty
```C
bool empty(list *l){
    if (size(l) == 0){
        return true;
    }
    else{
        return false;
    }
}
```
>To check if the list is empty, the function only needs to get the size of the list - which was proved to be done in $O(1)$ time - and then check if it is equal to 0 - also in $O(1)$ time. So the function would run in $O(1)$ time, as well.
<br>**Q.E.D.**

### get
```C
int64_t normal_get(list *l, int i){
    if (i<0 || i>((l->size) - 1)){
        printf("Index Out of Range\n");
        return -1;
    }
    int distance = i;
    tree_root *temp = l->head;
    while(distance>=(1LL<<(temp->type))){
        distance -= 1LL<<(temp->type);
        temp = temp->right;
    }
    while(temp->left_child!= NULL){
        if (distance>=(1LL<<(temp->left_child->type))){
            distance -= 1LL<<(temp->left_child->type);
            temp = temp->right_child;
        }
        else{
            temp = temp->left_child;
        }
    }
    return temp->val;   
}

int64_t reverse_get(list *l, int i){
    if (i<0 || i>((l->size) - 1)){
        printf("Index Out of Range\n");
        return -1;
    }
    int distance = i;
    tree_root *temp = l->tail;
    while(distance>=(1LL<<(temp->type))){
        distance -= 1LL<<(temp->type);
        temp = temp->left;
    }
    while(temp->right!= NULL){
        if (distance>=(1LL<<(temp->right_child->type))){
            distance -= 1LL<<(temp->right_child->type);
            temp = temp->left_child;
        }
        else{
            temp = temp->right;
        }
    }
    return temp->val;   
}

int64_t get(list *l, int i){
    if (l->orientation == 0){
        return normal_get(l,i);
    }
    else{
        return reverse_get(l,i);
    }
}
```
>To get the value of the needed index, the functions first traverses through the linked list of trees. Once it finds the correct tree, it then traverses through that tree to reach the needed leaf. Every traversal step takes $O(1)$ time. It then returns the value of that node. 

>So, the time complexity depends on how many $O(1)$ steps it needs to reach the required node. That is list traversal plus tree traversal. The list traversal, in the worst case, merely depends on the number of trees present or $t$. The tree traversal on the other hand works by repeatedly choosing between the left and right child to move down to until it reaches the corrrect leaf. This effectively repeatedly halves the choices until only one remains, so it's $log_2(n_0)$ where $n_0$ is the number of elements in the target tree.

>The time complexity would then be $O(t) + O(log_2(n_0)) = O(t) + O(log(n_0))$
<br> Note that the maximum value of $t$ can be expressed as $ceil(log_2(n))$ where $n$ is the total number of elements, since we can maximize $t$ by storing all values in the leaves of only 1 or 2 trees then decomposing the levels of the larger tree such that we minimize consecutive trees of the same type. So, 
<br>$t = O(ceil(log_2(n))) = O(floor(log_2(n-1) + 1)) = O(log_2(n-1) + 1)$
<br>$=O(log(n-1)) = O(log(n))$

>Therefore, the final time complexity to traverse to the needed node and return its value is 
<br>$O(O(log(n))) + O(log(n_0)) + O(1)= O(log(n)) + O(log(n_0))$
<br>Note that $n > n_0$ since $n$ is the total amount of elements and $n_0$ is the number of elements in just one tree. So,
<br>$O(log(n)) + O(log(n_0)) = O(log(n))$
<br>**Q.E.D.**

### set
```C
void normal_set(list *l, int i, int64_t v){
    if (i<0 || i>((l->size) - 1)){
        printf("Index Out of Range\n");
        return;
    }
    int distance = i;
    tree_root *temp = l->head;
    while(distance>=(1LL<<(temp->type))){
        distance -= 1LL<<(temp->type);
        temp = temp->right;
    }
    if (temp->type == 0){
        temp->left_most_value = v;
        temp->right_most_value = v;
        temp->val = v;
        return;
    }
    int arr_size = temp->type;
    int *back_track_arr = (int*)malloc(arr_size*sizeof(int));
    /*Array takes note of whether we went left_child or right_child in the tree, 0 is left 1 is right
    We use this to update the left_most_val and right_most_val for the peek() functions
    After reaching the end and changing the value, we update the right_most_val and left_most_val of the higher trees*/
    int curr_index_bta = 0; //Keeps track of index we update in the array above

    while(temp->left_child!= NULL){
        if (distance>=(1LL<<(temp->left_child->type))){
            distance -= 1LL<<(temp->left_child->type);
            temp->right_child->parent = temp;
            temp = temp->right_child;
            back_track_arr[curr_index_bta] = 1;
            curr_index_bta++;
        }
        else{
            temp->left_child->parent = temp;
            temp = temp->left_child;
            back_track_arr[curr_index_bta] = 0;
            curr_index_bta++;
        }
    }

    temp->left_most_value = v;
    temp->right_most_value = v;
    temp->val = v;

    for (int i = arr_size - 1; i>=0; i--){
        temp = temp->parent;
        
        if (back_track_arr[i] == 0){
            printf("Pass 0\n");
            temp->left_most_value = temp->left_child->left_most_value;
            temp->val = temp->left_most_value;
        }
        else{
            temp->right_most_value = temp->right_child->right_most_value;
        }
    }
    free(back_track_arr);
}

void reverse_set(list *l, int i, int64_t v){
    if (i<0 || i>((l->size) - 1)){
        printf("Index Out of Range\n");
        return;
    }
    int distance = i;
    tree_root *temp = l->tail;
    while(distance>=(1LL<<(temp->type))){
        distance -= 1LL<<(temp->type);
        temp = temp->left;
    }
    if (temp->type == 0){
        temp->left_most_value = v;
        temp->right_most_value = v;
        temp->val = v;
        return;
    }
    int arr_size = temp->type;
    int *back_track_arr = (int*)malloc(arr_size*sizeof(int));
    /*Array takes note of whether we went left_child or right_child in the tree, 0 is left 1 is right
    We use this to update the left_most_val and right_most_val for the peek() functions
    After reaching the end and changing the value, we update the right_most_val and left_most_val of the higher trees*/
    int curr_index_bta = 0; //Keeps track of index we update in the array above

    while(temp->right_child!= NULL){
        if (distance>=(1LL<<(temp->right_child->type))){
            distance -= 1LL<<(temp->right_child->type);
            temp->left_child->parent = temp;
            temp = temp->left_child;
            back_track_arr[curr_index_bta] = 0;
            curr_index_bta++;
        }
        else{
            temp->right_child->parent = temp;
            temp = temp->right_child;
            back_track_arr[curr_index_bta] = 1;
            curr_index_bta++;
        }
    }

    temp->left_most_value = v;
    temp->right_most_value = v;
    temp->val = v;

    for (int i = arr_size - 1; i>=0; i--){
        temp = temp->parent;
        
        if (back_track_arr[i] == 0){
            temp->left_most_value = temp->left_child->left_most_value;
            temp->val = temp->left_most_value;
        }
        else{
            temp->right_most_value = temp->right_child->right_most_value;
        }
    }
    free(back_track_arr);
}

void set(list *l, int i, int64_t v){
    if (l->orientation == 0){
        normal_set(l,i,v);
    }
    else{
        reverse_set(l,i,v);
    }
}
```
>The ```set``` function works very similarly to the ```get``` functions in its traversal to the target node - that is, it traverses to said node in $O(log(n))$ time. The only difference is that: with that node, instead of returning it, it changes its value still in $O(1)$ time. So, the final time complexity of traversing to and setting the value is
<br>$O(log(n)) + O(1) = O(log(n))$
<br>**Q.E.D.**

### reverse
```C
void reverse(list *l){
    if (l->orientation == 0){
        l->orientation = 1;
    }
    else{
        l->orientation = 0;
    }
}
```
>Since the function only flips the value ```reversed``` in the ```list``` class between 1 and 0, it only runs in $O(1)$ time.
<br>**Q.E.D.**

## Auxiliary Functions

### create_root
```C
tree_root *create_root(int64_t v){
    tree_root *new_root = (tree_root*)malloc(sizeof(tree_root));
    new_root->val = v;
    new_root->left = NULL;
    new_root->right = NULL;
    new_root->left_child = NULL;
    new_root->right_child = NULL;
    new_root->type = 0;
    new_root->left_most_value = v;
    new_root->right_most_value = v;
    return new_root;
}
```
>The function creates a new root by allocating memory and setting the appropriate values and pointers. Since the function only does allocations and definition of class values, it runs in $O(1)$ time.
<br>**Q.E.D.**

### combine_trees_*
```C
void combine_trees_right (list *l){
    tree_root *current_tree = l->tail;
    tree_root *new_root = create_root(current_tree->left->val);
    new_root->left_child = current_tree->left;
    new_root->right_child = current_tree;
    new_root->left_most_value = new_root->left_child->left_most_value;
    new_root->right_most_value = new_root->right_child->right_most_value;
    new_root->type = new_root->left_child->type + 1;

    if (current_tree->left->left == NULL){
        l->head = new_root;
        l->tail = new_root;
        return;
    }

    current_tree->left->left->right = new_root;
    new_root->left = current_tree->left->left;
    l->tail = new_root;

}

void combine_trees_left (list *l){
    tree_root *current_tree = l->head;
    tree_root *new_root = create_root(current_tree->right->val);
    new_root->left_child = current_tree;
    new_root->right_child = current_tree->right;
    new_root->left_most_value = new_root->left_child->left_most_value;
    new_root->right_most_value = new_root->right_child->right_most_value;
    new_root->type = new_root->left_child->type + 1;
    if (current_tree->right->right == NULL){
        l->head = new_root;
        l->tail = new_root;
        return;
    }

    current_tree->right->right->left = new_root;
    new_root->right = current_tree->right->right;
    l->head = new_root;

}
```
>To combine two trees of the same type, the functions create a new root - done in $O(1)$ time - and set that the two trees as the children of that root. This effectively combines the trees into a new $k + 1$ tree where $k$ is the type of the trees. With the ```create_root``` function and all other $O(1)$ time processes, the functions take $O(1)$ time as well.
<br>**Q.E.D.**

### decompose_*
```C
void decompose_left(list *l){
    if(l->head->right == NULL){
        tree_root *temp = l->head;
        l->head = l->head->left_child;
        l->tail = l->head->right_child;
        free(temp);
    }
    else{
        tree_root *temp = l->head;
        l->head->right->left = l->head->right_child;
        l->head->right_child->right = l->head->right;
        l->head = l->head->left_child;
        free(temp);
    }
}

void decompose_right(list *l){
    if(l->tail->left == NULL){
        tree_root *temp = l->tail;
        l->head = l->tail->left_child;
        l->tail =l->tail->right_child;
        free(temp);
    }
    else{
        tree_root *temp = l->tail;
        l->tail->left->right = l->tail->left_child;
        l->tail->left_child->left = l->tail->left;
        l->tail = l->tail->right_child;
        free(temp);
    }
}
```
>To decompose a tree, the function removes the root and disconnects it from its children. This effectively create two separate tree of type $k - 1$, which were previously part of the old type $k$ tree. To achieve this, it only needs to change around pointer values and free the memory used by the old root. So it only takes $O(1)$ time.
<br>**Q.E.D.**