#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../include/ds_queue.h"

void test_enqueue_dequeue()
{
    Queue *queue = q_init(1, sizeof(int));

    q__enqueue(queue, &(int){44});
    q__enqueue(queue, &(int){100});
    q__enqueue(queue, &(int){105});

    int data = 0;

    q_dequeue(queue, &data);
    assert(data == 44);

    q_dequeue(queue, &data);
    assert(data == 100);

    q_dequeue(queue, &data);
    assert(data == 105);

    printf("Basic enqueue dequeue test is passed.\n");

    q_destroy(queue);
}

void test_queue_wraparound()
{
    const int total = 1000000;
    Queue *q = q_init(4, sizeof(int)); // start small to force wraparound/resizing
    assert(q != NULL);

    // Enqueue 1 million integers
    for (int i = 0; i < total; ++i)
    {
        assert(q__enqueue(q, &i) == 0);
    }

    // Dequeue and check correctness
    for (int i = 0; i < total; ++i)
    {
        int val = -1;
        assert(q_dequeue(q, &val) == 0);
        assert(val == i);
    }

    // Final check: queue should be empty
    assert(q_size(q) == 0);

    printf("Wraparound and 1 million enqueue/dequeue test passed.\n");

    q_destroy(q); 
}

void test_queue_resize_wraparound() 
{
    Queue *q = q_init(8, sizeof(int));
    assert(q);

    int val;

    // Fill queue: [0–7]
    for (int i = 0; i < 8; i++)
        assert(q__enqueue(q, &i) == 0);

    // Dequeue 5 elements (front moves forward)
    for (int i = 0; i < 5; i++) {
        assert(q_dequeue(q, &val) == 0);
        assert(val == i);
    }

    // Enqueue 5 more: [8–12] — rear wraps
    for (int i = 8; i < 13; i++)
        assert(q__enqueue(q, &i) == 0);

    // Now queue is full again, with front > rear
    // Trigger resize
    int sentinel = 999;
    assert(q__enqueue(q, &sentinel) == 0);

    // Dequeue and check all remaining values
    int expected[] = {5, 6, 7, 8, 9, 10, 11, 12, 999};
    for (int i = 0; i < 9; i++) {
        assert(q_dequeue(q, &val) == 0);
        assert(val == expected[i]);
    }

    assert(q_size(q) == 0);
    printf("Short wraparound + resize test passed.\n");

    q_destroy(q);
}

void test_peek() 
{
    Queue *q = q_init(4, sizeof(int));
    assert(q);

    int x = 42, y = -1;
    assert(q__enqueue(q, &x) == 0);
    assert(q_peek(q, &y) == 0);
    assert(y == 42);

    int temp;
    assert(q_dequeue(q, &temp) == 0);
    assert(temp == 42);

    // Now queue is empty
    assert(q_peek(q, &y) == 1);

    q_destroy(q);
    printf("q_peek test passed.\n");
}

void test_q_enqueue_macro_constants() 
{
    Queue *q = q_init(4, sizeof(int));
    assert(q);

    // Test with integer constants
    q_enqueue(q, int, 5);
    q_enqueue(q, int, -123);
    q_enqueue(q, int, 0);

    int val;

    assert(q_dequeue(q, &val) == 0); assert(val == 5);
    assert(q_dequeue(q, &val) == 0); assert(val == -123);
    assert(q_dequeue(q, &val) == 0); assert(val == 0);

    q_destroy(q);

    // Test with double constants
    q = q_init(4, sizeof(double));
    assert(q);

    q_enqueue(q, double, 3.1415);
    q_enqueue(q, double, -2.71);

    double dval;

    assert(q_dequeue(q, &dval) == 0); assert(dval == 3.1415);
    assert(q_dequeue(q, &dval) == 0); assert(dval == -2.71);

    q_destroy(q);

    // Test with char constants
    q = q_init(4, sizeof(char));
    assert(q);

    q_enqueue(q, char, 'A');
    q_enqueue(q, char, 'z');

    char cval;

    assert(q_dequeue(q, &cval) == 0); assert(cval == 'A');
    assert(q_dequeue(q, &cval) == 0); assert(cval == 'z');

    q_destroy(q);

    printf("q_enqueue macro works correctly with int, double, and char constants.\n");
}

void test_queue_supplement_functions() 
{
    Queue *q = q_init(4, sizeof(int));
    assert(q);

    // Initially empty
    assert(q_size(q) == 0);
    assert(q_capacity(q) == 4);
    assert(q_empty(q) == 1);
    assert(q_full(q) == 0);

    // Enqueue 4 elements (fill the queue)
    for (int i = 0; i < 4; i++) {
        assert(q_enqueue(q, int, i) == 0);
        assert(q_size(q) == (size_t)(i + 1));
        assert(q_empty(q) == 0);
    }

    assert(q_full(q) == 1);  // Should be full now

    // Clear the queue
    assert(q_clear(q) == 0);
    assert(q_size(q) == 0);
    assert(q_empty(q) == 1);
    assert(q_full(q) == 0);

    // After clearing, we should be able to enqueue again
    assert(q_enqueue(q, int, 42) == 0);
    assert(q_size(q) == 1);
    assert(q_empty(q) == 0);
    assert(q_full(q) == 0);

    q_destroy(q);
    printf("Supplementary queue functions tested successfully.\n");
}

typedef struct 
{
    int id;
    char grade;
} Student;

void test_queue_with_struct_q__enqueue() 
{
    Queue *q = q_init(4, sizeof(Student));
    assert(q);

    Student s1 = {101, 'A'};
    Student s2 = {102, 'B'};

    // Enqueue using q__enqueue directly (not the macro)
    assert(q__enqueue(q, &s1) == 0);
    assert(q__enqueue(q, &s2) == 0);

    Student out;

    // Dequeue and check contents
    assert(q_dequeue(q, &out) == 0);
    assert(out.id == 101 && out.grade == 'A');

    assert(q_dequeue(q, &out) == 0);
    assert(out.id == 102 && out.grade == 'B');

    // Should be empty now
    assert(q_size(q) == 0);
    assert(q_empty(q) == 1);

    q_destroy(q);
    printf(" Struct enqueue/dequeue with q__enqueue passed.\n");
}

void test_queue_invalid_inputs() 
{
    Queue *q = q_init(4, sizeof(int));
    assert(q);

    int x = 42;
    int out = 0;

    // ==== NULL queue pointer ====
    assert(q__enqueue(NULL, &x) == -1);
    assert(q_dequeue(NULL, &out) == -1);
    assert(q_peek(NULL, &out) == -1);
    assert(q_clear(NULL) == -1);
    assert(q_size(NULL) == 0);
    assert(q_capacity(NULL) == 0);
    assert(q_empty(NULL) == 1);
    assert(q_full(NULL) == 0);

    // ==== NULL data pointer ====
    assert(q__enqueue(q, NULL) == -1);
    assert(q_dequeue(q, NULL) == -1);
    assert(q_peek(q, NULL) == -1);

    // ==== Dequeue from empty queue ====
    assert(q_dequeue(q, &out) == 1);  // returns 1 to indicate empty
    assert(q_peek(q, &out) == 1);     // peek from empty also returns 1

    q_destroy(q);
    printf("Invalid input and empty-queue behavior tested successfully.\n");
}

void test_queue_repeated_enqueue_dequeue_cycles() 
{
    Queue *q = q_init(4, sizeof(int));
    assert(q);

    const int cycles = 100000;

    for (int i = 0; i < cycles; ++i) {
        // Enqueue one item
        assert(q_enqueue(q, int, i) == 0);

        // Dequeue the same item immediately
        int val = -1;
        assert(q_dequeue(q, &val) == 0);
        assert(val == i);

        // The queue should remain empty after each cycle
        assert(q_empty(q) == 1);
    }

    q_destroy(q);
    printf("Repeated enqueue-dequeue cycle test passed (%d cycles).\n", cycles);
}

void test_queue_randomized_operations() 
{
    const size_t N = 1000000000;  // 1 billion
    Queue *q = q_init(32, sizeof(int));
    assert(q);

    srand((unsigned)time(NULL));  // Seed randomness

    size_t total_enq = 0, total_deq = 0;
    int counter = 0;  // Increasing value to enqueue
    int val = -1;

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    for (size_t i = 0; i < N; ++i) 
    {
        int action = rand() % 2;

        if (action == 0) { // Try enqueue
            if (!q_full(q)) {
                assert(q_enqueue(q, int, counter) == 0);
                counter++;
                total_enq++;
            }
        } else { // Try dequeue
            if (!q_empty(q)) {
                assert(q_dequeue(q, &val) == 0);
                total_deq++;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &t2);
    long ms = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_nsec - t1.tv_nsec) / 1000000;

    printf("Randomized test completed: %zu enqueues, %zu dequeues\n", total_enq, total_deq);
    printf("Total time: %ld ms (%.2f sec)\n", ms, ms / 1000.0);

    q_destroy(q);
}


void test_queue_stress() 
{
    const size_t N = 1000000000;  // 1 billion
    Queue *q = q_init(32, sizeof(int));
    assert(q);

    struct timespec t1, t2, t3;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    for (size_t i = 0; i < N; i++)
        assert(q_enqueue(q, int, i) == 0);

    clock_gettime(CLOCK_MONOTONIC, &t2);

    for (size_t i = 0; i < N; i++) {
        int val;
        assert(q_dequeue(q, &val) == 0);
        assert(val == (int)i);
    }

    clock_gettime(CLOCK_MONOTONIC, &t3);

    long ms_enqueue = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_nsec - t1.tv_nsec) / 1000000;
    long ms_dequeue = (t3.tv_sec - t2.tv_sec) * 1000 + (t3.tv_nsec - t2.tv_nsec) / 1000000;

    printf("Enqueue: %ld ms (%.2f sec)\n", ms_enqueue, ms_enqueue / 1000.0);
    printf("Dequeue: %ld ms (%.2f sec)\n", ms_dequeue, ms_dequeue / 1000.0);

    q_destroy(q);
}


int main(void)
{
    test_enqueue_dequeue();
    test_queue_wraparound();
    test_queue_resize_wraparound();
    test_peek();
    test_q_enqueue_macro_constants();
    test_queue_supplement_functions();
    test_queue_with_struct_q__enqueue();
    test_queue_invalid_inputs();
    test_queue_repeated_enqueue_dequeue_cycles();
    test_queue_randomized_operations();
    test_queue_stress();

    printf("\n====================== All tests are passed! =========================\n");

    return 0;
}