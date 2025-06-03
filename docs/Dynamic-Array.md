# Vector Library Documentation

A dynamically resizable, generic vector implementation in C.

---

## Initialization & Cleanup

### `Vector *vec_create(size_t capacity, size_t data_size);`
Initializes a new vector with the specified initial `capacity` and size of each element (`data_size` in bytes).  
Returns a pointer to the new vector on success, or `NULL` on failure.

### `void vec_destroy(Vector *vec);`
Frees all memory allocated by the vector.  
Takes a pointer to the vector as input.

---

## Element Manipulation

### `int v_push_back(Vector *vec, void *data);`
Appends an element pointed to by `data` to the end of the vector `vec`.  
Returns `0` on success, `-1` for invalid input, and `-2` on memory allocation failure.

### `int v_pop_back(Vector *vec);`
Removes the last element of the vector.  
Returns `0` on success, `1` if the vector is empty, and `-1` for invalid input.

### `int v_top(Vector *vec, void *dest);`
Copies the last element of the vector into the buffer pointed to by `dest`.  
Returns `0` on success, `1` if the vector is empty, and `-1` for invalid input.

---

## Indexed Access & Modification

### `int v_get(Vector *vec, void *dest, size_t index);`
Retrieves the element at the given `index` and copies it into `dest`.  
Returns `0` on success, `-1` for invalid input, and `-2` if the index is out of bounds.

### `int v_set(Vector *vec, void *data, size_t index);`
Sets the value at the given `index` to the content pointed to by `data`.  
Returns `0` on success, `-1` for invalid input, and `-2` for out-of-bounds access.

---

## Insertions & Deletions

### `int v_insert(Vector *vec, void *data, size_t index);`
Inserts the element at the specified `index` by shifting subsequent elements.  
Returns `0` on success, `-1` for invalid input, and `-2` for out-of-bounds access or allocation failure.

### `int v_erase(Vector *vec, size_t index);`
Removes the element at the specified `index` and shifts remaining elements.  
Returns `0` on success, `-1` for invalid input, and `-2` for out-of-bounds index.

---

## Properties

### `size_t v_size(Vector *vec);`
Returns the number of elements currently stored in the vector.

### `size_t v_capacity(Vector *vec);`
Returns the current capacity of the vector before resizing is required.

### `int v_empty(Vector *vec);`
Returns `1` if the vector is `NULL` or contains no elements, otherwise returns `0`.

---

## Memory Management

### `int v_clear(Vector *vec);`
Removes all elements from the vector without deallocating the underlying buffer.  
Returns `0` on success or `-1` for invalid input.

### `int v_resize(Vector *vec, size_t new_capacity);`
Attempts to resize the vector's capacity to `new_capacity`.  
Returns `0` on success, `-1` for invalid input, and `-2` on allocation failure.

---

## Sorting

### `int v_sort(Vector *vec, int (*cmp)(void *a, void *b));`
Sorts the vector in-place using the comparator `cmp`.  
Returns `0` on success or `-1` for invalid input or failure.

---

## Example
```c
Vector *v = vec_create(10, sizeof(int));
int val = 5;
v_push_back(v, &val);
v_pop_back(v);
vec_destroy(v);
