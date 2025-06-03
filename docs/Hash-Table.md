# Hash Table — Generic Chaining Hash Table in C

A generic, dynamically allocated **Hash Table** data structure in C that supports insertion, deletion, and retrieval of key-value pairs using chaining. Automatically resizes and rehashes when the load factor exceeds a threshold.

---

## Function Pointer Interface

### `hsh_func`
```c
typedef unsigned int (*hsh_func)(const void *key, unsigned int table_size);
```
A user-defined hash function to compute an index from a key:
- Accepts a pointer to the key and the current hash table size.
- Returns an unsigned integer index within `[0, table_size - 1]`.

---

## ⚠️ Usage Warning
> If storing **structs** or multi-block data for keys/values, use the internal function wrappers (e.g., `ht__insert_internal`). Scalar values (e.g., `int`, `float`) can safely use the macros provided.

---

## Initialization & Destruction

### `HashTable *ht_create(size_t key_size, size_t key_blocks, size_t value_size, size_t value_blocks, hsh_func hash_function, unsigned int init_size);`
Creates an empty hash table.

- **Parameters:**
  - `key_size`: Size of a single key block in bytes.
  - `key_blocks`: Number of contiguous blocks that make up the key (for arrays/structs).
  - `value_size`: Size of a single value block in bytes.
  - `value_blocks`: Number of contiguous blocks that make up the value.
  - `hash_function`: User-defined hash function.
  - `init_size`: Initial number of buckets in the table.
- **Returns:** Pointer to `HashTable` on success, `NULL` on failure.

### `void ht_destroy(HashTable *hashtable);`
Frees all memory used by the hash table, including keys, values, nodes, and the bucket array.

---

## Core Operations (Public API)

### `int ht_insert(HashTable *hashtable, key, value);`
Inserts a key-value pair into the hash table.
- Wrapper macro around `ht__insert_internal`.

### `int ht_remove(HashTable *hashtable, key);`
Removes the key (and its associated value) from the hash table.
- Wrapper macro around `ht__remove_internal`.
- Returns `1` if removed, `0` if not found, `-1` on error.

### `void *ht_get(HashTable *hashtable, key, size_t bytes_comp);`
Retrieves the value associated with `key`.
- `bytes_comp` specifies how many bytes to compare for key equality.
- Returns a pointer to the value on success, or `NULL` if not found.
- Wrapper macro around `ht__get_internal`.

---

## Internal Functions (Use with Structs Only)

### `int ht__insert_internal(HashTable *hashtable, const void *key, const void *value);`
Inserts a key-value pair by copying both key and value data.

### `int ht__remove_internal(HashTable *hashtable, const void *key);`
Removes a key-value pair by key.

### `void *ht__get_internal(const HashTable *hashtable, const void *key, size_t bytes_comp);`
Retrieves a value pointer by key comparison on `bytes_comp` bytes.

---

## Structure

- `HashTable` tracks:
  - `key_size`, `key_blocks`
  - `value_size`, `value_blocks`
  - Pointer to an array of buckets (`Node **hash_table`)
  - Number of elements (`num_elements`)
  - Current capacity (`hash_table_size`)
  - Current `load_factor` (`num_elements / hash_table_size`)
  - User-provided `hash_function`

- Each bucket is a **singly linked list** of `Node`:
  - `void *key` (dynamically allocated)
  - `void *value` (dynamically allocated)
  - `Node *nextNode`

- When `load_factor` ≥ 0.75, the table doubles its `hash_table_size` and rehashes all existing nodes.

---

## Notes

- **Chaining:** Collisions are handled by inserting new nodes at the head of the linked list for the computed bucket.
- **Resizing:** On insert, if `load_factor` ≥ 0.75, the table size doubles and rehashing reassigns nodes to new buckets.
- **Time Complexity:** Average-case **O(1)** for insertion, deletion, and retrieval; worst-case **O(n)** if many collisions occur and all keys hash to the same bucket.

---
