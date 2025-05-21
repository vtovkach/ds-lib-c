#ifndef __STACK_H_
#define __STAACK_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct Stack Stack;


Stack *stk_init(unsigned int init_size, size_t data_size);

void stk_destroy(Stack *stk_ptr);

int stk__push_internal(Stack *stk_ptr, void *data);

int stk_pop(Stack *stk_ptr, void *dest_ptr);

int peek(Stack *stk_ptr, void *dest_ptr);

int stk_clear(Stack *stk_ptr);

int stk_reverse(Stack *stk_ptr);

int stk_shrink(Stack **stk_ptr);

unsigned int stk_size(Stack *stk_ptr);

unsigned int stk_capacity(Stack *stk_ptr);

bool stk_empty(Stack *stk_ptr);

#define stk_push(stk_ptr, datatype, data) \
    stk__push_internal((stk_ptr), &(datatype){(data)})

#endif