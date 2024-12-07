#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 100

int checkBipartite(int graph[MAX_NODES][MAX_NODES], int nodeCount) {
    int nodeColor[MAX_NODES];
    memset(nodeColor, -1, sizeof(nodeColor));
    
    for (int startNode = 0; startNode < nodeCount; startNode++) {
        if (nodeColor[startNode] == -1) {
            int queue[MAX_NODES], front = 0, rear = 0;
            queue[rear++] = startNode;
            nodeColor[startNode] = 0;

            while (front < rear) {
                int currentNode = queue[front++];

                for (int neighbor = 0; neighbor < nodeCount; neighbor++) {
                    if (graph[currentNode][neighbor] == 1) {
                        if (nodeColor[neighbor] == -1) {
                            nodeColor[neighbor] = 1 - nodeColor[currentNode];
                            queue[rear++] = neighbor;
                        } else if (nodeColor[neighbor] == nodeColor[currentNode]) {
                            return -1;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int detectCycle(int graph[MAX_NODES][MAX_NODES], int nodeCount) {
    int visited[MAX_NODES] = {0};
    
    for (int startNode = 0; startNode < nodeCount; startNode++) {
        if (!visited[startNode]) {
            int parent[MAX_NODES], queue[MAX_NODES], front = 0, rear = 0;
            memset(parent, -1, sizeof(parent));
            
            queue[rear++] = startNode;
            visited[startNode] = 1;

            while (front < rear) {
                int currentNode = queue[front++];

                for (int neighbor = 0; neighbor < nodeCount; neighbor++) {
                    if (graph[currentNode][neighbor] == 1) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = 1;
                            parent[neighbor] = currentNode;
                            queue[rear++] = neighbor;
                        } else if (parent[currentNode] != neighbor) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int validateTree(int graph[MAX_NODES][MAX_NODES], int nodeCount) {
    if (detectCycle(graph, nodeCount) == 1 || nodeCount <= 0) {
        return -1;
    }

    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES], front = 0, rear = 0, edgeCounter = 0, visitedNodes = 0;

    queue[rear++] = 0;
    visited[0] = 1;
    visitedNodes++;

    while (front < rear) {
        int currentNode = queue[front++];

        for (int neighbor = 0; neighbor < nodeCount; neighbor++) {
            if (graph[currentNode][neighbor] == 1) {
                edgeCounter++;
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    visitedNodes++;
                    queue[rear++] = neighbor;
                }
            }
        }
    }

    for (int i = 0; i < nodeCount; i++) {
        if (!visited[i]) {
            return -1;
        }
    }

    if (edgeCounter / 2 == nodeCount - 1) {
        return 1;
    }
    return -1;
}

int main() {
    int nodeCount;
    int graph[MAX_NODES][MAX_NODES];

    scanf("%d", &nodeCount);

    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    char command;
    while (1) {
        scanf(" %c", &command);

        switch (command) {
            case 'a':
                printf("%d\n", checkBipartite(graph, nodeCount));
                break;
            case 'b':
                printf("%d\n", detectCycle(graph, nodeCount));
                break;
            case 'c':
                printf("%d\n", validateTree(graph, nodeCount));
                break;
            case 'x':
                return 0;
        }
    }

    return 0;
}
