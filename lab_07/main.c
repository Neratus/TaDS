#include "tree.h"
#include "test.h"
#include "hash.h"
#include "hash_closed.h"
#include <stdlib.h>


int main(void)
{
    char input[MAX_STR_LEN];
    struct tree_node_t *root = NULL;
    struct tree_node_t *node;
    Hash_table_t *table = malloc(sizeof(Hash_table_t));
    Hash_closed_table_t *table_close = malloc(sizeof(Hash_closed_table_t));
    init_hash_table(table, 47);
    init_closed_hash_table(table_close, 47);
    printf("Построить дерево в соответствии со своим вариантом задания. Вывести его на экран в виде дерева.\n");
    printf("Реализовать основные операции работы с деревом: обход дерева, включение, исключение и поиск узлов. \n");
    printf("Сравнить эффективность алгоритмов сортировки и поиска в зависимости от высоты деревьев и степени их ветвления.\n");
    printf("Построить бинарное дерево поиска, в вершинах которого находятся слова из текстового файла(предполагается, что исходный файл не содержит повторяющихся слов). \n");
    printf("Вывести его на экран в виде дерева. Удалить все слова, начинающиеся на указанную букву. Сравнить время удаления слов, начинающихся на указанную букву, в дереве и в файле.\n");
    printf("Cбалансировать полученное дерево. Вывести его на экран в виде дерева. Построить хеш-таблицу из слов текстового файла. \n");
    printf("Вывести построенную таблицу слов на экран. Осуществить поиск и удаление введенного слова. \n");
    printf("Выполнить программу для различных размерностей таблицы и сравнить время удаления, объем памяти и количество сравнений при использовании сбалансированных деревьев и хеш-таблиц.\n");
    printf("Выберите опцию:\n");
    printf("ДЕРЕВО: \n");
    printf("\t1  - Инициализировать дерево из файла \n");
    printf("\t2  - Добавить строку в дерево \n");
    printf("\t3  - Удалить строку из дерева \n");
    printf("\t4  - Вывести дерево в файл show.dot\n");
    printf("\t5  - Найти и удалить слова, начинающиеся на заданную букву \n");
    printf("\t6  - Найти узел \n");
    printf("\t7  - in-order обход \n");
    printf("\t8  - Сбалансировать дерево \n");
    printf("ХЭШ-ТАБЛИЦА: ОТКРЫТАЯ АДРЕСАЦИЯ\n");
    printf("\t9  - Инициализировать таблицу из файла\n");
    printf("\t10 - Найти строку в таблице \n");
    printf("\t11 - Добавить строку в таблицу \n");
    printf("\t12 - Удалить строку из таблицы \n");
    printf("\t13 - Найти и удалить слова, начинающиеся на заданную букву\n");
    printf("\t14 - Вывести хэш-таблицу \n");
    printf("ХЭШ-ТАБЛИЦА: ЗАКРЫТАЯ АДРЕСАЦИЯ\n");
    printf("\t15  - Инициализировать таблицу из файла\n");
    printf("\t16 - Найти строку в таблице \n");
    printf("\t17 - Добавить строку в таблицу \n");
    printf("\t18 - Удалить строку из таблицы \n");
    printf("\t19 - Найти и удалить слова, начинающиеся на заданную букву\n");
    printf("\t20 - Вывести хэш-таблицу \n");
    printf("21 - Замер производительности \n");
    printf("22 - Вывод доступных опций \n");
    printf("0 - Завершение работы..... \n");
    printf("Опция: ");
    int current_option = 1;
    while(current_option != 0)
    {
        rewind(stdin);
        int rc = read_line(input, MAX_STR_LEN, stdin);
        char *end;
        current_option = strtol(input, &end, 10);
        if ((rc != OK) || (input == end))
        {
            rewind(stdin);
            current_option = -1;
        }
        if (current_option == 1)
        {
            printf("Введите название файла: \n");
            char file[MAX_STR_LEN];
            int rc = read_line(file, MAX_STR_LEN, stdin);
            if (rc != OK)
                printf("ERROR: Ошибка чтения строки");
            if (root) 
                tree_free(root);
            root = NULL;
            read_words_from_file(file, &root);
            if (root == NULL)
                printf("ERROR:Не удалось считать слова из файла или файл пуст \n");
            else
                printf("Инициализация успешна \n");
        }
        else if (current_option == 2)
        {
            printf("Введите строку для добавления: \n");
            char str[MAX_STR_LEN];
            int rc = read_line(str, MAX_STR_LEN, stdin);
            if (rc != OK)
                printf("ERROR: Ошибка чтения строки");
            else
            {
                node = create_node(str);
                int cmp = 0;
                if (node == NULL)
                    printf("ERROR: Ошибка добавления\n");
                else if (find_elem(root, node->name, &cmp) == NULL)
                {
                    struct tree_node_t *new_node = insert_node(root, node);
                    if (new_node != NULL)
                    {
                        printf("Добавление успешно \n");
                        root = new_node;  
                    }
                    else 
                        printf("ERROR: Эта строка уже есть в таблице\n");
                }
                else 
                    printf("ERROR: Эта строка уже есть в таблице\n");
           }
        }
        else if (current_option == 3)
        {
            if (root == NULL)
                printf("ERROR: удаление из пустого дерева,повторите попытку\n");
            else
            {
                printf("Введите строку для удаления: \n");
                char str[MAX_STR_LEN];
                int rc = read_line(str, MAX_STR_LEN, stdin);
                if (rc != OK)
                    printf("ERROR: Ошибка чтения строки");
                else
                {
                    root = delete_node(root, str, 1);    
                    printf("Удаление успешно \n");
                }   
            }      
        }
        else if (current_option == 4)
        {
            FILE *f = fopen("show.dot","w");
            if (f == NULL)
                printf("ERROR: не удалось открыть файл");
            tree_export_to_dot(f, "tree", root);
            printf("Вывод успешен \n");
            fclose(f);
        }
        else if (current_option == 5)
        {
            printf("Введите символ: ");
            char ch = getchar();
            if (ch != EOF)
            {
                int comp_cnt = 0;
                get_cmp_cnt(&root, ch, &comp_cnt);
                delete_words_starting_with(&root, ch);
                printf("Записи удалены успешно, количество сравнений равно %d\n",comp_cnt);
            }
            else
                printf("Ошибка чтения \n"); 
        }
        else if (current_option == 6)
        {
            printf("Введите строку для поиска: \n");
            char str[MAX_STR_LEN];
            int rc = read_line(str, MAX_STR_LEN, stdin);
            if (rc != OK)
                printf("ERROR: Ошибка чтения строки");
            else
            {
                int cmp = 0;
                node = find_elem(root, str, &cmp);
                if (node == NULL)
                    printf("Узел не найден \n");
                else
                {
                    printf("Узел со строкой %s найден \n", str);
                    printf("Вывод узла в файл node.dot\n");
                    FILE *f = fopen("node.dot","w");
                    if (f == NULL)
                        printf("ERROR: не удалось открыть файл");
                    tree_export_to_dot(f, "tree", node);
                    printf("Вывод успешен \n");
                    fclose(f);
                }
            }
        }
        else if (current_option == 7)
            in_order(root);
        else if (current_option == 8)
        {
            int balance_cnt = 0;
            int prev_cnt = 0;
            root = balance_tree(root, &balance_cnt);
            while(balance_cnt != prev_cnt)
            {
                prev_cnt = balance_cnt;
                root = balance_tree(root, &balance_cnt);
            }
            printf("Балансировка завершена, количество вращений %d \n", balance_cnt);
        }
        else if (current_option == 9)
        {
            printf("Введите название файла: \n");
            char file[MAX_STR_LEN];
            int rc = read_line(file, MAX_STR_LEN, stdin);
            if (rc != OK)
                printf("ERROR: Ошибка чтения строки");
            else
            {
                rc = init_table_from_file(&table, file);
                if (rc != OK)
                    printf("ERROR:Не удалось считать слова из файла или файл пуст \n");
                else
                    printf("Инициализация успешна \n");
            }
        }
        else if (current_option == 10)
        {
            if (table->keysCount == 0)
                printf("ERROR: поиск в пустом хэше,повторите попытку\n");
            else
            {
                printf("Введите строку для поиска: \n");
                char str[MAX_STR_LEN];
                int rc = read_line(str, MAX_STR_LEN, stdin);
                if (rc != OK)
                    printf("ERROR: Ошибка чтения строки");
                else
                {   
                    int cmp = 0;
                    Hash_node_t *node = find_node(table, str, &cmp);
                    if (node == NULL)
                        printf("ERROR: Такого элемента в таблице нет \n");   
                    else
                        printf("Элемент найден за %d сравнений, Адрес: %p \n", cmp,(void *) node);
                }   
            }
        }      
        else if (current_option == 11)
        {
            printf("Введите строку для добавления: \n");
            char str[MAX_STR_LEN];
            int rc = read_line(str, MAX_STR_LEN, stdin);
            if (rc != OK)
                printf("ERROR: Ошибка чтения строки");
            else
            {
                rc = add_elem_to_table(&table, str);
                if (rc != OK)
                    printf("ERROR: Эта строка уже есть в таблице\n");
                else
                    printf("Добавление успешно \n");
           }
        }
        else if (current_option == 12)
        {
            if (table->keysCount == 0)
                printf("ERROR: удаление из пустого хэша,повторите попытку\n");
            else
            {
                printf("Введите строку для удаления: \n");
                char str[MAX_STR_LEN];
                int rc = read_line(str, MAX_STR_LEN, stdin);
                if (rc != OK)
                    printf("ERROR: Ошибка чтения строки");
                else
                {   
                    rc = delete_elem_from_table(table, str);
                    if (rc != OK)
                        printf("ERROR: Такого элемента в таблице нет \n");   
                    else
                        printf("Удаление успешно \n");
                }   
            }      
        }
        else if (current_option == 13)
        {
            if (table->keysCount == 0)
                printf("ERROR: удаление в пустом хэше,повторите попытку\n");
            else
            {
                printf("Введите символ: ");
                char ch = getchar();
                if (ch != EOF)
                {
                    int comp_cnt = 0;
                    hash_delete_words_starting_with(table, ch, &comp_cnt);
                    printf("Записи удалены успешно, количество сравнений равно %d\n",comp_cnt);
                }
                else
                    printf("Ошибка чтения \n"); 
            }
        }     
        else if (current_option == 14)
            print_hash_table(table);
        else if (current_option == 15)
        {
            printf("Введите название файла: \n");
            char file[MAX_STR_LEN];
            int rc = read_line(file, MAX_STR_LEN, stdin);
            if (rc != OK)
                printf("ERROR: Ошибка чтения строки");
            else
            {
                rc = init_closed_table_from_file(&table_close, file);
                if (rc != OK)
                    printf("ERROR:Не удалось считать слова из файла или файл пуст \n");
                else
                    printf("Инициализация успешна \n");
            }
        }
        else if (current_option == 16)
        {
            if (table_close->keysCount == 0)
                printf("ERROR: поиск в пустом хэше,повторите попытку\n");
            else
            {
                printf("Введите строку для поиска: \n");
                char str[MAX_STR_LEN];
                int rc = read_line(str, MAX_STR_LEN, stdin);
                if (rc != OK)
                    printf("ERROR: Ошибка чтения строки");
                else
                {   
                    int cmp = 0;
                    Hash_closed_node_t *node = find_closed_node(table_close, str, &cmp);
                    if (node == NULL)
                        printf("ERROR: Такого элемента в таблице нет \n");   
                    else
                        printf("Элемент найден за %d сравнений, Адрес: %p \n", cmp,(void *) node);
                }   
            }
        }      
        else if (current_option == 17)
        {
            printf("Введите строку для добавления: \n");
            char str[MAX_STR_LEN];
            int rc = read_line(str, MAX_STR_LEN, stdin);
            if (rc != OK)
                printf("ERROR: Ошибка чтения строки");
            else
            {
                rc = add_elem_to_closed_table(&table_close, str);
                if (rc != OK)
                    printf("ERROR: Эта строка уже есть в таблице\n");
                else
                    printf("Добавление успешно \n");
           }
        }
        else if (current_option == 18)
        {
            if (table_close->keysCount == 0)
                printf("ERROR: удаление из пустого хэша,повторите попытку\n");
            else
            {
                printf("Введите строку для удаления: \n");
                char str[MAX_STR_LEN];
                int rc = read_line(str, MAX_STR_LEN, stdin);
                if (rc != OK)
                    printf("ERROR: Ошибка чтения строки");
                else
                {   
                    rc = delete_elem_from_closed_table(table_close, str);
                    if (rc != OK)
                        printf("ERROR: Такого элемента в таблице нет \n");   
                    else
                        printf("Удаление успешно \n");
                }   
            }      
        }
        else if (current_option == 19)
        {
            if (table_close->keysCount == 0)
                printf("ERROR: удаление в пустом хэше,повторите попытку\n");
            else 
            {
                printf("Введите символ: ");
                char ch = getchar();
                if (ch != EOF)
                {
                    int comp_cnt = 0;
                    closed_hash_delete_words_starting_with(table_close, ch, &comp_cnt);
                    printf("Записи удалены успешно, количество сравнений равно %d\n",comp_cnt);
                }
                else
                    printf("Ошибка чтения \n"); 
            }
        }     
        else if (current_option == 20)
            print_closed_hash_table(table_close);
        else if (current_option == 21)
            test();
        else if (current_option == 22)
        {
            printf("ДЕРЕВО: \n");
            printf("\t1  - Инициализировать дерево из файла \n");
            printf("\t2  - Добавить строку в дерево \n");
            printf("\t3  - Удалить строку из дерева \n");
            printf("\t4  - Вывести дерево в файл show.dot\n");
            printf("\t5  - Найти и удалить слова, начинающиеся на заданную букву \n");
            printf("\t6  - Найти узел \n");
            printf("\t7  - in-order обход \n");
            printf("\t8  - Сбалансировать дерево \n");
            printf("ХЭШ-ТАБЛИЦА: \n");
            printf("\t9  - Инициализировать таблицу из файла\n");
            printf("\t10 - Найти строку в таблице \n");
            printf("\t11 - Добавить строку в таблицу \n");
            printf("\t12 - Удалить строку из таблицы \n");
            printf("\t13 - Найти и удалить слова, начинающиеся на заданную букву\n");
            printf("\t14 - Вывести хэш-таблицу \n");
            printf("ХЭШ-ТАБЛИЦА: ЗАКРЫТАЯ АДРЕСАЦИЯ\n");
            printf("\t15  - Инициализировать таблицу из файла\n");
            printf("\t16 - Найти строку в таблице \n");
            printf("\t17 - Добавить строку в таблицу \n");
            printf("\t18 - Удалить строку из таблицы \n");
            printf("\t19 - Найти и удалить слова, начинающиеся на заданную букву\n");
            printf("\t20 - Вывести хэш-таблицу \n");
            printf("21 - Замер производительности \n");
            printf("22 - Вывод доступных опций \n");
            printf("0 - Завершение работы..... \n");
        }
        else if (current_option == 0)
        {
            printf("Завершение работы \n");
            if (root != NULL)
                tree_free(root);
            free_table(table);
            return OK;
        }
        else
            printf("Недопустимая опция, пожалуйста повторите  \n");
        printf("Опция: ");
    }
    if (root != NULL)
        tree_free(root);
    free_table(table);
    printf("Завершение работы \n");
    return OK;
}
