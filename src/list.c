#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "../include/ds_list.h"

typedef struct Node 
{
    void *data; 
    struct Node *nextptr;

} Node;

typedef struct List 
{
    Node *front;            // Pointer to the front of the list 
    Node *rear;             // Pointer to the back of the list 
    size_t num_elements;    // Current number of elements in the list 
    size_t data_size;       // Data size in bytes 

} List;

List *list_init(size_t data_size)
{
    if(data_size == 0)
        return NULL;

    List *new_list = malloc(sizeof(List));
    if(!new_list)
        return NULL;

    new_list->front = NULL;
    new_list->rear = NULL;
    new_list->num_elements = 0;
    new_list->data_size = data_size;

    return new_list;
}

void list_destroy(List *l_ptr)
{
    if(l_ptr == NULL)
        return;

    // Free every node and its data memory block
    Node *cur_node = l_ptr->front;
    while(cur_node)
    {
        Node *next_node = cur_node->nextptr;
        free(cur_node->data);
        free(cur_node);
        cur_node = next_node;
    }
    
    // Free list itself 
    free(l_ptr);
}

int l__push_front(List *l_ptr, void *data)
{
    if(!l_ptr || !data)
        return -1; 

    Node *new_node = malloc(sizeof(Node));
    if(!new_node)
        return -1;

    new_node->data = malloc(l_ptr->data_size);
    if(!new_node->data)
    {
        free(new_node);
        return -1;
    }

    // Copy data 
    memcpy(new_node->data, data, l_ptr->data_size);

    if(l_ptr->front == NULL)
    {
        l_ptr->rear = new_node;
    }

    new_node->nextptr = l_ptr->front;

    l_ptr->front = new_node;

    l_ptr->num_elements++;

    return 0;    
}

int l__push_back(List *l_ptr, void *data)
{
    if(!l_ptr || !data)
        return -1; 

    Node *new_node = malloc(sizeof(Node));
    if(!new_node)
        return -1;
    
    new_node->data = malloc(l_ptr->data_size);
    if(!new_node->data)
    {
        free(new_node);
        return -1;
    }

    memcpy(new_node->data, data, l_ptr->data_size);

    // Empty list 
    if(l_ptr->rear == NULL)
    {
        l_ptr->front = new_node;
        new_node->nextptr = NULL;
        l_ptr->rear = new_node;
    }
    else
    {
        l_ptr->rear->nextptr = new_node; 
        new_node->nextptr = NULL;
        l_ptr->rear = new_node;
    }

    l_ptr->num_elements++;

    return 0;
}