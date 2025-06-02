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

int v_top(Vector *vec, void *dest)
{
    if(!vec || !dest)
        return -1;
    
    if(vec->num_elements == 0)
        return 1; 

    memcpy(dest, (uint8_t *)vec->vec_array + (vec->num_elements - 1) * vec->data_size, vec->data_size);
    
    return 0;
}

int v_get(Vector *vec, void *dest, size_t index)
{
    if(!vec || !dest)
        return -1; 
    
    if(index >= vec->num_elements)
        return -2; // Indicate index out of bounds

    // Copy data from internal vector array to user's space  
    memcpy(dest, (uint8_t *)vec->vec_array + index * vec->data_size, vec->data_size);

    return 0;
}

int v_set(Vector *vec, void *data, size_t index)
{
    if(!vec || !data)
        return -1; 

    if(index >= vec->num_elements)
        return -2; // Index is out of bounds 
    
    // Copy data to internal array 
    memcpy((uint8_t *)vec->vec_array + index * vec->data_size, data, vec->data_size);

    return 0;
}

int v_insert(Vector *vec, void *data, size_t index)
{
    if(!vec || !data)
        return -1; // Incorrect input 

    if(index > vec->num_elements)
        return -2; // Index is out of bounds 

    // Resize the internal vector  
    if(vec->num_elements + 1 > vec->capacity)
    {
        // double vector's capacity 
        size_t new_capacity = vec->capacity * 2;
        
        // Check for integer overflow 
        if (vec->capacity > SIZE_MAX / 2 / vec->data_size)
            return -2; // Indicate error resizing vector 

        void *new_vec_array = realloc(vec->vec_array, new_capacity * vec->data_size);
        if(!new_vec_array)
            return -2; // Error allocating memory 
            
        vec->vec_array = new_vec_array;
        vec->capacity = new_capacity;
    }

    memmove((uint8_t *)vec->vec_array + (index + 1) * vec->data_size, 
            (uint8_t *)vec->vec_array + index * vec->data_size, 
            (vec->num_elements - index) * vec->data_size
           );

    memcpy((uint8_t *)vec->vec_array + index * vec->data_size, data, vec->data_size);

    vec->num_elements++;

    return 0;
}

int v_erase(Vector *vec, size_t index)
{
    if(!vec)
        return -1; // Incorrect input 

    if(index >= vec->num_elements)
        return -2; // Index is out of bounds 

    // Index is at the last element 
    if(index == vec->num_elements - 1)
        return v_pop_back(vec);
    
    memmove((uint8_t *)vec->vec_array + index * vec->data_size, 
            (uint8_t *)vec->vec_array + (index + 1) * vec->data_size, 
            (vec->num_elements - index - 1) * vec->data_size      
           );

    vec->num_elements--;

    return 0;
}

size_t v_size(Vector *vec)
{
    return !vec ? 0 : vec->num_elements;
}

size_t v_capacity(Vector *vec)
{
    return !vec ? 0 : vec->capacity;
}

int v_empty(Vector *vec)
{
    return (!vec || vec->num_elements == 0) ? 1 : 0;
}

int v_clear(Vector *vec)
{
    if(!vec)
        return -1;

    vec->num_elements = 0; 

    return 0;
}

int v_resize(Vector *vec, size_t new_capacity)
{
    if(!vec || new_capacity == 0)
        return -1; // Invalid input

    void *new_array = realloc(vec->vec_array, new_capacity * vec->data_size);
    if(!new_array)
        return -2; // Allocation failed 
    
    vec->vec_array = new_array;
    vec->capacity = new_capacity;

    if(vec->num_elements > new_capacity)
        vec->num_elements = new_capacity;
    
    return 0;
}

static int get_partition(uint8_t *arr, size_t data_size, int begin, int end, int(*cmp)(void *a, void *b))
{
    void *pivot = malloc(data_size);
    if(!pivot)
        return -1;
        
    void *temp = malloc(data_size);
    if(!temp)
    {
        free(pivot);
        return -1;
    }

    memcpy(pivot, arr + end * data_size, data_size);

    int i = begin - 1; 

    for(int j = begin; j <= end - 1; ++j)
    {
        if(cmp(arr + j * data_size, pivot) < 0)
        {
            i++;
            memcpy(temp, arr + i * data_size, data_size);
            memcpy(arr + i * data_size, arr + j * data_size, data_size);
            memcpy(arr + j * data_size, temp, data_size);
        }
    }
    
    i++;
    memcpy(temp, arr + i * data_size, data_size);
    memcpy(arr + i * data_size, arr + end * data_size, data_size);
    memcpy(arr + end * data_size, temp, data_size);

    free(pivot);
    free(temp);

    return i;
}

static int quick_sort(uint8_t *arr, size_t data_size, int begin, int end, int(*cmp)(void *a, void *b))
{
    if(begin >= end)
        return 0; 
    
    int pivot = get_partition(arr, data_size, begin, end, cmp);
    // Validate pivot 
    if(pivot == -1)
        return -1;
    
    // Return -1 to exit on failure 
    if(quick_sort(arr, data_size, begin, pivot - 1, cmp))
        return -1;

    if(quick_sort(arr, data_size, pivot + 1, end, cmp) == -1)
        return -1;
    
    return 0;
}

static int insertionSort(uint8_t *arr, size_t data_size, int size, int(*cmp)(void *a, void *b))
{
    void *temp = malloc(data_size); 
    if(!temp)
        return -1;

    for(int i = 1; i < size; i++)
    {
        memcpy(temp, arr + (i * data_size), data_size);

        int j = i - 1; 
        
        while(j >= 0 && cmp(arr + (j * data_size), temp) > 0)
        {
            memcpy(arr + ((j + 1) * data_size), arr + (j * data_size), data_size);
            j--;
        }
        memcpy(arr + ((j + 1) * data_size), temp, data_size);
    }

    free(temp);

    return 0;
}

int v_sort(Vector *vec, int(*cmp)(void *a, void *b))
{
    if(!vec || !cmp)
        return -1; // Invalid input  
    
    if(vec->num_elements == 0)
        return 0;
    if(vec->num_elements < 100)
        return insertionSort(vec->vec_array, vec->data_size, vec->num_elements, cmp);
    else    
        return quick_sort(vec->vec_array, vec->data_size, 0, vec->num_elements - 1, cmp);
}