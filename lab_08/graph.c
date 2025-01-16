#include "graph.h"

void free_graph(graph_t* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        free(graph->railroad_matrix[i]);
        free(graph->highway_matrix[i]);
    }
    free(graph->railroad_matrix);
    free(graph->highway_matrix);
}


int create_graph_matrix(graph_t* graph) {
    printf("Введите количество вершин: ");
    int vertices;
    if (scanf("%d", &vertices) != 1) {
        printf("Ошибка ввода количества вершин\n");
        return -1;
    }
    if (vertices <= 0) {
        printf("Количество вершин не может быть меньше или равно нулю\n");
        return -1;
    }
    
    graph->vertices = vertices;
    
    graph->railroad_matrix = (int**)malloc(vertices * sizeof(int*));
    graph->highway_matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->railroad_matrix[i] = (int*)malloc(vertices * sizeof(int));
        graph->highway_matrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->railroad_matrix[i][j] = INF;  
            graph->highway_matrix[i][j] = INF;  
        }
    }

    printf("Ввод железных дорог: \n");
    for (int i = 0; i < graph->vertices - 1; i++) {
        printf("Введите количество железных дорог для вершины %d: ", i);
        int cnt;
        if (scanf("%d", &cnt) != 1) {
            printf("Ошибка ввода количества дорог\n");
            return -1;
        }
        if (cnt < 0) {
            printf("Количество дорог не может быть меньше нуля\n");
            return -1;
        }
        for (int j = 0; j < cnt; j++) {
            printf("Введите соединение (Вершина, Длина_дороги_туда, Длина_дороги_обратно): ");
            int node, weight, second_weight;
            if (scanf("%d %d %d", &node, &weight, &second_weight) != 3)
                return -1;
            if (node < 0 || node >= graph->vertices || weight <= 0 || second_weight <= 0)
                return -1;
            if (node == i)
                printf("ERROR ");
            else 
            {
                graph->railroad_matrix[i][node] = weight;
                graph->railroad_matrix[node][i] = second_weight; 
            } 
        }
    }

    printf("Ввод шоссейных дорог: \n");
    for (int i = 0; i < graph->vertices - 1; i++) {
        printf("Введите количество шоссейных дорог для вершины %d: ", i);
        int cnt;
        if (scanf("%d", &cnt) != 1) {
            printf("Ошибка ввода количества дорог\n");
            return -1;
        }
        if (cnt < 0) {
            printf("Количество дорог не может быть меньше нуля\n");
            return -1;
        }
        for (int j = 0; j < cnt; j++) {
            printf("Введите соединение (Вершина, Длина_дороги_туда, Длина_дороги_обратно): ");
            int node, weight, second_weight;
            if (scanf("%d %d %d", &node, &weight, &second_weight) != 3)
                return -1;
            if (node < 0 || node >= graph->vertices || weight <= 0 || second_weight <= 0 || node == i)
                return -1;
            graph->highway_matrix[i][node] = weight;
            graph->highway_matrix[node][i] = second_weight; 
        }
    }

    printf("Ввод успешен\n");
    return 0;
}


void print_graph(graph_t* graph) {
    printf("Граф:\n");

    printf("Железные дороги (матрица смежности):\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->railroad_matrix[i][j] != INF) {
                printf("Вершина %d -> Вершина %d: %d\n", i + 1, j + 1, graph->railroad_matrix[i][j]);
            }
        }
    }

    printf("Шоссейные дороги (матрица смежности):\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->highway_matrix[i][j] != INF) {
                printf("Вершина %d -> Вершина %d: %d\n", i + 1, j + 1, graph->highway_matrix[i][j]);
            }
        }
    }
}


void print_graph_dot(graph_t* graph) 
{
    FILE* file = fopen("show.dot", "w");
    if (!file) 
    {
        printf("Ошибка при открытии файла для записи\n");
        return;
    }

    fprintf(file, "digraph G {\n");

    bool* has_edges = (bool*)malloc(graph->vertices * sizeof(bool));
    for (int i = 0; i < graph->vertices; i++) 
    {
        has_edges[i] = false;
    }

    for (int i = 0; i < graph->vertices; i++) 
    {
        for (int j = 0; j < graph->vertices; j++) 
        {
            if (graph->railroad_matrix[i][j] != INF) 
            {
                fprintf(file, "  %d -> %d [label=\"%d\" color=blue];\n", i, j, graph->railroad_matrix[i][j]);
                has_edges[i] = true; 
            }
        }
    }

    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->highway_matrix[i][j] != INF) 
            {
                fprintf(file, "  %d -> %d [label=\"%d\" color=red];\n", i, j, graph->highway_matrix[i][j]);
                has_edges[i] = true; 
            }
        }
    }

    for (int i = 0; i < graph->vertices; i++) 
    {
        if (!has_edges[i]) 
            fprintf(file, "  %d [label=\"%d\" style=dashed color=gray];\n", i, i);
    }

    fprintf(file, "}\n");

    free(has_edges);
    fclose(file);
}


void dijkstra(graph_t* graph, int start, dist_t* dist) 
{
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = false;
        dist[i].prev = -1;
        if ((graph->railroad_matrix[start][i] != INF) || (graph->highway_matrix[start][i] != INF))
        {
            if ((graph->railroad_matrix[start][i] >= graph->highway_matrix[start][i]) || (graph->railroad_matrix[start][i] == INF))
            {
                dist[i].distance = graph->highway_matrix[start][i];
                dist[i].type = HIGHWAY;
            }
            else if ((graph->railroad_matrix[start][i] < graph->highway_matrix[start][i]) || (graph->highway_matrix[start][i] == INF))
            {
                dist[i].distance = graph->railroad_matrix[start][i];
                dist[i].type = RAILROAD;
            }
        }
        else 
        {
            dist[i].distance = INF;
            dist[i].type = OFFROAD;
        }
    }

    dist[start].distance = 0;

    int index = 0;
    int u = 0;
    for (int i = 0; i < graph->vertices; i++) {
        int min_dist = INF;

        for (int j = 0; j < graph->vertices; j++) {
            if (!visited[j] && dist[j].distance < min_dist) 
            {
                min_dist = dist[j].distance;
                index = j;
            }
        }
        u = index;

        visited[u] = true;

        for (int v = 0; v < graph->vertices; v++) 
        {
            int type;
            int weight;
            if (graph->railroad_matrix[u][v] >=  graph->highway_matrix[u][v])
            {
                type = HIGHWAY;
                weight = graph->highway_matrix[u][v];
            }
            else
            {
                type = RAILROAD;
                weight = graph->railroad_matrix[u][v];
            }

            if (!visited[v] && weight != INF && dist[u].distance != INF && dist[u].distance + weight <= dist[v].distance) 
            {
                dist[v].distance = dist[u].distance + weight;
                dist[v].prev = u;

                dist[v].type = type;
            }
        }
    }
    free(visited);
}


void print_path(graph_t* graph, dist_t* dist, int start, int end) {
    if (dist[end].distance == INF) 
    {
        printf("Нет пути\n");
        return;
    }

    printf("Длина пути из пункта %d в пункт %d равен %d \n", start, end, dist[end].distance);
    int* path = (int*)malloc(graph->vertices * sizeof(int));
    int path_size = 0;

    int v = end;
    while (v != start) {
        if (v < 0 || v >= graph->vertices) 
        {
            printf("Ошибка: неверный индекс узла %d\n", v);
            free(path);
            return;
        }
        path[path_size++] = v;

        if ((dist[v].prev == -1) && (v != start))
         {
            printf("Ошибка: нет предшественника для узла %d\n", v);
            free(path);
            return;
        }
        
        v = dist[v].prev;
    }

    path[path_size++] = start;

    printf("Путь: ");
    for (int i = path_size - 1; i >= 0; i--)
    {
        if (path[i]!= -1)
            printf("%d ", path[i]);
    }

    printf("\n");

    printf("Места пересадок: ");
    for (int i = path_size - 1; i > 0; i--) 
    {
        if ((dist[path[i]].type != dist[path[i - 1]].type) && (path[i] != start))
            printf("%d ", path[i]);
    }
    printf("\n");

    free(path);
}
