#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "func.h"


typedef struct
{
    char *array;
    size_t index_cur;
    size_t allocated_memory;
}
dynamic_stack_t;

int stack_dynamic_size(dynamic_stack_t stack);

void stack_dynamic_current(dynamic_stack_t stack);

int stack_dynamic_allocate(dynamic_stack_t *stack);

char stack_dynamic_pop(dynamic_stack_t *stack);

int stack_dynamic_push(dynamic_stack_t *stack, char cur);

int stack_dynamic_is_empty(dynamic_stack_t stack);

dynamic_stack_t stack_dynamic_init(void);

int check_string_stack_dynamic(char *string, size_t str_len, size_t *size);

int polindrom_check_stack_dynamic(void);



#endif 
