#include <stdio.h>

#include "../include/hashtable.h"

#define STRING_SIZE 100


// Error with compound literal string input 

// I will use char datatype 
unsigned int hash_function(const void *key, unsigned int ht_size)
{
    char *ht_key = (char *)key;
    unsigned int hash = 0;

    while(*ht_key != '\0')
    {
        hash += *ht_key;
        ht_key++;    
    }

    return hash % ht_size;
}

int main(void)
{
    HashTable *hash = ht_create(sizeof(char), 1, sizeof(int), 1, hash_function, 10);
    
    ht_destroy(hash);
}