# Stack Library Documentation

A generic, dynamically resizable stack implementation in C.

---

## Initialization & Destruction

### `Stack *stk_init(unsigned int init_size, size_t data_size);`
Creates a new stack with initial capacity `init_size` and element size `data_size` (in bytes).  
Returns a pointer to the stack on success, or `NULL` on failure.

### `void stk_destroy(Stack *stk_ptr);`
Frees all memory used by the stack.  
Takes a pointer to the stack as input.

---

## Push & Pop

### `int stk__push_internal(Stack *stk_ptr, void *data);`
Pushes an element onto the stack.  
Returns `0` on success or `-1` on error. For internal use only.

### Macro: `stk_push(stk_ptr, datatype, data)`
A type-safe macro wrapper around `stk__push_internal` using compound literals.  
Only safe for scalar types.

> ⚠️ **Warning:** For structs or complex types, use `stk__push_internal` directly. The macro `stk_push` is not safe for these types.

### `int stk_pop(Stack *stk_ptr, void *dest_ptr);`
Pops the top element into `dest_ptr`.  
Returns `0` on success or `-1` if the stack is empty or input is invalid.

### `int peek(Stack *stk_ptr, void *dest_ptr);`
Copies the top element into `dest_ptr` without removing it.  
Returns `0` on success or `-1` on error.

---

## Utilities

### `int stk_clear(Stack *stk_ptr);`
Removes all elements from the stack.  
Returns `0` on success or `-1` if input is invalid.

### `int stk_reverse(Stack *stk_ptr);`
Reverses the order of elements in the stack.  
Returns `0` on success or `-1` on failure.

### `int stk_shrink(Stack **stk_ptr);`
Shrinks the internal buffer to match the number of elements.  
Returns:  
- `0` on success  
- `1` if the stack is empty and destroyed  
- `-1` on error

---

## Properties

### `unsigned int stk_size(Stack *stk_ptr);`
Returns the number of elements in the stack.

### `unsigned int stk_capacity(Stack *stk_ptr);`
Returns the current capacity of the stack.

### `bool stk_empty(Stack *stk_ptr);`
Returns `true` if the stack is empty or `NULL`, otherwise `false`.

---

## Example
```c
Stack *s = stk_init(4, sizeof(int));
stk_push(s, int, 42);
int top;
stk_pop(s, &top);
stk_destroy(s);
