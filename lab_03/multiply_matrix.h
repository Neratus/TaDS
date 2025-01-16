#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "full_matrix_input.h"
#include "sparse_matrix_input.h"

#define ERROR_WRONG_MATR_SIZE -7

int mult_matrix(full_matrix_t first, full_matrix_t second, full_matrix_t *result);

int multiply_matrix_sparse(sparse_matrix_B_t first, sparse_matrix_A_t second, sparse_matrix_B_t *result);

#endif
