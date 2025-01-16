#ifndef FLOAT_DIV_H
#define FLOAT_DIV_H

#include "float.h"
#include "stdio.h"
#include <string.h>

#define ERROR_ZERO_DIVISION -3

int my_float_division(my_float_t first, my_float_t second,my_float_t *total);

void round_up(my_float_t *cur);

#endif
