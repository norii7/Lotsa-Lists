## Skip List Implementation


For the skip list implementation three structs were made. The ```node``` struct represents each node in a "normal" linked list. The struct ```linked_list``` is used to represent the linked lists in the varying layers in a skip list. These ```linked_list``` structs are kept in an array ```arr```  in ```list``` which serves as an access point to the different layers and express ways in a skip list. The sturct ```list``` is effectively the skip list.

```C
struct node{
    int64_t val;
    struct node *left;
    struct node *right;
    struct node *below;
    struct node *above; //Added for popping
    int64_t relative_position;
}typedef node;


struct linked_list{
    node *head;
    node *tail;
    int size;
}typedef linked_list;


struct list{
    linked_list **arr;
    int active_layers; //0 indexed, -1 if no list
    int arr_size; // 0 if list has no items, 1 if list has a "regular" linked list
    int orientation; // 0 if forward 1 if reversed;
    int size;
}typedef list;
```

### Main Functions
#### Reverse in O(1)
The state of the direction of the array is stored within the ```list``` struct with the ```orientation``` property. Wherein 0 represents normal direction and 1 represents the reverse dirrectoin. O(1) reverse is achieved through simply calling different functions depending on the state. For example: 

```C
void push_right(list *sl, int64_t v){
    if (sl->orientation == 0){
        absolute_push_right(sl, v);
    }
    else{
        absolute_push_left(sl,v);
    }
}
```

In the code snippet above it can be seen that when calling ```push_right()``` the program calls helper functions depending on the current orientation. The ```absolute_push_right``` and ```absolute_push_left``` represents the actual implementation of the push functions when the orientation is normal. Other functions with reverse are implemented similarly, having an "absolute" version of the function. We will take a look at the "absolute" version of the functions going forward.


#### push()
When the ```push()``` function is called we attach a new node to the bottom most layer of the skip list. We then "flip a coin" through the ```rand()``` function. We add a node above the recently pushed node if the coin lands on heads (i.e., ```rand()%2 == 1```). When this is done, we update the respective heads/tails of the layer we are adding a node to. We continue to do this unti we land on a tails (i.e., ```rand()%2 == 0```)

```C
void absolute_push_right(list *sl, int64_t v){

    int layer = 0; //0 indexed
    node *new_node = create_node(v);
    sl->size++;
    linked_list *new_linked_list;
    if (sl->active_layers == -1){
        new_node->relative_position = 0;
        linked_list *new_linked_list = (linked_list*)malloc(sizeof(linked_list));
        new_linked_list->size = 0;
        new_linked_list->head = new_node;
        new_linked_list->tail = new_node;
        sl->arr[layer] = new_linked_list;
        sl->arr[layer]->size++;
        sl->active_layers++;
    }

    else{
        new_node->relative_position = sl->arr[0]->tail->relative_position + 1;
        sl->arr[layer]->tail->right = new_node;
        new_node->left = sl->arr[layer]->tail;
        sl->arr[layer]->tail = new_node;
        sl->arr[layer]->size++;
    }
    int p = rand() % 2;

    while (p == 1) {
        layer++;
        if (sl->arr_size<=(layer+1)){ 
            sl->arr = realloc(sl->arr, sizeof(linked_list*)*2*(sl->arr_size));
            sl->arr_size *= 2;
        }
        new_node = create_node(v);
        new_node->below = sl->arr[layer - 1]->tail;
        new_node->relative_position = new_node->below->relative_position;
        sl->arr[layer-1]->tail->above = new_node;
        if (sl->active_layers<layer){//If layer does not exist
            new_linked_list = (linked_list*)malloc(sizeof(linked_list));
            new_linked_list->head = new_node;
            new_linked_list->tail = new_node;
            sl->arr[layer] = new_linked_list;
            sl->active_layers++;
        }
        
        else{
            sl->arr[layer]->tail->right = new_node;
            new_node->left = sl->arr[layer]->tail;
            sl->arr[layer]->tail = new_node;
        }
        p = rand() % 2;
    }

}
```
Note: ```absolute_push_left``` is implemented similarly with some of the snippets of code changed (i.e., insteal of tail we type head, instead of right we type left)

#### pop()
The ```pop()``` functions are implemented by going to the head/tail (depending if pop_right or pop_left) of the bottom most layer. The program then sets a temporary variable on the current node to keep track of node where we need to use ```free()```. The program then incrementally goes to the layer above the node (i.e.,```temp->above```), consequently freeing the node below. We do this until all layers have been cleared.
```C
bool absolute_pop_right(list * sl){
    if (size(sl)<=0){
        printf("Size 0 Cannot Pop\n");
        return false;
    }
    int layer = 0;
    node *next_pop = sl->arr[0]->tail;
    node *temp;
    while (next_pop != NULL){
        temp = next_pop;
        if (sl->arr[layer]->tail == sl->arr[layer]->head){
            sl->active_layers--;
            sl->arr[layer]->tail = NULL;
            sl->arr[layer]->head = NULL;
            next_pop = temp->above;
        }

        else{
            sl->arr[layer]->tail = temp->left;
            sl->arr[layer]->tail->right = NULL;
            next_pop = temp->above; 
        }
        free(temp);
        layer++;
    }
    sl->arr[0]->size--;
    sl->size--;
    return true;
}
```
Note: ```absolute_pop_left()``` is implemented similarly with some of the snippets of code changed (i.e., insteal of tail we type head, instead of right we type left)

#### make()
The make function takes advantage of the already made push function, repeatedly calling it for each element in the given sequence of numbers.
```C
list * make (int n, int64_t *seq){
    list *sl = (list*)malloc(sizeof(list));
    sl->active_layers = -1; //-1 is empty, since 0 indexed
    sl->arr_size = n;
    sl->orientation = 0; //Forward Orientation
    sl->size = 0;
    if (n==0){
        sl->arr_size = 1;
        sl->arr = (linked_list**)malloc(1*sizeof(linked_list*));
    }
    else{
        sl->arr = (linked_list**)malloc(n*sizeof(linked_list*));
        for (int i = 0; i<n; i++){
            push_right(sl, seq[i]);
    }
    }

    return sl;
}
```
#### peek()
The ```peek()``` function simply checks the head or tail of the bottom most layer in the skip list.
```C
int64_t absolute_peek_left(list *sl){
    if (size(sl) == 0){
        printf("No elements Cannot Peek\n");
        return -1;
    }
    return sl->arr[0]->head->val;
}

int64_t absolute_peek_right(list *sl){
    if (size(sl) == 0){
        printf("No elements Cannot Peek\n");
        return -1;
    }
    return sl->arr[0]->tail->val;
}
```
Note: the actual peek functions calls these absolute functions whether the list is reversed or not.

#### size() and empty()
The ```list``` struct has a size atribute which constantly gets updated whenever calling ```push``` or ```pop```. The ```size()``` function simply returns that value.
```C
int size(list *sl){
    return sl->size;
}
```
The ```empty()``` function simply checks if the size is 0 or not.

```C
bool empty(list *sl){
    if (size(sl)==0){
        return true;
    }

    else{
        return false;
    }
}
```
#### get()
When pushed each node is given a ```relative_position```. For example, if we push a node in an empty list that nodes relative position is 0. If we then push left to this list the pushed node would have relative position -1. If we push right, the node would have a relative position of 1. Using this we can calculate the distance between two nodes. The index then acts as the "distance" that needs to be travelled.

The ```get()``` function goes through the layers from top to bottom. When it sees a node it can sufficiently travel to we move to that node, we then update the distance we have travelled. When the program encounters a node it cannot travel to horizontally, it will go down a layer. We do this until we have sufficiently travelled the "distance" we needed to (i.e., the given index).
```C
int64_t normal_get(list *sl, int i){
    int distance_remaining = i;
    if (empty(sl) == true){
        printf("List Empty\n");
        return -1;
    }

    if (i>=size(sl)){
        printf("List size is %d. No element at index %d.\n", size(sl), i);
        return -1;
    }

    if (i<0){
        printf("Cannot index negatively\n");
        return -1;
    }
    
    if (i == 0){
        return sl->arr[0]->head->val;
    }

    int64_t edge_weight;
    node *current_node = sl->arr[0]->head;
    printf("Pre-for loop pass\n");
    for (int j = sl->active_layers; j>= 0; j--){

        if (current_node->relative_position == sl->arr[j]->head->relative_position){
                if (sl->arr[j]->head->right!=NULL){
                    node *compare_node = sl->arr[j]->head->right;
                    edge_weight = compare_node->relative_position - sl->arr[0]->head->relative_position;
                    if (edge_weight<0){
                        edge_weight *= -1;
                    }
                    
                    if (distance_remaining>=edge_weight){
                        current_node = compare_node;
                        distance_remaining -= edge_weight;
                        break;                       
                    }
                }
                else{
                    continue;
                }
            }
        edge_weight = sl->arr[j]->head->relative_position - sl->arr[0]->head->relative_position;
        if (edge_weight < 0){
            edge_weight *= -1;
        }

        if (distance_remaining>=edge_weight){
            current_node = sl->arr[j]->head;
            distance_remaining -= edge_weight;
            break;
        }
    }
    while (distance_remaining>0){
        while (current_node->right == NULL){
            current_node = current_node->below;
        }
        edge_weight = current_node->right->relative_position - current_node->relative_position;

        if (edge_weight<0){
            edge_weight *= -1;
        }

        if (distance_remaining>=edge_weight){
            current_node = current_node->right;
            distance_remaining -= edge_weight;
        }
        else{
            current_node = current_node->below;
        }
    }
    return current_node->val;
}

```
#### set()
The ```set()``` function initially behaves similarly to the ```get()```, going through the nodes in the same way until we travel the distance we need to. It is guaranteed that we reach the top most layer of a unique index when travelling to it. Hence, to change all values of a node in a certain index, upon traveling the needed distance, the program changes the value of the node in the top most available layer, then goes down until the bottom most layer.
```C
void normal_set(list *sl, int i, int64_t v){
    if (empty(sl) == true){
        printf("List empty\n");
        return;
    }

    if (i>=size(sl)){
        printf("List size is %d. No element at index %d.\n", size(sl), i);
        return;
    }

    if (i<0){
        printf("Cannot index negatively\n");
        return;
    }

    if (i == 0){
        node *temp = sl->arr[0]->head;
        while(temp!= NULL){
            temp->val = v;
            temp = temp->above;
        }
    }

    else{
        int distance_remaining = i;
        int64_t edge_weight;
        node *current_node = sl->arr[0]->head;
        for (int j = sl->active_layers; j>= 0; j--){
            if (current_node->relative_position == sl->arr[j]->head->relative_position){
                if (sl->arr[j]->head->right!=NULL){
                    node *compare_node = sl->arr[j]->head->right;
                    edge_weight = compare_node->relative_position - sl->arr[0]->head->relative_position;
                    if (edge_weight<0){
                        edge_weight *= -1;
                    }
                    
                    if (distance_remaining>=edge_weight){
                        current_node = compare_node;
                        distance_remaining -= edge_weight;
                        break;                       
                    }
                }
                else{
                    continue;
                }
            }
            edge_weight = sl->arr[j]->head->relative_position - sl->arr[0]->head->relative_position;
            if (edge_weight < 0){
                edge_weight *= -1;
            }

            if (distance_remaining>=edge_weight){
                current_node = sl->arr[j]->head;
                distance_remaining -= edge_weight;
                break;
            }
        }
        while (distance_remaining>0){
            while (current_node->right == NULL){
                current_node = current_node->below;
            }
            
            edge_weight = current_node->right->relative_position - current_node->relative_position;
            if (edge_weight<0){
                edge_weight *= -1;
            }
            
            if (distance_remaining>=edge_weight){
                current_node = current_node->right;
                distance_remaining -= edge_weight;
            }
            else{
                current_node = current_node->below;
            }
        }
        while (current_node != NULL){
            current_node->val = v;
            current_node = current_node->below;
            
        }
}
}
```
