#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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


int main(void)
{
    test_init_destroy();
    test_front_pop();
    test_pop_back();
    test_push_at();
    test_pop_at();
    test_push_at_pop_at_edge_cases();

    printf("All tests have been passed.\n");

    return 0;
}