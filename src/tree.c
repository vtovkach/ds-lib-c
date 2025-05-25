#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/ds_tree.h"

typedef struct Node
{
    struct Node    *left;        // Pointer to first child 
    struct Node    *right;       // Pointer to second child 
    void           *data;        // Generic pointer to the data stored in this node
    int             height;         
} Node;

typedef struct AVL_Tree
{
    Node            *root;              //
    unsigned int     num_elements;      // Keeps how many elements are in the tree  
    Compare_Func     compare;           // User-defined compare function 

    size_t           data_size;
    size_t           data_blocks; 

} AVL_Tree;


#define max(a, b) ((a) > (b)) ? (a) : (b)

// ======================= Helper Functions ==========================

static int get_height(Node *node)
{
    return node ? node->height : 0; 
}

static int get_balance(Node *node)
{
    if(!node)
    {
        return 0;
    }
    else
    {
        return get_height(node->left) - get_height(node->right);
    }
}

// Frees all nodes in the tree
// Each node owns dynamically allocated `data`
static void free_nodes(Node *root)
{
    // Base case: nothing to free 
    if(root == NULL)
    {
        return;
    }

    // Recursively free left and right subtrees
    free_nodes(root->left);
    free_nodes(root->right);

    // Free node's data and the node itself
    free(root->data);
    free(root);
    
    return; 
}

// ========================== Create and Destroy AVL Tree ==================================

AVL_Tree *avl_create(size_t data_size, size_t data_blocks, Compare_Func compare_func)
{
    // Validate input parameters
    if(data_size == 0 || data_blocks == 0 || !compare_func)
    {
        fprintf(stderr, "Error creating avl tree. Check inserted parameters.\n");
        return NULL;
    }

    // Allocate memory for AVL tree structure
    AVL_Tree *avl_tree = malloc(sizeof(AVL_Tree));
    if(!avl_tree)
    {
        fprintf(stderr, "AVL creation failed: memory allocation error.\n");
        return NULL;
    }   

    // Initialize tree fields
    avl_tree->root = NULL;
    avl_tree->num_elements = 0;
    avl_tree->data_size = data_size;
    avl_tree->data_blocks = data_blocks;
    avl_tree->compare = compare_func;

    return avl_tree;
}

void avl_destroy(AVL_Tree *tree)
{
    free_nodes(tree->root);

    free(tree);
}


// ================================= Helper Functions for Insertion ============================================

static Node *right_rotate(Node *node)
{
    Node *root = node->left;
    node->left = root->right;
    root->right = node;

    node->height = 1 + (max(get_height(node->left), get_height(node->right)));
    root->height = 1 + (max(get_height(root->left), get_height(root->right)));

    return root;
}

static Node *left_rotate(Node *node)
{
    Node *root = node->right;
    node->right = root->left;
    root->left = node;

    node->height = 1 + (max(get_height(node->left), get_height(node->right)));
    root->height = 1 + (max(get_height(root->left), get_height(root->right)));

    return root;
}

static Node* rebalance(Node *node, void *key, Compare_Func compare)
{
    int balance_factor = get_balance(node);

    if(balance_factor < -1)
    {
        // right heavey 
        if(compare(key, node->right->data) > 0)
        {
            return left_rotate(node);
        }
        else
        {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
    }
    else if(balance_factor > 1) 
    {
        // left heavy 
        if(compare(key, node->left->data) < 0)
        {
            return right_rotate(node);
        }
        else
        {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    }

    return node;
}

static Node* insert_node(Node *node, Node *new_node, Compare_Func compare)
{
    if(!node)
    {
        return new_node;
    }
    else if(compare(new_node->data, node->data) >= 0)
    {
        node->right = insert_node(node->right, new_node, compare);
    }
    else
    {
        node->left = insert_node(node->left, new_node, compare);
    }

    // Update height 
    node->height = 1 + (max(get_height(node->right), get_height(node->left)));

    // Rebalance if needed 
    node = rebalance(node, new_node->data, compare);
    
    return node;
}

// =================================== Insert Implementation ====================================

__attribute__((visibility("hidden")))
int avl__insert_internal(AVL_Tree *tree, void *data)
{
    if(!data || !tree)
    {   
        return -1;
    }

    // Initialize new node 
    Node *new_node = malloc(sizeof(Node));
    if(!new_node)
    {
        fprintf(stderr, "Erorr allocating memory for new node.\n");
        return -1;
    }

    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = malloc(tree->data_size * tree->data_blocks);
    if(!new_node->data)
    {
        fprintf(stderr, "Erorr allocating memory for new node.\n");
        free(new_node);
        return -1;
    }
    memcpy(new_node->data, data, tree->data_size * tree->data_blocks);
    new_node->height = 0;

    tree->root = insert_node(tree->root, new_node, tree->compare);
    
    tree->num_elements++;

    return 0;
}

// =============================== Search Node ==============================
static Node *search_node(Node *root, void *key, Compare_Func compare)
{
    // Case: key is not found 
    if(!root) return NULL;

    // Case: key is successfuly found 
    if(compare(key, root->data) == 0)
    {
        return root;
    }
    else if(compare(key, root->data) < 0)
    {
        return search_node(root->left, key, compare);
    }
    else
    {
        return search_node(root->right, key, compare);
    }
}

__attribute__((visibility("hidden")))
void *avl__search_internal(AVL_Tree *tree, void *key)
{
    if(!tree || !key)
    {
        return NULL;
    }

    // Search for the node that contains the key 
    Node *result = search_node(tree->root, key, tree->compare);

    if(!result) return NULL;

    // return void pointer to data  
    return result->data;
}

// ============================= Remove Node ==============================


static Node *remove_node(Node *root, void *key, Compare_Func compare, size_t size)
{
    if (!root) return NULL;

    if (compare(key, root->data) < 0)
    {
        root->left = remove_node(root->left, key, compare, size);
    }
    else if (compare(key, root->data) > 0)
    {
        root->right = remove_node(root->right, key, compare, size);
    }
    else
    {
        // Node with one or no child
        if (!root->left || !root->right)
        {
            Node *temp = root->left ? root->left : root->right;
            free(root->data);
            free(root);
            return temp;
        }

        // Node with two children: find in-order successor
        Node *succ = root->right;
        while (succ->left)
            succ = succ->left;

        // Copy successor’s data to root
        memcpy(root->data, succ->data, size);

        // Delete successor
        root->right = remove_node(root->right, succ->data, compare, size);
    }

    // Update height
    root->height = 1 + (max(get_height(root->left), get_height(root->right)));
    
    // Rebalance
    return rebalance(root, key, compare);
}

__attribute__((visibility("hidden")))
int avl__remove_internal(AVL_Tree *tree, void *key)
{   
    if(!tree || !tree->root || !key)
    {
        return -1;
    }

    tree->root = remove_node(tree->root, key, tree->compare, tree->data_size * tree->data_blocks);
    
    return 0;
}

// ============================ Traversal Functions ======================================

static void inorder_traversal(Node *node, TraverseAction action)
{
    if(!node)
    {
        return;
    }

    inorder_traversal(node->left, action);

    action(node->data);
    
    inorder_traversal(node->right, action);
}

static void preorder_traversal(Node *node, TraverseAction action)
{
    if(!node) return;

    action(node->data);

    preorder_traversal(node->left, action);

    preorder_traversal(node->right, action);
}

static void postorder_traversal(Node *node, TraverseAction action)
{
    if(!node) return;
    
    postorder_traversal(node->left, action);
    postorder_traversal(node->right, action);

    action(node->data);
}

__attribute__((visibility("hidden")))
void avl__traverse_internal(AVL_Tree *tree, TraverseAction action, Traverse_Type type)
{
    if(!tree || !action)
    {
        return;
    }

    switch(type)
    {
        case TRAVERSE_INORDER:
            inorder_traversal(tree->root, action);
            break;
        case TRAVERSE_POSTORDER:
            postorder_traversal(tree->root, action);
            break;
        case TRAVERSE_PREORDER:
            preorder_traversal(tree->root, action);
            break;
        default:
            fprintf(stderr, "Wrong traversal type.\n");
            return;
    }
}

// ================================= Find Min and Find Max Functions ==========================================

static void *minimum(Node *node)
{
    if(!node->left)
    {
        return node->data;
    }
    else
    {
        return minimum(node->left);
    }
}

static void *maximum(Node *node)
{
    if(!node->right)
    {
        return node->data;
    }
    else
    {
        return maximum(node->right);
    }
}

void *find_max(AVL_Tree *tree)
{
    if(!tree || !tree->root)
    {
        return NULL;
    }

    return maximum(tree->root);
}

void *find_min(AVL_Tree *tree)
{
    if(!tree || !tree->root)
    {
        return NULL;
    }

    return minimum(tree->root);
}