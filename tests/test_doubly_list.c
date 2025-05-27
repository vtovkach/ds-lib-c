#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/ds_doubly_list.h"

// test pop_at

void test_init_destroy()
{
    D_List *list = d_list_init(0);
    assert(!list);

    list = d_list_init(sizeof(int));

    d_list_destroy(list);
}

void test_front_pop()
{
    D_List *list = d_list_init(sizeof(int));

    int data = 0;

    d_l__push_front(list, &(int){100});
    d_l__push_front(list, &(int){101});
    d_l__push_front(list, &(int){102});
    d_l__push_front(list, &(int){103});
    d_l__push_front(list, &(int){104});
    d_l__push_back(list, &(int){105});

    d_l_pop_front(list, &data);
    assert(data == 104);

    d_l_pop_front(list, &data);
    assert(data == 103);

    d_l_pop_front(list, &data);
    assert(data == 102);

    d_l_pop_front(list, &data);
    assert(data == 101);

    d_l_pop_front(list, &data);
    assert(data == 100);

    d_l_pop_front(list, &data);
    assert(data == 105);

    assert(d_l_pop_front(list, &data) == 1);
    
    d_list_destroy(list);
}

void test_pop_back()
{
    D_List *list = d_list_init(sizeof(int));

    int data = 0;

    d_l__push_front(list, &(int){100});
    d_l__push_front(list, &(int){101});
    d_l__push_front(list, &(int){102});
    d_l__push_front(list, &(int){103});
    d_l__push_front(list, &(int){104});
    d_l__push_back(list, &(int){105});
    d_l__push_back(list, &(int){200});
    d_l__push_back(list, &(int){205});

    
    d_l_pop_back(list, &data);
    assert(data == 205);
    
    d_l_pop_back(list, &data);
    assert(data == 200);

    d_l_pop_back(list, &data);
    assert(data == 105);

    d_l_pop_back(list, &data);
    assert(data == 100);

    d_l_pop_back(list, &data);
    assert(data == 101);

    d_l_pop_back(list, &data);
    assert(data == 102);

    d_l_pop_back(list, &data);
    assert(data == 103);

    d_l_pop_back(list, &data);
    assert(data == 104);

    d_list_destroy(list);
}

// TODO 
void test_push_at()
{
    D_List *list = d_list_init(sizeof(int));

    for(int i = 0; i < 10; i++)
    {
        d_l__push_at(list, &(int){i}, i);
    }

    for(int i = 0; i < 10; i++)
    {
        int dest = 0;
        d_l_pop_front(list, &dest);
        assert(dest == i);
    }

    d_list_destroy(list);
}

void test_pop_at()
{
    D_List *list = d_list_init(sizeof(int));

    for(int i = 0; i < 10; i++)
    {
        d_l__push_at(list, &(int){i}, i);
    }

    int dest = 0; 

    d_l_pop_at(list, &dest, 0);
    assert(dest == 0);
    
    d_l_pop_at(list, &dest, 0);
    assert(dest == 1);

    d_l_pop_at(list, &dest, 0);
    assert(dest == 2);

    d_l_pop_at(list, &dest, 0);
    assert(dest == 3);

    d_list_destroy(list);
}

// Assume your header file is already included
// #include "doubly_list.h"

void test_push_at_pop_at_edge_cases() 
{
    D_List *list = d_list_init(sizeof(int));
    assert(list != NULL);

    int val, out;

    // === Edge Case 1: pop_at from empty list ===
    assert(d_l_pop_at(list, &out, 0) == 1);  // Should return "empty list"
    assert(d_l_pop_at(list, &out, 100) == 1);

    // === Edge Case 2: push_at at index 0 when list is empty ===
    val = 5;
    assert(d_l__push_at(list, &val, 0) == 0);  // Should succeed

    // === Edge Case 3: push_at at invalid index > size ===
    val = 10;
    assert(d_l__push_at(list, &val, 5) == -2); // Invalid index

    // === Edge Case 4: push_at at end of list ===
    val = 15;
    assert(d_l__push_at(list, &val, 1) == 0); // push at end (index == size)

    // List now: [5, 15]

    // === Edge Case 5: push_at at middle ===
    val = 10;
    assert(d_l__push_at(list, &val, 1) == 0); // Insert between 5 and 15

    // List now: [5, 10, 15]

    // === Edge Case 6: pop_at with invalid index ===
    assert(d_l_pop_at(list, &out, 3) == -2);  // Index = size → invalid

    // === Edge Case 7: pop_at first element ===
    assert(d_l_pop_at(list, &out, 0) == 0);
    assert(out == 5);

    // === Edge Case 8: pop_at last element ===
    assert(d_l_pop_at(list, &out, 1) == 0);  // index 1 now refers to last element (was 15)
    assert(out == 15);

    // === Edge Case 9: pop_at only remaining element ===
    assert(d_l_pop_at(list, &out, 0) == 0);
    assert(out == 10);

    // === Edge Case 10: pop_at from now empty list ===
    assert(d_l_pop_at(list, &out, 0) == 1);

    d_list_destroy(list);
}

void test_list_utilities()
{
    D_List *list = d_list_init(sizeof(int));
    assert(list != NULL);

    // === Test 1: l_empty on new list ===
    assert(d_l_empty(list) == 1); // List should be empty

    // === Test 2: l_peek_at on empty list ===
    int out = 0;
    assert(d_l_peek_at(list, &out, 0) == -2); // Out-of-bounds

    // === Test 3: Add items and test l_peek_at ===
    for (int i = 0; i < 5; i++)
        assert(d_l__push_back(list, &i) == 0); // List: [0, 1, 2, 3, 4]

    assert(d_l_empty(list) == 0); // Should not be empty

    // Peek at all values to verify correctness
    for (int i = 0; i < 5; i++) {
        out = -1;
        assert(d_l_peek_at(list, &out, i) == 0);
        assert(out == i);
    }

    // === Test 4: l_reverse and verify values ===
    assert(d_l_reverse(list) == 0);

    // Should now be [4, 3, 2, 1, 0]
    for (int i = 0; i < 5; i++) {
        out = -1;
        assert(d_l_peek_at(list, &out, i) == 0);
        assert(out == 4 - i);
    }

    // === Test 5: l_clear and check behavior ===
    assert(d_l_clear(list) == 0);
    assert(d_l_empty(list) == 1); // List should be empty again

    // l_peek_at after clear should fail
    assert(d_l_peek_at(list, &out, 0) == -2);

    d_list_destroy(list);
}

void test_d_list_brutal() 
{
    printf("Starting brutal edge case tests for doubly linked list...\n");

    int val = 42, out = -1;

    // === Null pointer tests ===
    assert(d_l__push_front(NULL, &val) == -1);
    assert(d_l__push_back(NULL, &val) == -1);
    assert(d_l__push_at(NULL, &val, 0) == -1);
    assert(d_l_pop_front(NULL, &out) == -1);
    assert(d_l_pop_back(NULL, &out) == -1);
    assert(d_l_pop_at(NULL, &out, 0) == -1);
    assert(d_l_peek_front(NULL, &out) == -1);
    assert(d_l_peek_back(NULL, &out) == -1);
    assert(d_l_peek_at(NULL, &out, 0) == -1);
    assert(d_l_size(NULL) == 0);
    assert(d_l_empty(NULL) == 1);
    assert(d_l_clear(NULL) == -1);
    assert(d_l_reverse(NULL) == -1);

    // === Init with zero size ===
    assert(d_list_init(0) == NULL);

    // === Basic functional tests ===
    D_List *list = d_list_init(sizeof(int));
    assert(list);

    // Pop and peek from empty list
    assert(d_l_pop_front(list, &out) == 1);
    assert(d_l_pop_back(list, &out) == 1);
    assert(d_l_pop_at(list, &out, 0) == 1);
    assert(d_l_peek_front(list, &out) == 1);
    assert(d_l_peek_back(list, &out) == 1);
    assert(d_l_peek_at(list, &out, 0) == -2);
    assert(d_l_empty(list) == 1);

    // Invalid indices
    val = 5;
    assert(d_l__push_at(list, &val, 1) == -2);

    // Push and peek at front and back
    val = 1; assert(d_l__push_front(list, &val) == 0);
    val = 2; assert(d_l__push_back(list, &val) == 0);
    val = 0; assert(d_l__push_at(list, &val, 0) == 0); // Now: [0, 1, 2]
    val = 3; assert(d_l__push_at(list, &val, 3) == 0); // Now: [0, 1, 2, 3]

    // Peek and verify
    for (size_t i = 0; i < 4; ++i) {
        out = -1;
        assert(d_l_peek_at(list, &out, i) == 0);
        assert(out == (int)i);
    }

    // Reverse the list and check new order: [3, 2, 1, 0]
    assert(d_l_reverse(list) == 0);
    for (size_t i = 0; i < 4; ++i) {
        out = -1;
        assert(d_l_peek_at(list, &out, i) == 0);
        assert(out == (int)(3 - i));
    }

    // Pop at various positions
    assert(d_l_pop_at(list, &out, 1) == 0); // Removes 2 → [3, 1, 0]
    assert(out == 2);

    assert(d_l_pop_front(list, &out) == 0); // Removes 3
    assert(out == 3);

    assert(d_l_pop_back(list, &out) == 0); // Removes 0
    assert(out == 0);

    assert(d_l_size(list) == 1); // Only [1] left

    // Clear the list
    assert(d_l_clear(list) == 0);
    assert(d_l_empty(list) == 1);
    assert(d_l_size(list) == 0);

    // Try clearing again
    assert(d_l_clear(list) == 0);

    // Reuse list after clear
    val = 99;
    assert(d_l__push_back(list, &val) == 0);
    assert(d_l_size(list) == 1);

    // Destroy and test invalid reuse
    d_list_destroy(list);

    // Avoid using list now — undefined behavior if reused

    printf("All destructive edge case tests passed!\n");
}

#define ITEM_COUNT 100000000

void stress_test_insert_delete() {
    printf("Running stress test with %d items...\n", ITEM_COUNT);

    D_List *list = d_list_init(sizeof(int));
    assert(list != NULL);

    // Timing start
    clock_t start = clock();

    for (int i = 0; i < ITEM_COUNT; ++i) {
        assert(d_l__push_back(list, &i) == 0);
    }

    clock_t insert_end = clock();

    int out;
    for (int i = 0; i < ITEM_COUNT; ++i) {
        assert(d_l_pop_front(list, &out) == 0);
        assert(out == i);
    }

    clock_t end = clock();

    d_list_destroy(list);

    double insert_time = (double)(insert_end - start) / CLOCKS_PER_SEC;
    double delete_time = (double)(end - insert_end) / CLOCKS_PER_SEC;
    double total_time  = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Insertion time: %.2f seconds\n", insert_time);
    printf("Deletion  time: %.2f seconds\n", delete_time);
    printf("Total     time: %.2f seconds\n", total_time);
}

int main(void)
{
    test_init_destroy();
    test_front_pop();
    test_pop_back();
    test_push_at();
    test_pop_at();
    test_push_at_pop_at_edge_cases();
    test_list_utilities();
    test_d_list_brutal();
    stress_test_insert_delete();

    printf("All tests have been passed.\n");

    return 0;
}