#include <string.h>
#include <stdlib.h>

#include "../include/ds_vector.h"

typedef struct Vector 
{
    void    *vec_array;     // dynamic array 
    size_t  data_size;      // data size in bytes 
    size_t  num_elements;   // current number of elements 
    size_t  capacity;       // current capacity of the list 

} Vector;

Vector *vec_create(size_t capacity, size_t data_size)
{
    if(capacity == 0 || data_size == 0)
        return NULL;

    Vector *new_vec = malloc(sizeof(Vector));
    if(!new_vec)
        return NULL; 

    new_vec->vec_array = malloc(capacity * data_size);
    if(!new_vec->vec_array)
    {
        free(new_vec);
        return NULL;
    }

    new_vec->data_size = data_size;
    new_vec->capacity = capacity;
    new_vec->num_elements = 0;

    return new_vec;
}

void vec_destroy(Vector *vec)
{
    free(vec->vec_array);
    free(vec);
}