#include "print_matrix.h"

int print_matrix(char *path, full_matrix_t matrix)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
        return ERROR_FILE;
    for (size_t i = 0; i < matrix.m; i++)
        fprintf(f, "---------");
    fprintf(f,"\n");
    for (size_t i = 0; i < matrix.n; i++)
    {
        for (size_t j = 0; j < matrix.m; j++)
            fprintf(f, "|%5f|", matrix.data[i][j]);  
        fprintf(f,"\n");
        for (size_t j = 0; j < matrix.m; j++)
            fprintf(f, "---------");
        fprintf(f,"\n");
    }
    fclose(f);
    return OK;
}

void print_matrix_in_console(full_matrix_t matrix)
{
    for (size_t i = 0; i < matrix.m; i++)
        printf("---------");
    printf("\n");
    for (size_t i = 0; i < matrix.n; i++)
    {
        for (size_t j = 0; j < matrix.m; j++)
            printf("|%5f|", matrix.data[i][j]);  
        printf("\n");
        for (size_t j = 0; j < matrix.m; j++)
            printf( "---------");
        printf("\n");
    }
}

int print_matrix_coord(char *path, full_matrix_t matrix)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
        return ERROR_FILE;
    size_t count_not_null = 0;
    for (size_t i = 0; i < matrix.n; i++)
        for (size_t j = 0; j < matrix.m; j++)
            if (fabs(matrix.data[i][j]) >= EPS)
                count_not_null++;
    fprintf(f, "%zu %zu %zu\n", matrix.n, matrix.m, count_not_null);
    for (size_t i = 0; i < matrix.n; i++)
        for (size_t j = 0; j < matrix.m; j++)
            if (fabs(matrix.data[i][j]) >= EPS)
                fprintf(f, "%zu %zu %lf\n", i + 1, j + 1, matrix.data[i][j]);
    fclose(f);
    return OK;
}

void print_matrix_coord_in_console(full_matrix_t matrix)
{
    size_t count_not_null = 0;
    for (size_t i = 0; i < matrix.n; i++)
        for (size_t j = 0; j < matrix.m; j++)
            if (fabs(matrix.data[i][j]) >= EPS)
                count_not_null++;
    printf("%zu %zu %zu\n", matrix.n, matrix.m, count_not_null);
    for (size_t i = 0; i < matrix.n; i++)
        for (size_t j = 0; j < matrix.m; j++)
            if (fabs(matrix.data[i][j]) >= EPS)
                printf("%zu %zu %lf\n", i + 1, j + 1, matrix.data[i][j]);
}

int print_sparse_matrix_A_standart(char*path, sparse_matrix_A_t matrix)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
        return ERROR_FILE;

    fprintf(f, "A: ");
    for (size_t i = 0; i < matrix.elem_cnt; i++)
        fprintf(f, "%lf ", matrix.A[i]);
    fprintf(f, "\n");

    fprintf(f, "IA: ");
    for (size_t i = 0; i < matrix.elem_cnt; i++)
        fprintf(f, "%d ", matrix.IA[i]);
    fprintf(f, "\n");

    fprintf(f, "JA: ");
    for (size_t i = 0; i < matrix.JA_len; i++)
        fprintf(f, "%d ", matrix.JA[i]);
    fprintf(f, "\n");

    fclose(f);
    return OK;
}

void print_sparse_matrix_A_standart_in_console(sparse_matrix_A_t matrix)
{

    printf( "A: ");
    for (size_t i = 0; i < matrix.elem_cnt; i++)
        printf("%lf ", matrix.A[i]);
    printf("\n");

    printf("IA: ");
    for (size_t i = 0; i < matrix.elem_cnt; i++)
        printf("%d ", matrix.IA[i]);
    printf("\n");

    printf("JA: ");
    for (size_t i = 0; i < matrix.JA_len; i++)
        printf("%d ", matrix.JA[i]);
    printf("\n");

}

int print_sparse_matrix_A_coord(char*path, sparse_matrix_A_t matrix)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
        return ERROR_FILE;
    for (size_t i = 0; i < matrix.JA_len; i++)
        for (int j = matrix.JA[i]; j < matrix.JA[i + 1]; j++)
            fprintf(f, "%lf %d %zu\n", matrix.A[j], matrix.IA[j],i);
    fclose(f);
    return OK;
}

void print_sparse_matrix_A_coord_in_console(sparse_matrix_A_t matrix)
{
    for (size_t i = 0; i < matrix.JA_len; i++)
        for (int j = matrix.JA[i]; j < matrix.JA[i + 1]; j++)
            printf("%lf %d %zu\n", matrix.A[j], matrix.IA[j],i);
}

int print_sparse_matrix_B_standart(char*path, sparse_matrix_B_t matrix)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
        return ERROR_FILE;

    fprintf(f, "B: ");
    for (size_t i = 0; i < matrix.elem_cnt; i++)
        fprintf(f, "%lf ", matrix.B[i]);
    fprintf(f, "\n");

    fprintf(f, "JB: ");
    for (size_t i = 0; i < matrix.elem_cnt; i++)
        fprintf(f, "%d ",  matrix.JB[i]);
    fprintf(f, "\n");

    fprintf(f, "IB: ");
    for (size_t i = 0; i < matrix.IB_len; i++)
        fprintf(f, "%d ", matrix.IB[i]);
    fprintf(f, "\n");

    fclose(f);
    return OK;
}

void print_sparse_matrix_B_standart_in_console(sparse_matrix_B_t matrix)
{
    printf("B: ");
    for (size_t i = 0; i < matrix.elem_cnt; i++)
        printf( "%lf ", matrix.B[i]);
    printf("\n");

    printf("JB: ");
    for (size_t i = 0; i < matrix.elem_cnt; i++)
        printf("%d ",  matrix.JB[i]);
    printf("\n");

    printf("IB: ");
    for (size_t i = 0; i < matrix.IB_len; i++)
        printf("%d ", matrix.IB[i]);
    printf("\n");
}

int print_sparse_matrix_B_coord(char*path,sparse_matrix_B_t matrix)
{
    FILE *f = fopen(path, "w");
    if (f == NULL)
        return ERROR_FILE;
    for (size_t i = 0; i < matrix.IB_len; i++)
        for (int j = matrix.IB[i]; j < matrix.IB[i + 1]; j++)
            fprintf(f, "%lf %zu %d\n", matrix.B[j], i, matrix.JB[j]);
    fclose(f);
    return OK;
}

void print_sparse_matrix_B_coord_in_console(sparse_matrix_B_t matrix)
{
    for (size_t i = 0; i < matrix.IB_len; i++)
        for (int j = matrix.IB[i]; j < matrix.IB[i + 1]; j++)
            printf( "%lf %zu %d\n", matrix.B[j], i, matrix.JB[j]);
}
