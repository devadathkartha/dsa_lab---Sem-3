#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int JID;
    int priority;
} Job;

typedef struct {
    Job heap[1000];
    int size;          
} PriorityQueue;

void swap(Job *x, Job *y) {
    Job temp = *x;
    *x = *y;
    *y = temp;
}

void heapifyUp(PriorityQueue *pq, int i) {
    int parent = i / 2;
    if (i > 1 && pq->heap[i].priority < pq->heap[parent].priority) {
        swap(&pq->heap[i], &pq->heap[parent]);
        heapifyUp(pq, parent);
    }
}

void heapifyDown(PriorityQueue *pq, int i) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int smallest = i;

    if (left <= pq->size && pq->heap[left].priority < pq->heap[smallest].priority)
        smallest = left;

    if (right <= pq->size && pq->heap[right].priority < pq->heap[smallest].priority)
        smallest = right;

    if (smallest != i) {
        swap(&pq->heap[i], &pq->heap[smallest]);
        heapifyDown(pq, smallest);
    }
}

void Add(PriorityQueue *pq, int JID, int priority) {
    if (pq->size == 1000) {
        return;
    }

    pq->size++;
    pq->heap[pq->size].JID = JID;
    pq->heap[pq->size].priority = priority;

    heapifyUp(pq, pq->size);
}

void Schedule(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("-1\n");
        return;
    }

    printf("%d\n", pq->heap[1].JID);

    pq->heap[1] = pq->heap[pq->size];
    pq->size--;
    heapifyDown(pq, 1);
}

void NextJob(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("-1\n");
        return;
    }

    printf("%d\n", pq->heap[1].JID);
}

void ReplacePriority(PriorityQueue *pq, int JID, int newPriority) {
    int found = 0;
    int idx = -1;

    for (int i = 1; i <= pq->size; i++) {
        if (pq->heap[i].JID == JID) {
            idx = i;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("-1\n");
        return;
    }

    int oldPriority = pq->heap[idx].priority;
    pq->heap[idx].priority = newPriority;

    if (newPriority < oldPriority) {
        heapifyUp(pq, idx);
    } else {
        heapifyDown(pq, idx);
    }
}

void Display(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("-1\n");
        return;
    }

    for (int i = 1; i <= pq->size; i++) {
        printf("%d %d\n", pq->heap[i].JID, pq->heap[i].priority);
    }
}

int main() {
    PriorityQueue pq;
    pq.size = 0;

    char operation;
    int JID, priority, newPriority;

    while (scanf(" %c", &operation) != EOF) {
        switch (operation) {
            case 'a':
                scanf("%d %d", &JID, &priority);
                Add(&pq, JID, priority);
                break;
            case 'b':
                Schedule(&pq);
                break;
            case 'c':
                NextJob(&pq);
                break;
            case 'd':
                scanf("%d %d", &JID, &newPriority);
                ReplacePriority(&pq, JID, newPriority);
                break;
            case 'e':
                Display(&pq);
                break;
            case 'g':
                return 0;
        }
    }

    return 0;
}
