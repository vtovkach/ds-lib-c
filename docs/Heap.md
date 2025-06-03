# Heap — Generic Binary Heap in C

A generic, dynamically allocated **binary heap** data structure in C that supports insertion, removal of the top element, peeking at the top, and querying size. Automatically resizes when capacity is exceeded.

---

## Function Pointer Interface

### `CompareFunc`
```c
typedef int (*CompareFunc)(const void *array, int child_idx, int parent_idx);
```
A user-defined function to compare two elements in the heap array:
- `array`: Pointer to the heap's internal array.
- `child_idx`: Index of the child element.
- `parent_idx`: Index of the parent element.
- **Returns:** `1` if element at `array[child_idx]` should be placed above `array[parent_idx]` (e.g., larger in a max-heap), otherwise `0`.

---

## ⚠️ Usage Warning
> Only scalar values (e.g., `int`, `float`) can use the `heap_insert` macro safely. For **structs** or multi-block data, use the internal function `hp__insert_internal` directly.

---

## Initialization & Destruction

### `Heap *hp_init(size_t data_size, int heap_size, CompareFunc comp_func);`
Creates an empty heap.

- **Parameters:**
  - `data_size`: Size of each element in bytes.
  - `heap_size`: Initial capacity (number of elements).
  - `comp_func`: User-defined comparison function for heap order.
- **Returns:** Pointer to `Heap` on success, `NULL` on failure.

### `void hp_destroy(Heap *heap);`
Frees all memory used by the heap.

---

## Core Operations (Public API)

### `int heap_insert(Heap *heap_ptr, data_type, data);`
Inserts an element into the heap.
- Macro wrapper around `hp__insert_internal`.
- Example: `heap_insert(heap, int, 42);`

### `int hp_peek(Heap *heap, void *dest_ptr);`
Retrieves the top element without removing it.
- Copies top element into `dest_ptr`.
- Returns `0` on success, `-1` on failure (e.g., empty heap).

### `int hp_remove_top(Heap *heap);`
Removes the top element from the heap.
- Performs heapify to maintain order.
- Returns `0` on success, `-1` on failure (e.g., empty heap).

### `int hp_get_size(Heap *heap);`
Returns the current number of elements in the heap.
- Returns `-1` if `heap` is `NULL`.

---

## Structure

- `Heap` tracks:
  - `void *heaparray`: 0-indexed dynamic array of elements.
  - `int heap_size`: Current capacity (number of allocated slots).
  - `int current_index`: Next insertion index (also equals number of elements).
  - `int num_elements`: Number of elements currently in the heap.
  - `size_t data_size`: Size of each element in bytes.
  - `CompareFunc cmp_func`: User-provided comparison function.

---

## Notes

- **Heap Order:** Use `CompareFunc` to define a max-heap or min-heap.
- **Automatic Resizing:** When inserting into a full heap, capacity doubles using `realloc`.
- **Time Complexity:** `O(log n)` for insertion and removal; `O(1)` for peeking and size query.
- **Indexing:** Root is at index `0`; for node at index `i`, children are at `2*i + 1` (left) and `2*i + 2` (right).

---
