# Stack Library Documentation

A generic, dynamically resizable stack implementation in C.

---

## Initialization & Destruction

### `Stack *stk_init(unsigned int init_size, size_t data_size);`
Creates a new stack with initial capacity and element size.
- **Inputs:**
  - `init_size`: Initial number of elements stack can hold.
  - `data_size`: Size of each element in bytes.
- **Returns:** Pointer to stack or `NULL` on failure.

### `void stk_destroy(Stack *stk_ptr);`
Frees all memory used by the stack.
- **Input:**
  - `stk_ptr`: Pointer to the stack.

---

## Push & Pop

### `int stk__push_internal(Stack *stk_ptr, void *data);`
Pushes an element onto the stack. Internal use only.
- **Inputs:**
  - `stk_ptr`: Pointer to the stack.
  - `data`: Pointer to the value to be pushed.
- **Returns:** `0` on success, `-1` on error.

### Macro: `stk_push(stk_ptr, datatype, data)`
Type-safe push using a compound literal. Wraps `stk__push_internal`. Only safe for scalar types.

> ⚠️ **Warning:** When pushing structs or complex types, you must use `stk__push_internal`. The `stk_push` macro only supports scalar types via compound literals.

### `int stk_pop(Stack *stk_ptr, void *dest_ptr);`
Pops the top element into `dest_ptr`.
- **Inputs:**
  - `stk_ptr`: Pointer to the stack.
  - `dest_ptr`: Output buffer.
- **Returns:** `0` on success, `-1` if empty or invalid input.

### `int peek(Stack *stk_ptr, void *dest_ptr);`
Copies the top element without popping.
- **Inputs:**
  - `stk_ptr`: Pointer to the stack.
  - `dest_ptr`: Output buffer.
- **Returns:** `0` on success, `-1` on error.

---

## Utilities

### `int stk_clear(Stack *stk_ptr);`
Clears all elements in the stack.
- **Input:**
  - `stk_ptr`: Pointer to the stack.
- **Returns:** `0` on success, `-1` if invalid.

### `int stk_reverse(Stack *stk_ptr);`
Reverses the order of elements.
- **Input:**
  - `stk_ptr`: Pointer to the stack.
- **Returns:** `0` on success, `-1` on failure.

### `int stk_shrink(Stack **stk_ptr);`
Shrinks internal buffer to fit number of elements.
- **Input:**
  - `stk_ptr`: Double pointer to the stack.
- **Returns:**
  - `0` on success  
  - `1` if stack is empty and destroyed  
  - `-1` on error

---

## Properties

### `unsigned int stk_size(Stack *stk_ptr);`
Returns number of elements.
- **Input:**
  - `stk_ptr`: Pointer to the stack.

### `unsigned int stk_capacity(Stack *stk_ptr);`
Returns current capacity.
- **Input:**
  - `stk_ptr`: Pointer to the stack.

### `bool stk_empty(Stack *stk_ptr);`
Checks if stack is empty.
- **Input:**
  - `stk_ptr`: Pointer to the stack.
- **Returns:** `true` if empty or NULL, `false` otherwise.

---

## Example
```c
Stack *s = stk_init(4, sizeof(int));
stk_push(s, int, 42);
int top;
stk_pop(s, &top);
stk_destroy(s);
```
