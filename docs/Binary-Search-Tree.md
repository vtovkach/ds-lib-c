# AVL Tree — Self-Balancing Binary Search Tree in C

A generic, dynamically allocated **AVL Tree** data structure in C that supports insertion, deletion, searching, and traversal with automatic balancing after each operation. Optimized for fast lookups and ordered data operations.

## Function Pointer Interfaces

### `Compare_Func`
```c
typedef int (*Compare_Func)(void *left, void *right);
```
A user-defined function to compare two data elements:
- Returns `< 0` if `left < right`
- Returns `0` if `left == right`
- Returns `> 0` if `left > right`

### `TraverseAction`
```c
typedef void (*TraverseAction)(void *data);
```
A user-defined function applied to each element during tree traversal. It accepts a pointer to the node's data.

---

---

## ⚠️ Usage Warning
> If storing **structs**, you must use the internal function wrappers (e.g., `avl__insert_internal`). Scalar values (e.g., `int`, `float`) can safely use the macros provided.

---

## Initialization & Destruction

### `AVL_Tree *avl_create(size_t data_size, size_t data_blocks, Compare_Func compare);`
Creates an empty AVL tree.

- **Parameters:**
  - `data_size`: Size of each element in bytes
  - `data_blocks`: Number of contiguous blocks to store per element (used for arrays/structs)
  - `compare`: Comparison function
- **Returns:** Pointer to AVL_Tree on success, `NULL` on failure

### `void avl_destroy(AVL_Tree *tree);`
Frees all memory used by the tree.

---

## Core Operations (Public API)

### `int tree_insert(AVL_Tree *tree, value);`
Inserts a value into the AVL tree.
- Wrapper macro around `avl__insert_internal`

### `int tree_remove(AVL_Tree *tree, value);`
Removes a value from the AVL tree.
- Wrapper macro around `avl__remove_internal`

### `void *tree_search(AVL_Tree *tree, value);`
Searches for a value in the AVL tree.
- Returns pointer to found data or `NULL`.

### `void traverse_tree(AVL_Tree *tree, TraverseAction action, Traverse_Type type);`
Traverses the tree and applies `action` on each element.

- `Traverse_Type` options:
  - `TRAVERSE_INORDER`
  - `TRAVERSE_PREORDER`
  - `TRAVERSE_POSTORDER`

---

## Additional Utilities

### `void *find_min(AVL_Tree *tree);`
Returns a pointer to the smallest element.

### `void *find_max(AVL_Tree *tree);`
Returns a pointer to the largest element.

---

## Internal Functions (Use with Structs Only)

### `int avl__insert_internal(AVL_Tree *tree, void *data);`
### `int avl__remove_internal(AVL_Tree *tree, void *key);`
### `void *avl__search_internal(AVL_Tree *tree, void *key);`
### `void avl__traverse_internal(AVL_Tree *tree, TraverseAction action, Traverse_Type type);`

---

## Notes

- The AVL tree guarantees **O(log n)** complexity for insert, delete, and search operations.
- Balancing is automatically handled after each modification.
- Fully generic via user-defined comparison and block handling.

---

