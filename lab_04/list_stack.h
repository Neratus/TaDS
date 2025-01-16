#ifndef LIST_STACK_H
#define LIST_STACK_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "func.h"

typedef struct Node
{
    char value;
    struct Node *next;
}Node;

typedef struct
{
    Node *head;
    size_t size;
    size_t allocated;
}list_stack_t;

typedef struct freed_adress_t
{
    char* adress;
    size_t size;
    struct freed_adress_t* next;
}freed_adress_t;


int stack_list_size(list_stack_t stack);

int stack_list_is_empty(list_stack_t stack);

list_stack_t *stack_list_init(void);

Node* create_nod(char cur);

void add_adress(Node *adress, size_t size);

int stack_list_push(list_stack_t *stack, char cur);

char stack_list_pop(list_stack_t *stack);

void free_stack(list_stack_t *stack);

void free_adress(void);

void stack_list_current(list_stack_t stack);

int check_string_stack_list(char *string, size_t str_len, size_t *size);

int polindrom_check_stack_list(void);

#endif 
