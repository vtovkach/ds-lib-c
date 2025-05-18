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

    ht_insert(hash, 'a', 44);
    ht_insert(hash, 'b', 56);
    ht_insert(hash, 'c', 100);

    int a = *(int *)ht_get(hash, 'a', 1);
    int b = *(int *)ht_get(hash, 'b', 1);
    int c = *(int *)ht_get(hash, 'c', 1);
    void *d = ht_get(hash, 't', 1);; 
    int result = -1;
    if(d)
        result = *(int *)d;

    fprintf(stdout, "%d\n", a);
    fprintf(stdout, "%d\n", b);
    fprintf(stdout, "%d\n", c);
    fprintf(stdout, "%d\n", result);


    ht_destroy(hash);
}