#include <assert.h>
#include <stdio.h>

#include "../include/ds_doubly_list.h"

// test push_at
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

    d_l__push_back(list, &(int){1});
    d_l__push_back(list, &(int){2});
    d_l__push_back(list, &(int){3});
    d_l__push_back(list, &(int){4});
    
    //d_l__push_at(list, &(int){10}, 0);

    int data = 0; 

    for(int i = 0; i < 4; i++)
    {
        printf("%d ", d_l_pop_at(list, &data, i));
    }

    d_list_destroy(list);
}

int main(void)
{
    test_init_destroy();
    test_front_pop();
    test_pop_back();
    test_push_at();

    printf("All tests have been passed.\n");

    return 0;
}