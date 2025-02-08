#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "temporaryTree.c" //Change File Name Of Implementation



// Helper function to print test results
void print_result(const char* test_name, bool result) {
    printf("%s: %s\n", test_name, result ? "PASSED" : "FAILED");
}

// Test suite
void run_tests() {
    // Normal Test Cases
    {
        // Test 1: Initialization and Basic Operations
        int64_t seq1[] = {10, 20, 30, 40, 50};
        list* l1 = make(5, seq1);
        print_result("Test 1 - Size Check", size(l1) == 5);
        print_result("Test 1 - Peek Left", peek_left(l1) == 10);
        print_result("Test 1 - Peek Right", peek_right(l1) == 50);
        print_result("Test 1 - Get Index 2", get(l1, 2) == 30);
        set(l1, 2, 35);
        print_result("Test 1 - Set Index 2", get(l1, 2) == 35);
        free(l1);
    }

    {
        // Test 2: Push and Pop Operations
        int64_t seq2[] = {1, 2, 3};
        list* l2 = make(3, seq2);
        push_left(l2, 0);
        push_right(l2, 4);
        print_result("Test 2 - Push Left", peek_left(l2) == 0);
        print_result("Test 2 - Push Right", peek_right(l2) == 4);
        pop_left(l2);
        pop_right(l2);
        print_result("Test 2 - Size After Pops", size(l2) == 3);
        free(l2);
    }

    {
        // Test 3: Basic Reversal Handling
        int64_t seq3[] = {11, 22, 33, 44};
        list* l3 = make(4, seq3);
        reverse(l3);
        print_result("Test 3 - Reverse Peek Left", peek_left(l3) == 44);
        print_result("Test 3 - Reverse Peek Right", peek_right(l3) == 11);
        reverse(l3);
        print_result("Test 3 - Re-Reverse Peek Left", peek_left(l3) == 11);

        free(l3);
    }
    /*
    {
        // Test 4: Inflation (For Dynamic Array)
        int64_t seq4[] = {5, 10};
        list* l4 = make(2, seq4);
        push_right(l4, 15);
        push_right(l4, 20);
        push_right(l4, 25);
        print_result("Test 4 - Inflation Capacity", l4->capacity == 8);
        free(l4);
    }

    {
        // Test 5: Deflation (For Dynamic Array)
        int64_t seq5[] = {1, 2, 3, 4, 5, 6};
        list* l5 = make(6, seq5);
        pop_left(l5);
        pop_left(l5);
        pop_left(l5);
        print_result("Test 5 - Deflation Capacity", l5->capacity == 3);
        free(l5);
    }*/

    // Edge Test Cases
    {
        // Test 6: Empty List Operations
        list* l6 = make(0, NULL);
        print_result("Test 6 - Pop Left on Empty", !pop_left(l6));
        print_result("Test 6 - Peek Left on Empty", peek_left(l6) == -1);
        free(l6);
    }

    {
        // Test 7: Single Element List
        int64_t seq7[] = {99};
        list* l7 = make(1, seq7);
        print_result("Test 7 - Peek Left", peek_left(l7) == 99);
        pop_left(l7);
        print_result("Test 7 - Pop Left Result", size(l7) == 0);
        free(l7);
    }

    {
        // Test 8: Reverse Operations and Dynamic Capacity
        int64_t seq8[] = {10, 20, 30, 40};
        list* l8 = make(4, seq8);
        reverse(l8); //40, 30, 20, 10
        push_left(l8, 50); //50, 40, 30, 20, 10
        push_left(l8, 60); //60, 50, 40, 30, 20, 10
        print_result("Test 8 - Reverse with Inflation", peek_left(l8) == 60);

        print_result("Test 8 - Reverse with Inflation", get(l8, 3) == 30);

        set(l8, 4, 13); //60, 50, 40, 30, 13, 10
        print_result("Test 8 - Reverse with Inflation", get(l8, 4) == 13);

        pop_right(l8); //60, 50, 40, 30, 13
        print_result("Test 8 - Reverse with Inflation", peek_right(l8) == 13);

        free(l8);
    }

    {
        // Test 9: Repeated Reverse
        int64_t seq9[] = {100, 200, 300};
        list* l9 = make(3, seq9);
        for (int i = 0; i < 10; ++i) {
            reverse(l9);
        }
        print_result("Test 9 - Repeated Reverse Consistency", peek_left(l9) == 100);
        free(l9);
    }

    {   //Test 10: Interweaving Operations Between Forward and Reverse Orientation
        int64_t seq10[] = {1,2,3,4,5,6,7,8,9,10};
        list* l10 = make(10,seq10);

        reverse(l10); //10,9,8,7,6,5,4,3,2,1
        pop_left(l10); //9,8,7,6,5,4,3,2,1
        print_result("Test 10 - Interweaved Operations", peek_left(l10) == 9);

        pop_right(l10); //9,8,7,6,5,4,3,2
        print_result("Test 10 - Interweaved Operations", peek_right(l10) == 2);

        reverse(l10); //2,3,4,5,6,7,8,9
        print_result("Test 10 - Interweaved Operations", peek_left(l10) == 2);
        print_result("Test 10 - Interweaved Operations", peek_right(l10) == 9);

        pop_right(l10); //2,3,4,5,6,7,8
        push_left(l10,13); //13,2,3,4,5,6,7,8
        reverse(l10); //8,7,6,5,4,3,2,13
        print_result("Test 10 - Interweaved Operations", peek_left(l10) == 8);
        print_result("Test 10 - Interweaved Operations", peek_right(l10) == 13);


        set(l10, 4, 20); //8,7,6,5,20,3,2,13
        print_result("Test 10 - Interweaved Operations", get(l10,4) == 20);
    }
}

int main() {
    srand(time(NULL));
    run_tests();
    return 0;
}