#ifndef _QUEUE_
#define _QUEUE_

#include <stddef.h>

typedef struct Queue Queue; 


Queue *q_init(size_t initial_capacity, size_t data_size);

void q_destroy(Queue *q_ptr);

int q_enqueue();

int q_dequeue();

int q_peek();

size_t q_size();

size_t q_capacity();

int q_empty();

int q_full();

int q_clear();


#endif