#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ds_hashtable.h"


typedef struct Node
{
    void  *value;
    void  *key;
    struct Node  *nextNode;
} Node;

typedef struct HashTable
{
    size_t          value_size;         // Size of a single data block for the value (in bytes)
    size_t          key_size;           // Size of a single data block for the key (in bytes)
    size_t          value_blocks;       // Number of blocks that make up the value
    size_t          key_blocks;         // Number of blocks that make up the key
    Node            **hash_table;       // Array with Nodes 
    unsigned int    num_elements;       // Current number of elements in the hash table 
    unsigned int    hash_table_size;    // Maximum number of elements in a hash_table 
    double          load_factor;
    hsh_func        hash_function;      // User-implemented hash function 
} HashTable;


static void destroy_linked_list(Node *head)
{
    Node *current_node = head;
    Node *temp;
    
    while(current_node)
    {
        temp = current_node->nextNode;

        //  Free dynamically allocated key and value 
        free(current_node->key);
        free(current_node->value);

        // Free the node itself 
        free(current_node);

        current_node = temp;
    }
}

static int rechain(HashTable *hash)
{
    Node **new_ht_array = (Node**)calloc(hash->hash_table_size, sizeof(Node*));
    if(!new_ht_array)
    {
        return -1;
    }
    // New doubled size is alrady assigned, to get an old size divide by 2 
    unsigned int old_size = hash->hash_table_size / 2;

    for(unsigned int i = 0; i < old_size; i++)
    {
        Node *current_node = hash->hash_table[i];

        while(current_node)
        { 
            Node *next_node = current_node->nextNode;
            
            unsigned int new_index = hash->hash_function(current_node->key, hash->hash_table_size);
            // 
            current_node->nextNode = new_ht_array[new_index];
            new_ht_array[new_index] = current_node; 

            current_node = next_node; 
        }
    } 

    free(hash->hash_table);
    hash->hash_table = new_ht_array;

    return 0;
}

__attribute__((malloc, warn_unused_result))
HashTable *ht_create(size_t key_size, size_t key_blocks, size_t value_size, size_t value_blocks, hsh_func hash_function, unsigned int hash_table_size)
{   
    if(hash_table_size == 0 || key_size == 0 || value_size == 0 || hash_function == NULL)
    {
        fprintf(stderr, "Error initializing hash table. Check your parameters!\n");
        return NULL;
    }

    HashTable *hash;
    if((hash = (HashTable *)malloc(sizeof(HashTable))) == NULL)
    {
        fprintf(stderr, "Error allocating memory.\n");
        return NULL;
    }   

    Node **hash_table;
    if((hash_table = (Node**)calloc(hash_table_size, sizeof(Node*))) == NULL)
    {
        fprintf(stderr, "Error allocating memory.\n");
        free(hash);
        return NULL;
    }
    
    // Initialize Hash attributes 
    hash->value_size            = value_size;
    hash->value_blocks          = value_blocks;
    hash->key_size              = key_size;
    hash->key_blocks            = key_blocks;
    hash->hash_table            = hash_table;
    hash->num_elements          = 0;
    hash->hash_table_size       = hash_table_size;
    hash->load_factor           = 0.0;
    hash->hash_function         = hash_function;

    return hash;
}

void ht_destroy(HashTable *hashtable)
{
    if(hashtable == NULL)
    {
        // Nothing to destroy
        return;
    }

    // Free all linked lists in each bucket 
    for(unsigned int i = 0; i < hashtable->hash_table_size; ++i)
    {
        destroy_linked_list(hashtable->hash_table[i]);
    }
    
    free(hashtable->hash_table);  // free the array of Node* pointers 
    free(hashtable);              // free the HashTable structure itself 

    return;
}

int ht__insert_internal(HashTable *hash, const void *key, const void *value)
{
    if(!hash || !key || !value)
    {
        return -1;
    }

    // If load factor > 0.75 resize and rehash hash table 
    if(hash->load_factor >= 0.75)
    {
        hash->hash_table_size = hash->hash_table_size * 2;
        if(rechain(hash) == -1) 
        {
            hash->hash_table_size /= 2;
            return -1;
        }
    }

    // Get index in a hash table 
    unsigned int index = hash->hash_function(key, hash->hash_table_size);

    // Allocate node
    Node *new_node = (Node *)malloc(sizeof(Node));
    if(!new_node)
    {
        fprintf(stderr, "Error allocating memory for node.\n");
        return -1;
    }

    // Allocate memory for key and value 
    new_node->key   = malloc(hash->key_size * hash->key_blocks);
    new_node->value = malloc(hash->value_size * hash->value_blocks);

    if(!new_node->key || !new_node->value)
    {
        fprintf(stderr, "Error allocating memory for key & value.\n");
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return -1;
    }
    
    // Copy key and value 
    memcpy(new_node->key, key, hash->key_size * hash->key_blocks);
    memcpy(new_node->value, value, hash->value_size * hash->value_blocks);

    // Insert at the beginning of the linked list 
    new_node->nextNode = hash->hash_table[index];
    hash->hash_table[index] = new_node;

    hash->num_elements++;
    hash->load_factor = (double)hash->num_elements / hash->hash_table_size;

    return 0;
}

int ht__remove_internal(HashTable *hash, const void *key)
{
    if(!hash || !key)
    {
        return -1;
    }
    
    unsigned int index = hash->hash_function(key, hash->hash_table_size);
    Node *bucket = hash->hash_table[index]; 
    
    if(!bucket)
    {
        // not found 
        return 0;
    }
    
    // check first node
    if(memcmp(key, bucket->key, hash->key_size * hash->key_blocks) == 0)
    {
        Node *temp = bucket;
        hash->hash_table[index] = bucket->nextNode;
        free(temp->key);
        free(temp->value);
        free(temp);

        hash->num_elements--;
        hash->load_factor = (double)hash->num_elements / hash->hash_table_size;
        
        return 1;
    }

    Node *prev_node = bucket;
    Node *cur_node  = bucket->nextNode; 
    while(cur_node)
    {
        if(memcmp(key, cur_node->key, hash->key_size * hash->key_blocks) == 0)
        {
            prev_node->nextNode = cur_node->nextNode;
            free(cur_node->key);
            free(cur_node->value);
            free(cur_node);

            hash->num_elements--;
            hash->load_factor = (double)hash->num_elements / hash->hash_table_size;

            return 1;
        }
        prev_node = cur_node;
        cur_node = cur_node->nextNode;
    }

    return 0;
}

void *ht__get_internal(const HashTable *hash, const void *key, size_t bytes)
{   
    // Check function's arguments 
    if(!hash || !key)
    {
        return NULL;
    }

    unsigned int index = hash->hash_function(key, hash->hash_table_size);
    Node *current_node = hash->hash_table[index];

    while(current_node)
    {
        if(memcmp(key, current_node->key, bytes) == 0)
        {
            return current_node->value; 
        }
        current_node = current_node->nextNode;
    }
    
    return NULL;
}