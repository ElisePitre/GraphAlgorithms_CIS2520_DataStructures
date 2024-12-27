/* Name: Elise Pitre
Student ID: 1267817
Date: Dec 1 2024
Assignment name: CIS*2520 — Assignment #4 */

#include "graph.h"

/*
 * A basic menu based structure has been provided
 */

int main(int argc, char *argv[]){

    if (argc != 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    //Create the graph
    Graph *graph = readGraph(argv[1]);
    if(graph == NULL){
        return 1;
    }

    int choice;
    // int startVertex = 1;

    bool endLoop = false;
    do{

        // Display the options
        prompt();

        // Get user input
        printf("Enter a Choice: ");
        scanf("%d", &choice);


        switch (choice) {
            //Display Adjacency list
            case 1:
                displayAdjacencyList(graph);
                break;
            
            //Perform Breadth-First Search (BFS)
            case 2:
                bfs(graph, 1);
                break;
            
            //Perform Depth-First Search (DFS)
            case 3:
                dfs(graph, 1);
                break;
            
            //Find Shortest Path using Dijkstra's Algorithm
            case 4:
                dijkstra(graph, 1);
                break;
            
            //Exit
            case 5:
                freeGraph(graph);
                endLoop = true;
                printf("Exiting...\n");
                break;

            default:
                printf("Please choose a valid option (an integer from 1 to 5)\n");
                break;
        }

    } while (endLoop == false);

    return 0;
}
