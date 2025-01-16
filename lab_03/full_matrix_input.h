#ifndef FULL_MATX_INPUT_H
#define FULL_MATX_INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR_FILE -1
#define ERROR_INPUT_SIZE -2
#define ERROR_INPUT_SIZE_VAL -3
#define ERROR_INPUT -4
#define ERROR_MALLOC -5
#define ERROR_INDEX -6
#define OK 0

#define EPS 1e-8

typedef struct
{
    size_t n;
    size_t m;
    double **data;
}full_matrix_t;

double **allocate_matrix(size_t n, size_t m);

int input_matrix_standart(char *path, full_matrix_t *matrix);

int input_matrix_standart_from_console(full_matrix_t *matrix);

int input_matrix_coord(char *path, full_matrix_t *matrix);

int input_matrix_coord_from_console(full_matrix_t *matrix);

#endif
