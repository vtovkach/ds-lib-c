#include <assert.h>
#include <stdio.h>

#include "../include/ds_doubly_list.h"

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

int main(void)
{
    test_init_destroy();
    test_front_pop();

    printf("All tests have been passed.\n");

    return 0;
}