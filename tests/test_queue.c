#include <assert.h>
#include <stdio.h>

#include "../include/ds_queue.h"


void test_init()
{
    Queue *queue = q_init(10, sizeof(int));

    q_destroy(queue);
}

int main(void)
{
    test_init();
    
    printf("All tests are passed!\n");
    return 0;
}