#ifndef _DS_VECTOR_H
#define _DS_VECTOR_H

#include <stddef.h>

typedef struct Vector Vector; 

Vector *vec_create(size_t capacity, size_t data_size);

void vec_destroy(Vector *vec);

int v_push_back(Vector *vec);

int v_pop_back(Vector *vec, void *dest);

int v_get(Vector *vec, void *dest, size_t index);

int v_set(Vector *vec, void *data, size_t index);

int v_insert(Vector *vec, void *data, size_t index);

int v_erase(Vector *vec, size_t index);

size_t v_size(Vector *vec);

size_t v_capacity(Vector *vec);

int v_empty(Vector *vec);

int v_clear(Vector *vec);

int v_resize(Vector *vec, size_t new_size);

int v_sort(Vector *vec, void (*cmp)(const void *, const void*));

#endif
