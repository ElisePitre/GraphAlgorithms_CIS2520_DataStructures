/* Name: Elise Pitre
Student ID: 1267817
Date: Dec 1 2024
Assignment name: CIS*2520 — Assignment #4 */

// Libraries Used Add more here if needed

#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

// Define maximum number of vertices in the graph
#define MAX_VERTICES 100

// Structure representing a node in an adjacency list
typedef struct Node{
    int vertex;
    struct Node *next;
} Node;

// Structure representing a graph
typedef struct Graph{
    int numVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    Node *adjList[MAX_VERTICES];
} Graph;

// Function definitions
void prompt(void);
Graph *readGraph(const char *filename);
Node *createNode(int vertex);
void displayAdjacencyList(Graph *graph);
void createAdjacencyList(Graph *graph);
void bfs(Graph *graph, int startVertex);
void dfs(Graph *graph, int startVertex);
void dijkstra(Graph *graph, int startVertex);
void freeGraph(Graph *graph);
bool inArray(int *arr, int length, int value);

#endif // GRAPH_H
