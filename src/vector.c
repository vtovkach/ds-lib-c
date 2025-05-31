#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

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

int v_push_back(Vector *vec, void *data)
{
    if(!vec || !data)
        return -1; // Indicate wrong input  

    if(vec->capacity == vec->num_elements)
    {
        // double vector's capacity 
        size_t new_capacity = vec->capacity * 2;
        
        // Check for integer overflow 
        if (vec->capacity > SIZE_MAX / 2 / vec->data_size)
            return -2; // Indicate error resizing vector 

        void *new_vec_array = realloc(vec->vec_array, new_capacity * vec->data_size);
        if(!new_vec_array)
            return -2; // Indicate error resizing vector 
        
        vec->vec_array = new_vec_array; 
        vec->capacity = new_capacity; 
    }

    // Copy data to internal vector array 
    memcpy((uint8_t *)vec->vec_array + vec->data_size * vec->num_elements, data, vec->data_size);

    vec->num_elements++;

    return 0;
}   

int v_pop_back(Vector *vec)
{
    if(!vec)
        return -1; // Indicate wrong input  

    if(vec->num_elements == 0)
        return 1; // Indicate empty vector
    
    vec->num_elements--; 
    
    return 0;
}