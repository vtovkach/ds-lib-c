#ifndef _HEAP_
#define _HEAP_ 

typedef struct Heap Heap; 

typedef int (*CompareFunc)(const void *, int, int);

// Function for internal use
int hp__insert_internal(Heap *heap, void *data);

/* =========================== Public API  ======================== */

Heap *hp_init(size_t data_size, int heap_size, CompareFunc comp_func);

void hp_destroy(Heap *heap);

int hp_peek(Heap *heap, void *dest_ptr);

int hp_get_size(Heap *heap);

int hp_remove_top(Heap *heap);

#define heap_insert(heap_ptr, data_type, data)  \
    hp__insert_internal(heap_ptr, &((data_type){(data)}))


// Development Stage Only

typedef void (*PrintFunc)(const void *heaparr, int size);

void displayData(Heap *heap, PrintFunc print);

#endif