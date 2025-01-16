#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "full_matrix_input.h"
#include "sparse_matrix_input.h"

int print_matrix(char *path, full_matrix_t matrix);

void print_matrix_in_console(full_matrix_t matrix);

int print_matrix_coord(char *path, full_matrix_t matrix);

void print_matrix_coord_in_console(full_matrix_t matrix);

int print_sparse_matrix_A_standart(char*path, sparse_matrix_A_t matrix);

void print_sparse_matrix_A_standart_in_console(sparse_matrix_A_t matrix);

int print_sparse_matrix_A_coord(char*path, sparse_matrix_A_t matrix);

void print_sparse_matrix_A_coord_in_console(sparse_matrix_A_t matrix);

int print_sparse_matrix_B_standart(char*path, sparse_matrix_B_t matrix);

void print_sparse_matrix_B_standart_in_console(sparse_matrix_B_t matrix);

int print_sparse_matrix_B_coord(char*path,sparse_matrix_B_t matrix);

void print_sparse_matrix_B_coord_in_console(sparse_matrix_B_t matrix);

#endif
