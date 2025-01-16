#include "test_tree.h"
#include <time.h>

unsigned long long cur_time_nanosec(void)
{
    struct timespec val;
    clock_gettime(CLOCK_MONOTONIC_RAW,&val);
    return val.tv_nsec;
}

int read_line(char *str, size_t str_max, FILE *f)
{
    if (!fgets(str, str_max, f))
    {
        return ERROR_STR_INPUT;
    }
    char *p = strchr(str, '\n');
    if (p)
    {
        *p = 0;
        return OK;
    }
    return ERROR_STR_SIZE;
}


void remove_words_starting_with(const char *input_filename, const char *output_filename, char letter) 
{
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL) 
        return;

    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) 
    {
        fclose(input_file);
        return;
    }

    char word[MAX_STR_LEN];

    while (fscanf(input_file, "%s", word) != EOF) 
        if (word[0] != letter) 
            fprintf(output_file, "%s\n", word);

    fclose(input_file);
    fclose(output_file);
}



void test_tree(void)
{
    size_t cnt = 50;
    printf("Введите название файла: \n");
    char file[MAX_STR_LEN];
    int rc = read_line(file, MAX_STR_LEN, stdin);

    unsigned long long time_start,time_end;
    unsigned long long safe_lock = 0;

    unsigned long long time_tree = 0;
    double res_time_tree = 0;

    unsigned long long time_balanced_tree = 0;
    double res_balanced_tree = 0;

    if (rc != OK)
    {
        printf("ERROR: Ошибка чтения строки");
        return;
    }
    printf("Замер производительности для файла %s на %zu итерациях: \n",file, cnt);
    struct tree_node_t *root = NULL;
    read_words_from_file(file, &root);
    char word[MAX_STR_LEN];
    for (size_t k = 0; k < cnt; k++)
    {
        FILE *input_file = fopen(file, "r");
        if (input_file == NULL) 
            return;
        unsigned long long cur_time = 0;
        int file_cnt = 0;
        while (fscanf(input_file, "%s", word) != EOF) 
        {
            int cmp;
            time_start = cur_time_nanosec();
            in_order_silent(root, &cmp);
            time_end = cur_time_nanosec();
            cur_time += time_end - time_start;
            file_cnt++;
        }
        fclose(input_file);
        cur_time /= file_cnt;
        if (safe_lock == 0)
            safe_lock = (unsigned long long)cur_time;
        else if (cur_time <= safe_lock * 10)
            time_tree += (unsigned long long)cur_time;
        else
            k--;
    }
    res_time_tree = time_tree / cnt;
    printf("Вырожденное дерево - %lf, высота - %d\n", res_time_tree, root->height);
    
    int balance_cnt = 0;
    int prev_cnt = 0;
    root = balance_tree(root, &balance_cnt);
    while(balance_cnt != prev_cnt) 
    {
        prev_cnt = balance_cnt;
        root = balance_tree(root, &balance_cnt);
    }
    int deep = 0;
    for (size_t k = 0; k < cnt; k++)
    {
        FILE *input_file = fopen(file, "r");
        if (input_file == NULL) 
            return;
        unsigned long long cur_time = 0;
        int file_cnt = 0;
        while (fscanf(input_file, "%s", word) != EOF) 
        {
            time_start = cur_time_nanosec();
            in_order_silent(root, &deep);
            time_end = cur_time_nanosec();
            cur_time += time_end - time_start;
            file_cnt++;
        }
        fclose(input_file);
        cur_time /= file_cnt;
        if (safe_lock == 0)
            safe_lock = (unsigned long long)cur_time;
        else if (cur_time <= safe_lock * 10)
            time_balanced_tree += (unsigned long long)cur_time;
        else
            k--;
    }
    tree_free(root);
    res_balanced_tree = time_balanced_tree / cnt;
    printf("Сбалансированное дерево - %lf, высота - %d\n", res_balanced_tree, deep);
    printf("Разность производительности = %.2lf нс\n", fabs(res_balanced_tree - res_time_tree));
    printf("Сортировка в вырожденном дереве дольше на %lf %%\n", fabs(100 - (100 * res_time_tree / res_balanced_tree)));
    printf("\n");

}
