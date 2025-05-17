#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include <stddef.h>

// C23 typeof 

typedef struct HashTable HashTable;

typedef unsigned int (*hsh_func)(const void *, unsigned int);

HashTable *ht_create(size_t key_size, size_t key_blocks, size_t data_size, size_t data_blocks, hsh_func hash_func_ptr, unsigned int init_size);

void ht_destroy(HashTable *hashtable);

// ============================ Internal Functions =============================

int ht__insert_internal(HashTable *hashtable, const void *key, const void *value);

int ht__remove_internal(HashTable *hashtable, const void *key);

const void *ht__get_internal(const HashTable *hashtable, const void *key, size_t bytes_comp);

// ================================ Public API ==================================


#define ht_insert(hashtable, key, value) \
    ht__insert_internal((hashtable), &(__typeof__(key)){(key)}, &(__typeof__(value)){(value)});

#define ht_remove(hashtable, key) \
    ht__remove_internal((hashtable), &(__typeof__(key)){(key)});

#define ht_get(hashtable, key, bytes_comp)    \
    ht__get_internal((hashtable), &(__typeof__(key)){(key)}, bytes_comp);


#endif 