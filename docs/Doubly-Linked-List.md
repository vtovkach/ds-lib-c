# D_List — Generic Doubly Linked List in C

A dynamically allocated, generic **doubly linked list** data structure implemented in C.  
Supports efficient insertions, deletions, and access operations at both ends and arbitrary positions.

---

## Initialization & Destruction

### `D_List *d_list_init(size_t data_size);`
Initializes an empty list with elements of `data_size` bytes.

- **Returns:** Pointer to list on success, `NULL` on failure.

### `void d_list_destroy(D_List *l_ptr);`
Frees all memory, including list and its nodes.

---

## Insertion Functions

> Use structs or primitive values. Avoid heap pointers unless you manage deep copies.

### `int d_l__push_front(D_List *l_ptr, void *data);`  
Insert `data` at the front.

### `int d_l__push_back(D_List *l_ptr, void *data);`  
Insert `data` at the rear.

### `int d_l__push_at(D_List *l_ptr, void *data, size_t index);`  
Insert at `index`. Behaves like `push_front`/`push_back` when `index == 0` or `size`.

---

##  Removal Functions

Copy removed data to `dest`.

### `int d_l_pop_front(D_List *l_ptr, void *dest);`  
Remove first element.

### `int d_l_pop_back(D_List *l_ptr, void *dest);`  
Remove last element.

### `int d_l_pop_at(D_List *l_ptr, void *dest, size_t index);`  
Remove element at index.

---

##  Peek Functions

Access data without removing it.

### `int d_l_peek_front(D_List *l_ptr, void *dest);`  
Read first element.

### `int d_l_peek_back(D_List *l_ptr, void *dest);`  
Read last element.

### `int d_l_peek_at(D_List *l_ptr, void *dest, size_t index);`  
Read element at `index`. Optimized for direction.

---

##  Utility Functions

### `int d_l_empty(D_List *l_ptr);`  
Returns `1` if empty, `0` otherwise.

### `int d_l_clear(D_List *l_ptr);`  
Frees all nodes, preserves list structure.

### `int d_l_reverse(D_List *l_ptr);`  
Reverses list order.

### `size_t d_l_size(D_List *l_ptr);`  
Returns current element count.

---

## ⚠️ Return Codes

| Code | Meaning                        |
|------|--------------------------------|
| `0`  | Success                        |
| `-1` | Null pointer / malloc failure |
| `-2` | Index out of bounds           |
| `1`  | List is empty                 |

---

##  Macro Helpers (Optional)

```c
#define dl_push_front(l_ptr, type, val)  d_l__push_front(l_ptr, &(type){val})
#define dl_push_back(l_ptr, type, val)   d_l__push_back(l_ptr, &(type){val})
#define dl_push_at(l_ptr, type, val, i)  d_l__push_at(l_ptr, &(type){val}, i)
```

> ⚠️ Prefer **non-macro functions** (e.g., `d_l__push_back`) when passing structs for clarity and better debugging.

---

##  Example

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

##  Summary

- Generic, memory-safe, efficient doubly linked list
- Full support for dynamic memory operations
- Clean API for systems and embedded use
