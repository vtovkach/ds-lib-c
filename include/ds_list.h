#ifndef _DS_LIST_H
#define _DS_LIST_H

#include <stddef.h>

typedef struct List List; 


List *list_init(size_t data_size);

void list_destroy(List *l_ptr);

int l__push_front(List *l_ptr, void *data);

int l__push_back(List *l_ptr, void *data);

int l_pop_front(List *l_ptr, void *dest);

int l_pop_back(List *l_ptr, void *dest);

int l_remove_at(List *l_ptr, size_t index);

int l_peek_at(List *l_ptr, void *dest, size_t index);

int l_peek_front(List *l_ptr, void *dest);

int l_peek_back(List *l_ptr, void *dest);

int l__insert_at(List *l_ptr, void *data, size_t index);

int l_empty(List *l_ptr);

int l_clear(List *l_ptr);

int l_reverse(List *l_ptr);

size_t l_size(List *l_ptr);


// =========================== Macro Wrappers =============================

#define l_push_front(l_ptr, data_type, data)        \
    l__push_front(l_ptr, &(data_type){(data)})

#define l_push_back(l_ptr, data_type, data)         \
    l__push_back(l_ptr, &(data_type){(data)})

#define l_insert_at(l_ptr, data_type, data, index)  \
    l__insert_at(l_ptr, &(data_type){(data)}, index) 

#endif 