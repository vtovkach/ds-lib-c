#include <stdio.h>

#include "tree.h"


int compare(void *left_ptr, void *right_ptr)
{
    int left = *(int *)left_ptr;
    int right = *(int *)right_ptr;

    if(left == right)
        return 0;
    else if(left > right)
        return 1; 
    else 
        return -1;
}

void print_data(void *data)
{
    if(!data)
    {
        return;
    }
    else
    {
        printf("%d ", *(int *)data);
    }
}


int main(int argc, char *argv[])
{
    AVL_Tree *tree = avl_create(sizeof(int), 1, compare);

    inorder_traversal(tree, compare);

    avl_destroy(tree);

}