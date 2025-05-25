#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "../include/ds_singly_list.h"

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

int l_pop_front(List *l_ptr, void *dest)
{
    if(!l_ptr || !dest)
        return -1; 

    if(l_ptr->num_elements == 0)   
        return 1; // Indicate list is empty 

    memcpy(dest, l_ptr->front->data, l_ptr->data_size);   
    
    Node *temp = l_ptr->front;

    l_ptr->front = temp->nextptr;

    free(temp->data);
    free(temp);

    l_ptr->num_elements--;

    if(l_ptr->num_elements == 0)
        l_ptr->rear = NULL;

    return 0;
}

int l_pop_back(List *l_ptr, void *dest)
{
    if(!l_ptr || !dest)
        return -1;

    if(l_ptr->num_elements == 0)
        return 1; // Indicate list is empty

    if(l_ptr->num_elements == 1)
    {
        return l_pop_front(l_ptr, dest);
    }

    Node *cur_node = l_ptr->front;
    while(cur_node->nextptr->nextptr != NULL)
    {
        cur_node = cur_node->nextptr;
    }

    memcpy(dest, cur_node->nextptr->data, l_ptr->data_size);

    free(cur_node->nextptr->data);
    free(cur_node->nextptr);

    cur_node->nextptr = NULL;
    l_ptr->rear = cur_node;

    l_ptr->num_elements--;

    return 0;
}

int l_pop_at(List *l_ptr, void *dest, size_t index)
{
    if(!l_ptr)
        return -1; 
    
    if(l_ptr->num_elements == 0)
        return 1; // Indicate empty list 

    if(index  >= l_ptr->num_elements)
        return -2; // Index is out of bounds 
    
    if(index == l_ptr->num_elements - 1)
        return l_pop_back(l_ptr, dest);

    if(index == 0)
        return l_pop_front(l_ptr, dest);

    Node *cur_node = l_ptr->front;
    Node *prev_node = NULL;
    size_t count = 0;
    while(count++ < index)
    {
        prev_node = cur_node;
        cur_node = cur_node->nextptr;
    }

    memcpy(dest, cur_node->data, l_ptr->data_size);

    prev_node->nextptr = cur_node->nextptr;

    free(cur_node->data);
    free(cur_node);

    l_ptr->num_elements--;

    return 0;
}

int l_peek_front(List *l_ptr, void *dest)
{
    if(!l_ptr || !dest)
        return -1;
    
    if(l_ptr->num_elements == 0)
        return 1; // List is empty

    memcpy(dest, l_ptr->front->data, l_ptr->data_size);

    return 0;
}

int l_peek_back(List *l_ptr, void *dest)
{
    if(!l_ptr || !dest)
        return -1;
    
    if(l_ptr->num_elements == 0)
        return 1; // List is empty 

    memcpy(dest, l_ptr->rear->data, l_ptr->data_size);

    return 0;
}

int l_peek_at(List *l_ptr, void *dest, size_t index)
{
    if(!l_ptr || !dest)
        return -1;

    if(l_ptr->num_elements == 0)
        return 1; // List is empty

    if(index >= l_ptr->num_elements)
        return -2; // Index is out of bounds 

    if(index == 0)
        return l_peek_front(l_ptr, dest);

    if(index == l_ptr->num_elements - 1)
        return l_peek_back(l_ptr, dest);

    size_t count = 0;
    Node *cur_node = l_ptr->front;
    while(count++ < index)
    {
        cur_node = cur_node->nextptr;
    }

    memcpy(dest, cur_node->data, l_ptr->data_size);

    return 0;
}

int l__insert_at(List *l_ptr, void *data, size_t index)
{
    if(!l_ptr || !data)
        return -1;  
    
    if(index  > l_ptr->num_elements)
        return -2; // Index out of bounds 

    if(index == l_ptr->num_elements)
        return l__push_back(l_ptr, data);

    if(index == 0)
        return l__push_front(l_ptr, data); 
    
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
    new_node->nextptr = NULL;

    Node *cur_node = l_ptr->front;
    Node *prev_node = NULL;
    size_t i = 0;
    while(i++ < index)
    {
        prev_node = cur_node;
        cur_node = cur_node->nextptr;
    }

    prev_node->nextptr = new_node;
    new_node->nextptr = cur_node;

    l_ptr->num_elements++;

    return 0;
}

int l_empty(List *l_ptr)
{
    return (!l_ptr || l_ptr->num_elements == 0) ? 1 : 0;
}

int l_clear(List *l_ptr)
{
    if(!l_ptr)
        return -1; 

    if(l_ptr->num_elements == 0)
        return 1;

    Node *cur_node = l_ptr->front;
    Node *next = NULL;
    while(cur_node)
    {
        next = cur_node->nextptr;

        free(cur_node->data);
        free(cur_node);

        cur_node = next;
    }

    l_ptr->front = NULL;
    l_ptr->rear = NULL;
    l_ptr->num_elements = 0;

    return 0;
}

// test this one 
int l_reverse(List *l_ptr)
{
    if(!l_ptr)
        return -1;
    
    if(l_ptr->num_elements == 0)
        return 1; // List is empty 

    Node *prev = NULL;
    Node *cur  = l_ptr->front;
    Node *next = NULL;
    while(cur != NULL)
    {
        next = cur->nextptr;
        cur->nextptr = prev; 
        prev = cur;
        cur = next; 
    }

    Node *temp = l_ptr->front;
    l_ptr->front = l_ptr->rear;
    l_ptr->rear = temp;

    return 0;
}

size_t l_size(List *l_ptr)
{
    return (!l_ptr || l_ptr->num_elements == 0) ? 0 : l_ptr->num_elements;
}