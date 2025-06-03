# Vector Library Documentation

A dynamically resizable, generic vector implementation in C.

## Overview
The `Vector` is a generic dynamic array capable of storing any data type. It supports insertion, deletion, access, resizing, and sorting operations. Internally, it uses a contiguous block of memory with automatic resizing.

---

## Initialization & Cleanup

### `Vector *vec_create(size_t capacity, size_t data_size);`
Initializes a new vector.
- **Inputs:**
  - `capacity`: Initial number of elements it can hold.
  - `data_size`: Size in bytes of each element.
- **Returns:** Pointer to the new vector or `NULL` on failure.

### `void vec_destroy(Vector *vec);`
Frees all allocated memory.
- **Input:**
  - `vec`: Pointer to the vector.

---

## Element Manipulation

### `int v_push_back(Vector *vec, void *data);`
Appends an element to the end.
- **Inputs:**
  - `vec`: Pointer to the vector.
  - `data`: Pointer to the data to insert.
- **Returns:** `0` on success, `-1` for invalid input, `-2` on allocation failure.

### `int v_pop_back(Vector *vec);`
Removes the last element.
- **Input:**
  - `vec`: Pointer to the vector.
- **Returns:** `0` on success, `1` if empty, `-1` for invalid input.

### `int v_top(Vector *vec, void *dest);`
Copies the last element into `dest`.
- **Inputs:**
  - `vec`: Pointer to the vector.
  - `dest`: Pointer to the destination buffer.
- **Returns:** `0` on success, `1` if empty, `-1` for invalid input.

---

## Indexed Access & Modification

### `int v_get(Vector *vec, void *dest, size_t index);`
Gets the value at `index`.
- **Inputs:**
  - `vec`: Pointer to the vector.
  - `dest`: Pointer to buffer to store the retrieved value.
  - `index`: Index of the element.
- **Returns:** `0` on success, `-1` for invalid input, `-2` for out-of-bounds.

### `int v_set(Vector *vec, void *data, size_t index);`
Sets the value at `index`.
- **Inputs:**
  - `vec`: Pointer to the vector.
  - `data`: Pointer to the new value.
  - `index`: Index to update.
- **Returns:** `0` on success, `-1` for invalid input, `-2` for out-of-bounds.

---

## Insertions & Deletions

### `int v_insert(Vector *vec, void *data, size_t index);`
Inserts `data` at `index`.
- **Inputs:**
  - `vec`: Pointer to the vector.
  - `data`: Pointer to data to insert.
  - `index`: Insertion position (0 ≤ index ≤ size).
- **Returns:** `0` on success, `-1` for invalid input, `-2` for out-of-bounds or memory failure.

### `int v_erase(Vector *vec, size_t index);`
Removes the element at `index`.
- **Inputs:**
  - `vec`: Pointer to the vector.
  - `index`: Index of the element to erase.
- **Returns:** `0` on success, `-1` for invalid input, `-2` for out-of-bounds.

---

## Properties

### `size_t v_size(Vector *vec);`
Returns the current number of elements.
- **Input:**
  - `vec`: Pointer to the vector.

### `size_t v_capacity(Vector *vec);`
Returns the maximum number of elements it can hold without resizing.
- **Input:**
  - `vec`: Pointer to the vector.

### `int v_empty(Vector *vec);`
Checks if the vector is empty.
- **Input:**
  - `vec`: Pointer to the vector.
- **Returns:** `1` if empty or NULL, `0` otherwise.

---

## Memory Management

### `int v_clear(Vector *vec);`
Clears all contents.
- **Input:**
  - `vec`: Pointer to the vector.
- **Returns:** `0` on success, `-1` on invalid input.

### `int v_resize(Vector *vec, size_t new_capacity);`
Changes capacity.
- **Inputs:**
  - `vec`: Pointer to the vector.
  - `new_capacity`: New capacity to set.
- **Returns:** `0` on success, `-1` for invalid input, `-2` on memory failure.

---

## Sorting

### `int v_sort(Vector *vec, int (*cmp)(void *a, void *b));`
Sorts the vector in-place.
- **Inputs:**
  - `vec`: Pointer to the vector.
  - `cmp`: Comparator function returning negative if `a < b`, 0 if equal, positive if `a > b`.
- **Returns:** `0` on success, `-1` for invalid input or sort failure.

---

## Notes
- All data is passed and copied by value using `memcpy`.
- Thread-safety is not guaranteed.
- Designed for general-purpose usage with emphasis on performance and correctness.

---

## Example
```c
Vector *v = vec_create(10, sizeof(int));
int val = 5;
v_push_back(v, &val);
v_pop_back(v);
vec_destroy(v);
```
