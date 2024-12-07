#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vertexCount;
int graph[300][300];

int visitedNodes[300], lowTime[300], discoveryTime[300], parentNodes[300], currentTime = 0;
int articulationPoints[300], bridgeEdges[300][300];

void performDFS(int node, int *componentSize) {
    visitedNodes[node] = 1;
    (*componentSize)++;
    for (int neighbor = 0; neighbor < vertexCount; neighbor++) {
        if (graph[node][neighbor] && !visitedNodes[neighbor]) {
            performDFS(neighbor, componentSize);
        }
    }
}

int countConnectedComponents() {
    memset(visitedNodes, 0, sizeof(visitedNodes));
    int componentCount = 0;

    for (int i = 0; i < vertexCount; i++) {
        if (!visitedNodes[i]) {
            componentCount++;
            int componentSize = 0;
            performDFS(i, &componentSize);
        }
    }
    return componentCount;
}

void findComponentSizes() {
    memset(visitedNodes, 0, sizeof(visitedNodes));
    int componentSizes[300], index = 0;

    for (int i = 0; i < vertexCount; i++) {
        if (!visitedNodes[i]) {
            int componentSize = 0;
            performDFS(i, &componentSize);
            componentSizes[index++] = componentSize;
        }
    }

    for (int i = 0; i < index - 1; i++) {
        for (int j = 0; j < index - i - 1; j++) {
            if (componentSizes[j] > componentSizes[j + 1]) {
                int temp = componentSizes[j];
                componentSizes[j] = componentSizes[j + 1];
                componentSizes[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < index; i++) {
        printf("%d ", componentSizes[i]);
    }
    printf("\n");
}

void exploreForBridgesAndArtPoints(int node) {
    visitedNodes[node] = 1;
    discoveryTime[node] = lowTime[node] = ++currentTime;

    int childrenCount = 0;

    for (int neighbor = 0; neighbor < vertexCount; neighbor++) {
        if (graph[node][neighbor]) {
            if (!visitedNodes[neighbor]) {
                childrenCount++;
                parentNodes[neighbor] = node;
                exploreForBridgesAndArtPoints(neighbor);

                if (lowTime[neighbor] > discoveryTime[node]) {
                    bridgeEdges[node][neighbor] = bridgeEdges[neighbor][node] = 1;
                }

                if (parentNodes[node] == -1 && childrenCount > 1) {
                    articulationPoints[node] = 1;
                }
                if (parentNodes[node] != -1 && lowTime[neighbor] >= discoveryTime[node]) {
                    articulationPoints[node] = 1;
                }

                lowTime[node] = (lowTime[node] < lowTime[neighbor]) ? lowTime[node] : lowTime[neighbor];
            } else if (neighbor != parentNodes[node]) {
                lowTime[node] = (lowTime[node] < discoveryTime[neighbor]) ? lowTime[node] : discoveryTime[neighbor];
            }
        }
    }
}

int countBridges() {
    memset(visitedNodes, 0, sizeof(visitedNodes));
    memset(bridgeEdges, 0, sizeof(bridgeEdges));
    currentTime = 0;

    for (int i = 0; i < vertexCount; i++) {
        if (!visitedNodes[i]) {
            exploreForBridgesAndArtPoints(i);
        }
    }

    int bridgeCount = 0;
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            if (bridgeEdges[i][j]) {
                bridgeCount++;
            }
        }
    }
    return bridgeCount / 2;
}

int countArticulationPoints() {
    memset(visitedNodes, 0, sizeof(visitedNodes));
    memset(articulationPoints, 0, sizeof(articulationPoints));
    memset(parentNodes, -1, sizeof(parentNodes));
    currentTime = 0;

    for (int i = 0; i < vertexCount; i++) {
        if (!visitedNodes[i]) {
            exploreForBridgesAndArtPoints(i);
        }
    }

    int apCount = 0;
    for (int i = 0; i < vertexCount; i++) {
        if (articulationPoints[i]) {
            apCount++;
        }
    }
    return apCount;
}

int main() {
    scanf("%d", &vertexCount);

    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    char command;
    while (scanf(" %c", &command) && command != 'x') {
        switch (command) {
            case 'a':
                printf("%d\n", countConnectedComponents());
                break;
            case 'b':
                findComponentSizes();
                break;
            case 'c':
                printf("%d\n", countBridges());
                break;
            case 'd':
                printf("%d\n", countArticulationPoints());
                break;
        }
    }

    return 0;
}
