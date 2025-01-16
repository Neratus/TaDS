#include "tree.h"
#include "test_tree.h"
#include <stdlib.h>


int main(void)
{
    char input[MAX_STR_LEN];
    struct tree_node_t *root = NULL;
    struct tree_node_t *node;
    int cmp = 0;
    printf("Построить дерево в соответствии со своим вариантом задания. Вывести его на экран в виде дерева.\n");
    printf("Реализовать основные операции работы с деревом: обход дерева, включение, исключение и поиск узлов. \n");
    printf("Сравнить эффективность алгоритмов сортировки и поиска в зависимости от высоты деревьев и степени их ветвления.\n");
    printf("Построить бинарное дерево поиска, в вершинах которого находятся слова из текстового файла(предполагается, что исходный файл не содержит повторяющихся слов). \n");
    printf("Вывести его на экран в виде дерева. Удалить все слова, начинающиеся на указанную букву. Сравнить время удаления слов, начинающихся на указанную букву, в дереве и в файле.\n");
    printf("Выберите опцию:\n");
    printf("ДЕРЕВО: \n");
    printf("\t1  - Инициализировать дерево из файла \n");
    printf("\t2  - Добавить строку в дерево \n");
    printf("\t3  - Удалить строку из дерева \n");
    printf("\t4  - Вывести дерево в файл show.dot\n");
    printf("\t5  - Найти и удалить слова, начинающиеся на заданную букву \n");
    printf("\t6  - Найти узел \n");
    printf("\t7  - in-order обход \n");
    printf("8 - Замер производительности \n");
    printf("9 - Вывод доступных опций \n");
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
                    root = delete_node(root, str);    
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
            test_tree();
        else if (current_option == 9)
        {
            printf("ДЕРЕВО: \n");
            printf("\t1  - Инициализировать дерево из файла \n");
            printf("\t2  - Добавить строку в дерево \n");
            printf("\t3  - Удалить строку из дерева \n");
            printf("\t4  - Вывести дерево в файл show.dot\n");
            printf("\t5  - Найти и вывести слова, начинающиеся на заданную букву \n");
            printf("\t6  - Найти узел \n");
            printf("\t7  - Обход в глубину \n");
            printf("8 - Замер производительности \n");
            printf("9 - Вывод доступных опций \n");
            printf("0 - Завершение работы..... \n");
        }
        else if (current_option == 0)
        {
            printf("Завершение работы \n");
            if (root != NULL)
                tree_free(root);
            return OK;
        }
        else
            printf("Недопустимая опция, пожалуйста повторите  \n");
        printf("Опция: ");
    }
    if (root != NULL)
        tree_free(root);
    printf("Завершение работы \n");
    return OK;
}
