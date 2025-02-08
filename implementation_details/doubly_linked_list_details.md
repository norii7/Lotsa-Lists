## Doubly Linked List Implementation

For the Doubly Linked List implementation, a class ```node``` was created in order to be used to make up the actual doubly linked list. 

```C
typedef struct node{
    int64_t val;
    struct node *next;
    struct node *prev;
} Node;
```
The dynamic list itself would be defined in the ```list``` class, with pointers to ```head``` and ```tail``` nodes; a boolean value to track if the list is reversed; and the int ```size``` to track to current number of elements in the list.

```C
typedef struct list{
    Node *head;
    Node *tail;
    int size;
    bool reversed;
} list;
```

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
list *make(int n, int64_t *seq){
    list *l = malloc(sizeof(list));

    Node *head = NULL, *tail = NULL, *prev = NULL;

    for(int i = 0; i < n; i++){
        Node *new = malloc(sizeof(Node));

        new->val = *(seq + i);
        new->prev = prev;
        if(prev != NULL){
            prev->next = new;
        }
        if(i == 0){
            head = new;
        }
        if(i == n-1){
            new->next = NULL;
            tail = new;
        }

        prev = new;
    }

    l->head = head; 
    l->tail = tail;
    l->size = n; 
    l->reversed = false;

    return l;
}
```

This function "initializes" the list by allocating memory for and creating an instance of the ```list``` class. At first, this list would have its ```head``` and ```tail``` as ```NULL```; ```size``` equal to 0; and ```reversed``` set to ```false```. It then copies the elements of the input sequence to the ```list``` as nodes then sets ```head```, ```tail```, and ```size``` accordingly.

#### Push and Pop

```C
void push_left(list *l, int64_t v){
    Node *new = malloc(sizeof(Node));
    new->val = v;

    if(empty(l) == true){
        new->next = NULL;
        new->prev = NULL;
        l->tail = new;
        l->head = new;
    }else{
        if(l->reversed == false){
            Node *old = l->head;
            new->next = old;
            new->prev = NULL;
            old->prev = new;
            l->head = new;
        }else{
            Node *old = l->tail;
            new->next = NULL;
            new->prev = old;
            old->next = new;
            l->tail = new;
        }
    }

    l->size += 1;
}

void push_right(list *l, int64_t v){
    Node *new = malloc(sizeof(Node));
    new->val = v;

    if(empty(l) == true){
        new->next = NULL;
        new->prev = NULL;
        l->tail = new;
        l->head = new;
    }else{
        if(l->reversed == false){
            Node *old = l->tail;
            new->next = NULL;
            new->prev = old;
            old->next = new;
            l->tail = new;
        }else{
            Node *old = l->head;
            new->next = old;
            new->prev = NULL;
            old->prev = new;
            l->head = new;
        }
    }

    l->size += 1;
}

bool pop_left(list *l){
    if(empty(l) == true){
        return false;
    }else if(size(l) == 1){
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;

        return true;
    }else{
        if(l->reversed == false){
            Node *new = l->head->next, *old = l->head;
            new->prev = NULL;
            l->head = new;
            free(old);
        }else{
            Node *new = l->tail->prev, *old = l->tail;
            new->next = NULL;
            l->tail = new;
            free(old);
        }

        l->size -= 1;

        return true;
    }
}

bool pop_right(list *l){
    if(empty(l) == true){
        return false;
    }else if(size(l) == 1){
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;

        return true;
    }else{
        if(l->reversed == false){
            Node *new = l->tail->prev, *old = l->tail;
            new->next = NULL;
            l->tail = new;
            free(old);
        }else{
            Node *new = l->head->next, *old = l->head;
            new->prev = NULL;
            l->head = new;
            free(old);
        }

        l->size -= 1;

        return true;
    }
}
```

These functions perform operations as their names suggest. The ```push``` functions put the input element either in the front or the back of the list. While the ```pop``` operations "removes" either the front or the back element and returns a ```bool``` statement of whether the operation is successful.

To push, a new node is allocated in memory and set with the input value. Its ```next``` and ```prev``` properties are set based on whether it is pushed on the left or on the right. Once it's properly linked, the list ```size``` is incremented by 1 and the ```head``` or ```tail``` pointers are adjusted accordingly. If ```reversed``` is ```true```, the functionalities for left and right are simply switched around.

To pop, the list ```head``` or ```tail``` is simply freed from memory and the nodes that were linked to them have their ```prev``` or ```next``` pointers adjusted accordingly. The list ```head``` and/or ```tail``` is also changed as needed and ```size``` is decremented by 1, then the function returns ```true```. However, if the list was empty to begin with, return ```false``` immediately. If ```reversed``` is ```true```, the functionalities for left and right are simply switched around.

#### Peek

```C
int64_t peek_left(list *l){
    if(empty(l) == true){
        printf("The list is empty. Nothing to peek.\n");
        return -1;
    }else{
        if(l->reversed == false){
            return l->head->val;
        }else{
            return l->tail->val;
        }
    }
}

int64_t peek_right(list *l){
    if(empty(l) == true){
        printf("The list is empty. Nothing to peek.\n");
        return -1;
    }else{
        if(l->reversed == false){
            return l->tail->val;
        }else{
            return l->head->val;
        }
    }
}
```

The ```peek_left()``` and ```peek_right()``` functions return the ```val``` of ```head``` and ```tail``` respectively. If the list is empty to begin with, print a message and return -1.

#### Size and Empty

```C
int size(list *l){
    return l->size;
}

bool empty(list *l){
    if(size(l) == 0){
        return true;
    }else{
        return false;
    }
}
```

The ```size``` function returns the ```size``` parameter of the list and the ```empty``` function returns the boolean for whether or not this ```size``` is equal to 0.

#### Get and Set

```C
int64_t get(list *l, int i){
    if(empty(l) == true){
        printf("The list is empty. Nothing to get.\n");
        exit(EXIT_FAILURE);
    }else{
        Node *current;
        if(l->reversed == false){
            current = l->head;
        }else{
            current = l->tail;
        }
        int curr = 0;        

        while(curr < i){
            if(l->reversed == false){
                current = current->next;
            }else{
                current = current->prev;
            }
            
            curr++;
        }

        return current->val;
    }

}

void set(list *l, int i, int64_t v){
    if(empty(l) == true){
        printf("The list is empty. Nothing to set.\n");
        exit(EXIT_FAILURE);
    }else{
        Node *current;
        if(l->reversed == false){
            current = l->head;
        }else{
            current = l->tail;
        }
        int curr = 0;        

        while(curr < i){
            if(l->reversed == false){
                current = current->next;
            }else{
                current = current->prev;
            }
            
            curr++;
        }

        current->val = v;
    }
}
```

The ```get()``` function takes the element in the index provided by the input and simply returns it. The ```set()``` function changes the element in the input index to the input element. Just like the ```push```,```pop``` and ```peek``` functions, ```get()``` and ```set()``` take into account cases when ```list->reversed == true``` and changes the indexing "direction" accordingly.

#### Reverse

```C
void reverse(list *l){
    l->reversed = !(l->reversed);
    return;
}
```

The ```reverse``` function simply flips the boolean value ```reversed``` stored in the ```list``` class. This value affects the functionalities of ```push```, ```pop```, ```peek```, ```get```, and ```set```.