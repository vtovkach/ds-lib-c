#ifndef _TREE_
#define _TREE_

#include <stdio.h>

typedef int (*Compare_Func)(void *left, void *right);
typedef void (*TraverseAction)(void *data);

typedef struct AVL_Tree AVL_Tree;
typedef struct Node Node; 

AVL_Tree *avl_create(size_t data_size, size_t data_blocks, Compare_Func);

void avl_destroy(AVL_Tree *);


#define tree_insert(tree_ptr, value) \
    avl__insert_internal((tree_ptr), &(__typeof__(value)){(value)})

#define tree_remove(tree_ptr, value) \
    avl__remove_internal((tree_ptr), &(__typeof__(value)){(value)})

#define tree_search(tree_ptr, value) \
    avl__search_internal((tree_ptr), &(__typeof__(value)){(value)})

#define traverse_tree(tree_ptr, action_function, traverse_type)
    

void inorder_traversal(Node *, TraverseAction);
void preorder_traversal(Node *, TraverseAction);
void postorder_traversal(Node *, TraverseAction);

void *find_min(AVL_Tree *);
void *find_max(AVL_Tree *);

#endif