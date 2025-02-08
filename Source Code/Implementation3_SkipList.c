#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

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

int size(list *sl){
    return sl->size;
}

node *create_node(int64_t v){
    node *new_node = (node*)malloc(sizeof(node));
    new_node->val = v;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->below = NULL;
    new_node->above = NULL;
    return new_node;
}

void absolute_push_left(list *sl, int64_t v){

    int layer = 0; //0 indexed
    node *new_node = create_node(v);
    sl->size++;
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
        new_node->relative_position = sl->arr[0]->head->relative_position - 1;
        sl->arr[layer]->head->left= new_node;
        new_node->right = sl->arr[layer]->head;
        sl->arr[layer]->head = new_node;
        sl->arr[layer]->size++;
    }
    int p = rand() % 2;
    while (p == 1) {
        layer++;

        if (sl->arr_size<(layer+1)){
            sl->arr = realloc(sl->arr, sizeof(linked_list*)*2*(sl->arr_size));
            sl->arr_size *= 2;
        }
        node *new_node = create_node(v);
        new_node->below = sl->arr[layer - 1]->head;
        new_node->relative_position = new_node->below->relative_position; 
        sl->arr[layer-1]->head->above = new_node;
        if (sl->active_layers<layer){
            linked_list *new_linked_list = (linked_list*)malloc(sizeof(linked_list));
            new_linked_list->head = new_node;
            new_linked_list->tail = new_node;
            sl->arr[layer] = new_linked_list;
            sl->active_layers++;
        }
        
        else{
            sl->arr[layer]->head->left = new_node;
            new_node->right= sl->arr[layer]->head;
            sl->arr[layer]->head = new_node;
        }
        p = rand() % 2;
    }
    }

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

void push_left(list *sl, int64_t v){
    if (sl->orientation == 0){
        absolute_push_left(sl, v);
    }
    else{
        absolute_push_right(sl,v);
    }
}

void push_right(list *sl, int64_t v){
    if (sl->orientation == 0){
        absolute_push_right(sl, v);
    }
    else{
        absolute_push_left(sl,v);
    }
}

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


bool absolute_pop_left(list * sl){
    if (size(sl)<=0){
        printf("Size 0 Cannot Pop\n");
        return false;
    }
    int layer = 0;
    node *next_pop = sl->arr[0]->head;
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
            sl->arr[layer]->head = temp->right;
            sl->arr[layer]->head->left = NULL;
            next_pop = temp->above;
        }
        free(temp);
        layer++;
    }
    sl->arr[0]->size--;
    sl->size--;
    return true;
}

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

bool pop_left(list *sl){
    if (sl->orientation==0){
        absolute_pop_left(sl);
    }
    else{
        absolute_pop_right(sl);
    }
}

bool pop_right(list *sl){
    if (sl->orientation==0){
        absolute_pop_right(sl);
    }
    else{
        absolute_pop_left(sl);
    }
}

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

int64_t peek_left(list *sl){
    if (sl->orientation == 0){
        return absolute_peek_left(sl);
    }
    else{
        return absolute_peek_right(sl);
    }
}

int64_t peek_right(list *sl){
    if (sl->orientation == 0){
        return absolute_peek_right(sl);
    }
    else{
        return absolute_peek_left(sl);
    }
}

bool empty(list *sl){
    if (sl->active_layers==-1){
        return true;
    }

    else{
        return false;
    }
}

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

int64_t reverse_get(list *sl, int i){
    int distance_remaining = i;
    if (empty(sl) == true){
        printf("List empty\n");
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
        return sl->arr[0]->tail->val;
    }

    int64_t edge_weight;
    node *current_node = sl->arr[0]->tail;
    for (int j = sl->active_layers; j>= 0; j--){
        if (current_node->relative_position == sl->arr[j]->tail->relative_position){;
                if (sl->arr[j]->tail->left!=NULL){
                    node *compare_node = sl->arr[j]->tail->left;
                    edge_weight = compare_node->relative_position - sl->arr[0]->tail->relative_position;
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
        edge_weight = sl->arr[j]->tail->relative_position - sl->arr[0]->tail->relative_position;
        
        if (edge_weight < 0){
            edge_weight *= -1;
        }

        if (distance_remaining>=edge_weight){
            current_node = sl->arr[j]->tail;
            distance_remaining -= edge_weight;
            break;
        }
    }
    while (distance_remaining>0){
        while (current_node->left == NULL){
            current_node = current_node->below;
        }
        edge_weight = current_node->left->relative_position - current_node->relative_position;

        if (edge_weight<0){
            edge_weight *= -1;
        }

        if (distance_remaining>=edge_weight){
            current_node = current_node->left;
            distance_remaining -= edge_weight;
        }
        else{
            current_node = current_node->below;
        }
    }
    return current_node->val;
}

int64_t get(list *sl, int i){
    if (sl->orientation == 0){
        return normal_get(sl,i);
    }
    else{
        return reverse_get(sl,i);
    }
}

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

void reverse_set(list *sl, int i, int64_t v){
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
        node *temp = sl->arr[0]->tail;
        while(temp!= NULL){
            temp->val = v;
            temp = temp->above;
        }
    }

    else{
        int distance_remaining = i;
        int64_t edge_weight;
        node *current_node = sl->arr[0]->tail;
        for (int j = sl->active_layers; j>= 0; j--){
            if (current_node->relative_position == sl->arr[j]->tail->relative_position){
                if (sl->arr[j]->tail->left!=NULL){
                    node *compare_node = sl->arr[j]->tail->left;
                    edge_weight = compare_node->relative_position - sl->arr[0]->tail->relative_position;
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

            edge_weight = sl->arr[j]->tail->relative_position - sl->arr[0]->tail->relative_position;
            if (edge_weight < 0){
                edge_weight *= -1;
            }

            if (distance_remaining>=edge_weight){
                current_node = sl->arr[j]->tail;
                distance_remaining -= edge_weight;
                break;
            }
        }
        while (distance_remaining>0){
            while (current_node->left == NULL){
                current_node = current_node->below;
            }
            
            edge_weight = current_node->left->relative_position - current_node->relative_position;
                
            if (edge_weight<0){
                edge_weight *= -1;
            }
            if (distance_remaining>=edge_weight){
                current_node = current_node->left;
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

void set(list *sl, int i, int64_t v){
    if (sl->orientation == 0){
        return normal_set(sl,i,v);
    }
    else{
        return reverse_set(sl,i,v);
    }
}

void reverse(list *sl){
    if (sl->orientation == 0){
        sl->orientation = 1;
    }
    else {
        sl->orientation = 0;
    }
}