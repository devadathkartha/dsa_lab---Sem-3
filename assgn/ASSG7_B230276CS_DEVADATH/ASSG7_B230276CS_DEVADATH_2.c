#include <stdio.h>
#include <stdlib.h>

int compareEdges(const void *edgeA, const void *edgeB) {
    const int(*firstEdge)[3] = edgeA;
    const int(*secondEdge)[3] = edgeB;
    return (*firstEdge)[2]-(*secondEdge)[2];
}

void setupUnionFind(int leaders[], int heights[], int count) {
    for (int i=0;i<count;i++) {
        leaders[i]=i,heights[i]=0;
    }
}

int findSetLeader(int leaders[],int node) {
    if (leaders[node]!=node) {
        leaders[node]=findSetLeader(leaders,leaders[node]);
    }
    return leaders[node];
}

void mergeSets(int nodeA, int nodeB, int leaders[], int heights[]) {
    int leaderA = findSetLeader(leaders, nodeA);
    int leaderB = findSetLeader(leaders, nodeB);

    if (heights[leaderA] < heights[leaderB]) {
        leaders[leaderA] = leaderB;
    } else if (heights[leaderA] > heights[leaderB]) {
        leaders[leaderB] = leaderA;
    } else {
        leaders[leaderB] = leaderA;
        heights[leaderA]++;
    }
}

void kruskalMST(int numEdges, int graphEdges[][3]) {
    qsort(graphEdges, numEdges, sizeof(graphEdges[0]), compareEdges);

    int leaders[numEdges];
    int heights[numEdges];
    setupUnionFind(leaders, heights, numEdges);

    int mstCost = 0;
    for (int i = 0; i < numEdges; i++) {
        int fromNode = findSetLeader(leaders, graphEdges[i][0]);
        int toNode = findSetLeader(leaders, graphEdges[i][1]);
        int edgeWeight = graphEdges[i][2];

        if (fromNode != toNode) {
            mergeSets(fromNode, toNode, leaders, heights);
            mstCost += edgeWeight;
        }
    }

    printf("%d\n", mstCost);
}

int main() {
    int numVertices;
    scanf("%d", &numVertices);

    int **matrix = (int **)malloc(numVertices * sizeof(int *));
    for (int i = 0; i < numVertices; i++) {
        matrix[i] = (int *)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++) {
            matrix[i][j] = 0;
        }
    }

    int source, destination;
    char delimiter;
    for (int i = 0; i < numVertices; i++) {
        scanf("%d%c", &source, &delimiter);
        while (delimiter != '\n') {
            scanf("%d%c", &destination, &delimiter);
            matrix[source][destination] = 1;
        }
    }

    int row, weight;
    for (int i = 0; i < numVertices; i++) {
        scanf("%d%c", &row, &delimiter);
        while (delimiter != '\n') {
            for (int j = 0; j < numVertices; j++) {
                if (matrix[row][j] == 1) {
                    scanf("%d%c", &weight, &delimiter);
                    matrix[row][j] = weight;
                }
            }
        }
    }

    int edges[200][3];
    int edgeCounter = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matrix[i][j] != 0 && i < j) {
                edges[edgeCounter][0] = i;
                edges[edgeCounter][1] = j;
                edges[edgeCounter][2] = matrix[i][j];
                edgeCounter++;
            }
        }
    }

    kruskalMST(edgeCounter, edges);

    for (int i = 0; i < numVertices; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
