#include "test.h"
#include <time.h>

unsigned long long cur_time_nanosec(void)
{
    struct timespec val;
    clock_gettime(CLOCK_MONOTONIC_RAW,&val);
    return val.tv_nsec;
}


void test_queue(void)
{
    size_t queue_size[] =  {1, 10, 25, 50, 100, 250, 500, 1000, 5000};
    size_t iter_cnt = 40;//600 + 1;
    size_t queue_size_cnt = sizeof(queue_size) / sizeof(queue_size[0]);
    unsigned long long time_start,time_end;
    unsigned long long safe_lock = 0;
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Количество элементов очереди| Память(static), байты| Время(static), нс| Память(dynamic), байты| Время(dynamic), нс| Память(list), байты| Время(list), нс|\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (size_t i = 0; i < queue_size_cnt; i++)
    {

        unsigned long long time_static = 0;
        double res_time_static = 0;

        unsigned long long time_dynamic = 0;
        double res_time_dynamic = 0;

        unsigned long long time_list = 0;
        double res_time_list = 0;

        safe_lock = 0;

        size_t memory_static = MAX_LEN * sizeof(double);
        size_t memory_dynamic = 0;
        size_t memory_list = 0;
        static_queue_t static_queue = init_static();
        for (size_t k = 0; k < iter_cnt; k++)
        {
            time_start = cur_time_nanosec();
            for (size_t r = 0; r < queue_size[i]; r++)
                queue_static_push(&static_queue, 1);
            for (size_t r = 0; r < queue_size[i]; r++)
                queue_static_pop(&static_queue);
            time_end = cur_time_nanosec();
            if (safe_lock == 0)
                safe_lock = time_end - time_start;
            else if ((time_end - time_start) <= safe_lock * 10)
                time_static += (time_end - time_start);
            else
                k--;
        }
        res_time_static = time_static / iter_cnt;
        safe_lock = 0;
        for (size_t k = 0; k < iter_cnt; k++)
        {
            time_start = cur_time_nanosec();
            dynamic_queue_t dynamic_queue = init_dynamic();
            for (size_t r = 0; r < queue_size[i]; r++)
                queue_dynamic_push(&dynamic_queue, 1);
            memory_dynamic = dynamic_queue.allocated_memory * sizeof(double);
            for (size_t r = 0; r < queue_size[i]; r++)
                queue_dynamic_pop(&dynamic_queue);
            free_dynamic(&dynamic_queue);
            time_end = cur_time_nanosec();
            if (safe_lock == 0)
                safe_lock = time_end - time_start;
            else if ((time_end - time_start) <= safe_lock * 10)
                time_dynamic += (time_end - time_start);
            else
                k--;
        }
        res_time_dynamic = time_dynamic / iter_cnt;
        safe_lock = 0;
        list_queue_t *list_queue;
        for (size_t k = 0; k < iter_cnt; k++)
        {
            time_start = cur_time_nanosec();
            list_queue = init_list();
            for (size_t r = 0; r < queue_size[i]; r++)
                queue_list_push(list_queue, 1);
            memory_list = sizeof(Node) * list_queue->size;
            for (size_t r = 0; r < queue_size[i]; r++)
                queue_list_pop(list_queue);
            free_list(list_queue);
            time_end = cur_time_nanosec();
            if (safe_lock == 0)
                safe_lock = time_end - time_start;
            else if ((time_end - time_start) <= safe_lock * 10)
                time_list += (time_end - time_start);
            else
                k--;
        }
        res_time_list = time_list / iter_cnt;

        printf("%26zu|%22zu|%18lf|%23zu|%19lf|%20zu|%16lf|\n",queue_size[i], memory_static, res_time_static, memory_dynamic, res_time_dynamic, memory_list, res_time_list);
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    }

    printf("Симуляция : \n");
    double t1_start = 0;
    double t1_finish = 6;
    double t2_start = 0;
    double t2_finish = 1;
    double probability = 0.8;
    printf("Запустить симуляцию с данными по умолчанию(1) или ввести собственные(2): ");
    int option;
    if ((scanf("%d",&option) != 1) || ((option < 1) || (option > 2)))
    {
        printf("Ошибка ввода опции \n");
        return;
    }
    else if (option == 2)
    {
        printf("Введите интервал времени поступления T1 \n ");
        printf("Введите интервал поступления через тире в формате Ts-Te : ");
        if ((scanf("%lf-%lf", &t1_start, &t1_finish) != 2) || (t1_start >= t1_finish) || (t1_start < 0) || (t1_finish <= 0))
        {
            printf("Ошибка ввода интервала \n");
            return;
        }
        printf("Введите интервал времени обслуживания T2 \n ");
        printf("Введите интервал обслуживания через тире в формате Ts-Te : ");
        if ((scanf("%lf-%lf", &t2_start, &t2_finish) != 2) || (t2_start >= t2_finish) || (t2_start < 0) || (t2_finish <= 0))
        {
            printf("Ошибка ввода интервала \n");
            return;
        }
        printf("Введите вероятность возвращение заявки в конец очереди: ");
        if ((scanf("%lf",&probability) != 1) || (probability < 0) || (probability > 0.97))
        {
            printf("Ошибка ввода вероятности \n");
            return;
        }
        printf("Ввод успешен \n");
    }
    unsigned long long time_static = 0;
    unsigned long long time_dynamic = 0;
    unsigned long long time_list = 0;
    size_t memory_dinamic = 0;
    size_t memory_list = 0;
    safe_lock = 0;
    for (size_t i = 0; i < 20; i++)
    {
        time_start = cur_time_nanosec();
        simulate_static_silent(t1_start, t1_finish, t2_start, t2_finish, probability);
        time_end = cur_time_nanosec();
        if (safe_lock == 0)
            safe_lock = time_end - time_start;
        else if ((time_end - time_start) <= safe_lock * 10)
            time_static += (time_end - time_start);
        else
            i--;
    }
    safe_lock = 0;
    for (size_t i = 0; i < 20; i++)
    {
        time_start = cur_time_nanosec();
        memory_dinamic = simulate_dynamic_silent(t1_start, t1_finish, t2_start, t2_finish, probability);
        time_end = cur_time_nanosec();
        if (safe_lock == 0)
            safe_lock = time_end - time_start;
        else if ((time_end - time_start) <= safe_lock * 10)
            time_dynamic += (time_end - time_start);
        else
            i--;
    }
    safe_lock = 0;
    for (size_t i = 0; i < 20; i++)
    {
        time_start = cur_time_nanosec();
        memory_list = simulate_list_silent(t1_start, t1_finish, t2_start, t2_finish, probability);
        time_end = cur_time_nanosec();
        if (safe_lock == 0)
            safe_lock = time_end - time_start;
        else if ((time_end - time_start) <= safe_lock * 10)
            time_list += (time_end - time_start);
        else
            i--;
    }
    printf("\tСтатический массив:  %lf, максимально занимаемая память - %lu\n", (double)(time_dynamic / 35), MAX_LEN * sizeof(double));
    printf("\tДинамический массив: %lf, максимально занимаемая память - %lu\n", (double)(time_dynamic / 20), memory_dinamic);
    printf("\tСписок: \t     %lf, максимально занимаемая память - %lu\n", (double)(time_list / 20),memory_list);
    
}
