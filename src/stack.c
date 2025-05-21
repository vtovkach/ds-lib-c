#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "../include/stack.h"

// finish push 

typedef struct Stack
{
    void                *stack_arr;   // dynamically allocated array 
    size_t              data_size;     // size of the data in bytes 
    int                 top_index;     // index of the top element 
    unsigned int        capacity;      // size of the stack   
    unsigned int        num_elements;  // current number of elements in the stack 
} Stack;

Stack *stk_init(unsigned int init_size, size_t data_size)
{
    // Validate input 
    if(init_size == 0 || data_size == 0)
        return NULL;
 
    Stack *stack = malloc(sizeof(Stack));
    
    if(!stack)
        return NULL;

    stack->stack_arr = calloc(init_size, data_size);
    if(!stack->stack_arr)
    {
        free(stack);
        return NULL;
    }

    stack->data_size = data_size;
    stack->top_index = -1;  // -1 means empty 
    stack->capacity  = init_size;
    stack->num_elements = 0;

    return stack; 
}

void stk_destroy(Stack *stk_ptr)
{
    free(stk_ptr->stack_arr);
    free(stk_ptr);
}

int stk_push(Stack *stk_ptr, void *data)
{
    // Validate input 
    if(!stk_ptr || !data)
        return -1;
    
    // Check if stack has enough space 
    if(stk_ptr->num_elements == stk_ptr->capacity)
    {
        // realloc array with double size 
    }

    stk_ptr->top_index++;

    memcpy(stk_ptr->stack_arr + stk_ptr->top_index * stk_ptr->data_size, data, stk_ptr->data_size);

    stk_ptr->num_elements++;

    return 0;
}   

int stk_pop(Stack *stk_ptr, void *dest_ptr)
{
    if(!stk_ptr || !dest_ptr)
        return -1; 

    // Stack is empty 
    if(stk_ptr->num_elements == 0)
        return -1;

    memcpy(dest_ptr, (uint8_t *)stk_ptr->stack_arr + stk_ptr->top_index * stk_ptr->data_size, stk_ptr->data_size);

    stk_ptr->top_index--;
    stk_ptr->num_elements--;

    return 0;
}