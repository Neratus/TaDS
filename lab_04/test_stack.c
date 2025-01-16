#include "test_stack.h"
#include <time.h>

unsigned long long cur_time_nanosec(void)
{
    struct timespec val;
    clock_gettime(CLOCK_MONOTONIC_RAW,&val);
    return val.tv_nsec;
}


void test_stack(void)
{
    size_t stack_size[] =  {1, 10, 25, 50, 100, 250, 500, 1000, 5000};
    size_t iter_cnt = 600 + 1;
    size_t stack_size_cnt = sizeof(stack_size) / sizeof(stack_size[0]);
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Количество элементов стека| Память(static), байты| Время(static), нс| Память(dynamic), байты| Время(dynamic), нс| Память(list), байты| Время(list), нс|\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (size_t i = 0; i < stack_size_cnt; i++)
    {
        unsigned long long time_start,time_end;

        unsigned long long time_polindrom_static = 0;
        double res_time_polindrom_static = 0;

        unsigned long long time_polindrom_dynamic = 0;
        double res_time_polindrom_dynamic = 0;

        unsigned long long time_polindrom_list = 0;
        double res_time_polindrom_list = 0;

        unsigned long long safe_lock = 0;
        int rc;

        char *str = malloc(stack_size[i] * sizeof(char));
        if (str == NULL)
            return;
        for (size_t j = 0; j < stack_size[i]; j++)
            str[j] = 'A';
        size_t memory_static = 0;
        size_t memory_dynamic = 0;
        size_t memory_list = 0;
        for (size_t k = 0; k < iter_cnt; k++)
        {
            time_start = cur_time_nanosec();
            rc = check_string_stack_static(str, stack_size[i], &memory_static);
            time_end = cur_time_nanosec();
            if (rc != YES)
                return;
            if (safe_lock == 0)
                safe_lock = time_end - time_start;
            else if ((time_end - time_start) <= safe_lock * 10)
                time_polindrom_static += (time_end - time_start);
            else
                k--;
        }
        res_time_polindrom_static = time_polindrom_static / iter_cnt;
        safe_lock = 0;
        for (size_t k = 0; k < iter_cnt; k++)
        {
            time_start = cur_time_nanosec();
            rc = check_string_stack_dynamic(str, stack_size[i], &memory_dynamic);
            time_end = cur_time_nanosec();
            if (rc != YES)
                return;
            if (safe_lock == 0)
                safe_lock = time_end - time_start;
            else if ((time_end - time_start) <= safe_lock * 10)
                time_polindrom_dynamic += (time_end - time_start);
            else
                k--;
        }
        res_time_polindrom_dynamic = time_polindrom_dynamic / iter_cnt;
        safe_lock = 0;
        for (size_t k = 0; k < iter_cnt; k++)
        {
            time_start = cur_time_nanosec();
            rc = check_string_stack_list(str, stack_size[i],&memory_list);
            time_end = cur_time_nanosec();
            if (rc != YES)
                return;
            if (safe_lock == 0)
                safe_lock = time_end - time_start;
            else if ((time_end - time_start) <= safe_lock * 10)
                time_polindrom_list += (time_end - time_start);
            else
                k--;
        }
        res_time_polindrom_list = time_polindrom_list / iter_cnt;

        printf("%26zu|%22zu|%18lf|%23zu|%19lf|%20zu|%16lf|\n",stack_size[i], memory_static, res_time_polindrom_static, memory_dynamic, res_time_polindrom_dynamic, memory_list, res_time_polindrom_list);
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        free(str);
    }
}
