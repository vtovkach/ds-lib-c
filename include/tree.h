#ifndef _TREE_
#define _TREE_

typedef int (*Compare_Func)(void *left, void *right);
typedef void (*TraverseAction)(void *data);

typedef enum 
{
    TRAVERSE_INORDER,
    TRAVERSE_PREORDER,
    TRAVERSE_POSTORDER
} Traverse_Type;

typedef struct AVL_Tree AVL_Tree;
typedef struct Node Node; 

AVL_Tree *avl_create(size_t data_size, size_t data_blocks, Compare_Func);

void avl_destroy(AVL_Tree *);

void *find_min(AVL_Tree *);

void *find_max(AVL_Tree *);


// ==================== Internal Functions ======================

int avl__insert_internal(AVL_Tree *tree, void *data);

void *avl__search_internal(AVL_Tree *tree, void *key);

int avl__remove_internal(AVL_Tree *tree, void *key);

void avl__traverse_internal(AVL_Tree *tree, TraverseAction action, Traverse_Type type);

// ======================== Public API ============================

#define tree_insert(tree_ptr, value) \
    avl__insert_internal((tree_ptr), &(__typeof__(value)){(value)})

#define tree_remove(tree_ptr, value) \
    avl__remove_internal((tree_ptr), &(__typeof__(value)){(value)})

#define tree_search(tree_ptr, value) \
    avl__search_internal((tree_ptr), &(__typeof__(value)){(value)})

#define traverse_tree(tree_ptr, action_function, traverse_type) \
    avl__traverse_internal((tree_ptr), (action_function), (traverse_type))

#endif