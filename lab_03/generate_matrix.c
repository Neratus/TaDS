#include "generate_matrix.h"

int random_percentage(void) 
{
    return rand() % 101;
}

void fill_standard_matrix(full_matrix_t *matrix, int fill_percentage) 
{
    size_t nonzero_count = (fill_percentage * matrix->n * matrix->m) / 100;
    for (size_t i = 0; i < matrix->n; i++)
        for (size_t j = 0; j < matrix->m; j++)
            matrix->data[i][j] = 0;
    for (size_t i = 0; i < nonzero_count; i++) 
    {
        int random_row = rand() % matrix->n;
        int random_col = rand() % matrix->m;
        if (fabs(matrix->data[random_row][random_col]) > EPS)
            i--;
        else
            matrix->data[random_row][random_col] = random_percentage() + 1;
    }
}

int compare_matrix_operations(void) 
{
    int n, m;
    printf("Введите количество строк матрицы: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Некорректный ввод для количества строк.\n");
        return ERROR_INPUT_SIZE;
    }

    printf("Введите количество столбцов матрицы: ");
    if (scanf("%d", &m) != 1 || m <= 0) 
    {
        printf("Некорректный ввод для количества столбцов.\n");
        return ERROR_INPUT_SIZE;
    }

    printf("Процент заполнения    | Объем памяти (разреженная_1) | Объем памяти (стандартная_1)| Объем памяти (разреженная_2) | Объем памяти (стандартная_2) | Время (разреженная) | Время (стандартная)\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int fill_percentage = 10; fill_percentage <= 100; fill_percentage += 10) {
        
        full_matrix_t test_1, test_2;
        full_matrix_t result_placeholder;
        sparse_matrix_B_t sparse_test_1;
        sparse_matrix_A_t sparse_test_2;
        sparse_matrix_B_t place_holder;
        test_1.n = n;
        test_1.m = m;
        test_1.data = allocate_matrix(n, m);
        if (test_1.data == NULL) 
        {
            printf("Ошибка выделения памяти.\n");
            return ERROR_MALLOC;
        }
        fill_standard_matrix(&test_1, fill_percentage);

        test_2.n = n;
        test_2.m = m;
        test_2.data = allocate_matrix(n, m);
        if (test_2.data == NULL) 
        {
            printf("Ошибка выделения памяти.\n");
            free(test_1.data);
            return ERROR_MALLOC;
        }
        fill_standard_matrix(&test_2, fill_percentage);

        int rc = input_sparse_matrix_B(test_1, &sparse_test_1);
        if (rc != OK)
        {
            printf("Ошибка конвертации в расширенную.\n");
            free(test_1.data);
            free(test_2.data);
            return ERROR_MALLOC;
        }

        rc = input_sparse_matrix_A(test_2, &sparse_test_2);
        if (rc != OK)
        {
            free(test_1.data);
            free(test_2.data);
            free(sparse_test_1.B);
            free(sparse_test_1.IB);
            free(sparse_test_1.JB);
            printf("Ошибка конвертации в расширенную.\n");
            return ERROR_MALLOC;
        }

        size_t sparseMemory_1 = (sizeof(double) + sizeof(int)) * sparse_test_2.elem_cnt + sizeof(int) * sparse_test_1.IB_len;
        size_t standardMemory_1 = sizeof(test_1.data) * test_1.n * test_1.m;

        size_t sparseMemory_2 =(sizeof(double) + sizeof(int)) * sparse_test_2.elem_cnt + sizeof(int) * sparse_test_2.JA_len;
        size_t standardMemory_2 = sizeof(test_2.data)* test_2.n * test_2.m;

        struct timespec start, end;
        clock_gettime(CLOCK_REALTIME, &start); 
        rc = mult_matrix(test_1, test_2, &result_placeholder);
        clock_gettime(CLOCK_REALTIME, &end);
        double standardTime = ((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec)); 

        clock_gettime(CLOCK_REALTIME, &start);
        rc = multiply_matrix_sparse(sparse_test_1, sparse_test_2, &place_holder);
        clock_gettime(CLOCK_REALTIME, &end);
        double sparseTime = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec); 

        printf("|%d%%\t\t\t\t %zu байт\t\t\t%zu байт\t\t\t  %zu байт\t\t\t %zu байт\t\t\t %.1lf нс\t\t %.1lf нс|\n", fill_percentage, sparseMemory_1, standardMemory_1,sparseMemory_2, standardMemory_2, sparseTime, standardTime);

        free(test_1.data);
        free(test_2.data);
        free(sparse_test_1.B);
        free(sparse_test_1.IB);
        free(sparse_test_1.JB);
        free(sparse_test_2.A);
        free(sparse_test_2.IA);
        free(sparse_test_2.JA);
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    return OK;
}
