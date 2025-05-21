#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>

#include "../include/stack.h"


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

int stk__push_internal(Stack *stk_ptr, void *data)
{
    // Validate input 
    if(!stk_ptr || !data)
        return -1;
    
    // Check if stack has enough space 
    if(stk_ptr->num_elements == stk_ptr->capacity)
    {
        // double the capacity of the stack 
        void *new_arr = realloc(stk_ptr->stack_arr, stk_ptr->capacity * stk_ptr->data_size * 2);
        if(!new_arr)
            return -1; 

        stk_ptr->stack_arr = new_arr;
        stk_ptr->capacity *= 2; 
    }

    stk_ptr->top_index++;
    
    memcpy((uint8_t *)stk_ptr->stack_arr + stk_ptr->top_index * stk_ptr->data_size, data, stk_ptr->data_size);

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

int peek(Stack *stk_ptr, void *dest_ptr)
{
    if(!stk_ptr || !dest_ptr)
        return -1;

    // Stack is empty 
    if(stk_ptr->num_elements == 0)
        return - 1;  

    memcpy(dest_ptr, (uint8_t *)stk_ptr->stack_arr + stk_ptr->top_index * stk_ptr->data_size, stk_ptr->data_size);

    return 0; 
}

unsigned int stk_size(Stack *stk_ptr)
{
    return !stk_ptr ? 0 : stk_ptr->num_elements;
}

bool stk_empty(Stack *stk_ptr)
{
    return !stk_ptr || stk_ptr->num_elements == 0;
}

unsigned int stk_capacity(Stack *stk_ptr)
{
    return !stk_ptr ? 0 : stk_ptr->capacity;
}

int stk_clear(Stack *stk_ptr)
{
    if(!stk_ptr)
        return -1; 

    if(stk_ptr->num_elements == 0)
        return 0; // already empty 
    
    stk_ptr->top_index = -1;
    stk_ptr->num_elements = 0; 

    return 0; 
}

int stk_reverse(Stack *stk_ptr)
{
    if(!stk_ptr)
        return -1; 
    
    // empty or only single element 
    if(stk_ptr->num_elements == 0 || stk_ptr->top_index == 0)
        return 0; 

    void *stk_array = stk_ptr->stack_arr;
    size_t data_size = stk_ptr->data_size;

    unsigned int i = 0; 
    unsigned int j = stk_ptr->top_index;

    void *temp = malloc(data_size);
    if(!temp)
        return -1; 

    while(i < j)
    {
        uint8_t *ptr_left = stk_array + data_size * i; 
        uint8_t *ptr_right = stk_array + data_size * j; 
        
        memcpy(temp, ptr_left, data_size);

        memcpy(ptr_left, ptr_right, data_size);
        memcpy(ptr_right, temp, data_size);

        i++;
        j--;
    }
    free(temp);

    return 0;
}

// If stack is empty, this function is equivalent to stack destroy.
int stk_shrink(Stack **stk_ptr_ref)
{
    if(!stk_ptr_ref || !*stk_ptr_ref)
        return -1;
    
    Stack *stk_ptr = *stk_ptr_ref;
    // If stack is empty then free the entire stack 
    if(stk_ptr->num_elements == 0)
    {
        free(stk_ptr->stack_arr);
        free(stk_ptr);
        *stk_ptr_ref = NULL;
        return 1; 
    }

    // Shrink array to the current number of elements 
    void *new_arr = realloc(stk_ptr->stack_arr, stk_ptr->data_size * stk_ptr->num_elements);
    if(!new_arr)
        return -1; 

    stk_ptr->stack_arr = new_arr;

    stk_ptr->capacity = stk_ptr->num_elements;

    return 0;
}