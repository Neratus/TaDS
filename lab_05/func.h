#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ERROR_STR_INPUT -1
#define ERROR_STR_SIZE -2
#define ERROR_EMPTY -3
#define ERROR_STACK_OVERFLOW -4
#define ERROR_MALLOC -5

#define OK 0

int read_line(char *str, size_t str_max, FILE *f);

#endif
