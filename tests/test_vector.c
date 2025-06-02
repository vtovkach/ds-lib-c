// vector_tests.c
// Refactored test suite for the custom Vector library (ds_vector.h).
// Each test case is split into small functions targeting specific operations.
//
// To compile (adjust library path/names as needed):
//     gcc -Wall -Wextra -o vector_tests vector_tests.c -L../lib -lds_vector

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdint.h>

#include "../include/ds_vector.h"

// Globals to track total and failed assertions
static int total_tests = 0;
static int failed_tests = 0;

// Assertion macros
#define EXPECT_EQ_INT(actual, expected, message) do {             \
    total_tests++;                                                \
    if ((actual) != (expected)) {                                 \
        fprintf(stderr, "[FAIL] %s: expected %d, got %d\n",       \
                (message), (int)(expected), (int)(actual));       \
        failed_tests++;                                           \
    }                                                              \
} while (0)

#define EXPECT_EQ_SIZE(actual, expected, message) do {            \
    total_tests++;                                                \
    if ((actual) != (expected)) {                                 \
        fprintf(stderr, "[FAIL] %s: expected %zu, got %zu\n",     \
                (message), (size_t)(expected), (size_t)(actual));\
        failed_tests++;                                           \
    }                                                              \
} while (0)

#define EXPECT_TRUE(cond, message) do {                           \
    total_tests++;                                                \
    if (!(cond)) {                                                \
        fprintf(stderr, "[FAIL] %s: condition is false\n", (message)); \
        failed_tests++;                                           \
    }                                                              \
} while (0)

// Simple integer comparator for sorting
static int cmp_int(void *a, void *b) {
    int ia = *(int *)a;
    int ib = *(int *)b;
    return (ia < ib) ? -1 : (ia > ib);
}

// Comparator for a struct (Pair) by its 'value' field
typedef struct {
    int key;
    int value;
} Pair;
static int cmp_pair_by_value(void *a, void *b) {
    int va = ((Pair *)a)->value;
    int vb = ((Pair *)b)->value;
    return (va < vb) ? -1 : (va > vb);
}

// 1. Test vec_create and vec_destroy
static void test_create_destroy(void) {
    Vector *v;

    v = vec_create(0, sizeof(int));
    EXPECT_TRUE(v == NULL, "vec_create(0, sizeof(int)) should return NULL");

    v = vec_create(10, 0);
    EXPECT_TRUE(v == NULL, "vec_create(10, 0) should return NULL");

    v = vec_create(5, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create(5, sizeof(int)) should succeed");
    if (v) {
        EXPECT_EQ_SIZE(v_size(v), 0, "New vector should have size 0");
        EXPECT_EQ_SIZE(v_capacity(v), 5, "New vector capacity should be 5");
        EXPECT_TRUE(v_empty(v) == 1, "New vector should be empty");
        vec_destroy(v);
    }
}

// 2. Test v_push_back (including resizing) and v_top
static void test_push_back_and_top(void) {
    Vector *v = vec_create(3, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create for push_back test should succeed");
    int dummy = 42;

    EXPECT_EQ_INT(v_push_back(NULL, &dummy), -1, "v_push_back(NULL, &data) should return -1");
    EXPECT_EQ_INT(v_push_back(v, NULL), -1, "v_push_back(v, NULL) should return -1");

    // Fill initial capacity
    for (int i = 0; i < 3; i++) {
        int x = i * 7;
        EXPECT_EQ_INT(v_push_back(v, &x), 0, "v_push_back should succeed");
        EXPECT_EQ_SIZE(v_size(v), (size_t)(i + 1), "Size after push");
    }
    EXPECT_EQ_SIZE(v_capacity(v), 3, "Capacity should remain 3 before overflow");

    
    // Trigger resize (from 3 to 6)
    int extra = 999;
    EXPECT_EQ_INT(v_push_back(v, &extra), 0, "v_push_back should succeed and resize");
    EXPECT_EQ_SIZE(v_size(v), 4, "Size should be 4 after resize push");
    EXPECT_EQ_SIZE(v_capacity(v), 6, "Capacity should double to 6 after resize");
    
    // Test v_top
    int top_val = -1;
    
    EXPECT_EQ_INT(v_top(NULL, &top_val), -1, "v_top(NULL) should return -1");

    EXPECT_EQ_INT(v_top(v, NULL), -1, "v_top(v, NULL) should return -1");

    EXPECT_EQ_INT(v_top(v, &top_val), 0, "v_top should succeed");
    EXPECT_EQ_INT(top_val, 999, "v_top should return last pushed value");
    

    // Clear to test v_top on empty
    EXPECT_EQ_INT(v_clear(v), 0, "v_clear should succeed");
    EXPECT_EQ_INT(v_top(v, &top_val), 1, "v_top on empty vector should return 1");
    
    vec_destroy(v);
}

// 3. Test v_pop_back (normal, empty, null)
static void test_pop_back(void) {
    Vector *v = vec_create(2, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create for pop_back test should succeed");

    EXPECT_EQ_INT(v_pop_back(NULL), -1, "v_pop_back(NULL) should return -1");
    EXPECT_EQ_INT(v_pop_back(v), 1, "v_pop_back on empty vector should return 1");

    // Push a few elements
    for (int i = 0; i < 2; i++) {
        int x = 100 + i;
        EXPECT_EQ_INT(v_push_back(v, &x), 0, "v_push_back should succeed");
    }
    EXPECT_EQ_SIZE(v_size(v), 2, "Size should be 2 after pushes");

    EXPECT_EQ_INT(v_pop_back(v), 0, "v_pop_back should succeed");
    EXPECT_EQ_SIZE(v_size(v), 1, "Size should be 1 after pop");
    EXPECT_EQ_INT(v_pop_back(v), 0, "v_pop_back should succeed");
    EXPECT_EQ_INT(v_pop_back(v), 1, "v_pop_back on now-empty should return 1");

    vec_destroy(v);
}

// 4. Test v_get and v_set (including edge cases)
static void test_get_and_set(void) {
    Vector *v = vec_create(5, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create for get/set test should succeed");

    // Populate vector with negative multiples
    for (int i = 0; i < 5; i++) {
        int x = i * (-5);
        EXPECT_EQ_INT(v_push_back(v, &x), 0, "v_push_back in get/set test");
    }
    EXPECT_EQ_SIZE(v_size(v), 5, "Size should be 5 after pushes");

    int out = 0;
    EXPECT_EQ_INT(v_get(NULL, &out, 0), -1, "v_get(NULL) should return -1");
    EXPECT_EQ_INT(v_get(v, NULL, 0), -1, "v_get(v, NULL) should return -1");
    EXPECT_EQ_INT(v_get(v, &out, 0), 0, "v_get valid index 0 should succeed");
    EXPECT_EQ_INT(out, 0, "v_get idx 0 should return 0");
    EXPECT_EQ_INT(v_get(v, &out, 4), 0, "v_get idx 4 should succeed");
    EXPECT_EQ_INT(out, -20, "v_get idx 4 should return -20");
    EXPECT_EQ_INT(v_get(v, &out, 5), -2, "v_get OOB idx should return -2");

    // Test v_set
    int new_val = 777;
    EXPECT_EQ_INT(v_set(NULL, &new_val, 0), -1, "v_set(NULL) should return -1");
    EXPECT_EQ_INT(v_set(v, NULL, 0), -1, "v_set(v, NULL) should return -1");
    EXPECT_EQ_INT(v_set(v, &new_val, 5), -2, "v_set OOB idx should return -2");
    EXPECT_EQ_INT(v_set(v, &new_val, 2), 0, "v_set valid idx should succeed");
    EXPECT_EQ_INT(v_get(v, &out, 2), 0, "v_get after v_set should succeed");
    EXPECT_EQ_INT(out, 777, "v_get idx 2 should return 777");

    vec_destroy(v);
}

// 5. Test v_insert (beginning, middle, end, invalid, resizing)
static void test_insert(void) {
    Vector *v = vec_create(4, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create for insert test should succeed");

    int val = 5;
    EXPECT_EQ_INT(v_insert(NULL, &val, 0), -1, "v_insert(NULL) should return -1");
    EXPECT_EQ_INT(v_insert(v, NULL, 0), -1, "v_insert(v, NULL) should return -1");
    EXPECT_EQ_INT(v_insert(v, &val, 1), -2, "v_insert idx > size should return -2");

    // Insert at beginning
    size_t old_size = v_size(v);
    EXPECT_EQ_INT(v_insert(v, &val, 0), 0, "v_insert at 0 should succeed");
    EXPECT_EQ_SIZE(v_size(v), old_size + 1, "Size should increment after insert at 0");
    int out = 0;
    EXPECT_EQ_INT(v_get(v, &out, 0), 0, "v_get idx 0 after insert");
    EXPECT_EQ_INT(out, 5, "Value at idx 0 should be 5");

    // Insert in middle
    for (int i = 0; i < 3; i++) {
        int x = (i + 1) * 10;
        EXPECT_EQ_INT(v_push_back(v, &x), 0, "Populate for middle insert");
    }
    size_t mid = v_size(v) / 2;
    int mid_val = 42;
    old_size = v_size(v);
    EXPECT_EQ_INT(v_insert(v, &mid_val, mid), 0, "v_insert in middle should succeed");
    EXPECT_EQ_SIZE(v_size(v), old_size + 1, "Size should increment after middle insert");
    EXPECT_EQ_INT(v_get(v, &out, mid), 0, "v_get new middle");
    EXPECT_EQ_INT(out, 42, "Inserted middle value should be 42");

    // Insert at end (index == size)
    old_size = v_size(v);
    int end_val = 99;
    EXPECT_EQ_INT(v_insert(v, &end_val, old_size), 0, "v_insert at end should succeed");
    EXPECT_EQ_SIZE(v_size(v), old_size + 1, "Size should increment after end insert");
    EXPECT_EQ_INT(v_get(v, &out, old_size), 0, "v_get new end");
    EXPECT_EQ_INT(out, 99, "Inserted end value should be 99");

    // Force multiple resizes by inserting at 0 repeatedly
    for (int i = 0; i < 50; i++) {
        int rv = i + 1000;
        EXPECT_EQ_INT(v_insert(v, &rv, 0), 0, "Stress v_insert at 0");
    }
    EXPECT_TRUE(v_capacity(v) >= v_size(v), "Capacity >= size after many inserts");

    vec_destroy(v);
}

// 6. Test v_erase (beginning, middle, end, invalid, null)
static void test_erase(void) {
    Vector *v = vec_create(5, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create for erase test should succeed");

    // Populate
    for (int i = 0; i < 5; i++) {
        int x = i;
        EXPECT_EQ_INT(v_push_back(v, &x), 0, "v_push_back for erase test");
    }

    EXPECT_EQ_INT(v_erase(NULL, 0), -1, "v_erase(NULL) should return -1");
    EXPECT_EQ_INT(v_erase(v, 5), -2, "v_erase OOB idx should return -2");

    // Erase first element
    size_t before = v_size(v);
    EXPECT_EQ_INT(v_erase(v, 0), 0, "v_erase idx 0 should succeed");
    EXPECT_EQ_SIZE(v_size(v), before - 1, "Size should decrement after erase 0");

    // Erase middle element
    size_t mid = v_size(v) / 2;
    int before_val = 0, after_val = 0;
    EXPECT_EQ_INT(v_get(v, &before_val, mid), 0, "v_get before erase middle");
    before = v_size(v);
    EXPECT_EQ_INT(v_erase(v, mid), 0, "v_erase middle should succeed");
    EXPECT_EQ_SIZE(v_size(v), before - 1, "Size should decrement after erase middle");
    EXPECT_EQ_INT(v_get(v, &after_val, mid), 0, "v_get after erase middle");
    EXPECT_TRUE(after_val != before_val, "Value should shift after erase middle");

    // Erase last element (should call v_pop_back)
    size_t last = v_size(v) - 1;
    int last_val = 0;
    EXPECT_EQ_INT(v_get(v, &last_val, last), 0, "v_get last before erase");
    EXPECT_EQ_INT(v_erase(v, last), 0, "v_erase last should succeed");
    EXPECT_EQ_SIZE(v_size(v), last, "Size should decrement after erase last");

    vec_destroy(v);
}

// 7. Test v_size, v_capacity, v_empty, v_clear
static void test_size_capacity_empty_clear(void) {
    Vector *v = vec_create(3, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create for size/capacity test should succeed");

    EXPECT_EQ_SIZE(v_size(v), 0, "Size initially should be 0");
    EXPECT_EQ_SIZE(v_capacity(v), 3, "Capacity initially should be 3");
    EXPECT_TRUE(v_empty(v) == 1, "Vector should be empty initially");

    for (int i = 0; i < 2; i++) {
        int x = i;
        EXPECT_EQ_INT(v_push_back(v, &x), 0, "v_push_back for size test");
    }
    EXPECT_EQ_SIZE(v_size(v), 2, "Size after pushes should be 2");
    EXPECT_TRUE(v_empty(v) == 0, "Vector should not be empty after pushes");

    EXPECT_EQ_INT(v_clear(v), 0, "v_clear should succeed");
    EXPECT_EQ_SIZE(v_size(v), 0, "Size should be 0 after clear");
    EXPECT_TRUE(v_empty(v) == 1, "Vector should be empty after clear");

    vec_destroy(v);
}

// 8. Test v_resize (enlarge, shrink, invalid, null)
static void test_resize(void) {
    Vector *v = vec_create(4, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create for resize test should succeed");

    EXPECT_EQ_INT(v_resize(NULL, 5), -1, "v_resize(NULL) should return -1");
    EXPECT_EQ_INT(v_resize(v, 0), -1, "v_resize(v, 0) should return -1");

    // Populate 6 elements to force auto-resize
    for (int i = 0; i < 6; i++) {
        int x = i;
        EXPECT_EQ_INT(v_push_back(v, &x), 0, "v_push_back for resize test");
    }
    EXPECT_TRUE(v_capacity(v) >= 6, "Capacity should have grown automatically");

    // Manually enlarge to 10
    EXPECT_EQ_INT(v_resize(v, 10), 0, "v_resize enlarge should succeed");
    EXPECT_EQ_SIZE(v_capacity(v), 10, "Capacity should be 10 after enlarge");
    EXPECT_TRUE(v_size(v) == 6, "Size should remain 6 after enlarge");

    // Fill to capacity 10
    for (int i = 6; i < 10; i++) {
        EXPECT_EQ_INT(v_push_back(v, &i), 0, "Push to fill resized capacity");
    }
    EXPECT_EQ_SIZE(v_size(v), 10, "Size should be 10 after filling");

    // Shrink capacity to 5 (size > new capacity)
    EXPECT_EQ_INT(v_resize(v, 5), 0, "v_resize shrink should succeed");
    EXPECT_EQ_SIZE(v_capacity(v), 5, "Capacity should be 5 after shrink");
    EXPECT_EQ_SIZE(v_size(v), 5, "Size should be truncated to 5 after shrink");

    vec_destroy(v);
}

// 9. Test v_sort on ints (empty, small, large)
static void test_sort_integers(void) {
    Vector *v = vec_create(5, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create for sort test should succeed");

    // Sorting empty
    EXPECT_EQ_INT(v_sort(v, cmp_int), 0, "v_sort on empty should return 0");

    // Small (<100) sort with 50 random ints
    EXPECT_EQ_INT(v_clear(v), 0, "Clear before small sort");
    for (int i = 0; i < 50; i++) {
        int r = rand() % 1000 - 500;
        EXPECT_EQ_INT(v_push_back(v, &r), 0, "v_push_back for small sort");
    }
    EXPECT_EQ_INT(v_sort(v, cmp_int), 0, "v_sort small vector should succeed");
    // Check sorted order
    int prev = INT32_MIN, curr = 0;
    for (size_t i = 0; i < v_size(v); i++) {
        EXPECT_EQ_INT(v_get(v, &curr, i), 0, "v_get during small sort verification");
        EXPECT_TRUE(prev <= curr, "Elements should be in non-decreasing order");
        prev = curr;
    }

    // Large (≥100) sort with 200 random ints
    EXPECT_EQ_INT(v_clear(v), 0, "Clear before large sort");
    for (int i = 0; i < 200; i++) {
        int r = rand() % 10000 - 5000;
        EXPECT_EQ_INT(v_push_back(v, &r), 0, "v_push_back for large sort");
    }
    EXPECT_EQ_INT(v_sort(v, cmp_int), 0, "v_sort large vector should succeed");
    // Check sorted order
    prev = INT32_MIN;
    for (size_t i = 0; i < v_size(v); i++) {
        EXPECT_EQ_INT(v_get(v, &curr, i), 0, "v_get during large sort verification");
        EXPECT_TRUE(prev <= curr, "Elements should be sorted");
        prev = curr;
    }

    vec_destroy(v);
}

// 10. Test v_sort on structs (Pair) by 'value'
static void test_sort_structs(void) {
    Vector *vsp = vec_create(30, sizeof(Pair));
    EXPECT_TRUE(vsp != NULL, "vec_create for struct sort should succeed");

    // Push random Pair structs
    for (int i = 0; i < 30; i++) {
        Pair p = { .key = i, .value = rand() % 200 };
        EXPECT_EQ_INT(v_push_back(vsp, &p), 0, "v_push_back for struct sort");
    }
    EXPECT_EQ_INT(v_sort(vsp, cmp_pair_by_value), 0, "v_sort on Pair vector should succeed");

    // Verify sorted by 'value'
    int last_val = INT32_MIN, curr_val = 0;
    Pair temp;
    for (size_t i = 0; i < v_size(vsp); i++) {
        EXPECT_EQ_INT(v_get(vsp, &temp, i), 0, "v_get struct after sort");
        curr_val = temp.value;
        EXPECT_TRUE(last_val <= curr_val, "Structs should be sorted by value");
        last_val = curr_val;
    }

    vec_destroy(vsp);
}

// 11. Stress test: random push/pop/get operations
static void test_stress_operations(void) {
    Vector *v = vec_create(10, sizeof(int));
    EXPECT_TRUE(v != NULL, "vec_create for stress test should succeed");

    size_t iterations = 50000;
    for (size_t i = 0; i < iterations; i++) {
        int op = rand() % 3;
        if (op == 0) {
            // Push random int
            int r = rand();
            int res = v_push_back(v, &r);
            EXPECT_TRUE(res == 0, "v_push_back in stress should succeed or OOM");
        } else if (op == 1) {
            // Pop if not empty
            if (v_size(v) > 0) {
                int res = v_pop_back(v);
                EXPECT_TRUE(res == 0, "v_pop_back in stress should succeed");
            }
        } else { // op == 2
            // Get random element if not empty
            if (v_size(v) > 0) {
                size_t idx = rand() % v_size(v);
                int out = 0;
                EXPECT_EQ_INT(v_get(v, &out, idx), 0, "v_get in stress should succeed");
            }
        }
        // Always check capacity >= size
        EXPECT_TRUE(v_capacity(v) >= v_size(v), "Capacity >= size during stress");
    }

    vec_destroy(v);
}


static void test_timed_insert_erase(void) {
    const uint64_t NUM_OPS = 100000000ULL;
    const size_t INITIAL_CAPACITY = NUM_OPS; // pre-allocate so we don't measure realloc overhead

    Vector *v = vec_create(INITIAL_CAPACITY, sizeof(int));
    if (!v) {
        fprintf(stderr, "[ERROR] Could not allocate vector for performance test.\n");
        return;
    }

    struct timespec start, end;
    // Record start time
    if (clock_gettime(1, &start) != 0) {
        perror("clock_gettime");
        vec_destroy(v);
        return;
    }

    // Perform NUM_OPS iterations of push_back + pop_back
    for (uint64_t i = 0; i < NUM_OPS; i++) {
        int value = (int)i;
        v_push_back(v, &value);
        v_pop_back(v);
    }

    // Record end time
    if (clock_gettime(1, &end) != 0) {
        perror("clock_gettime");
        vec_destroy(v);
        return;
    }

    // Calculate elapsed time in seconds (as double)
    double elapsed_sec = (end.tv_sec - start.tv_sec)
                       + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Performed %llu inserts+erases in %.3f seconds\n",
           (unsigned long long)NUM_OPS, elapsed_sec);

    vec_destroy(v);
}

int main(void) {
    srand((unsigned)time(NULL));

    // Call individual test functions
    test_create_destroy();
    test_push_back_and_top();
    test_pop_back();
    test_get_and_set();
    test_insert();
    test_erase();
    test_size_capacity_empty_clear();
    test_resize();
    test_sort_integers();
    test_sort_structs();
    test_stress_operations();

    test_timed_insert_erase();

    // Print summary
    printf("\n========== Test Summary ==========\n");
    printf("Total tests run: %d\n", total_tests);
    printf("Total failures : %d\n", failed_tests);
    if (failed_tests == 0) {
        printf("ALL TESTS PASSED\n");
        return EXIT_SUCCESS;
    } else {
        printf("SOME TESTS FAILED\n");
        return EXIT_FAILURE;
    }
}
