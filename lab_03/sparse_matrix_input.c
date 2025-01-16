#include "sparse_matrix_input.h"

int input_sparse_matrix_A(full_matrix_t matrix, sparse_matrix_A_t *sparse)
{
    size_t elem_cnt = 0;
    size_t JA_len = 0;
    double *a = malloc(sizeof(double) * matrix.n * matrix.m);
    if (a == NULL)
        return ERROR_MALLOC;
    int *IA = malloc(sizeof(int) * matrix.n * matrix.m);
    if (IA == NULL)
    {
        free(a);
        return ERROR_MALLOC;
    }
    int *JA = malloc(sizeof(int) * matrix.n * matrix.m);
    if (JA == NULL)
    {
        free(a);
        free(IA);
        return ERROR_MALLOC;
    }
    for (size_t j = 0; j < matrix.m; j++)
    {
        for (size_t i = 0; i < matrix.n; i++)
        {
            if (fabs(matrix.data[i][j]) > EPS)
            {
                a[elem_cnt] = matrix.data[i][j];
                IA[elem_cnt] = i;
                elem_cnt++;
            }
        }
        if (elem_cnt != 0)
        {
            JA_len++;
            JA[JA_len] = elem_cnt;
        }
    }
    JA_len++;
    JA[JA_len] = elem_cnt;
    sparse->A = a;
    sparse->IA = IA;
    sparse->JA = JA;
    sparse->elem_cnt = elem_cnt;
    sparse->JA_len = JA_len;
    return OK;
}


int input_sparse_matrix_B(full_matrix_t matrix, sparse_matrix_B_t *sparse)
{
    size_t elem_cnt = 0;
    size_t IB_len = 0;
    double *b = malloc(sizeof(double) * matrix.n * matrix.m);
    if (b == NULL)
        return ERROR_MALLOC;
    int *IB = malloc(sizeof(int) * matrix.n * matrix.m);
    if (IB == NULL)
    {
        free(b);
        return ERROR_MALLOC;
    }
    int *JB = malloc(sizeof(int) * matrix.n * matrix.m);
    if (JB == NULL)
    {
        free(b);
        free(IB);
        return ERROR_MALLOC;
    }
    for (size_t i = 0; i < matrix.n; i++)
    {
        for (size_t j = 0; j < matrix.m; j++)
        {
            if (fabs(matrix.data[i][j]) > EPS)
            {
                b[elem_cnt] = matrix.data[i][j];
                JB[elem_cnt] = j;
                elem_cnt++;
            }
        }
        if (elem_cnt != 0)
        {
            IB_len++;
            IB[IB_len] = elem_cnt;
        }
    }
    IB_len++;
    IB[IB_len] = elem_cnt;
    sparse->B = b;
    sparse->IB = IB;
    sparse->JB = JB;
    sparse->elem_cnt = elem_cnt;
    sparse->IB_len = IB_len;
    return OK;
}
