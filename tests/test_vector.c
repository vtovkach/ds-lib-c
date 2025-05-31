#include <assert.h>
#include <stdio.h>

#include "../include/ds_vector.h"

void init_destroy_test()
{
    Vector *vec = vec_create(0, 0);

    assert(vec == NULL);
    vec = vec_create(10, sizeof(int));
    assert(vec != NULL);


    vec_destroy(vec);
}

void test_vector_push_pop() 
{
    int x = 10, y = 20, z = 30, out;

    // Push with NULL vector
    assert(v_push_back(NULL, &x) == -1);

    // Create a vector
    Vector *v = vec_create(2, sizeof(int));
    assert(v != NULL);

    // Push with NULL data
    assert(v_push_back(v, NULL) == -1);

    // Pop with NULL vector
    assert(v_pop_back(NULL) == -1);

    // Pop from empty vector
    assert(v_pop_back(v) == 1);

    // Push values
    assert(v_push_back(v, &x) == 0);
    assert(v_push_back(v, &y) == 0);

    // Trigger resize
    assert(v_push_back(v, &z) == 0);
    assert(v_size(v) == 3);
    assert(v_capacity(v) >= 3);

    // Get values
    assert(v_get(v, &out, 0) == 0); assert(out == 10);
    assert(v_get(v, &out, 1) == 0); assert(out == 20);
    assert(v_get(v, &out, 2) == 0); assert(out == 30);

    // Pop and check
    assert(v_pop_back(v) == 0);
    assert(v_size(v) == 2);
    assert(v_get(v, &out, 1) == 0); assert(out == 20);

    // Clear vector
    assert(v_clear(v) == 0);
    assert(v_size(v) == 0);
    assert(v_empty(v) == 1);

    vec_destroy(v);
}

void test_vector_access_and_modification() 
{
    int x = 10, y = 20, z = 30, out;

    // NULL tests
    assert(v_get(NULL, &out, 0) == -1);
    assert(v_get((Vector *)1, NULL, 0) == -1);  // fake pointer, NULL dest
    assert(v_set(NULL, &x, 0) == -1);
    assert(v_set((Vector *)1, NULL, 0) == -1);
    assert(v_insert(NULL, &x, 0) == -1);
    assert(v_insert((Vector *)1, NULL, 0) == -1);
    assert(v_erase(NULL, 0) == -1);

    // Create vector
    Vector *v = vec_create(2, sizeof(int));
    assert(v != NULL);

    // Access out-of-bounds
    assert(v_get(v, &out, 0) == -2);
    assert(v_set(v, &x, 0) == -2);
    assert(v_erase(v, 0) == -2);
    assert(v_insert(v, &x, 1) == -2);  // index > size

    // Insert at index 0
    assert(v_insert(v, &x, 0) == 0);
    assert(v_size(v) == 1);
    assert(v_get(v, &out, 0) == 0); assert(out == 10);

    // Insert at back (index == size)
    assert(v_insert(v, &y, 1) == 0);
    assert(v_get(v, &out, 1) == 0); assert(out == 20);

    // Insert in middle (index 1)
    assert(v_insert(v, &z, 1) == 0);
    assert(v_size(v) == 3);
    assert(v_get(v, &out, 0) == 0); assert(out == 10);
    assert(v_get(v, &out, 1) == 0); assert(out == 30);
    assert(v_get(v, &out, 2) == 0); assert(out == 20);

    // Set value at index 1
    int newval = 99;
    assert(v_set(v, &newval, 1) == 0);
    assert(v_get(v, &out, 1) == 0); assert(out == 99);

    // Erase middle
    assert(v_erase(v, 1) == 0);
    assert(v_get(v, &out, 1) == 0); assert(out == 20);
    assert(v_size(v) == 2);

    // Erase last
    assert(v_erase(v, 1) == 0);
    assert(v_size(v) == 1);
    assert(v_get(v, &out, 0) == 0); assert(out == 10);

    // Erase only remaining
    assert(v_erase(v, 0) == 0);
    assert(v_size(v) == 0);

    // Final cleanup
    vec_destroy(v);
}

void test_vector_utility_functions() 
{
    // NULL vector behavior
    assert(v_size(NULL) == 0);
    assert(v_capacity(NULL) == 0);
    assert(v_empty(NULL) == 1);
    assert(v_clear(NULL) == -1);

    // Create vector
    Vector *v = vec_create(4, sizeof(int));
    assert(v != NULL);

    // Initial state
    assert(v_size(v) == 0);
    assert(v_capacity(v) == 4);
    assert(v_empty(v) == 1);

    int x = 42;
    assert(v_push_back(v, &x) == 0);
    assert(v_size(v) == 1);
    assert(v_empty(v) == 0);

    // Clear and check state
    assert(v_clear(v) == 0);
    assert(v_size(v) == 0);
    assert(v_empty(v) == 1);
    assert(v_capacity(v) == 4);  // capacity should not shrink

    vec_destroy(v);
}

void test_vector_resize() 
{
    int x = 1, y = 2, z = 3, out;

    // Resize with NULL vector
    assert(v_resize(NULL, 5) == -1);

    // Resize to 0 (if disallowed)
    Vector *v = vec_create(2, sizeof(int));
    assert(v != NULL);
    assert(v_resize(v, 0) == -1);

    // Fill vector
    assert(v_push_back(v, &x) == 0);
    assert(v_push_back(v, &y) == 0);
    assert(v_size(v) == 2);
    assert(v_capacity(v) == 2);

    // Increase capacity
    assert(v_resize(v, 10) == 0);
    assert(v_capacity(v) == 10);
    assert(v_size(v) == 2);
    assert(v_get(v, &out, 0) == 0); assert(out == 1);
    assert(v_get(v, &out, 1) == 0); assert(out == 2);

    // Add a third value
    assert(v_push_back(v, &z) == 0);
    assert(v_size(v) == 3);
    assert(v_get(v, &out, 2) == 0); assert(out == 3);

    // Shrink capacity (truncate)
    assert(v_resize(v, 1) == 0);
    assert(v_capacity(v) == 1);
    assert(v_size(v) == 1);
    assert(v_get(v, &out, 0) == 0); assert(out == 1);
    assert(v_get(v, &out, 1) == -2);  // out-of-bounds now

    vec_destroy(v);
}

int main(void)
{
    // Vector Test 

    init_destroy_test();
    test_vector_push_pop();
    test_vector_access_and_modification();
    test_vector_utility_functions();
    test_vector_resize();

    printf("All tests were passed!\n");

    return 0; 
}