#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../include/heap.h"

/* ===============  Potential Improvements  ==================== */

// 1.) Use loops instead of recursion 
// 

typedef struct
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
        fprintf(stderr, "Swap. Error allocating memory!\n");
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


static size_t resize(void **ptr, size_t data_size, size_t current_size)
{
    // Resize array to twice as many elements 

    size_t new_size = current_size * 2;

    printf("New Size is %zu\n", new_size);

    void *temp = realloc(*ptr, new_size * data_size);

    printf("I am here resizing!\n");

    if(temp == NULL)
    {
        return 0;
    }

    *ptr = temp;

    return new_size;
}

// ============================= PRIMARY FUNCTIONS ====================================

// Initialize Heap Function  
Heap *initHeap(size_t data_size, int heap_size, CompareFunc comp_func)
{
    // Input: requested num_elem for the heap
    // Output: pointer to the heap data structure 
    
    // Check if the num_elem != 0
    if(heap_size == 0)
    {
        fprintf(stderr, "The input num_elem is 0. No heap will be created!\n");
        return NULL;
    }
    
    // Check if data size is invalid 
    if(data_size == 0)
    {
        fprintf(stderr, "Data Size is 0 bytes. Quit.\n");
        return; 
    }

    if(!comp_func)
    {
        fprintf(stderr, "Compare function is null. Quit.\n");
        return NULL;
    }

    // Dynamically allocate space for heap 
    Heap *heapptr = malloc(sizeof(Heap));

    if(heapptr == NULL)
    {
        fprintf(stderr, "Error allocating memory for heap.\n");
        return NULL;
    }

    // Dynamically allocate space for heap elements
    // void *
    heapptr->heaparray = (void *)malloc(data_size * heap_size);

    if(heapptr->heaparray == NULL)
    {
        fprintf(stderr, "Error allocating memory for heap.\n");
        free(heapptr);
        return NULL;
    }
    
    // Initialize heap data 
    heapptr->current_index = 0;
    heapptr->heap_size = heap_size;
    heapptr->data_size = data_size;
    heapptr->cmp_func = comp_func;

    return heapptr;
}

