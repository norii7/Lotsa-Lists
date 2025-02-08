#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct list {
    int elem;
    int capacity;
    int head;
    int tail;
    bool is_reversed;
    int64_t *arr;
} list;

// Main functions
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

// Helper functions
void inflate(list *l);
void deflate(list *l);
void help_push_left(list *l, int64_t v);
void help_push_right(list *l, int64_t v);
bool help_pop_left(list *l);
bool help_pop_right(list *l);

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

int size(list *l) {
    return l->elem;
}

bool empty(list *l) {
    if(l->elem == 0) {return true;}
    return false;
}

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

void reverse(list *l) {
    if(l->is_reversed) {
        l->is_reversed = false;
    } else {
        l->is_reversed = true;
    }
}

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