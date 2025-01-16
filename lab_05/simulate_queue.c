#include "simulate_queue.h"

double random_float(double min, double max)
{
    if (min >= max)
        return min;
    
    return ((double)rand() / RAND_MAX) * (max - min) + min;
}

void simulate_static(void)
{
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
    double e_arr_time = (t1_start + t1_finish) / 2.0; 
    double e_serv_time = (t2_start + t2_finish) / 2.0; 

    double e_now_time;

    double exp_serv_time = e_serv_time * (MAX_REQ / (1-probability));
    double exp_arr_time = e_arr_time * MAX_REQ;

    if (exp_serv_time < exp_arr_time)
        e_now_time = exp_arr_time;
    else
        e_now_time = exp_serv_time;
     
    static_queue_t static_queue = init_static();
    int entered_req = 0;
    int serviced_req = 0;
    int freed = 0;

    double average_len = 0;
    int measur_cnt = 0;
    int printed = 0;

    double arr_time = random_float(t1_start, t1_finish);
    double serv_time = 0;
    double total_time = 0;
    double wait_time = 0;

    while(serviced_req < MAX_REQ)
    {
        if (arr_time <= serv_time)
        {
            int rc = queue_static_push(&static_queue, arr_time);
            if (rc != OK)
            {
                printf("ОШИБКА: При выполнении программы произошло переполнение очереди \n");
                return;
            }
            entered_req++;
            total_time = arr_time;
            arr_time = total_time + random_float(t1_start, t1_finish);
        }
        else
        {
            if (queue_static_size(static_queue) == 0)
            {
                wait_time += fabs(serv_time - total_time);
                serv_time = arr_time;
            }
            else
            {
                double cur = queue_static_pop(&static_queue);
                serv_time = cur < serv_time ? serv_time : cur;
                total_time += (serv_time - cur);
                freed++;
                if (rand() / (double)RAND_MAX < probability)
                {
                    serv_time += random_float(t2_start, t2_finish);
                    queue_static_push(&static_queue, serv_time);
                }
                else
                {
                    serviced_req++;
                    printed = 0;
                }
                if ((serviced_req % PRINT_REQ == 0) && (printed == 0))
                {
                    printf("Обслужено: %d, Текущая длина очереди: %zu\n", serviced_req, queue_static_size(static_queue));
                    printed = 1;
                }
            }

        }
        if ((serviced_req % PRINT_REQ == 0) && (printed == 0))
        {
            printf("Обслужено: %d, Текущая длина очереди: %zu\n", serviced_req, queue_static_size(static_queue));
            printed = 1;
        }
        average_len += (double)queue_static_size(static_queue); 
        measur_cnt++;
    }
    double delta_now_time = fabs(total_time - e_now_time) / e_now_time * 100;

    
    printf("Общее время моделирования: %.2f е.в.\n", total_time);
    printf("Вошли в систему: %d, Вышли из системы: %d\n", entered_req, serviced_req);
    printf("Среднее время пребывания заявки в очереди: %.2f е.в.\n", total_time / freed);
    printf("Средняя длина очереди: %.2f \n", average_len / measur_cnt);
    printf("Время простоя: %lf \n",wait_time);
    printf("Время моделирования: %lf (ожидаемое: %lf, погрешность: %lf%%)\n",
                total_time, e_now_time, delta_now_time);
}

void simulate_static_silent(double t1_start, double t1_finish, double t2_start, double t2_finish, double probability)
{
     
    static_queue_t static_queue = init_static();
    int serviced_req = 0;

    double arr_time = random_float(t1_start, t1_finish);
    double serv_time = 0;
    double total_time = 0;

    while(serviced_req < MAX_REQ)
    {
        if (arr_time <= serv_time)
        {
            int rc = queue_static_push(&static_queue, arr_time);
            if (rc != OK)
            {
                printf("ОШИБКА: При выполнении программы произошло переполнение очереди \n");
                exit(EXIT_FAILURE);
            }
            total_time = arr_time;
            arr_time = total_time + random_float(t1_start, t1_finish);
        }
        else
        {
            if (queue_static_size(static_queue) == 0)
                serv_time = arr_time;
            else
            {
                double cur = queue_static_pop(&static_queue);
                serv_time = cur < serv_time ? serv_time : cur;
                total_time += (serv_time - cur);
                if (rand() / (double)RAND_MAX < probability)
                {
                    serv_time += random_float(t2_start, t2_finish);
                    queue_static_push(&static_queue, serv_time);
                }
                    else
                        serviced_req++;

            }
        }
    }

}

void simulate_dynamic(void)
{
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
    double e_arr_time = (t1_start + t1_finish) / 2.0; 
    double e_serv_time = (t2_start + t2_finish) / 2.0; 

    double e_now_time;

    double exp_serv_time = e_serv_time * (MAX_REQ / (1-probability));
    double exp_arr_time = e_arr_time * MAX_REQ;

    if (exp_serv_time < exp_arr_time)
        e_now_time = exp_arr_time;
    else
        e_now_time = exp_serv_time;

    dynamic_queue_t dynamic_queue = init_dynamic();
    int entered_req = 0;
    int serviced_req = 0;
    int freed = 0;

    double average_len = 0;
    int measur_cnt = 0;
    int printed = 0;

    double arr_time = random_float(t1_start, t1_finish);
    double serv_time = 0;
    double total_time = 0;
    double wait_time = 0;

    while(serviced_req < MAX_REQ)
    {
        if (arr_time <= serv_time)
        {
            queue_dynamic_push(&dynamic_queue, arr_time);
            total_time = arr_time;
            arr_time = total_time + random_float(t1_start, t1_finish);
            entered_req++;
        }
        else
        {
            if (queue_dynamic_size(dynamic_queue) == 0)
            {
                 wait_time += fabs(serv_time - total_time);
                serv_time = arr_time;
            }
            else
            {
                double cur = queue_dynamic_pop(&dynamic_queue);
                serv_time = cur < serv_time ? serv_time : cur;
                total_time += (serv_time - cur);
                freed++;
                if (rand() / (double)RAND_MAX < probability)
                {
                    serv_time += random_float(t2_start, t2_finish);
                    queue_dynamic_push(&dynamic_queue, serv_time);
                }
                else
                {
                    serviced_req++;
                    printed = 0;
                }
                if ((serviced_req % PRINT_REQ == 0) && (printed == 0))
                {
                    printf("Обслужено: %d, Текущая длина очереди: %zu\n", serviced_req, queue_dynamic_size(dynamic_queue));
                    printed = 1;
                }
            }

        }
        if ((serviced_req % PRINT_REQ == 0) && (printed == 0))
        {
            printf("Обслужено: %d, Текущая длина очереди: %zu\n", serviced_req, queue_dynamic_size(dynamic_queue));
            printed = 1;
        }
        average_len += (double)queue_dynamic_size(dynamic_queue); 
        measur_cnt++;
    }
    double delta_now_time = fabs(total_time - e_now_time) / e_now_time * 100;

    
    printf("Общее время моделирования: %.2f е.в.\n", total_time);
    printf("Вошли в систему: %d, Вышли из системы: %d\n", entered_req, serviced_req);
    printf("Среднее время пребывания заявки в очереди: %.2f е.в.\n", total_time / freed);
    printf("Средняя длина очереди: %.2f \n", average_len / measur_cnt);
    printf("Время простоя: %lf \n",wait_time);
    printf("Время моделирования: %lf (ожидаемое: %lf, погрешность: %lf%%)\n",
                total_time, e_now_time, delta_now_time);
    free_dynamic(&dynamic_queue);
}

size_t simulate_dynamic_silent(double t1_start, double t1_finish, double t2_start, double t2_finish, double probability)
{

    dynamic_queue_t dynamic_queue = init_dynamic();
    int serviced_req = 0;
    size_t memory_dynamic = 0;

    double arr_time = random_float(t1_start, t1_finish);
    double serv_time = 0;
    double total_time = 0;

    while(serviced_req < MAX_REQ)
    {
        if (arr_time <= serv_time)
        {
            queue_dynamic_push(&dynamic_queue, arr_time);
            total_time = arr_time;
            arr_time = total_time + random_float(t1_start, t1_finish);
        }
        else
        {
            if (queue_dynamic_size(dynamic_queue) == 0)
                serv_time = arr_time;
            else
            {
                double cur = queue_dynamic_pop(&dynamic_queue);
                serv_time = cur < serv_time ? serv_time : cur;
                if (rand() / (double)RAND_MAX < probability)
                {
                    serv_time += random_float(t2_start, t2_finish);
                    queue_dynamic_push(&dynamic_queue, serv_time);
                }
                    else
                        serviced_req++;

            }  
            size_t cur_memory_dynamic = dynamic_queue.allocated_memory * sizeof(double);
            if (cur_memory_dynamic > memory_dynamic)
                memory_dynamic = cur_memory_dynamic;
        }

    }

    free_dynamic(&dynamic_queue);
    return memory_dynamic;
}

void simulate_list(void)
{
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
    double e_arr_time = (t1_start + t1_finish) / 2.0; 
    double e_serv_time = (t2_start + t2_finish) / 2.0; 

    double e_now_time;

    double exp_serv_time = e_serv_time * (MAX_REQ / (1-probability));
    double exp_arr_time = e_arr_time * MAX_REQ;

    if (exp_serv_time < exp_arr_time)
        e_now_time = exp_arr_time;
    else
        e_now_time = exp_serv_time;
    list_queue_t *list_queue = init_list();
    int entered_req = 0;
    int serviced_req = 0;
    int freed = 0;

    double average_len = 0;
    int measur_cnt = 0;
    int printed = 0;

    double arr_time = random_float(t1_start, t1_finish);
    double serv_time = 0;
    double total_time = 0;
    double wait_time = 0;

    while(serviced_req < MAX_REQ)
    {
        if (arr_time <= serv_time)
        {
            queue_list_push(list_queue, arr_time);
            total_time = arr_time;
            arr_time = total_time + random_float(t1_start, t1_finish);
            entered_req++;
        }
        else
        {
            if (queue_list_size(*list_queue) == 0)
            {
                 wait_time += fabs(serv_time - total_time);
                serv_time = arr_time;
            }
            else
            {
                double cur = queue_list_pop(list_queue);
                serv_time = cur < serv_time ? serv_time : cur;
                total_time += (serv_time - cur);
                freed++;
                if (rand() / (double)RAND_MAX < probability)
                {
                    serv_time += random_float(t2_start, t2_finish);
                    queue_list_push(list_queue, serv_time);
                }
                else
                {
                    serviced_req++;
                    printed = 0;
                }
                if ((serviced_req % PRINT_REQ == 0) && (printed == 0))
                {
                    printed = 1;
                    printf("Обслужено: %d, Текущая длина очереди: %d\n", serviced_req, queue_list_size(*list_queue));
                }
            }

        }
        if ((serviced_req % PRINT_REQ == 0) && (printed == 0))
        {
            printf("Обслужено: %d, Текущая длина очереди: %d\n", serviced_req, queue_list_size(*list_queue));
            printed = 1;
        }
        average_len += (double)queue_list_size(*list_queue); 
        measur_cnt++;
    }
    double delta_now_time = fabs(total_time - e_now_time) / e_now_time * 100;
    
    printf("Общее время моделирования: %.2f е.в.\n", total_time);
    printf("Вошли в систему: %d, Вышли из системы: %d\n", entered_req, serviced_req);
    printf("Среднее время пребывания заявки в очереди: %.2f е.в.\n", total_time / freed);
    printf("Средняя длина очереди: %.2f \n", average_len / measur_cnt);
    printf("Время простоя: %lf \n",wait_time);
    printf("Время моделирования: %lf (ожидаемое: %lf, погрешность: %lf%%)\n",
                total_time, e_now_time, delta_now_time);
    free_adress();
    free_list(list_queue);
}

size_t simulate_list_silent(double t1_start, double t1_finish, double t2_start, double t2_finish, double probability)
{

    size_t memory_list = 0;

    list_queue_t *list_queue = init_list();
    int serviced_req = 0;

    double arr_time = random_float(t1_start, t1_finish);
    double serv_time = 0;
    double total_time = 0;

    while(serviced_req < MAX_REQ)
    {
        if (arr_time <= serv_time)
        {
            queue_list_push(list_queue, arr_time);
            total_time = arr_time;
            arr_time = total_time + random_float(t1_start, t1_finish);
        }
        else
        {
            if (queue_list_size(*list_queue) == 0)
                serv_time = arr_time;
            else
            {
                double cur = queue_list_pop(list_queue);
                serv_time = cur < serv_time ? serv_time : cur;
                total_time += (serv_time - cur);
                if (rand() / (double)RAND_MAX < probability)
                {
                    serv_time += random_float(t2_start, t2_finish);
                    queue_list_push(list_queue, serv_time);
                }
                else
                    serviced_req++;

            }
            size_t cur_memory_list = sizeof(Node) * list_queue->size;
            if (cur_memory_list > memory_list)
                memory_list = cur_memory_list;
        }


    }

    free_list(list_queue);
    return memory_list;
}
