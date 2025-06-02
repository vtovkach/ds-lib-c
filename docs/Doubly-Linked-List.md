# D_List — Generic Doubly Linked List in C

A dynamically allocated, generic, resizable **doubly linked list** data structure implemented in C.  
Supports insertions, deletions, and access operations at both ends and arbitrary positions.

---

## Initialization & Destruction

### `D_List *d_list_init(size_t data_size);`
Initializes an empty list with elements of `data_size` bytes.

- **Parameters:**
  - `data_size`: Size in bytes of the data type to store.
- **Returns:** Pointer to list on success, `NULL` on failure.

---

### `void d_list_destroy(D_List *l_ptr);`
Frees all memory, including list and its nodes.

- **Parameters:**
  - `l_ptr`: Pointer to the list to destroy.

---

## Insertion Functions

> Use structs or primitive values. Avoid heap pointers unless you manage deep copies.

### `int d_l__push_front(D_List *l_ptr, void *data);`  
Insert `data` at the front.

- `l_ptr`: Pointer to the list.
- `data`: Pointer to the data to insert.

---

### `int d_l__push_back(D_List *l_ptr, void *data);`  
Insert `data` at the rear.

- `l_ptr`: Pointer to the list.
- `data`: Pointer to the data to insert.

---

### `int d_l__push_at(D_List *l_ptr, void *data, size_t index);`  
Insert at `index`. Behaves like `push_front`/`push_back` when `index == 0` or `size`.

- `l_ptr`: Pointer to the list.
- `data`: Pointer to the data to insert.
- `index`: Index at which to insert (0-based).

---

## Removal Functions

Copy removed data to `dest`.

### `int d_l_pop_front(D_List *l_ptr, void *dest);`  
Remove first element.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer where removed data will be copied.

---

### `int d_l_pop_back(D_List *l_ptr, void *dest);`  
Remove last element.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer where removed data will be copied.

---

### `int d_l_pop_at(D_List *l_ptr, void *dest, size_t index);`  
Remove element at index.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer where removed data will be copied.
- `index`: Index of the element to remove.

---

## Peek Functions

Access data without removing it.

### `int d_l_peek_front(D_List *l_ptr, void *dest);`  
Read first element.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer where the data will be stored.

---

### `int d_l_peek_back(D_List *l_ptr, void *dest);`  
Read last element.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer where the data will be stored.

---

### `int d_l_peek_at(D_List *l_ptr, void *dest, size_t index);`  
Read element at `index`. Optimized for direction.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer where the data will be stored.
- `index`: Index of the element to read.

---

## Utility Functions

### `int d_l_empty(D_List *l_ptr);`  
Returns `1` if empty, `0` otherwise.

- `l_ptr`: Pointer to the list.

---

### `int d_l_clear(D_List *l_ptr);`  
Frees all nodes, preserves list structure.

- `l_ptr`: Pointer to the list.

---

### `int d_l_reverse(D_List *l_ptr);`  
Reverses list order.

- `l_ptr`: Pointer to the list.

---

### `size_t d_l_size(D_List *l_ptr);`  
Returns current element count.

- `l_ptr`: Pointer to the list.

---

## ⚠️ Return Codes

| Code | Meaning                        |
|------|--------------------------------|
| `0`  | Success                        |
| `-1` | Null pointer / malloc failure |
| `-2` | Index out of bounds           |
| `1`  | List is empty                 |

---

## Macro Helpers (Optional)

```c
#define dl_push_front(l_ptr, type, val)  d_l__push_front(l_ptr, &(type){val})
#define dl_push_back(l_ptr, type, val)   d_l__push_back(l_ptr, &(type){val})
#define dl_push_at(l_ptr, type, val, i)  d_l__push_at(l_ptr, &(type){val}, i)
```

> ⚠️ Prefer **non-macro functions** (e.g., `d_l__push_back`) when passing structs for clarity and better debugging.

---

## Example

```c
typedef struct {
    int id;
    float score;
} Record;

D_List *list = d_list_init(sizeof(Record));
Record rec = {42, 3.14};

d_l__push_back(list, &rec);

Record out;
d_l_peek_front(list, &out);  // out == {42, 3.14}

d_list_destroy(list);
```

---

## Summary

- Generic, memory-safe, efficient doubly linked list
- Full support for dynamic memory operations
- Clean API for systems and embedded use
