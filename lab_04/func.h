#ifndef FUNC_H
#define FUNC_H

#define YES 1
#define NO 0
#define MAX_LEN 10000


#define ERROR_MALLOC -1
#define ERROR_EMPTY -2
#define ERROR_EMPTY_STR -3
#define ERROR_STR_INPUT -4
#define ERROR_STR_SIZE -5
#define ERROR_STACK_OVERFLOW -6
#define OK 0

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int read_line(char *str, size_t str_max, FILE *f);

#endif 
