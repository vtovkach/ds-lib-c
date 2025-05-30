#ifndef _D_DS_LIST_H
#define _D_DS_LIST_H

#include <stddef.h>

typedef struct D_List D_List; 


D_List *d_list_init(size_t data_size);

void d_list_destroy(D_List *l_ptr);

int d_l__push_front(D_List *l_ptr, void *data);

int d_l__push_back(D_List *l_ptr, void *data);

int d_l__push_at(D_List *l_ptr, void *data, size_t index);

int d_l_pop_front(D_List *l_ptr, void *dest);

int d_l_pop_back(D_List *l_ptr, void *dest);

int d_l_pop_at(D_List *l_ptr, void *dest, size_t index);

int d_l_peek_front(D_List *l_ptr, void *dest);

int d_l_peek_back(D_List *l_ptr, void *dest);

int d_l_peek_at(D_List *l_ptr, void *dest, size_t index);

int d_l_empty(D_List *l_ptr);

int d_l_clear(D_List *l_ptr);

int d_l_reverse(D_List *l_ptr);

size_t d_l_size(D_List *l_ptr);

#define dl_push_front(l_ptr, data_type, data)          \
    d_l__push_front(l_ptr, &(data_type){(data)})

#define dl_push_back(l_ptr, data_type, data)           \
    d_l__push_back(l_ptr, &(data_type){(data)})

#define dl_push_at(l_ptr, data_type, data, index)      \
    d_l__push_at(l_ptr, &(data_type){(data)}, index) 

#endif 