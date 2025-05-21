#include <assert.h>

#include "../include/stack.h"

int main(void)
{
    Stack *stack = stk_init(10, sizeof(int));
    assert(stack != NULL);

    stk_push(stack, &(int){44});
    stk_push(stack, &(int){90});

    int data = 0; 

    stk_pop(stack, &data);

    assert(data == 90);

    stk_pop(stack, &data);

    assert(data == 44);

    stk_destroy(stack);

    return 0;
}