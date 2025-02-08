[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Z6J1qvod)

# CS 32 MP 1: Lotsa Lists

This repository holds all the files our group submitted for the MP 1 requirement in our CS 32 course.

## Task

We implemented a dynamic list of integers in four ways: using a **(1) Doubly Linked List, (2) Dynamic Array, (3) Skip List** and a **(4) Sequence of Trees.** Each method has its own time complexities for the following list operations/functions:

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

The functions above are the *main* functions that each method are expected to have. However, auxiliary or helper functions may have also been defined for each implementation to help with the task. Specific details for each implementation can be found in the ```DETAILS.md``` file in this repository.

## Files and *Folders*

This repository contains the following: **(1) ```README.md```, (2) ```DETAILS.md```, (3) ```PROOFS.md```,** and two folders named **(4) ```Source Code```** and **(5) ```transcript```.**

### README.md

The README.md file.

### DETAILS.md

This file is a compilation of all the relevant details for each dynamic list implementation. It contains explanations for the functions, structs and methods used for each implementation.

### PROOFS.md

Compiled in this file are the proofs of the time complexity of the list operations for each implementation.

### Source Code

This folder contains the source code for each implementation in their own ```.c``` file. It also contains the unit tests for black-box testing.

### transcript

This folder is where the transcripts for ChatGPT interactions are contained, including unaltered prompts and responses.

## Testing

There are two unit test files in the ```Source Code``` folder: ```0_DynamicArrayTest.c``` and ```0_OtherTest.c```. The former, as the name suggests, is used to test the Dynamic Array implementation while the latter is used for the other three. The only difference between the two is that ```0_DynamicArrayTest.c``` contains tests for the "resizing" aspect of the Dynamic Array. These tests are contained inside comment markers in ```0_OtherTest.c``` so that they are ignored during runtime.

Both of these files contain normal and edge test cases that look into the different list operations to see if they are all performing as intended.

To run the test, make sure that the source codes are all in the same folder, then, simply compile the unit test files and run the program. The terminal should display whether the implementations have ```PASSED``` or ```FAILED``` the tests. In ```0_OtherTest.c```, you can change the filename included in the last ```#include``` to the name of the implementation you want to test.

You can add more test cases by following the format of the previous ones and recompiling the code.

## Other Contributors:

Manuel Lucas Bumanglag
Justin Kenneth Co

## Sources and References

Circular Queue Implementation - Array. “Circular Queue Implementation - Array.” YouTube, 12 June 2019, www.youtube.com/watch?v=8sjFA-IX-Ww&list=WL&index=2&t=207s&ab_channel=BlueTreeCode.

Typescript, in. “Data Structures in Typescript #17 - Binomial Heap Introduction.” YouTube, 11 June 2020, www.youtube.com/watch?v=m8rsw3KfDKs&ab_channel=j4orz.
