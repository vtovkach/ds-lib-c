#include <stdio.h>
#include <assert.h>

#include "../include/ds_heap.h"

// For a min-heap: return 1 if child < parent
int int_min_compare(const void *arr, int child_idx, int parent_idx) {
    const int *a = (const int *)arr;
    return a[child_idx] < a[parent_idx];
}

// Print function for testing
void print_int(const void *heaparr, int size) {
    const int *arr = (const int *)heaparr;
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// ========================= Test Cases ============================

void test_basic_insertion_and_peek() {
    Heap *heap = hp_init(sizeof(int), 10, int_min_compare);
    heap_insert(heap, int, 42);
    heap_insert(heap, int, 15);
    heap_insert(heap, int, 20);

    int top;
    hp_peek(heap, &top);
    assert(top == 15);
    hp_destroy(heap);
    printf("test_basic_insertion_and_peek passed\n");
}

void test_remove_top_and_validate_structure() {
    Heap *heap = hp_init(sizeof(int), 10, int_min_compare);
    heap_insert(heap, int, 8);
    heap_insert(heap, int, 3);
    heap_insert(heap, int, 10);
    heap_insert(heap, int, 1);

    int top;
    hp_remove_top(heap); // removes 1
    hp_peek(heap, &top);
    assert(top == 3);
    hp_destroy(heap);
    printf("test_remove_top_and_validate_structure passed\n");
}

void test_insert_and_remove_all() {
    Heap *heap = hp_init(sizeof(int), 5, int_min_compare);
    heap_insert(heap, int, 5);
    heap_insert(heap, int, 2);
    heap_insert(heap, int, 4);
    heap_insert(heap, int, 1);
    heap_insert(heap, int, 3);

    int result[5];
    for (int i = 0; i < 5; ++i) {
        hp_peek(heap, &result[i]);
        hp_remove_top(heap);
    }

    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i)
        assert(result[i] == expected[i]);

    hp_destroy(heap);
    printf("test_insert_and_remove_all passed\n");
}

void test_dynamic_size_reporting() {
    Heap *heap = hp_init(sizeof(int), 5, int_min_compare);
    assert(hp_get_size(heap) == 0);

    heap_insert(heap, int, 1);
    heap_insert(heap, int, 2);
    assert(hp_get_size(heap) == 2);

    hp_remove_top(heap);
    assert(hp_get_size(heap) == 1);

    hp_destroy(heap);
    printf("test_dynamic_size_reporting passed\n");
}

void test_peek_and_remove_on_empty_heap() {
    Heap *heap = hp_init(sizeof(int), 5, int_min_compare);
    int top;

    assert(hp_peek(heap, &top) == -1);
    assert(hp_remove_top(heap) == -1);

    hp_destroy(heap);
    printf("test_peek_and_remove_on_empty_heap passed\n");
}

void test_large_input_stress() {
    Heap *heap = hp_init(sizeof(int), 1000, int_min_compare);
    for (int i = 1000; i > 0; --i)
        heap_insert(heap, int, i);

    int prev = -1, curr;
    while (hp_get_size(heap)) {
        hp_peek(heap, &curr);
        assert(curr >= prev);
        prev = curr;
        hp_remove_top(heap);
    }

    hp_destroy(heap);
    printf("test_large_input_stress passed\n");
}

// ============================= Main ==============================

int main() {
    test_basic_insertion_and_peek();
    test_remove_top_and_validate_structure();
    test_insert_and_remove_all();
    test_dynamic_size_reporting();
    test_peek_and_remove_on_empty_heap();
    test_large_input_stress();
    printf("All tests passed successfully!\n");
    return 0;
}