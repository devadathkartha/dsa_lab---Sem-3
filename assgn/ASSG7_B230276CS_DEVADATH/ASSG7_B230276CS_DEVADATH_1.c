#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct {
    int sourceNode, destinationNode, edgeWeight;
} GraphEdge;

int adjacencyMatrix[MAX_NODES][MAX_NODES];
int totalWeightOfMST = 0;
int numberOfVertices;
GraphEdge minimumSpanningTreeEdges[MAX_NODES - 1];
int edgeCountInMST = 0;

int findMinimumKey(int key[], bool isInMST[], int numberOfVertices) {
    int minKeyValue = INT_MAX, minIndex;

    for (int vertexIndex = 0; vertexIndex < numberOfVertices; vertexIndex++) {
        if (isInMST[vertexIndex] == false && key[vertexIndex] < minKeyValue) {
            minKeyValue = key[vertexIndex];
            minIndex = vertexIndex;
        }
    }
    return minIndex;
}

void calculateTotalWeightOfMST(int parent[], int numberOfVertices) {
    totalWeightOfMST = 0;
    for (int vertexIndex = 0; vertexIndex < numberOfVertices; vertexIndex++) {
        if (parent[vertexIndex] != -1) {
            totalWeightOfMST += adjacencyMatrix[vertexIndex][parent[vertexIndex]];
        }
    }
}

int displayMinimumSpanningTree(GraphEdge edges[], int edgeCount) {
    for (int index = 0; index < edgeCount; index++) {
        printf("%d %d (%d) ", edges[index].sourceNode, edges[index].destinationNode, edges[index].edgeWeight);
    }
}

void applyPrimAlgorithm(int numberOfVertices, int startingVertex) {
    totalWeightOfMST = 0;
    int parent[numberOfVertices];
    int key[numberOfVertices];
    bool isInMST[numberOfVertices];

    for (int index = 0; index < numberOfVertices; index++) {
        key[index] = INT_MAX;
        isInMST[index] = false;
        parent[index] = -1;
    }

    key[startingVertex] = 0;

    for (int count = 0; count < numberOfVertices; count++) {
        int selectedVertex = findMinimumKey(key, isInMST, numberOfVertices);
        isInMST[selectedVertex] = true;

        for (int vertexIndex = 0; vertexIndex < numberOfVertices; vertexIndex++) {
            if (adjacencyMatrix[selectedVertex][vertexIndex] && isInMST[vertexIndex] == false && adjacencyMatrix[selectedVertex][vertexIndex] < key[vertexIndex]) {
                parent[vertexIndex] = selectedVertex;
                key[vertexIndex] = adjacencyMatrix[selectedVertex][vertexIndex];
            }
        }

        if (parent[selectedVertex] != -1) {
            minimumSpanningTreeEdges[edgeCountInMST].sourceNode = parent[selectedVertex];
            minimumSpanningTreeEdges[edgeCountInMST].destinationNode = selectedVertex;
            minimumSpanningTreeEdges[edgeCountInMST].edgeWeight = adjacencyMatrix[selectedVertex][parent[selectedVertex]];
            edgeCountInMST++;
        }
    }

    displayMinimumSpanningTree(minimumSpanningTreeEdges, edgeCountInMST);
    calculateTotalWeightOfMST(parent, numberOfVertices);
}

int main() {
    scanf("%d", &numberOfVertices);

    for (int rowIndex = 0; rowIndex < numberOfVertices; rowIndex++) {
        for (int columnIndex = 0; columnIndex < numberOfVertices; columnIndex++) {
            scanf("%d", &adjacencyMatrix[rowIndex][columnIndex]);
        }
    }

    char userChoice = '\0';
    while (userChoice != 'e') {
        scanf(" %c", &userChoice);

        if (userChoice == 's') {
            int startingVertex;
            scanf("%d", &startingVertex);
            applyPrimAlgorithm(numberOfVertices, startingVertex);
        }

        if (userChoice == 'b') {
            printf("%d\n", totalWeightOfMST);
        }
    }

    return 0;
}
