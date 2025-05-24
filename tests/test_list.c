#include <assert.h>
#include <stdio.h>

#include "../include/ds_list.h"


void test_init_destroy()
{
    List *list = list_init(0);

    assert(list == NULL);

    list = list_init(sizeof(double));
    assert(list != NULL);

    list_destroy(list);   
}

int main(void)
{
    test_init_destroy();

    printf("All cases have been passed!\n");    
    
    return 0;
}