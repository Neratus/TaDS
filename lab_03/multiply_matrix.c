#include "multiply_matrix.h"

int mult_matrix(full_matrix_t first, full_matrix_t second, full_matrix_t *result)
{
    if (first.m != second.n)
        return ERROR_WRONG_MATR_SIZE;

    result->n = first.n;
    result->m = second.m;

    result->data = allocate_matrix(result->n, result->m );
    if (result->data == NULL)
        return ERROR_MALLOC;

    for (size_t i = 0; i < result->n; i++)
        for (size_t j = 0; j < result->m; j++)
        {
            result->data[i][j] = 0;
            for (size_t g = 0; g < first.m; g++)
                result->data[i][j] += first.data[i][g] * second.data[g][j];
        }     
    return OK;
}

int multiply_matrix_sparse(sparse_matrix_B_t first, sparse_matrix_A_t second, sparse_matrix_B_t *result)
{
    size_t elem_cnt = 0;
    size_t IC_len = 1;
    double *c = malloc(sizeof(double) * second.JA_len * first.IB_len);
    if (c == NULL)
        return ERROR_MALLOC;
    int *IC = malloc(sizeof(int) * second.JA_len * first.IB_len);
    if (IC == NULL)
    {
        free(c);
        return ERROR_MALLOC;
    }
    int *JC = malloc(sizeof(int) * second.JA_len * first.IB_len);
    if (JC == NULL)
    {
        free(c);
        free(IC);
        return ERROR_MALLOC;
    }
    JC[0] = 0;
    for (size_t ib = 0; ib < first.IB_len - 1; ib++) 
    {
        for (size_t ia= 0; ia < second.JA_len - 1; ia++)
        {
            int cur_b =  first.IB[ib];
            int cur_a =  second.JA[ia];
            double total = 0;
            while ((cur_a < second.JA[ia + 1]) && (cur_b < first.IB[ib + 1]))
            {
                if (first.JB[cur_b] == second.IA[cur_a])
                {
                    total += first.B[cur_b]* second.A[cur_a];
                    cur_a++;
                    cur_b++;
                }
                if (first.JB[cur_b] > second.IA[cur_a])
                    cur_a++;
                if (first.JB[cur_b] < second.IA[cur_a])
                    cur_b++;
            }
            if (fabs(total) > EPS)
            {
                c[elem_cnt] = total;
                JC[elem_cnt] = ia;
                elem_cnt++;
            }
        }
        IC[ib + 1] = elem_cnt;
        IC_len++;
    }
    result->IB = IC;
    result->JB = JC;
    result->B = c;
    result->elem_cnt = elem_cnt;
    result->IB_len = IC_len;
    return 0;
}
