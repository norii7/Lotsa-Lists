## Dynamic Array Implementation

For the Dynamic Array implementation, a circular deque was utilized to meet the time complexity requirements. Unlike in a straight deque, the elements in a circle deque does not have to be moved when we want to insert an element in the front.

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
The circular dequeue was implemented using a struct named ```list```. It contains all the revelant parameters for a circular deuque including the array itself.

### Main Functions

The following functions were defined to perform the list operations as required in the problem specifications:

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

This function "initializes" the list by creating the deque. It allocates memory for the ```list``` struct and sets its parameters to the default values (elem & capacity = n, reversed = false etc.) It also allocates memory for the array ```arr``` and copies the elements of the input array to it. It returns the ```list``` as output.

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

These functions perform operations as their names suggest. The ```push``` functions put the input element either in the front or the back of the list. While the ```pop``` operations "removes" either the front or the back element and returns a ```bool``` statement of whether the operation is successful.

The actual "pushing" and "pulling" is done by the helper functions defined further down in this document in the **Axuliary Functions** section. The main ```push``` and ```pop``` functions take care of the reversed list case, that is, the functions reverse their directions whenever ```list->reversed == true```.

#### Peek

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

The ```peek_left()``` and ```peek_right()``` functions return the element in the front or the back of the list respectively. This functions "reverses", essentially, one becomes the other when ```list->reversed == true```.

#### Size and Empty

```C
int size(list *l) {
    return l->elem;
}

bool empty(list *l) {
    if(l->elem == 0) {return true;}
    return false;
}
```

These functions simply return ```list``` parameters.

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

The ```get()``` function takes the element in the index provided by the input and simply returns it. The ```set()``` function changes the element in the input index to the input element. Just like the ```push```,```pop``` and ```peek``` functions, ```get()``` and ```set()``` take into account cases when ```list->reversed == true``` and changes the indexing "direction" accordingly.

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

The reverse function simply "inverts" the current value of ```list->reversed```. The actual "reversing" is handled individually by each function.

### Auxiliary Functions

In addition to the required functions, the following auxiliary functions were also defined:

```C
void inflate(list *l);
void deflate(list *l);
void help_push_left(list *l, int64_t v);
void help_push_right(list *l, int64_t v);
bool help_pop_left(list *l);
bool help_pop_right(list *l);
```

#### Inflate

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
```

An array is made 'dynamic' by allowing it to be modified, more specifically—to be resized. While a static array has a fixed size, a dynamic array has no such constraint as long as the computer's memory allows it. 

The ```inflate()``` function doubles the size of the list when it is full, allowing for more elements to be pushed into the list.

#### Deflate

```C
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

The ```deflate()``` function cuts the size of the list in half when it becomes too sparse. This is to save unused memory.

#### Push and Pop Helpers

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

These helper functions do the bulk of the work for the main ```push``` and ```pop``` functions. The functions ```help_push_left()``` and ```help_push_right()``` takes the input element and put them in the head or tail of the list respectively.

The ```help_pop_left()``` and ```help_pop_right()``` functions "pop" the head or tail element by reassigning the current head or tail of the list respectively on the condition that the list is nonempty.

Both ```help_push``` and ```help_pop``` functions resize the list appropriately by calling ```inflate()``` when the list is full during ```help_push``` and ```deflate()``` when half of the list is empty during ```help_pop```.
