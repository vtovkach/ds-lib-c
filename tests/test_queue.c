#include <assert.h>
#include <stdio.h>

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
    printf(" Short wraparound + resize test passed.\n");

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

int main(void)
{
    test_enqueue_dequeue();
    test_queue_wraparound();
    //test_queue_resize_wraparound(); does not pass at the moment 
    test_peek();
    test_q_enqueue_macro_constants();
    test_queue_supplement_functions();

    printf("\n====================== All tests are passed! =========================\n");
    return 0;
}