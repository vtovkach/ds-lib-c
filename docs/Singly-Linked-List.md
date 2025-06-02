# List — Generic Singly Linked List in C

A lightweight, generic and resizable **singly linked list** implementation in C.  
Efficient for forward traversal, with support for dynamic insertions, deletions, and lookups.

---

##  Initialization & Destruction

### `List *list_init(size_t data_size);`
Initializes a list that holds items of `data_size` bytes.

- **Parameters:**
  - `data_size`: Size in bytes of the element type you intend to store (e.g., `sizeof(int)`).
- **Returns:** A pointer to the list on success, `NULL` on failure.

---

### `void list_destroy(List *l_ptr);`
Frees all internal memory and destroys the list.

- **Parameters:**
  - `l_ptr`: Pointer to the list to destroy.

---

##  Insertion Functions

These functions insert **copies** of data into the list.  
Data is copied using `memcpy`.

> ⚠️ **IMPORTANT:** Use **internal functions** (e.g., `l__push_back`) when inserting **structs** or complex types.  
> The macro wrappers are convenient for primitive values but not suitable for structs due to evaluation and debugging limitations.

### `int l__push_front(List *l_ptr, void *data);`  
Insert at the **front** of the list.

- `l_ptr`: Pointer to the list.
- `data`: Pointer to the data to insert.

---

### `int l__push_back(List *l_ptr, void *data);`  
Insert at the **rear** (O(1)).

- `l_ptr`: Pointer to the list.
- `data`: Pointer to the data to insert.

---

### `int l__insert_at(List *l_ptr, void *data, size_t index);`  
Insert at a specific `index`.

- `l_ptr`: Pointer to the list.
- `data`: Pointer to the data to insert.
- `index`: Position at which to insert (0-based).

---

##  Removal Functions

### `int l_pop_front(List *l_ptr, void *dest);`  
Remove and copy the first element to `dest`.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer where the removed element will be stored.

---

### `int l_pop_back(List *l_ptr, void *dest);`  
Remove and copy the last element to `dest`.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer where the removed element will be stored.

---

### `int l_pop_at(List *l_ptr, void *dest, size_t index);`  
Remove element at `index` and copy it to `dest`.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer to store the removed element.
- `index`: Index of the element to remove.

---

##  Peek Functions

### `int l_peek_front(List *l_ptr, void *dest);`  
Read the first element without removing it.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer to store the peeked element.

---

### `int l_peek_back(List *l_ptr, void *dest);`  
Read the last element without removing it.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer to store the peeked element.

---

### `int l_peek_at(List *l_ptr, void *dest, size_t index);`  
Read the element at `index`.

- `l_ptr`: Pointer to the list.
- `dest`: Pointer to store the peeked element.
- `index`: Position to access.

---

## Utility Functions

### `int l_empty(List *l_ptr);`  
Returns 1 if list is empty or null, 0 otherwise.

- `l_ptr`: Pointer to the list.

---

### `int l_clear(List *l_ptr);`  
Frees all nodes, retains list structure.

- `l_ptr`: Pointer to the list.

---

### `int l_reverse(List *l_ptr);`  
Reverses the list in-place (O(n)).

- `l_ptr`: Pointer to the list.

---

### `size_t l_size(List *l_ptr);`  
Returns number of elements in the list.

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

##  Macro Wrappers (Optional)

```c
#define l_push_front(l_ptr, type, val)  l__push_front(l_ptr, &(type){val})
#define l_push_back(l_ptr, type, val)   l__push_back(l_ptr, &(type){val})
#define l_insert_at(l_ptr, type, val, i) l__insert_at(l_ptr, &(type){val}, i)
```

>  For **struct types**, prefer calling `l__push_front`, `l__push_back`, or `l__insert_at` directly to ensure correct copying and debug behavior.

---

##  Example

```c
typedef struct {
    int id;
    float score;
} Record;

List *list = list_init(sizeof(Record));

Record r1 = {101, 9.5};
l__push_back(list, &r1);

Record out;
l_peek_front(list, &out);  // out = {101, 9.5}

list_destroy(list);
```

---

##  Summary

- Generic singly linked list with front/rear access
- Memory-safe and efficient
- Suitable for use in generic C libraries or system utilities
