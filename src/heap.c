#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../include/ds_heap.h"

typedef struct Heap
{   
    void   *heaparray;          // 0-indexed array
    int     heap_size;          // Max number of elements in the heap 
    int     current_index;      // First available index for insertion 
    int     num_elements;       // Current number of elements in the heap 
    size_t  data_size;          // Data Type Size in Bytes
    CompareFunc cmp_func;       // User-defined compare function 
} Heap;

// ======================= Helper Functions ===========================

static void swap(void *dest1, void *dest2, size_t bytes)
{
    // ========== Swap numbers in generic array ===========
    
    // Allocate memory for temporary value for swap
    void * temp = (void *) malloc(bytes);
    // Check for malloc failure 
    if(temp == NULL)
    {

        return;
    }

    // Perform Swap
    memcpy(temp, dest1, bytes);
    memcpy(dest1, dest2, bytes);
    memcpy(dest2, temp, bytes);

    // free temporary space
    free(temp);
}

static void bottom_up_heapify(Heap *heap, int cur_idx)
{
    // ========== Used for the insertion ===========

    // Base case 
    if(cur_idx == 0)
    {
        return;
    }
    
    int parent_idx = (cur_idx - 1) / 2;

    // Compare child with parent 
    if(heap->cmp_func(heap->heaparray, cur_idx, parent_idx) == 1)
    {   
        // Perform Swap
        swap((uint8_t*)heap->heaparray + cur_idx * heap->data_size, (uint8_t*)heap->heaparray + parent_idx * heap->data_size, heap->data_size);
        bottom_up_heapify(heap, parent_idx);
    }

    return;
}

// Heapify for removing
static void top_bottom_heapify(Heap *heap, int cur_idx)
{
    int largest = cur_idx;  
    int left = cur_idx * 2 + 1;     // Left child index
    int right = cur_idx * 2 + 2;    // Right child index

    // Check if left child exists and is greater than the current item
    if(left < heap->current_index && heap->cmp_func(heap->heaparray, left, largest) == 1)
    {
        largest = left;
    }

    // Check if right child exists and is greater than the current largest
    if(right < heap->current_index && heap->cmp_func(heap->heaparray, right, largest) == 1)
    {
        largest = right;
    }

    if(largest != cur_idx)
    {   
        // Perform Swap 
        swap((uint8_t*)heap->heaparray + cur_idx * heap->data_size, (uint8_t*)heap->heaparray + largest * heap->data_size, heap->data_size);
        
        // Continue heapifying at the new position
        top_bottom_heapify(heap, largest);
    }

    return;
}

static size_t resize(void **ptr, size_t data_size, size_t current_size)
{
    // Resize array to twice as many elements 

    size_t new_size = current_size * 2;

    void *temp = realloc(*ptr, new_size * data_size);


    if(temp == NULL)
    {
        return 0;
    }

    *ptr = temp;

    return new_size;
}

// ============================= PRIMARY FUNCTIONS ====================================

// Initialize Heap Function  
Heap *hp_init(size_t data_size, int heap_size, CompareFunc comp_func)
{
    // Input: requested num_elem for the heap
    // Output: pointer to the heap data structure 
    
    // Check if the num_elem != 0
    if(heap_size == 0)
    {
        return NULL;
    }
    
    // Check if data size is invalid 
    if(data_size == 0)
    {
        return NULL; 
    }

    if(!comp_func)
    {
        return NULL;
    }

    // Dynamically allocate space for heap 
    Heap *heapptr = malloc(sizeof(Heap));

    if(heapptr == NULL)
    {
        return NULL;
    }

    // Dynamically allocate space for heap elements
    // void *
    heapptr->heaparray = (void *)malloc(data_size * heap_size);

    if(heapptr->heaparray == NULL)
    {
        free(heapptr);
        return NULL;
    }
    
    // Initialize heap data 
    heapptr->current_index = 0;
    heapptr->heap_size = heap_size;
    heapptr->data_size = data_size;
    heapptr->cmp_func = comp_func;
    heapptr->num_elements = 0;

    return heapptr;
}

int hp__insert_internal(Heap *heap, void *data)
{
    // Return  0 if success 
    // return -1 if error

    if(heap == NULL)
    {
        return -1;
    }

    if(heap->current_index > heap->heap_size - 1)
    {   
        // Make array twice larger
        size_t new_size = resize(&heap->heaparray, heap->data_size, heap->heap_size);

        if(new_size == 0)
        {
            return -1;
        }
        heap->heap_size = new_size;
    }   

    memcpy((uint8_t*)heap->heaparray + (heap->current_index * heap->data_size), data, heap->data_size);

    bottom_up_heapify(heap, heap->current_index);

    heap->current_index++;
    heap->num_elements++;

    return 0;
}

int hp_remove_top(Heap *heap)
{   
    // Purpose: remove item from the top of the heap
    // Input pointer to heap & pointer to user-built compare function
    // Output: 0 if success, -1 if failure 

    if(heap == NULL)
    {
        return -1;
    }

    // Check if heap is empty
    if(heap->current_index == 0)
    {
        return -1;
    }

    // Cast heap array to be able to perform pointer arithmetic 
    uint8_t *heaparr = (uint8_t*)heap->heaparray;

    // Move the lowest item of the heap to the top 
    memcpy(heaparr, heaparr + (heap->current_index - 1) * heap->data_size, heap->data_size);

    heap->current_index--;
    heap->num_elements--;
    // Perform top bottom heapification
    top_bottom_heapify(heap, 0);

    return 0;
}

int hp_peek(Heap *heap, void *dest_ptr)
{
    // Input: pointer to heap, void* to a memory to save top value  
    // Output: assign void* to a data from the top of the heap

    if(heap == NULL)
    {
        return -1;
    }

    // Check if heap is empty
    if(heap->current_index == 0)
    {
        return -1;
    }
    
    memcpy(dest_ptr, (uint8_t*)heap->heaparray + 0 * heap->data_size, heap->data_size);

    return 0;
}

int hp_get_size(Heap *heap)
{
    return heap ? heap->num_elements : -1;
}

void hp_destroy(Heap *heap)
{
    if(heap == NULL)
    {
        return;
    }
    // Deallocation //
    free(heap->heaparray);
    free(heap);
}