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

int l_peek_front(D_List *l_ptr, void *dest);

int l_peek_back(D_List *l_ptr, void *dest);

int l_peek_at(D_List *l_ptr, void *dest, size_t index);

int l_empty(D_List *l_ptr);

int l_clear(D_List *l_ptr);

int l_reverse(D_List *l_ptr);

size_t l_size(D_List *l_ptr);


#endif 