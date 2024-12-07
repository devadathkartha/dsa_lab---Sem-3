#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int severity;
} Patient;

typedef struct {
    Patient heap[10000];
    int size;
} PriorityQueue;

void swap(Patient *x, Patient *y) {
    Patient temp = *x;
    *x = *y;
    *y = temp;
}

void heapifyUp(PriorityQueue *pq, int i) {
    int parent = i / 2;
    if (i > 1 && pq->heap[i].severity < pq->heap[parent].severity) {
        swap(&pq->heap[i], &pq->heap[parent]);
        heapifyUp(pq, parent);
    }
}

void heapifyDown(PriorityQueue *pq, int i) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int smallest = i;

    if (left <= pq->size && pq->heap[left].severity < pq->heap[smallest].severity)
        smallest = left;

    if (right <= pq->size && pq->heap[right].severity < pq->heap[smallest].severity)
        smallest = right;

    if (smallest != i) {
        swap(&pq->heap[i], &pq->heap[smallest]);
        heapifyDown(pq, smallest);
    }
}

void AdmitPatient(PriorityQueue *pq, int id, char *name, int severity) {
    if (pq->size == 10000) {
        return;
    }

    for (int i = 1; i <= pq->size; i++) {
        if (pq->heap[i].severity == severity) {
            return;
        }
    }

    pq->size++;
    pq->heap[pq->size].id = id;
    strncpy(pq->heap[pq->size].name, name, 50);
    pq->heap[pq->size].severity = severity;

    heapifyUp(pq, pq->size);
    
    for (int i = 1; i <= pq->size; i++) {
        printf("%d ", pq->heap[i].id);
    }
    printf("\n");
}

void TreatPatient(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("-1\n");
        return;
    }

    Patient mostSevere = pq->heap[1];
    printf("%d %s\n", mostSevere.id, mostSevere.name);

    pq->heap[1] = pq->heap[pq->size];
    pq->size--;
    heapifyDown(pq, 1);
}

void UpdateSeverity(PriorityQueue *pq, int id, int newSeverity) {
    int found = 0;
    int idx = -1;

    for (int i = 1; i <= pq->size; i++) {
        if (pq->heap[i].severity == newSeverity) {
            return;
        }
    }

    for (int i = 1; i <= pq->size; i++) {
        if (pq->heap[i].id == id) {
            idx = i;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("-1\n");
        return;
    }

    int oldSeverity = pq->heap[idx].severity;
    pq->heap[idx].severity = newSeverity;

    if (newSeverity < oldSeverity) {
        heapifyUp(pq, idx);
    } else {
        heapifyDown(pq, idx);
    }

    for (int i = 1; i <= pq->size; i++) {
        printf("%d ", pq->heap[i].id);
    }
    printf("\n");
}

void QueryPatient(PriorityQueue *pq, int id) {
    for (int i = 1; i <= pq->size; i++) {
        if (pq->heap[i].id == id) {
            printf("%s %d\n", pq->heap[i].name, pq->heap[i].severity);
            return;
        }
    }
    printf("-1\n");
}

void FindMostSevere(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("-1\n");
        return;
    }
    printf("%d %s %d\n", pq->heap[1].id, pq->heap[1].name, pq->heap[1].severity);
    if(pq->heap[2].severity<pq->heap[3].severity){
        printf("%d %s %d\n", pq->heap[2].id, pq->heap[2].name, pq->heap[2].severity);
        printf("%d %s %d\n", pq->heap[3].id, pq->heap[3].name, pq->heap[3].severity);
    }
    else{
        printf("%d %s %d\n", pq->heap[3].id, pq->heap[3].name, pq->heap[3].severity);
        printf("%d %s %d\n", pq->heap[2].id, pq->heap[2].name, pq->heap[2].severity);
    }
}

int main() {
    PriorityQueue pq;
    pq.size = 0;

    char c;
    int id, severity, newSeverity;
    char name[50];

    while (scanf(" %c", &c) != EOF) {
        switch (c) {
            case 'a':
                scanf("%d %d %[^\n]s", &id, &severity, name);
                AdmitPatient(&pq, id, name, severity);
                break; 
            case 'b':
                TreatPatient(&pq);
                break;
            case 'c':
                scanf("%d %d", &id, &newSeverity);
                UpdateSeverity(&pq, id, newSeverity);
                break;
            case 'd':
                scanf("%d", &id);
                QueryPatient(&pq, id);
                break;
            case 'e':
                FindMostSevere(&pq);
                break;
            case 'g':
                return 0;
        }
    }

    return 0;
}
