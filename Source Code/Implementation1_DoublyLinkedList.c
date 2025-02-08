#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node{
    int64_t val;
    struct node *next;
    struct node *prev;
} Node;

typedef struct list{
    Node *head;
    Node *tail;
    int size;
    bool reversed;
} list;

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

void reverse(list *l){
    l->reversed = !(l->reversed);
    return;
}