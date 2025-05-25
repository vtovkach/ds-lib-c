#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include "../include/ds_singly_list.h"

// Test initialization and destroy on empty list
void test_init_destroy_empty() {
    List *l = list_init(sizeof(int));
    assert(l != NULL);
    assert(l_empty(l) == 1);
    assert(l_size(l) == 0);
    list_destroy(l);
}

// Test push_front, push_back, size, empty
void test_push_front_back_size_empty() {
    List *l = list_init(sizeof(int));
    int x = 10;
    assert(l__push_front(l, &x) == 0);
    assert(l_empty(l) == 0);
    assert(l_size(l) == 1);

    int front_val = 0, back_val = 0;
    assert(l_peek_front(l, &front_val) == 0);
    assert(front_val == 10);
    assert(l_peek_back(l, &back_val) == 0);
    assert(back_val == 10);

    x = 20;
    assert(l__push_back(l, &x) == 0);
    assert(l_size(l) == 2);
    assert(l_peek_front(l, &front_val) == 0 && front_val == 10);
    assert(l_peek_back(l, &back_val) == 0 && back_val == 20);

    list_destroy(l);
}

// Test peek_front, peek_back on multiple elements
void test_peek_front_back() {
    List *l = list_init(sizeof(int));
    int vals[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
        l__push_back(l, &vals[i]);

    int v = 0;
    assert(l_peek_front(l, &v) == 0 && v == 1);
    assert(l_peek_back(l, &v) == 0 && v == 3);

    list_destroy(l);
}

// Test pop_front, pop_back, pop_at
void test_pop_front_back_at() {
    List *l = list_init(sizeof(int));
    int vals[] = {5, 6, 7, 8};
    for (int i = 0; i < 4; i++)
        l__push_back(l, &vals[i]);

    int out = 0;
    assert(l_pop_front(l, &out) == 0 && out == 5);
    assert(l_size(l) == 3);

    assert(l_pop_back(l, &out) == 0 && out == 8);
    assert(l_size(l) == 2);

    // pop at index 1 (last index now is 1)
    assert(l_pop_at(l, &out, 1) == 0 && out == 7);
    assert(l_size(l) == 1);

    // pop single remaining
    assert(l_pop_at(l, &out, 0) == 0 && out == 6);
    assert(l_empty(l) == 1);

    list_destroy(l);
}

// Test insert_at in middle, beginning, and end
void test_insert_at() {
    List *l = list_init(sizeof(int));
    int a = 1, b = 3, c = 2, d = 0, e = 4;
    // insert at empty list (index 0)
    assert(l__insert_at(l, &a, 0) == 0);
    // insert at end
    assert(l__insert_at(l, &b, 1) == 0);
    // insert in middle (index 1)
    assert(l__insert_at(l, &c, 1) == 0);

    // list is now [1,2,3]
    int out_vals[3] = {0};
    for (size_t i = 0; i < 3; i++)
        l_peek_at(l, &out_vals[i], i);
    assert(out_vals[0]==1 && out_vals[1]==2 && out_vals[2]==3);

    // insert at front
    assert(l__insert_at(l, &d, 0) == 0);
    // insert at back
    assert(l__insert_at(l, &e, l_size(l)) == 0);

    // list is now [0,1,2,3,4]
    for (int i = 0; i < 5; i++) {
        int v = 0;
        l_peek_at(l, &v, i);
        assert(v == i);
    }

    list_destroy(l);
}

// Test peek_at valid and invalid
void test_peek_at() {
    List *l = list_init(sizeof(int));
    int vals[] = {9, 8, 7};
    for (int i = 0; i < 3; i++) l__push_back(l, &vals[i]);

    int v = 0;
    assert(l_peek_at(l, &v, 0) == 0 && v == 9);
    assert(l_peek_at(l, &v, 2) == 0 && v == 7);
    // invalid index
    assert(l_peek_at(l, &v, 3) == -2);

    list_destroy(l);
}

// Test pop_at error codes
void test_pop_at_invalid() {
    List *l = list_init(sizeof(int));
    int out = 0;
    // empty list pop
    assert(l_pop_at(l, &out, 0) == 1);
    int x = 1;
    l__push_back(l, &x);
    // out of bounds
    assert(l_pop_at(l, &out, 5) == -2);

    list_destroy(l);
}

// Test clear
void test_clear() {
    List *l = list_init(sizeof(int));
    int x = 42;
    l__push_back(l, &x);
    assert(l_clear(l) == 0);
    assert(l_empty(l) == 1);
    // clear again
    assert(l_clear(l) == 1);
    list_destroy(l);
}

// Test reverse on multiple, single, empty
void test_reverse() {
    List *l = list_init(sizeof(int));
    // empty
    assert(l_reverse(l) == 1);
    int vals[] = {1,2,3};
    for (int i=0;i<3;i++) l__push_back(l,&vals[i]);
    assert(l_reverse(l) == 0);
    int out_vals2[3];
    for (size_t i=0;i<3;i++) l_peek_at(l,&out_vals2[i],i);
    // should be reversed [3,2,1]
    assert(out_vals2[0]==3 && out_vals2[1]==2 && out_vals2[2]==1);

    // single element
    l_clear(l);
    int y = 5;
    l__push_back(l,&y);
    assert(l_reverse(l)==0);
    int single = 0;
    l_peek_front(l,&single);
    assert(single==5);

    list_destroy(l);
}

// Test null and invalid input handling
void test_null_and_invalid_inputs() {
    int x = 0, out = 0;
    // list_init with zero size
    assert(list_init(0) == NULL);

    // empty and size on NULL
    assert(l_empty(NULL) == 1);
    assert(l_size(NULL) == 0);

    // invalid push_front args
    List *l1 = list_init(sizeof(int));
    assert(l__push_front(NULL, &x) == -1);
    assert(l__push_front(l1, NULL) == -1);
    list_destroy(l1);

    // invalid pop_front args
    List *l2 = list_init(sizeof(int));
    assert(l_pop_front(NULL, &out) == -1);
    assert(l_pop_front(l2, NULL) == -1);
    list_destroy(l2);

    // invalid peek_front args
    List *l3 = list_init(sizeof(int));
    assert(l_peek_front(NULL, &out) == -1);
    assert(l_peek_front(l3, NULL) == -1);
    list_destroy(l3);

    // invalid insert_at args
    List *l4 = list_init(sizeof(int));
    assert(l__insert_at(NULL, &x, 0) == -1);
    assert(l__insert_at(l4, NULL, 0) == -1);
    list_destroy(l4);
}

// Test with struct data (no macros)
typedef struct Person {
    int id;
    char name[32];
} Person;

void test_with_structs() {
    List *l = list_init(sizeof(Person));
    assert(l != NULL);

    Person p1 = {1, "Alice"};
    Person p2 = {2, "Bob"};
    Person p3 = {3, "Charlie"};

    // push back three persons
    assert(l__push_back(l, &p1) == 0);
    assert(l__push_back(l, &p2) == 0);
    assert(l__push_back(l, &p3) == 0);
    assert(l_size(l) == 3);

    // peek at each and verify deep copy
    Person out;
    assert(l_peek_at(l, &out, 0) == 0);
    assert(out.id == 1 && strcmp(out.name, "Alice") == 0);
    // mutate source and ensure list copy isn't affected
    strcpy(p1.name, "Zelda");
    assert(l_peek_at(l, &out, 0) == 0);
    assert(strcmp(out.name, "Alice") == 0);

    // pop front and check
    assert(l_pop_front(l, &out) == 0);
    assert(out.id == 1 && strcmp(out.name, "Alice") == 0);
    assert(l_size(l) == 2);

    // pop at index 1 (now last)
    assert(l_pop_at(l, &out, 1) == 0);
    assert(out.id == 3 && strcmp(out.name, "Charlie") == 0);
    assert(l_size(l) == 1);

    // pop remaining
    assert(l_pop_back(l, &out) == 0);
    assert(out.id == 2 && strcmp(out.name, "Bob") == 0);
    assert(l_empty(l) == 1);

    list_destroy(l);
}

// Mass insert/delete performance test
void test_mass_insert_delete() {
    const size_t N = 100000000;
    List *l = list_init(sizeof(int));
    if (!l) {
        printf("Failed to initialize list for mass test\n");
        return;
    }
    struct timeval t_start, t_mid, t_end;
    gettimeofday(&t_start, NULL);
    for (size_t i = 0; i < N; ++i) {
        l__push_back(l, &i);
    }
    gettimeofday(&t_mid, NULL);
    for (size_t i = 0; i < N; ++i) {
        int out;
        l_pop_front(l, &out);
    }
    gettimeofday(&t_end, NULL);

    double insert_sec = (t_mid.tv_sec - t_start.tv_sec) + (t_mid.tv_usec - t_start.tv_usec)/1e6;
    double delete_sec = (t_end.tv_sec - t_mid.tv_sec) + (t_end.tv_usec - t_mid.tv_usec)/1e6;
    printf("Inserted %zu items in %.3f seconds\n", N, insert_sec);
    printf("Deleted %zu items in %.3f seconds\n", N, delete_sec);

    list_destroy(l);
}

int main() {
    test_init_destroy_empty();
    test_push_front_back_size_empty();
    test_peek_front_back();
    test_pop_front_back_at();
    test_insert_at();
    test_peek_at();
    test_pop_at_invalid();
    test_clear();
    test_reverse();
    test_null_and_invalid_inputs();
    test_with_structs();
    test_mass_insert_delete();

    printf("All tests passed!\n");
    return 0;
}