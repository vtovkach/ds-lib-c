#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "../include/ds_queue.h"

typedef struct Queue
{
    void    *queue_arr;     // Dynamically allocated circular array 
    int     front;          // Index pointing to the front of the array 
    int     rear;           // Index pointing to the rear of the array 
    size_t  data_size;      // Size of the data type in bytes 
    size_t  capacity;       // Current maximum size of the queue 
    size_t  num_elements;   // Current number of elements in the queue 
} Queue;


Queue *q_init(size_t init_size, size_t data_size)
{
    // Validate input 
    if(init_size == 0 || data_size == 0)
        return NULL;
    
    Queue *new_queue = malloc(sizeof(Queue));
    if(!new_queue)
        return NULL;
    
    new_queue->queue_arr = calloc(init_size, data_size);
    if(!new_queue->queue_arr)
    {
        free(new_queue);
        return NULL;
    }

    new_queue->capacity = init_size;
    new_queue->front = -1; 
    new_queue->rear = -1; 
    new_queue->data_size = data_size;
    new_queue->num_elements = 0;

    return new_queue;
}

void q_destroy(Queue *q_ptr)
{
    free(q_ptr->queue_arr);
    free(q_ptr);
}


int q_enqueue(Queue *q_ptr, void *data)
{
    if(!q_ptr || !data)
        return -1;
    
    if(q_ptr->num_elements == q_ptr->capacity)
    {
        // double the size 
    }

    
    int rear = (q_ptr->rear + 1) % q_ptr->capacity;
    

    memcpy();

    return 0; 
}