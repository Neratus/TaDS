#include "test.h"
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

void test(void)
{
    size_t cnt = 30;
    size_t file_size[] =  {1, 10, 25, 50, 100, 250, 500, 1000};
    size_t file_size_cnt = sizeof(file_size) / sizeof(file_size[0]);

    unsigned long long time_start,time_end;
    unsigned long long safe_lock = 0;

    unsigned long long time_tree = 0;
    int cmp_tree;
    double res_time_tree = 0;

    unsigned long long time_balanced_tree = 0;
    int cmp_balanced_tree;
    double res_time_balanced_tree = 0;

    unsigned long long time_hash = 0;
    int cmp_hash;
    double res_time_hash = 0;

    unsigned long long time_hash_closed = 0;
    int cmp_hash_clos;
    double res_time_hash_closed = 0;

    printf("Замер производительности для удаления на %zu итерациях: \n", cnt);
    printf("УДАЛЕНИЕ : \n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|Количество элементов|Время(дерево)|Память(дерево)|Сравнения(дерево)|Время(сб. дерево)|Память(сб. дерево)|Сравнения(сб. дерево)|Время(хэш-таблица-откр)|Память(таблица-откр)|Сравнения(таблица-откр)|Время(хэш-таблица-закр)|Память(таблица-закр)|Сравнения(таблица-закр)|\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    char *cur_file = (char *)malloc(MAX_STR_LEN * sizeof(char));
    for (size_t i = 0; i < file_size_cnt; i++)
    {  

        int memory_tree = file_size[i] * sizeof(struct tree_node_t);
        int memoryhash = 0;
        int memory_closed = 0;
        char word[MAX_STR_LEN];
        sprintf(cur_file, "/Applications/programms/Types and structures of data - completed/lab_07-completed/example_files/%zuwords.txt", file_size[i]);
        for (size_t j = 0; j < cnt; j++)
        {
            int comp_cnt = 0;
            struct tree_node_t *root = NULL;
            FILE *input_file = fopen(cur_file, "r");
            if (input_file == NULL) 
                return;
            unsigned long long cur_time = 0;
            int file_cnt = 0;
            while (fscanf(input_file, "%s", word) != EOF) 
            {
                root = NULL;
                read_words_from_file(cur_file, &root);
                int cur_cnt = 0;
                find_elem(root, word, &cur_cnt);
                time_start = cur_time_nanosec();
                delete_node(root, word, 1);
                comp_cnt += cur_cnt;
                time_end = cur_time_nanosec();
                cur_time += time_end - time_start;
                file_cnt++;
            }
            fclose(input_file);
            cur_time /= file_cnt;
            comp_cnt /= file_cnt;
            cmp_tree = comp_cnt;
            if (safe_lock == 0)
                safe_lock = cur_time;
            else if ((cur_time) <= safe_lock * 10)
                time_tree += (cur_time);
            else
                j--;
        }
        safe_lock = 0;
        for (size_t j = 0; j < cnt; j++)
        {
            int comp_cnt = 0;
            struct tree_node_t *root = NULL;
            FILE *input_file = fopen(cur_file, "r");
            if (input_file == NULL) 
                return;
            unsigned long long cur_time = 0;
            int file_cnt = 0;
            while (fscanf(input_file, "%s", word) != EOF) 
            {
                read_words_from_file(cur_file, &root);
                int balance_cnt = 0;
                int prev_cnt = 0;
                root = balance_tree(root, &balance_cnt);
                while(balance_cnt != prev_cnt)
                {
                    prev_cnt = balance_cnt;
                    root = balance_tree(root, &balance_cnt);
                }
                int cur_cnt = 0;
                find_elem(root, word, &cur_cnt);
                time_start = cur_time_nanosec();
                delete_node(root, word, 0);
                time_end = cur_time_nanosec();
                comp_cnt += cur_cnt;
                cur_time += time_end - time_start;
                file_cnt++;
            }
            fclose(input_file);
            cur_time /= file_cnt;
            comp_cnt /= file_cnt;
            cmp_balanced_tree = comp_cnt;
            if (safe_lock == 0)
                safe_lock = cur_time;
            else if ((cur_time) <= safe_lock * 10)
                time_balanced_tree += (cur_time);
            else
                j--;
        }
        safe_lock = 0;
        for (size_t j = 0; j < cnt; j++)
        {
            int comp_cnt = 0;
            Hash_table_t *table = malloc(sizeof(Hash_table_t));
            FILE *input_file = fopen(cur_file, "r");
            if (input_file == NULL) 
                return;
            unsigned long long cur_time = 0;
            int file_cnt = 0;
            while (fscanf(input_file, "%s", word) != EOF) 
            {
                init_table_from_file(&table, cur_file);
                int cur_cnt = 0;
                find_node(table, word, &cur_cnt);
                time_start = cur_time_nanosec();
                delete_elem_from_table(table, word);
                time_end = cur_time_nanosec();
                if (cur_cnt >= comp_cnt)
                    comp_cnt = cur_cnt;
                cur_time += time_end - time_start;
                file_cnt++;
            }
            cur_time /= file_cnt;
            cmp_hash = comp_cnt;
            memoryhash = table->table_size * sizeof(Hash_node_t*) +  file_size[i] * sizeof(Hash_node_t);
            free_table(table);
            fclose(input_file);
            if (safe_lock == 0)
                safe_lock = cur_time;
            else if ((cur_time) <= safe_lock * 10)
                time_hash += (cur_time);
            else
                j--;
        }
        safe_lock = 0;
        for (size_t j = 0; j < cnt; j++)
        {
            int comp_cnt = 0;
            Hash_closed_table_t *table = malloc(sizeof(Hash_closed_table_t));
            FILE *input_file = fopen(cur_file, "r");
            if (input_file == NULL) 
                return;
            unsigned long long cur_time = 0;
            int file_cnt = 0;
            while (fscanf(input_file, "%s", word) != EOF) 
            {
                init_closed_table_from_file(&table, cur_file);
                int cur_cnt = 0;
                find_closed_node(table, word, &cur_cnt);
                time_start = cur_time_nanosec();
                delete_elem_from_closed_table(table, word);
                time_end = cur_time_nanosec();
                if (cur_cnt >= comp_cnt)
                    comp_cnt = cur_cnt;
                cur_time += time_end - time_start;
                file_cnt++;
            }
            cur_time /= file_cnt;
            cmp_hash_clos = comp_cnt;
            memory_closed = table->table_size * sizeof(Hash_closed_node_t*) +  file_size[i] * sizeof(Hash_closed_node_t);
            free_closed_table(table);
            fclose(input_file);
            if (safe_lock == 0)
                safe_lock = cur_time;
            else if ((cur_time) <= safe_lock * 10)
                time_hash_closed += (cur_time);
            else
                j--;
        }
        safe_lock = 0;
        res_time_tree = time_tree / cnt;
        res_time_balanced_tree = time_balanced_tree / cnt;
        res_time_hash = time_hash / cnt;
        res_time_hash_closed = time_hash_closed / cnt;
        printf("\t%5zu\t     |  %6lf  | %6d       |   %6d\t    |    %6lf    |     %6d       |      %6d         |       %6lf       |      %6d\t    |        %6d         |       %6lf       |      %6d\t |        %6d        |\n",file_size[i],res_time_tree, memory_tree, cmp_tree, res_time_balanced_tree, memory_tree, cmp_balanced_tree, res_time_hash, memoryhash, cmp_hash, res_time_hash_closed, memory_closed,cmp_hash_clos);
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        time_hash = 0;
        time_tree = 0;
        time_balanced_tree = 0;
        time_hash_closed = 0;
        sprintf(cur_file, "/Applications/programms/Types and structures of data - completed/lab_07-completed/example_files/%zu_sorted_words.txt", file_size[i]);
        for (size_t j = 0; j < cnt; j++)
        {
            int comp_cnt = 0;
            struct tree_node_t *root = NULL;
            FILE *input_file = fopen(cur_file, "r");
            if (input_file == NULL) 
                return;
            unsigned long long cur_time = 0;
            int file_cnt = 0;
            while (fscanf(input_file, "%s", word) != EOF) 
            {
                root = NULL;
                read_words_from_file(cur_file, &root);
                int cur_cnt = 0;
                find_elem(root, word, &cur_cnt);
                time_start = cur_time_nanosec();
                delete_node(root, word, 1);
                comp_cnt += cur_cnt;
                time_end = cur_time_nanosec();
                cur_time += time_end - time_start;
                file_cnt++;
            }
            fclose(input_file);
            cur_time /= file_cnt;
            comp_cnt /= file_cnt;
            cmp_tree = comp_cnt;
            if (safe_lock == 0)
                safe_lock = cur_time;
            else if ((cur_time) <= safe_lock * 10)
                time_tree += (cur_time);
            else
                j--;
        }
        safe_lock = 0;
        for (size_t j = 0; j < cnt; j++)
        {
            int comp_cnt = 0;
            struct tree_node_t *root = NULL;
            FILE *input_file = fopen(cur_file, "r");
            if (input_file == NULL) 
                return;
            unsigned long long cur_time = 0;
            int file_cnt = 0;
            while (fscanf(input_file, "%s", word) != EOF) 
            {
                read_words_from_file(cur_file, &root);
                int balance_cnt = 0;
                int prev_cnt = 0;
                root = balance_tree(root, &balance_cnt);
                while(balance_cnt != prev_cnt)
                {
                    prev_cnt = balance_cnt;
                    root = balance_tree(root, &balance_cnt);
                }
                int cur_cnt = 0;
                find_elem(root, word, &cur_cnt);
                time_start = cur_time_nanosec();
                delete_node(root, word, 0);
                time_end = cur_time_nanosec();
                comp_cnt += cur_cnt;
                cur_time += time_end - time_start;
                file_cnt++;
            }
            fclose(input_file);
            cur_time /= file_cnt;
            comp_cnt /= file_cnt;
            cmp_balanced_tree = comp_cnt;
            if (safe_lock == 0)
                safe_lock = cur_time;
            else if ((cur_time) <= safe_lock * 10)
                time_balanced_tree += (cur_time);
            else
                j--;
        }
        safe_lock = 0;
        for (size_t j = 0; j < cnt; j++)
        {
            int comp_cnt = 0;
            Hash_table_t *table = malloc(sizeof(Hash_table_t));
            FILE *input_file = fopen(cur_file, "r");
            if (input_file == NULL) 
                return;
            unsigned long long cur_time = 0;
            int file_cnt = 0;
            while (fscanf(input_file, "%s", word) != EOF) 
            {
                init_table_from_file(&table, cur_file);
                int cur_cnt = 0;
                find_node(table, word, &comp_cnt);
                time_start = cur_time_nanosec();
                delete_elem_from_table(table, word);
                time_end = cur_time_nanosec();
                comp_cnt += cur_cnt;
                cur_time += time_end - time_start;
                file_cnt++;
            }
            cur_time /= file_cnt;
            comp_cnt /= file_cnt;
            cmp_hash = comp_cnt;
            memoryhash = table->table_size * sizeof(Hash_node_t*) +  file_size[i] * sizeof(Hash_node_t);
            free_table(table);
            fclose(input_file);
            if (safe_lock == 0)
                safe_lock = cur_time;
            else if ((cur_time) <= safe_lock * 10)
                time_hash += (cur_time);
            else
                j--;
        }
        safe_lock = 0;
        for (size_t j = 0; j < cnt; j++)
        {
            int comp_cnt = 0;
            Hash_closed_table_t *table = malloc(sizeof(Hash_closed_table_t));
            FILE *input_file = fopen(cur_file, "r");
            if (input_file == NULL) 
                return;
            unsigned long long cur_time = 0;
            int file_cnt = 0;
            while (fscanf(input_file, "%s", word) != EOF) 
            {
                init_closed_table_from_file(&table, cur_file);
                int cur_cnt = 0;
                find_closed_node(table, word, &comp_cnt);
                time_start = cur_time_nanosec();
                delete_elem_from_closed_table(table, word);
                time_end = cur_time_nanosec();
                comp_cnt += cur_cnt;
                cur_time += time_end - time_start;
                file_cnt++;
            }
            cur_time /= file_cnt;
            comp_cnt /= file_cnt;
            cmp_hash_clos = comp_cnt;
            memory_closed = table->table_size * sizeof(Hash_closed_node_t*) +  file_size[i] * sizeof(Hash_closed_node_t);
            free_closed_table(table);
            fclose(input_file);
            if (safe_lock == 0)
                safe_lock = cur_time;
            else if ((cur_time) <= safe_lock * 10)
                time_hash_closed += (cur_time);
            else
                j--;
        }
        safe_lock = 0;
        res_time_tree = time_tree / cnt;
        res_time_balanced_tree = (unsigned long)time_balanced_tree / cnt;
        res_time_hash = time_hash / cnt;
        res_time_hash_closed = time_hash_closed / cnt;
        printf("\tSorted: %5zu|  %6lf  | %6d       |   %6d\t    |    %6lf    |     %6d       |      %6d         |       %6lf       |      %6d\t    |        %6d         |       %6lf       |      %6d\t |        %6d        |\n",file_size[i],res_time_tree, memory_tree, cmp_tree, res_time_balanced_tree, memory_tree, cmp_balanced_tree, res_time_hash, memoryhash, cmp_hash, res_time_hash_closed, memory_closed,cmp_hash_clos);
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    }
}
