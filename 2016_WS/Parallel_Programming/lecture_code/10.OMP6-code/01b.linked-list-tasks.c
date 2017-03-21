#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

#define N 10
#define NUMBER_OF_THREADS 2

struct list {
    int value;
    struct list *next;
};

// n > 0
void create_list( struct list **head, int nelems )
{
    struct list *cur;
    int i;

    // Initialize first entry of the list
    (*head) = (struct list*) malloc (sizeof(struct list)); 
    (*head)->value = rand()%100;
    // Initialize rest
    cur = (*head);
    for (i = 1; i < nelems; i++)
    {
        cur->next = (struct list*) malloc (sizeof(struct list)); 
        cur = cur->next;
        cur->value = rand()%100;
    }
    // End of list indicated by NULL pointer
    cur->next = NULL;
}

void destroy_list( struct list *head )
{
    struct list *next, *list_iter;

    next = list_iter = head;
    while (list_iter != NULL)
    {
        next = list_iter->next;
        free(list_iter);
        list_iter = next;
    }
}

int main(int argc, char *argv[])
{
    struct list *head, *list_iter;
    int n = 10;

    create_list( &head, n );

    // Traverses and "processes" a linked list (no canonical form)
    #pragma omp parallel private(list_iter)
    for ( list_iter = head; list_iter != NULL; list_iter = list_iter->next )
        #pragma omp single
        #pragma omp task
        printf( "%d ", list_iter->value );
    printf("\n");

    destroy_list( head );

    return 0;
}

