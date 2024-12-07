#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Element {
    int id;
    struct Element* next;
    int cost;
} Element;

void inputEdges(Element** graph, int count) {
    for (int i = 0; i < count; i++) {
        char line[100];
        fgets(line, 100, stdin);
        line[strlen(line) - 1] = '\0';

        int index = 0, isFirst = 1, mainIndex = 0;
        while (index < strlen(line)) {
            Element* newElement = (Element*)malloc(sizeof(Element));
            newElement->next = NULL;

            int key = 0;
            while (line[index] == ' ') index++;
            while (isdigit(line[index])) {
                key = key * 10 + (line[index] - '0');
                index++;
            }

            if (isFirst) {
                newElement->cost = 0;
                graph[key] = newElement;
                mainIndex = key;
                isFirst = 0;
            } else {
                Element* temp = graph[mainIndex];
                while (temp->next) temp = temp->next;
                temp->next = newElement;
            }
            newElement->id = key;
        }
    }
}

void inputWeights(Element** graph, int count) {
    for (int k = 0; k < count; k++) {
        char line[100];
        fgets(line, 100, stdin);
        line[strlen(line) - 1] = '\0';

        int index = 0, isFirst = 1;
        Element* temp = NULL;
        while (line[index]) {
            while (line[index] == ' ') index++;

            int weight = 0;
            while (isdigit(line[index])) {
                weight = weight * 10 + (line[index] - '0');
                index++;
            }

            if (isFirst) {
                temp = graph[weight];
                if (!temp) break;
                isFirst = 0;
            } else {
                if (temp && temp->next) {
                    temp = temp->next;
                    temp->cost = weight;
                }
            }
        }
    }
}

int getParent(int i) {
    return (i - 1) / 2;
}

void swapValues(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(int* heap, int* size, int element, int* distances) {
    heap[(*size)++] = element;
    int current = (*size) - 1;
    while (current > 0 && distances[getParent(current)] > distances[current]) {
        swapValues(&heap[current], &heap[getParent(current)]);
        current = getParent(current);
    }
}

void maintainHeap(int* heap, int index, int size, int* distances) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int min = index;

    if (left < size && distances[left] < distances[min]) min = left;
    if (right < size && distances[right] < distances[min]) min = right;

    if (min != index) {
        swapValues(&heap[index], &heap[min]);
        maintainHeap(heap, min, size, distances);
    }
}

int removeMin(int* heap, int* size, int* distances) {
    int min = heap[0];
    heap[0] = heap[--(*size)];
    maintainHeap(heap, 0, *size, distances);
    return min;
}

void computeShortestPath(Element** graph, int count, int start) {
    int* heap = (int*)malloc(sizeof(int) * count);
    int heapSize = 0;
    int* distances = (int*)malloc(sizeof(int) * (count + 1));

    for (int i = 0; i <= count; i++) distances[i] = INT_MAX;
    distances[start] = 0;

    insert(heap, &heapSize, start, distances);

    while (heapSize != 0) {
        int current = removeMin(heap, &heapSize, distances);
        Element* adjacent = graph[current]->next;

        while (adjacent) {
            if (distances[adjacent->id] > distances[current] + adjacent->cost) {
                distances[adjacent->id] = distances[current] + adjacent->cost;
                insert(heap, &heapSize, adjacent->id, distances);
            }
            adjacent = adjacent->next;
        }
    }

    for (int i = 0; i <= count; i++) {
        if (graph[i]) printf("%d ", distances[i]);
    }
    printf("\n");

    free(heap);
    free(distances);
}

int main() {
    int count, startNode;
    scanf("%d", &count);
    getchar();

    Element** graph = (Element**)calloc(count + 1, sizeof(Element*));

    inputEdges(graph, count);
    inputWeights(graph, count);

    scanf("%d", &startNode);
    computeShortestPath(graph, count, startNode);

    for (int i = 0; i <= count; i++) {
        Element* current = graph[i];
        while (current) {
            Element* next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph);

    return 0;
}
