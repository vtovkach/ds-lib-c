#include <stdio.h>
#include <time.h>
#include "../include/ds_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_BLOCKS 16

/* ===================== Compare Function ===================== */
int int_compare(void *left, void *right) {
    int l = *(int *)left;
    int r = *(int *)right;
    return (l > r) - (l < r);
}

/* ===================== Traverse Action ====================== */
void print_node(void *data) {
    printf("%d ", *(int *)data);
}

void collect_node(void *data) {
    static int index = 0;
    static int *arr = NULL;
    if (!arr) {
        arr = malloc(100 * sizeof(int));
    }
    arr[index++] = *(int *)data;
    if (index == 7) {
        printf("Collected: ");
        for (int i = 0; i < index; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        index = 0;
    }
}

/* ======================== Tests ============================ */
void test_insert_search_min_max() {
    AVL_Tree *tree = avl_create(sizeof(int), INIT_BLOCKS, int_compare);

    int values[] = {10, 5, 20, 3, 7, 15, 30};
    for (int i = 0; i < 7; ++i) {
        assert(tree_insert(tree, values[i]) == 0);
    }

    for (int i = 0; i < 7; ++i) {
        int *found = tree_search(tree, values[i]);
        assert(found != NULL);
        assert(*found == values[i]);
    }

    int *min = find_min(tree);
    int *max = find_max(tree);
    assert(*min == 3);
    assert(*max == 30);

    avl_destroy(tree);
}

void test_traversal() {
    AVL_Tree *tree = avl_create(sizeof(int), INIT_BLOCKS, int_compare);
    int values[] = {10, 5, 20, 3, 7, 15, 30};

    for (int i = 0; i < 7; ++i) {
        tree_insert(tree, values[i]);
    }

    printf("Inorder traversal: ");
    traverse_tree(tree, print_node, TRAVERSE_INORDER);
    printf("\n");

    printf("Preorder traversal: ");
    traverse_tree(tree, print_node, TRAVERSE_PREORDER);
    printf("\n");

    printf("Postorder traversal: ");
    traverse_tree(tree, print_node, TRAVERSE_POSTORDER);
    printf("\n");

    avl_destroy(tree);
}

void test_removal() {
    AVL_Tree *tree = avl_create(sizeof(int), INIT_BLOCKS, int_compare);
    int values[] = {10, 5, 20, 3, 7, 15, 30};
    for (int i = 0; i < 7; ++i) {
        tree_insert(tree, values[i]);
    }

    assert(tree_remove(tree, 3) == 0);   // leaf
    assert(tree_remove(tree, 20) == 0);  // node with one child
    assert(tree_remove(tree, 5) == 0);   // node with two children

    assert(tree_search(tree, 3) == NULL);
    assert(tree_search(tree, 5) == NULL);
    assert(tree_search(tree, 20) == NULL);

    assert(tree_search(tree, 10) != NULL); // still present

    avl_destroy(tree);
}

void test_duplicate_insertions_allowed() {
    AVL_Tree *tree = avl_create(sizeof(int), INIT_BLOCKS, int_compare);

    int dup = 42;
    assert(tree_insert(tree, dup) == 0);
    assert(tree_insert(tree, dup) == 0);
    assert(tree_insert(tree, dup) == 0);

    // Search should find at least one
    int *found = tree_search(tree, dup);
    assert(found != NULL);
    assert(*found == dup);

    printf("Traversal after inserting duplicates: ");
    traverse_tree(tree, print_node, TRAVERSE_INORDER);
    printf("\n");

    avl_destroy(tree);
}

/* ======================== Main ============================ */
int main() {
    test_insert_search_min_max();
    test_traversal();
    test_removal();
    test_duplicate_insertions_allowed();
    printf("All tests passed!\n");
    return 0;
}

