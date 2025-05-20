#include <stdio.h>

#include "../include/heap.h"


int compare(const void * array, int child, int parent)
{
    if(((int *)array)[child] > ((int *)array)[parent])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// For Integer Data Type  
void print(const void *heaparr, int size)
{
    for(int i = 0; i < size; ++i)
    {
        printf("%d ", ((int *)heaparr)[i]);
    }
    putchar('\n');
}   

int main(void)
{

    Heap *heap = hp_init(sizeof(int), 10, compare);

    heap_insert(heap, int, 1);
    heap_insert(heap, int, 2);
    heap_insert(heap, int, 3);
    heap_insert(heap, int, 18);
    heap_insert(heap, int, 20);
    heap_insert(heap, int, 1);
    heap_insert(heap, int, 2);
    heap_insert(heap, int, 3);
    heap_insert(heap, int, 18);
    heap_insert(heap, int, 20);
    heap_insert(heap, int, 1);
    heap_insert(heap, int, 2);
    heap_insert(heap, int, 3);
    heap_insert(heap, int, 18);
    heap_insert(heap, int, 20);

    printf("Before: ");
    displayData(heap, print);
    putchar('\n');
    
    printf("Num elem: %d\n", hp_get_size(heap));

    hp_remove_top(heap);
    printf("Num elem: %d\n", hp_get_size(heap));
    hp_remove_top(heap);
    hp_remove_top(heap);
    hp_remove_top(heap);
    printf("Num elem: %d\n", hp_get_size(heap));
    hp_remove_top(heap);
    hp_remove_top(heap);
    printf("Num elem: %d\n", hp_get_size(heap));

    printf("After: ");
    displayData(heap, print);


    hp_destroy(heap);

    return 0;
}