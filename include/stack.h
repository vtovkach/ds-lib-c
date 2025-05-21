#ifndef __STACK_H_
#define __STAACK_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct Stack Stack;


Stack *stk_init();

void stk_destroy();

int push();

void *pop();

// request pointer from the user to copy the data 
void *peek();

unsigned int stk_size();

bool stk_empty();

unsigned int stk_capacity();

int stk_clear();

int stk_reverse();

// free unused memory
int stk_shrink();


#endif