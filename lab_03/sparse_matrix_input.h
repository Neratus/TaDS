#ifndef SPARSE_MATX_INPUT_H
#define SPARSE_MATX_INPUT_H

#include <stdlib.h>
#include "full_matrix_input.h"

typedef struct
{
    double *A;
    int *IA;
    int *JA; 
    size_t elem_cnt;
    size_t JA_len;
}sparse_matrix_A_t;


typedef struct
{
    double *B;
    int *JB;
    int *IB; 
    size_t elem_cnt;
    size_t IB_len;
}sparse_matrix_B_t;

int input_sparse_matrix_A(full_matrix_t matrix, sparse_matrix_A_t *sparse);

int input_sparse_matrix_B(full_matrix_t matrix, sparse_matrix_B_t *sparse);

#endif
