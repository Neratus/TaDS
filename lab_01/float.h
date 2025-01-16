#ifndef FLOAT_H
#define FLOAT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MANTIS_LEN 40
#define MAX_ORD_LEN 5

#define ERROR_NUM_OVERFLOW -1 
#define ERROR_NOT_NUM -1 

typedef struct
{
    char sign;
    short mantiss[MAX_MANTIS_LEN + 2];
    size_t mantiss_len;
    int order;
}my_float_t;

int input_float(char *str,my_float_t *first);

void print_float(my_float_t my_float);

#endif
