#include "graph.h"
#include "func.h"

int main(void)
{
    char input[MAX_STR_LEN];
    graph_t *graph = malloc(sizeof(graph_t));
    dist_t *dist;
    printf("Обработать графовую структуру в соответствии с указанным вариантом задания. Обосновать выбор необходимого алгоритма и выбор структуры для представления графов.\n");
    printf("Заданы две системы двухсторонних дорог с одним и тем же множеством городов (железные и шоссейные дороги). Найти минимальный по длине путь из города A в город \n");
    printf("B, который может проходить как по железной так и по шоссейной дорогам, и места пересадок с одного вида транспорта на другой на этом пути. \n");
    printf("1  - Инициализировать граф \n");
    printf("2  - Вывести граф в файл \n");
    printf("3  - Вывести граф в консоль\n");
    printf("4  - Найти кратчайшее расстояние\n");
    printf("5 - Вывод доступных опций \n");
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
            if (graph)
                free_graph(graph);
            
            rc = create_graph_matrix(graph);
        }
        else if (current_option == 2)
        {
            if (graph && graph->railroad_matrix && graph->highway_matrix)
            {
                print_graph_dot(graph);
                printf("Вывод успешен \n");
            }
            else 
                printf("Граф не введен \n");
        }
        else if (current_option == 3)
        {
            if (graph && graph->railroad_matrix && graph->highway_matrix)
            {
                print_graph(graph);
            }
            else 
                printf("Граф не введен \n");
        }
        else if (current_option == 4)
        {
            if (graph && graph->railroad_matrix && graph->highway_matrix)
            {
                printf("Введите начальный город (A): ");
                int start, end;
                scanf("%d", &start);
                printf("Введите конечный город (B): ");
                scanf("%d", &end);
                
                dist = (dist_t*)malloc(graph->vertices * sizeof(dist_t));
                dijkstra(graph, start, dist);
                print_path(graph, dist, start, end);
                
                free(dist);
            }
            else 
                printf("Граф не введен \n");
        }
        else if (current_option == 5)
        {
            printf("1  - Инициализировать граф \n");
            printf("2  - Вывести граф в файл \n");
            printf("3  - Вывести граф в консоль\n");
            printf("4  - Найти кратчайшее расстояние\n");
            printf("5 - Вывод доступных опций \n");
            printf("0 - Завершение работы..... \n");
        }
        else if (current_option == 0)
        {
            printf("Завершение работы \n");
            if (graph && graph->railroad_matrix && graph->highway_matrix)
            {
                free_graph(graph);
                free(graph);
            }
            return OK;
        }
        else
            printf("Недопустимая опция, пожалуйста повторите  \n");
        printf("Опция: ");
    }
    if (graph && graph->railroad_matrix && graph->highway_matrix)
    {
        free_graph(graph);
        free(graph);
    }
    printf("Завершение работы \n");
    return OK;
}
