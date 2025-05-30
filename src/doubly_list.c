#include <stdlib.h>
#include <string.h>

#include "../include/ds_doubly_list.h"

typedef struct Node
{
    void *data; 
    struct Node *nextptr; 
    struct Node *prevptr;     
} Node;

typedef struct D_List
{
    Node *front; 
    Node *rear; 
    size_t num_elements; 
    size_t data_size; 
} D_List;


D_List *d_list_init(size_t data_size)
{
    if(data_size == 0)
        return NULL; 
    
    D_List *new_list = malloc(sizeof(D_List));
    if(!new_list)
        return NULL; 
    
    new_list->front = NULL;
    new_list->rear = NULL;
    new_list->num_elements = 0;
    new_list->data_size = data_size; 

    return new_list; 
}

void d_list_destroy(D_List *l_ptr)
{
    if(!l_ptr)
        return;

    // Free all nodes 
    Node *cur_node = l_ptr->front;
    Node *next = NULL;
    while(cur_node != NULL)
    {
        next = cur_node->nextptr; 
        
        free(cur_node->data);
        free(cur_node);

        cur_node = next; 
    }

    // Free list itself 
    free(l_ptr);
}

int d_l__push_front(D_List *l_ptr, void *data)
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

    new_node->prevptr = NULL;
    new_node->nextptr = l_ptr->front;
    
    if(l_ptr->num_elements == 0)
    {
        l_ptr->front = new_node;
        l_ptr->rear = new_node;
        l_ptr->num_elements++;
        return 0; 
    }    
    
    l_ptr->front->prevptr = new_node;
    l_ptr->front = new_node;

    l_ptr->num_elements++;

    return 0;
}

int d_l__push_back(D_List *l_ptr, void *data)
{
    if(!l_ptr || !data)
        return -1; 

    if(l_ptr->num_elements == 0)
        return d_l__push_front(l_ptr, data);

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
    new_node->prevptr = l_ptr->rear;
    
    l_ptr->rear->nextptr = new_node;
    l_ptr->rear = new_node; 
    
    l_ptr->num_elements++;

    return 0;
}

int d_l__push_at(D_List *l_ptr, void *data, size_t index)
{
    if(!l_ptr || !data)
        return -1; 
    
    if(index > l_ptr->num_elements)
        return -2; // Index out of bounds

    if(index == 0)
        return d_l__push_front(l_ptr, data);

    if(index == l_ptr->num_elements)
        return d_l__push_back(l_ptr, data);

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
    new_node->prevptr = NULL;

    Node *cur_node = l_ptr->front;
    for(size_t i = 0; i < index; i++)
    {
        cur_node = cur_node->nextptr;
    }
    
    new_node->nextptr = cur_node;
    new_node->prevptr = cur_node->prevptr;

    if(new_node->prevptr)
        new_node->prevptr->nextptr = new_node;

    cur_node->prevptr = new_node;

    l_ptr->num_elements++;

    return 0;
}


int d_l_pop_front(D_List *l_ptr, void *dest)
{
    if(!l_ptr || !dest)
        return -1; 

    if(l_ptr->num_elements == 0)
        return 1; // List is empty

    memcpy(dest, l_ptr->front->data, l_ptr->data_size);

    if(l_ptr->num_elements == 1)
    {
        free(l_ptr->front->data);
        free(l_ptr->front);

        l_ptr->front = NULL;
        l_ptr->rear = NULL;
        l_ptr->num_elements = 0;

        return 0;
    }   

    Node *temp = l_ptr->front;

    l_ptr->front = temp->nextptr;
    l_ptr->front->prevptr = NULL;
    
    free(temp->data);
    free(temp);

    l_ptr->num_elements--; 

    return 0;
}

int d_l_pop_back(D_List *l_ptr, void *dest)
{
    if(!l_ptr || !dest)
        return -1; 

    if(l_ptr->num_elements == 0)
        return 1; 

    if(l_ptr->num_elements == 1)
        return d_l_pop_front(l_ptr, dest);

    memcpy(dest, l_ptr->rear->data, l_ptr->data_size);
    
    Node *temp = l_ptr->rear;

    l_ptr->rear = l_ptr->rear->prevptr;
    l_ptr->rear->nextptr = NULL;

    free(temp->data);
    free(temp);

    l_ptr->num_elements--;

    return 0;
}

int d_l_pop_at(D_List *l_ptr, void *dest, size_t index)
{
    if(!l_ptr || !dest)
        return -1; 
    
    if(l_ptr->num_elements == 0)
        return 1; // List is empty 

    if(index >= l_ptr->num_elements)
        return -2; // Index is out of bounds 

    if(index == 0)
        return d_l_pop_front(l_ptr, dest);
    
    if(index == l_ptr->num_elements - 1)
        return d_l_pop_back(l_ptr, dest);

    Node *cur_node = l_ptr->front;
    for(size_t i = 0; i < index; ++i)
        cur_node = cur_node->nextptr;

    memcpy(dest, cur_node->data, l_ptr->data_size);

    if(cur_node->nextptr)
        cur_node->nextptr->prevptr = cur_node->prevptr;

    if(cur_node->prevptr)
        cur_node->prevptr->nextptr = cur_node->nextptr;

    free(cur_node->data);
    free(cur_node);

    l_ptr->num_elements--;

    return 0;
}

int d_l_peek_front(D_List *l_ptr, void *dest)
{
    if(!l_ptr || !dest)
        return -1;

    if(l_ptr->num_elements == 0)
        return 1; // List is empty 

    memcpy(dest, l_ptr->front->data, l_ptr->data_size);

    return 0;
}

int d_l_peek_back(D_List *l_ptr, void *dest)
{
    if(!l_ptr || !dest)
        return -1;

    if(l_ptr->num_elements == 0)
        return 1; // List is empty 

    memcpy(dest, l_ptr->rear->data, l_ptr->data_size);

    return 0;
}

int d_l_peek_at(D_List *l_ptr, void *dest, size_t index)
{
    if(!l_ptr || !dest)
        return -1;

    if(index >= l_ptr->num_elements)
        return -2; // Index is out of bounds 


    // Determine from which end of the list to approach the data

    size_t mid_point = (l_ptr->num_elements - 1) / 2;
    Node *cur_node = NULL;
    size_t cur_index;

    if(index > mid_point)
    {   
        cur_index = l_ptr->num_elements - 1; 
        cur_node = l_ptr->rear;
        while(cur_index > index)
        {
            cur_node =cur_node->prevptr;
            cur_index--;
        }
    }
    else
    {
        cur_node = l_ptr->front;
        cur_index = 0;
        while(cur_index < index)
        {
            cur_node = cur_node->nextptr;
            cur_index++;
        }
    } 

    memcpy(dest, cur_node->data, l_ptr->data_size);

    return 0 ; 
}

int d_l_empty(D_List *l_ptr)
{
    return (!l_ptr || l_ptr->num_elements == 0) ? 1 : 0;
}

int d_l_clear(D_List *l_ptr)
{
    if(!l_ptr)
        return -1;
    
    if(l_ptr->num_elements == 0)
        return 0;

    Node *cur_node = l_ptr->front;
    while(cur_node) 
    {
        Node *next = cur_node->nextptr;
        
        free(cur_node->data);
        free(cur_node);

        cur_node = next;
    }

    l_ptr->front = NULL;
    l_ptr->rear = NULL;

    l_ptr->num_elements = 0;

    return 0;
}

int d_l_reverse(D_List *l_ptr)
{
    if(!l_ptr)
        return -1; 

    if(l_ptr->num_elements < 2)
        return 0;
    
    Node *cur_node = l_ptr->front;
    Node *next_node = NULL;
    while(cur_node)
    {
        // Update nodes
        next_node = cur_node->nextptr;
        cur_node->nextptr = cur_node->prevptr;
        cur_node->prevptr = next_node;

        // Update current node
        cur_node = next_node;
    }

    Node *temp = l_ptr->front;
    l_ptr->front = l_ptr->rear;
    l_ptr->rear = temp;

    return 0;
}

size_t d_l_size(D_List *l_ptr)
{
    return (!l_ptr) ? 0 : l_ptr->num_elements;
}