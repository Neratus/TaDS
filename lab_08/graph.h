#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX

#define OFFROAD -1
#define RAILROAD 0 
#define HIGHWAY 1 

#define OK 0
#define ERROR_SIZE_INPUT -3
#define ERROR_SIZE_VALUE -4

#define ERROR_NODE_INPUT -5
#define ERROR_NODE_VALUE -6

typedef struct {
    int distance;
    int prev;
    int type;
} dist_t;

typedef struct {
    int** railroad_matrix;  
    int** highway_matrix; 
    int vertices;          
} graph_t;


void free_graph(graph_t* graph);

int create_graph_matrix(graph_t *graph);

void print_graph(graph_t* graph);

void print_graph_dot(graph_t* graph) ;

void dijkstra(graph_t* graph, int start, dist_t* dist);

void print_path(graph_t *graph, dist_t* dist, int start, int end);

#endif
