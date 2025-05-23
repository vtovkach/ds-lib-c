#ifndef _QUEUE_
#define _QUEUE_

#include <stddef.h>

typedef struct Queue Queue; 


Queue *q_init(size_t initial_capacity, size_t data_size);

void q_destroy(Queue *q_ptr);

int q__enqueue(Queue *q_ptr, void *data);

int q_dequeue(Queue *q_ptr, void *dest);

int q_peek(Queue *q_ptr, void *dest);

size_t q_size(Queue *q_ptr);

size_t q_capacity(Queue *q_ptr);

int q_empty(Queue *q_ptr);

int q_full(Queue *q_ptr);

int q_clear(Queue *q_ptr);

#define q_enqueue(q_ptr, data_type, data) \
     q__enqueue(q_ptr, &(data_type){(data)})


#endif