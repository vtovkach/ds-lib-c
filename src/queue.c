#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "../include/ds_queue.h"

// Fix resizing error in circular queue 

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


// Finish double quueu condition 

int q__enqueue(Queue *q_ptr, void *data)
{
    // Validate Input 
    if(!q_ptr || !data)
        return -1;
    

    /// FIX ERROR HERE 
    if(q_ptr->num_elements == q_ptr->capacity)
    {
        // double the size 
        size_t new_size = q_ptr->capacity * q_ptr->data_size * 2;

        void *new_arr = realloc(q_ptr->queue_arr, new_size);
        if(!new_arr)
            return 2; // Indicate that queue is full and can't be resized 
        
        q_ptr->queue_arr = new_arr;
        q_ptr->capacity *= 2; 
    }

    if(q_ptr->num_elements == 0)
    {
        q_ptr->front = 0;
        q_ptr->rear = 0;
    }
    else
    {
        q_ptr->rear = (q_ptr->rear + 1) % q_ptr->capacity;
    }

    memcpy((uint8_t *)q_ptr->queue_arr + q_ptr->rear * q_ptr->data_size, data, q_ptr->data_size);

    q_ptr->num_elements++;

    return 0; 
}

int q_dequeue(Queue *q_ptr, void *dest)
{
    // Validate input 
    if(!q_ptr || !dest)
        return -1; 

    if(q_ptr->num_elements == 0)
        return 1; // indicate that queue is empty 
    
    memcpy(dest, (uint8_t *)q_ptr->queue_arr + q_ptr->front * q_ptr->data_size, q_ptr->data_size);

    q_ptr->front = (q_ptr->front + 1) % q_ptr->capacity;
    q_ptr->num_elements--;

    return 0;
}

int q_peek(Queue *q_ptr, void *dest)
{
    if(!q_ptr || !dest)
        return -1;

    if(q_ptr->num_elements == 0)
        return 1; // Indicate empty queue 

    memcpy(dest, (uint8_t *)q_ptr->queue_arr + q_ptr->front * q_ptr->data_size, q_ptr->data_size);

    return 0;
}

size_t q_size(Queue *q_ptr)
{
    return q_ptr ? q_ptr->num_elements : 0;
}

size_t q_capacity(Queue *q_ptr)
{
    return q_ptr ? q_ptr->capacity : 0;
}

int q_empty(Queue *q_ptr)
{
    if(!q_ptr || q_ptr->num_elements == 0)
        return 1;
    
    return 0; 
}

int q_full(Queue *q_ptr)
{
    if(!q_ptr || q_ptr->num_elements != q_ptr->capacity)
        return 0; 

    return 1; 
}

int q_clear(Queue *q_ptr)
{
    if(!q_ptr)
        return -1; 
    
    q_ptr->front = -1; 
    q_ptr->rear = -1;
    q_ptr->num_elements = 0;

    return 0;
}