#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

typedef struct DirectedGraph {
    int totalVertices;
    ListNode** adjacencyList;
    int* isVisited;
} DirectedGraph;

ListNode* createListNode(int value) {
    ListNode* newNode = malloc(sizeof(ListNode));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

DirectedGraph* initializeGraph(int vertices) {
    DirectedGraph* graph = malloc(sizeof(DirectedGraph));
    graph->totalVertices = vertices;

    graph->adjacencyList = malloc(vertices * sizeof(ListNode*));
    graph->isVisited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacencyList[i] = NULL;
        graph->isVisited[i] = 0;
    }

    return graph;
}

void insertEdge(DirectedGraph* graph, int source, int destination) {
    ListNode* newNode = createListNode(destination);
    newNode->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = newNode;
}

int detectCycle(DirectedGraph* graph, int vertex, int* recursionStack) {
    graph->isVisited[vertex] = 1;
    recursionStack[vertex] = 1;

    ListNode* currentNode = graph->adjacencyList[vertex];
    while (currentNode != NULL) {
        int adjVertex = currentNode->data;
        if (!graph->isVisited[adjVertex] && detectCycle(graph, adjVertex, recursionStack)) {
            return 1;
        } else if (recursionStack[adjVertex]) {
            return 1;
        }
        currentNode = currentNode->next;
    }
    recursionStack[vertex] = 0;
    return 0;
}

int isAcyclicGraph(DirectedGraph* graph) {
    int recursionStack[graph->totalVertices];
    for (int i = 0; i < graph->totalVertices; i++) {
        recursionStack[i] = 0;
    }

    for (int i = 0; i < graph->totalVertices; i++) {
        if (!graph->isVisited[i]) {
            if (detectCycle(graph, i, recursionStack)) {
                return -1;
            }
        }
    }
    return 1;
}

void performDFS(DirectedGraph* graph, int vertex, int* stack, int* top) {
    graph->isVisited[vertex] = 1;

    ListNode* currentNode = graph->adjacencyList[vertex];
    while (currentNode != NULL) {
        int adjVertex = currentNode->data;
        if (!graph->isVisited[adjVertex]) {
            performDFS(graph, adjVertex, stack, top);
        }
        currentNode = currentNode->next;
    }

    if (stack != NULL) {
        stack[(*top)++] = vertex;
    }
}

DirectedGraph* reverseGraph(DirectedGraph* graph) {
    DirectedGraph* reversedGraph = initializeGraph(graph->totalVertices);
    for (int i = 0; i < graph->totalVertices; i++) {
        ListNode* currentNode = graph->adjacencyList[i];
        while (currentNode != NULL) {
            insertEdge(reversedGraph, currentNode->data, i);
            currentNode = currentNode->next;
        }
    }
    return reversedGraph;
}

int countSCCs(DirectedGraph* graph) {
    int stack[graph->totalVertices];
    int top = 0, sccCount = 0;

    for (int i = 0; i < graph->totalVertices; i++) {
        graph->isVisited[i] = 0;
    }
    for (int i = 0; i < graph->totalVertices; i++) {
        if (!graph->isVisited[i]) {
            performDFS(graph, i, stack, &top);
        }
    }

    DirectedGraph* reversedGraph = reverseGraph(graph);

    for (int i = 0; i < graph->totalVertices; i++) {
        reversedGraph->isVisited[i] = 0;
    }
    while (top > 0) {
        int vertex = stack[--top];
        if (!reversedGraph->isVisited[vertex]) {
            performDFS(reversedGraph, vertex, NULL, NULL);
            sccCount++;
        }
    }

    return sccCount;
}

int main() {
    int numVertices, numEdges;
    scanf("%d %d", &numVertices, &numEdges);

    DirectedGraph* graph = initializeGraph(numVertices);

    for (int i = 0; i < numVertices; i++) {
        int vertex;
        scanf("%d", &vertex);

        char line[256];
        fgets(line, sizeof(line), stdin);

        char* token = strtok(line, " ");
        while (token != NULL) {
            int adjVertex = atoi(token);
            if (adjVertex != 0) {
                insertEdge(graph, vertex - 1, adjVertex - 1);
            }
            token = strtok(NULL, " ");
        }
    }

    char choice;
    while (1) {
        scanf(" %c", &choice);
        switch (choice) {
            case 'a':
                for (int i = 0; i < numVertices; i++) {
                    graph->isVisited[i] = 0;
                }
                printf("%d\n", isAcyclicGraph(graph));
                break;
            case 'b':
                printf("%d\n", countSCCs(graph));
                break;
            case 'x':
                return 0;
            default:
                break;
        }
    }

    return 0;
}
