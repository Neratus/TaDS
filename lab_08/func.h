#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 200

#define OK 0
#define ERROR_STR_INPUT -1
#define ERROR_STR_SIZE -2

int read_line(char *str, size_t str_max, FILE *f);

#endif
