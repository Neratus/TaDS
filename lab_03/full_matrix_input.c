#include "full_matrix_input.h"

double **allocate_matrix(size_t n, size_t m)
{
    double **data = malloc(n * sizeof(double*) + n * m * sizeof(double));
    if (!data)
        return NULL;
    for (size_t i = 0; i < n; i++)
    {
        data[i] = (double*)((char*) data + n * sizeof(double*) + i * m * sizeof(double));
        if (!data[i])
        {
            free(data);
            return NULL;
        }
    }
    return data;
}

int input_matrix_standart(char *path, full_matrix_t *matrix)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
        return ERROR_FILE;
    size_t input_n, input_m;
    if (fscanf(f, "%zu %zu", &input_n, &input_m) != 2)
    {
        fclose(f);
        return ERROR_INPUT_SIZE;
    }
    if ((input_n == 0) || (input_m == 0))
    {
        fclose(f);
        return ERROR_INPUT_SIZE_VAL;
    }
    matrix->data = allocate_matrix(input_n, input_m);
    if (matrix->data == NULL)
    {
        fclose(f);
        return ERROR_MALLOC;
    }
    double cur_elem;
    for (size_t i = 0; i < input_n; i++)
        for (size_t j = 0; j < input_m; j++)
        {
            if (fscanf(f, "%lf", &cur_elem) != 1)
            {
                free(matrix->data);
                matrix->data = NULL;
                fclose(f);
                return ERROR_INPUT;
            }
            matrix->data[i][j] = cur_elem;
        }
    fclose(f);
    matrix->n = input_n;
    matrix->m = input_m;
    return OK;
}

int input_matrix_standart_from_console(full_matrix_t *matrix)
{
    size_t input_n, input_m;
    printf("Введите количество строк и столбцов: ");
    if (scanf("%zu %zu", &input_n, &input_m) != 2)
        return ERROR_INPUT_SIZE;
    if ((input_n == 0) || (input_m == 0))
        return ERROR_INPUT_SIZE_VAL;
    matrix->data = allocate_matrix(input_n, input_m);
    if (matrix->data == NULL)
        return ERROR_MALLOC;
    double cur_elem;
    printf("\nВведите матрицу построчно \n");
    for (size_t i = 0; i < input_n; i++)
        for (size_t j = 0; j < input_m; j++)
        {
            if (scanf("%lf", &cur_elem) != 1)
            {
                free(matrix->data);
                matrix->data = NULL;
                return ERROR_INPUT;
            }
            matrix->data[i][j] = cur_elem;
        }
    matrix->n = input_n;
    matrix->m = input_m;
    return OK;
}

int input_matrix_coord(char *path, full_matrix_t *matrix)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
        return ERROR_FILE;
    size_t input_n, input_m, non_zero_elem;
    if (fscanf(f, "%zu %zu %zu", &input_n, &input_m, &non_zero_elem) != 3)
    {
        fclose(f);
        return ERROR_INPUT_SIZE;
    }
    if ((input_n == 0) || (input_m == 0) || (non_zero_elem == 0))
    {
        fclose(f);
        return ERROR_INPUT_SIZE_VAL;
    }
    matrix->data = allocate_matrix(input_n, input_m);
    if (matrix->data == NULL)
    {
        fclose(f);
        return ERROR_MALLOC;
    }
    for (size_t i = 0; i < input_n; i++)
        for (size_t j = 0; j < input_m; j++)
            matrix->data[i][j] = 0;
    double cur_elem;
    size_t n_cur, m_cur;
    for (size_t i = 0; i < non_zero_elem; i++)
    {
        if (fscanf(f, "%lf %zu %zu", &cur_elem, &n_cur, &m_cur) != 3)
        {
            free(matrix->data);
            matrix->data = NULL;
            fclose(f);
            return ERROR_INPUT;
        }
        if ((n_cur > matrix->n) || (m_cur > matrix->m) || (n_cur < 0) || (m_cur < 0))
        {
            free(matrix->data);
            matrix->data = NULL;
            fclose(f);
            return ERROR_INDEX;
        }
        if ((fabs(cur_elem) <= EPS) || (fabs(matrix->data[n_cur][m_cur]) > EPS))
            return ERROR_INPUT;
        matrix->data[n_cur][m_cur] = cur_elem;
    }
    fclose(f);
    matrix->n = input_n;
    matrix->m = input_m;
    return OK;
}

int input_matrix_coord_from_console(full_matrix_t *matrix)
{
    printf("Введите количество строк,столбцов и ненулевых эелементов через пробел: ");
    size_t input_n, input_m, non_zero_elem;
    if (scanf("%zu %zu %zu", &input_n, &input_m, &non_zero_elem) != 3)
        return ERROR_INPUT_SIZE;
    if ((input_n == 0) || (input_m == 0) || (non_zero_elem == 0))
        return ERROR_INPUT_SIZE_VAL;
    matrix->data = allocate_matrix(input_n, input_m);
    if (matrix->data == NULL)
        return ERROR_MALLOC;
    for (size_t i = 0; i < input_n; i++)
        for (size_t j = 0; j < input_m; j++)
            matrix->data[i][j] = 0;
    double cur_elem;
    size_t n_cur, m_cur;
    printf("\n Введите ненулевые элементы в формате: значение номер_строки номер_столбца:  \n");
    for (size_t i = 0; i < non_zero_elem; i++)
    {
        if (scanf("%lf %zu %zu", &cur_elem, &n_cur, &m_cur) != 3)
        {
            free(matrix->data);
            matrix->data = NULL;
            return ERROR_INPUT;
        }
        if ((n_cur > matrix->n) || (m_cur > matrix->m) || (n_cur < 0) || (m_cur < 0))
        {
            free(matrix->data);
            matrix->data = NULL;
            return ERROR_INDEX;
        }
        if ((fabs(cur_elem) <= EPS) || (fabs(matrix->data[n_cur][m_cur]) > EPS))
            return ERROR_INPUT;
        matrix->data[n_cur][m_cur] = cur_elem;
    }
    matrix->n = input_n;
    matrix->m = input_m;
    return OK;
}
