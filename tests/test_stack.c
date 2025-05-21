#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "../include/stack.h"

void check_push()
{
    Stack *stack = stk_init(10, sizeof(int));
    assert(stack != NULL);

    for(int i = 0; i < 1000; i++)
        assert(stk_push(stack, int, i) == 0);

    int data = 0;
    for(int i = 999; i >= 0; i--) {
        assert(stk_pop(stack, &data) == 0);
        assert(data == i);
    }

    assert(stk_pop(stack, &data) == -1);  // empty stack
    stk_destroy(stack);
}

void test_stack_init_destroy() 
{
    Stack *stack = stk_init(5, sizeof(int));
    assert(stack != NULL);
    assert(stk_capacity(stack) == 5);
    assert(stk_size(stack) == 0);
    assert(stk_empty(stack) == true);
    stk_destroy(stack);
}

void test_stack_push_pop_peek() 
{
    Stack *stack = stk_init(2, sizeof(int));
    assert(stack != NULL);

    assert(stk_push(stack, int, 42) == 0);
    assert(stk_push(stack, int, 7) == 0);

    int peeked = 0;
    assert(peek(stack, &peeked) == 0);
    assert(peeked == 7);

    int popped = 0;
    assert(stk_pop(stack, &popped) == 0);
    assert(popped == 7);

    assert(stk_pop(stack, &popped) == 0);
    assert(popped == 42);

    assert(stk_pop(stack, &popped) == -1);  // empty
    stk_destroy(stack);
}

void test_stack_clear() 
{
    Stack *stack = stk_init(5, sizeof(int));
    assert(stack != NULL);

    for (int i = 0; i < 5; i++)
        assert(stk_push(stack, int, i) == 0);

    assert(stk_size(stack) == 5);
    assert(stk_clear(stack) == 0);
    assert(stk_size(stack) == 0);
    assert(stk_empty(stack) == true);

    int dummy = -1;
    assert(stk_pop(stack, &dummy) == -1);
    stk_destroy(stack);
}

void test_stack_reverse() 
{
    Stack *stack = stk_init(4, sizeof(int));
    assert(stack != NULL);

    for (int i = 1; i <= 4; i++)
        assert(stk_push(stack, int, i) == 0);  // stack: 4,3,2,1 (top to bottom)

    assert(stk_reverse(stack) == 0);          // stack: 1,2,3,4 (top to bottom)

    for (int i = 1; i <= 4; i++) {
        int val;
        assert(stk_pop(stack, &val) == 0);
        assert(val == i);
    }

    stk_destroy(stack);
}

void test_stack_shrink() 
{
    Stack *stack = stk_init(10, sizeof(int));
    assert(stack != NULL);

    for (int i = 0; i < 3; i++)
        assert(stk_push(stack, int, i) == 0);

    unsigned int before = stk_capacity(stack);
    assert(stk_shrink(&stack) == 0);
    unsigned int after = stk_capacity(stack);

    assert(after < before);
    assert(stk_size(stack) == 3);

    for (int i = 2; i >= 0; i--) {
        int x;
        assert(stk_pop(stack, &x) == 0);
        assert(x == i);
    }

    stk_destroy(stack);
}

void test_stack_types() 
{
    Stack *stack = stk_init(3, sizeof(double));
    assert(stack != NULL);

    assert(stk_push(stack, double, 3.1415) == 0);
    assert(stk_push(stack, double, 2.718) == 0);

    double x = 0;
    assert(stk_pop(stack, &x) == 0);
    assert(x > 2.7 && x < 2.72);

    assert(stk_pop(stack, &x) == 0);
    assert(x > 3.14 && x < 3.15);

    stk_destroy(stack);
}

void test_stack_size_capacity_empty() 
{
    Stack *stack = stk_init(5, sizeof(int));
    assert(stack != NULL);

    assert(stk_size(stack) == 0);
    assert(stk_capacity(stack) == 5);
    assert(stk_empty(stack) == true);

    assert(stk_push(stack, int, 123) == 0);
    assert(stk_size(stack) == 1);
    assert(stk_empty(stack) == false);

    stk_destroy(stack);
}

void test_pop_from_empty_stack() 
{
    Stack *stack = stk_init(5, sizeof(int));
    assert(stack != NULL);

    int sentinel = 12345;
    int result = stk_pop(stack, &sentinel);
    assert(result == -1);
    assert(sentinel == 12345);  // untouched

    stk_destroy(stack);
}

typedef struct 
{
    int id;
    char name[32];
} Person;

void test_stack_structs() 
{
    Stack *stack = stk_init(3, sizeof(Person));
    assert(stack != NULL);

    Person alice = {1, "Alice"};
    Person bob = {2, "Bob"};
    Person charlie = {3, "Charlie"};

    assert(stk__push_internal(stack, &alice) == 0);
    assert(stk__push_internal(stack, &bob) == 0);
    assert(stk__push_internal(stack, &charlie) == 0);

    Person temp;

    assert(stk_pop(stack, &temp) == 0);
    assert(temp.id == 3 && strcmp(temp.name, "Charlie") == 0);

    assert(stk_pop(stack, &temp) == 0);
    assert(temp.id == 2 && strcmp(temp.name, "Bob") == 0);

    assert(stk_pop(stack, &temp) == 0);
    assert(temp.id == 1 && strcmp(temp.name, "Alice") == 0);

    stk_destroy(stack);
}

void test_stack_stress_timed() 
{
    const size_t N = 1000000000;
    Stack *stack = stk_init(128, sizeof(int));
    assert(stack != NULL);

    clock_t start = clock();
    for (size_t i = 0; i < N; i++) {
        assert(stk_push(stack, int, i) == 0);
    }

    int val;
    for (size_t i = N - 1; i < N; i--) { // i < N to avoid unsigned wrap
        assert(stk_pop(stack, &val) == 0);
        assert(val == (int)i);
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Stress test (1B ops) completed in %.2f seconds\n", seconds);

    stk_destroy(stack);
}

void test_invalid_parameters() 
{
    Stack *stack = NULL;

    // NULL stack
    int dummy = 42;
    assert(stk_pop(NULL, &dummy) == -1);
    assert(peek(NULL, &dummy) == -1);
    assert(stk_clear(NULL) == -1);
    assert(stk_reverse(NULL) == -1);
    assert(stk_shrink(NULL) == -1);
    assert(stk_size(NULL) == 0);
    assert(stk_capacity(NULL) == 0);
    assert(stk_empty(NULL) == true);

    // NULL dest pointer
    stack = stk_init(5, sizeof(int));
    assert(stack != NULL);
    assert(stk_pop(stack, NULL) == -1);
    assert(peek(stack, NULL) == -1);

    // NULL input to push
    assert(stk__push_internal(stack, NULL) == -1);

    stk_destroy(stack);

    // Invalid init parameters
    assert(stk_init(0, sizeof(int)) == NULL);
    assert(stk_init(10, 0) == NULL);

    printf("Invalid parameter tests passed.\n");
}

int main(void) 
{
    check_push();
    test_stack_init_destroy();
    test_stack_push_pop_peek();
    test_stack_clear();
    test_stack_reverse();
    test_stack_shrink();
    test_stack_types();
    test_stack_size_capacity_empty();
    test_pop_from_empty_stack();
    test_stack_structs();
    test_stack_stress_timed();
    test_invalid_parameters();
    
    printf("All stack tests passed successfully.\n");
    return 0;
}