#ifndef STATIC_STACK_H
#define STATIC_STACK_H


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "func.h"

typedef struct
{
    char array[MAX_LEN];
    size_t index_cur;
}
static_stack_t;

void stack_static_current(static_stack_t stack);

int stack_static_size(static_stack_t stack);

char stack_static_pop(static_stack_t *stack);

int stack_static_push(static_stack_t *stack, char cur);

int stack_static_is_empty(static_stack_t stack);

void stack_static_copy(static_stack_t dest, static_stack_t source);

static_stack_t stack_static_init(void);

int check_string_stack_static(char *string, size_t str_len, size_t *size);

int polindrom_check_stack_static(void);

#endif 
