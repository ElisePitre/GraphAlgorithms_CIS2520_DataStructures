/* Name: Elise Pitre
Student ID: 1267817
Date: Dec 1 2024
Assignment name: CIS*2520 — Assignment #4*/

#include "graph.h"

/* function will display the primary user interface
    This is already done for you*/
void prompt(void)
{

    printf("\nMenu:\n");
    printf("1. Display Adjacency List\n");
    printf("2. Perform Breadth-First Search (BFS)\n");
    printf("3. Perform Depth-First Search (DFS)\n");
    printf("4. Find Shortest Path using Dijkstra's Algorithm\n");
    printf("5. Exit\n");
}

/**
 * Reads a graph from a file and constructs the graph structure.
 * @param filename The name of the file containing the adjacency matrix.
 * @return Pointer to the created Graph structure, or NULL if an error occurs.
 */
Graph *readGraph(const char *filename){
    char line[10000];
    int currentNum;
    int row = 0;
    int column;
    Graph *new_graph;
    new_graph = malloc(sizeof(Graph));
    new_graph->numVertices = 0;
    char * linePtr;

    FILE *fp;
	fp = fopen(filename, "r");

	// If the file does not exist
	if(fp == NULL){
		printf("Error: the file does not exist!\n");
		return NULL;
	}

    //Read information from the file
    while(!feof(fp)){
        while(fgets(line, 10000, fp) != NULL){
            column = 0;
            linePtr = line;
            while(sscanf(linePtr, "%d", &currentNum) != EOF){
                //Set linePtr to next non-blank value
                linePtr++;
                while(*linePtr != ' ' && *linePtr != '\0'){
                    linePtr++;
                }

                new_graph->adjMatrix[row][column] = currentNum;

                column++;
            }
            new_graph->numVertices++;
            //Increase row count
            row++;

       }
    }

    createAdjacencyList(new_graph);

    return new_graph;
}

/**
 * Creates a new node for the adjacency list.
 * @param vertex The vertex number that this node will represent.
 * @return Pointer to the newly created Node structure.
 */
Node *createNode(int vertex){
    Node *new_node;
    new_node = malloc(sizeof(Node));
    new_node->vertex = vertex;
    new_node->next = NULL;

    return new_node;
}

/**
 * Displays the adjacency list of the graph.
 * @param graph Pointer to the Graph structure.
 */
void displayAdjacencyList(Graph *graph){
    printf("Adjacency List:\n");
    Node *nodePtr;

    //Go through all of the adjacency lists
    for(int i=0; i<graph->numVertices; i++){
        printf("Vertex %d:", i+1);
        nodePtr = graph->adjList[i];
        while(nodePtr != NULL){
            printf(" -> %d (%d)", nodePtr->vertex, graph->adjMatrix[i][(nodePtr->vertex) - 1]);
            nodePtr = nodePtr->next;
        }
        printf(" NULL\n");
    }
}

/**
 * Converts the adjacency matrix of the graph to an adjacency list.
 * @param graph Pointer to the Graph structure.
 */
void createAdjacencyList(Graph *graph){
    Node *last_node;
    Node *new_node;

    //Every row in the matrix
    for(int i=0; i<graph->numVertices; i++){
        last_node = NULL;
        //Every element in the row
        for(int j=0; j<graph->numVertices; j++){
            //If it's a non-zero entry
            if(graph->adjMatrix[i][j] != 0){
                //Make node and add
                new_node = createNode(j+1);

                if(last_node == NULL){
                    graph->adjList[i] = new_node;
                }
                else{
                    last_node->next = new_node;
                }
                last_node = new_node;
            }
        }
    }
}

/**
 * Performs Breadth-First Search (BFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which BFS starts (0-based index).
 */
void bfs(Graph *graph, int startVertex){
    printf("Final BFS Order:\n");

    int queue[graph->numVertices];
    int frontIndex = 0;
    queue[0] = startVertex;
    int backIndex = 1;
    int currentVertex;
    Node *nodePtr;

    int discoveredSet[graph->numVertices];
    //initialize discoveredSet array
    for(int i=0; i<graph->numVertices; i++){
        discoveredSet[i] = -1;
    }
    discoveredSet[0] = startVertex;
    int discoveredSetNextIndex = 1;

    while(backIndex > frontIndex){
        //dequeue and set to current vertex
        currentVertex = queue[frontIndex];
        frontIndex++;

        //Print out visited vertex
        printf("%d ", currentVertex);

        //Go through every neighbour of current vertex
        nodePtr = graph->adjList[currentVertex - 1];
        while(nodePtr != NULL){
            if(inArray(discoveredSet, graph->numVertices, nodePtr->vertex) == false){
                queue[backIndex] = nodePtr->vertex;
                backIndex++;

                discoveredSet[discoveredSetNextIndex] = nodePtr->vertex;
                discoveredSetNextIndex++;
            }
            nodePtr = nodePtr->next;
        }
    }
    printf("\n");
}

/**
 * Checks if value is in arr
 * @param arr The array that we are checking if the value is in.
 * @param length The length of the array.
 * @param value The value that we are checking for int the array.
 * @return If the value is in the arr.
 */
bool inArray(int *arr, int length, int value){
    bool found = false;
    for(int i=0; i<length; i++){
        if(arr[i] == value){
            found = true;
        }
    }
    return found;
}

/**
 * Performs Depth-First Search (DFS) starting from a given vertex.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which DFS starts (0-based index).
 */
void dfs(Graph *graph, int startVertex){
    int stack[graph->numVertices];
    stack[0] = startVertex;
    int topIndex = 0;
    int currentVertex;
    Node *nodePtr;

    int tempStack[graph->numVertices];
    int tempTopIndex = -1;

    int visited[graph->numVertices];
    int visitedLength = 0;

    while(topIndex >= 0){
        //Pop stack
        currentVertex = stack[topIndex];
        topIndex--;

        if(inArray(visited, visitedLength, currentVertex) == false){
            printf("%d ", currentVertex);

            //add to visited set
            visited[visitedLength] = currentVertex;
            visitedLength++;

            //Go through every neighbour of current vertex
            nodePtr = graph->adjList[currentVertex - 1];
            while(nodePtr != NULL){
                if(inArray(visited, visitedLength, nodePtr->vertex) == false){
                    //push to temp stack
                    tempStack[tempTopIndex + 1] = nodePtr->vertex;
                    tempTopIndex++;
                }
                nodePtr = nodePtr->next;
            }

            //push to actual stack in reverse order
            while(tempTopIndex >= 0){
                //push to stack
                stack[topIndex + 1] = tempStack[tempTopIndex];
                topIndex++;
                tempTopIndex--;
            }
        }
    }
    printf("\n");
}




/**
 * Finds the shortest path from the start vertex to all other vertices using Dijkstra's algorithm.
 * @param graph Pointer to the Graph structure.
 * @param startVertex The vertex from which to start the algorithm (0-based index).
 */
void dijkstra(Graph *graph, int startVertex){
    int smallest;
    int smallestIndex;
    Node *nodePtr;
    int alt;

    //Initialize unvisited nodes set
    int unvisitedNodes[graph->numVertices];
    for(int i=0; i<graph->numVertices; i++){
        unvisitedNodes[i] = i+1;
    }
    int numUnvisited = graph->numVertices;

    //Initialize distances for all nodes
    int distance[graph->numVertices];
    for(int i=0; i<graph->numVertices; i++){
        distance[i] = INT_MAX;
    }
    distance[startVertex-1] = 0;


    while(numUnvisited > 0){
        smallest = -1;
        smallestIndex = -1;
        //Find smallest distance and mark it as visited
        for(int i=0; i<graph->numVertices; i++){
            if(inArray(unvisitedNodes, graph->numVertices, i+1) && (distance[i] < smallest || smallest == -1)){
                smallest = distance[i];
                smallestIndex = i;
            }
        }
        unvisitedNodes[smallestIndex] = -1;
        numUnvisited--;
        
        //Go through neighbours of smallest
        nodePtr = graph->adjList[smallestIndex];
        while(nodePtr != NULL){
            //Calculate distance of distance from node + distance to neighbouring node
            alt = distance[smallestIndex] + graph->adjMatrix[smallestIndex][(nodePtr->vertex)-1];

            //End algorithm if the potential distance is negative
            if(alt < 0){
                printf("Dijkstra's algorithm is not compatible with negative weights.\n");
                return;
            }

            if(alt < distance[(nodePtr->vertex)-1]){
                distance[(nodePtr->vertex)-1] = alt;
            }
            nodePtr = nodePtr->next;
        }

    }

    for(int i=0; i<graph->numVertices; i++){
        printf("Shortest distance from vertex %d to vertex %d: %d\n", startVertex, i+1, distance[i]);
    }
}

/**
 * Frees the memory allocated for the graph, including the adjacency list.
 * @param graph Pointer to the Graph structure to be freed.
 */
void freeGraph(Graph *graph){
    Node *ptr;
    Node *ptrNext;

    // Free nodes of linked lists
    for(int i=0; i<graph->numVertices; i++){
        ptr = graph->adjList[i];

        while(ptr != NULL){
            ptrNext = ptr->next;
            free(ptr);
            ptr = ptrNext;
        }
    }

    //Free graph
    free(graph);
}
