#ifndef __STACK_H_
#define __STAACK_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct Stack Stack;


Stack *stk_init(unsigned int init_size, size_t data_size);

void stk_destroy(Stack *stk_ptr);

int stk_push(Stack *stk_ptr, void *data);


int stk_pop(Stack *stk_ptr, void *dest_ptr);

int *peek(Stack *stk_ptr, void *dest_ptr);


unsigned int stk_size();

bool stk_empty();

unsigned int stk_capacity();

int stk_clear();

int stk_reverse();

// free unused memory
int stk_shrink();

#endif