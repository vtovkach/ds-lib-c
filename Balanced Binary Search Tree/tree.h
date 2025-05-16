#ifndef _TREE_
#define _TREE_

#include <stdio.h>


typedef int (*Compare_Func)(void *left, void *right);
typedef void (*Print_Func)(void *data);

typedef struct AVL_Tree AVL_Tree;
typedef struct Node Node; 

AVL_Tree *avl_create(size_t data_size, size_t data_blocks, Compare_Func);

void avl_destroy(AVL_Tree *);


#define avl_insert(tree_ptr, value)  \
    tree_insert((tree_ptr), &(__typeof__(value)){(value)})




void inorder_traversal(Node *, Print_Func);
void preorder_traversal(Node *, Print_Func);
void postorder_traversal(Node *, Print_Func);

void *find_min(AVL_Tree *);
void *find_max(AVL_Tree *);

#endif