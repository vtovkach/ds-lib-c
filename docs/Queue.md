# Queue Library Documentation

A generic, dynamically resizable, circular queue implementation in C.  
Supports enqueue, dequeue, peek, resizing, and property checks for general-purpose usage.

---

## Initialization & Destruction

### `Queue *q_init(size_t initial_capacity, size_t data_size);`
Initializes a new queue with the specified initial capacity and element size (in bytes).  
Returns a pointer to the new queue, or `NULL` on failure.

### `void q_destroy(Queue *q_ptr);`
Frees all memory allocated for the queue.  
Takes a pointer to the queue as input.

---

## Core Operations

### `int q__enqueue(Queue *q_ptr, void *data);`
Adds an element to the rear of the queue. Automatically resizes the buffer if full.  
Returns:
- `0` on success  
- `-1` for invalid input  
- `2` if resizing failed and the queue is full

### Macro: `q_enqueue(q_ptr, data_type, data)`
Type-safe macro wrapper for enqueueing scalar types using compound literals.  
Use `q__enqueue` directly for structs or complex types.

> ⚠️ **Warning:** Only use the macro with scalar values. Use `q__enqueue` for structs or arrays.

### `int q_dequeue(Queue *q_ptr, void *dest);`
Removes the front element and stores it in `dest`.  
Returns:
- `0` on success  
- `1` if the queue is empty  
- `-1` for invalid input

### `int q_peek(Queue *q_ptr, void *dest);`
Copies the front element into `dest` without removing it.  
Returns:
- `0` on success  
- `1` if the queue is empty  
- `-1` for invalid input

---

## Properties

### `size_t q_size(Queue *q_ptr);`
Returns the current number of elements in the queue.  
Returns `0` if `q_ptr` is `NULL`.

### `size_t q_capacity(Queue *q_ptr);`
Returns the total capacity of the queue’s buffer.  
Returns `0` if `q_ptr` is `NULL`.

### `int q_empty(Queue *q_ptr);`
Checks if the queue is empty or `NULL`.  
Returns `1` if empty, `0` otherwise.

### `int q_full(Queue *q_ptr);`
Checks if the queue is full.  
Returns `1` if full, `0` otherwise.

---

## Utilities

### `int q_clear(Queue *q_ptr);`
Resets the queue to an empty state without deallocating memory.  
Returns `0` on success or `-1` for invalid input.

---

## Example
```c
Queue *q = q_init(4, sizeof(int));
q_enqueue(q, int, 7);
q_enqueue(q, int, 11);
int val;
q_dequeue(q, &val); // val = 7
q_destroy(q);
