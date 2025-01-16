#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "func.h"

typedef struct Node
{
    double value;
    struct Node *next;
}Node;

typedef struct
{
    Node *head;
    Node *tail;
    size_t size;
    size_t allocated;
}list_queue_t;

typedef struct freed_adress_t
{
    Node* adress;
    char operation;
    size_t size;
    struct freed_adress_t* next;
}freed_adress_t;

int queue_list_size(list_queue_t queue);

int queue_list_is_empty(list_queue_t queue);

list_queue_t *init_list(void);

int queue_list_push(list_queue_t *queue, double cur);

double queue_list_pop(list_queue_t *queue);

void free_list(list_queue_t *queue);

void free_adress(void);

void queue_list_current(list_queue_t *queue);


#endif 
