#include <stdio.h>
#include <assert.h>

#include "../include/ds_hashtable.h"

#define STRING_SIZE 100

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

struct ComplexKey { int x; char y[3]; };
struct Payload { double val; char note; };

unsigned int complex_key_hash(const void *key, unsigned int ht_size)
{
    const struct ComplexKey *ckey = (const struct ComplexKey *)key;
    unsigned int hash = 0;

    // Hash the integer part
    hash += (unsigned int)(ckey->x);

    // Hash the character array part (3 characters + null terminator just in case)
    for (int i = 0; i < 3; ++i)
    {
        hash += (unsigned char)(ckey->y[i]);
    }

    return hash % ht_size;
}



// Test Insertion
void insert_test()
{
    HashTable *hash = ht_create(sizeof(int), 1, sizeof(double), 1, hash_function, 10);

    for(int i = 0; i < 1000; i++)
    {
        ht_insert(hash, i, 0.91299 + i);
    }

    printf("Print Table!!!!\n");
    for(int i = 0; i < 1020; i++)
    {
        double temp;
        void *ptr;  
        if((ptr = ht_get(hash, i, 4)) != NULL)
            temp = *(double *)ptr;
        else
            temp = -1; 

        printf("Key: %d Value: %lf\n", i, temp);
    }

    for(int i = 0; i < 1000; i++)
    {
        ht_remove(hash, i);
    }

    printf("Print Table!!!!\n");
    for(int i = 0; i < 1020; i++)
    {
        double temp;
        void *ptr;  
        if((ptr = ht_get(hash, i, 4)) != NULL)
            temp = *(double *)ptr;
        else
            temp = -1; 

        printf("Key: %d Value: %lf\n", i, temp);
    }

    ht_destroy(hash);
}

void insert_stress_test()
{
    HashTable *hash = ht_create(sizeof(int), 1, sizeof(double), 1, hash_function, 10);

    for(int i = 0; i < 1000000; i++)
    {
        ht_insert(hash, i, 0.91299 + i);
    }

    for(int i = 0; i < 1000000; i++)
    {
        ht_remove(hash, i);
    }

    ht_destroy(hash);
}

void collision_test()
{
    HashTable *hash = ht_create(sizeof(int), 1, sizeof(int), 1, hash_function, 10);

    int val1 = 42, val2 = 84;
    ht_insert(hash, 1, val1);
    ht_insert(hash, 2, val2);

    assert(*(int *)ht_get(hash, 1, sizeof(int)) == val1);
    assert(*(int *)ht_get(hash, 2, sizeof(int)) == val2);

    ht_destroy(hash);
}

void overwrite_test()
{
    HashTable *hash = ht_create(sizeof(int), 1, sizeof(double), 1, hash_function, 10);

    int key = 123;
    ht_insert(hash, key, 3.14);
    ht_insert(hash, key, 6.28); // overwrite

    double result = *(double *)ht_get(hash, key, sizeof(4));
    assert(result == 6.28);

    ht_destroy(hash);
}

void missing_key_test()
{
    HashTable *hash = ht_create(sizeof(int), 1, sizeof(double), 1, hash_function, 10);

    assert(ht_get(hash, 9999, sizeof(int)) == NULL);
    assert(ht_remove(hash, 9999) == 0); // Assume 0 means not found

    ht_destroy(hash);
}

void size_alignment_test()
{
    struct ComplexKey { int x; char y[3]; };
    struct Payload { double val; char note; };

    HashTable *hash = ht_create(sizeof(struct ComplexKey), 1, sizeof(struct Payload), 1, complex_key_hash, 10);

    struct ComplexKey key = {42, "hi"};
    struct Payload val = {9.81, 'A'};

    ht__insert_internal(hash, &key, &val);

    struct Payload *out = ht__get_internal(hash, &key, sizeof(struct ComplexKey));
    assert(out && out->val == 9.81 && out->note == 'A');

    ht_destroy(hash);
}

void resize_check_test()
{
    HashTable *hash = ht_create(sizeof(int), 1, sizeof(int), 1, hash_function, 2);

    for(int i = 0; i < 1000; ++i)
        ht_insert(hash, i, i * 2);

    for(int i = 0; i < 1000; ++i)
        assert(*(int *)ht_get(hash, i, sizeof(int)) == i * 2);

    ht_destroy(hash);
}

int main(void)
{

    insert_test();
    insert_stress_test();
    collision_test();
    overwrite_test();
    missing_key_test();
    size_alignment_test();

    resize_check_test();

    printf("All cases are passed!\n");
    return 0; 
}