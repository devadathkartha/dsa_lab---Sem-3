#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int heap[10000]; 
    int size;
} MaxHeap;

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void heapifyDown(MaxHeap *H, int i) {
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= H->size && H->heap[left] > H->heap[largest])
        largest = left;

    if (right <= H->size && H->heap[right] > H->heap[largest])
        largest = right;

    if (largest != i) {
        swap(&H->heap[i], &H->heap[largest]);
        heapifyDown(H, largest);
    }
}

void heapifyUp(MaxHeap *H, int i) {
    int parent = i / 2;
    if (i > 1 && H->heap[i] > H->heap[parent]) {
        swap(&H->heap[i], &H->heap[parent]);
        heapifyUp(H, parent);
    }
}

void InsertKey(MaxHeap *H, int n) {
    for (int i = 1; i <= H->size; i++) {
        if (H->heap[i] == n) {
            return;
        }
    }
    H->size++;
    H->heap[H->size] = n;
    heapifyUp(H, H->size);
}

int FindMax(MaxHeap *H) {
    if (H->size > 0)
        return H->heap[1];
    else
        return -1;
}

int ExtractMax(MaxHeap *H) {
    if (H->size == 0)
        return -1;

    int max_val = H->heap[1];
    H->heap[1] = H->heap[H->size];
    H->size--;
    heapifyDown(H, 1);

    return max_val;
}

int KthLargest(MaxHeap *H, int k) {
    if (k > H->size)
        return -1;

    int *temp = (int *)malloc((H->size + 1) * sizeof(int));
    for (int i = 1; i <= H->size; i++)
        temp[i] = H->heap[i];

    int result = -1;
    for (int i = 0; i < k; i++)
        result = ExtractMax(H);

    for (int i = 1; i <= H->size; i++)
        InsertKey(H, temp[i]);

    free(temp);
    return result;
}

void DeleteKey(MaxHeap *H, int x) {
    int found = 0;
    for (int i = 1; i <= H->size; i++) {
        if (H->heap[i] == x) {
            H->heap[i] = H->heap[H->size];
            H->size--;
            heapifyDown(H, i);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("-1\n");
}

int ReplaceKey(MaxHeap *H, int old_val, int new_val) {
    int found = 0;
    for (int i = 1; i <= H->size; i++) {
        if (H->heap[i] == old_val) {
            H->heap[i] = new_val;
            if (new_val > old_val)
                heapifyUp(H, i);
            else
                heapifyDown(H, i);
            found = 1;
            break;
        }
    }
    if (!found){
        printf("%d\n", abs(old_val - new_val));
    }
    return found;
}

void printHeap(MaxHeap *H) {
    if (H->size == 0) {
        printf("0\n");
        return;
    }
    for (int i = 1; i <= H->size; i++) {
        printf("%d ", H->heap[i]);
    }
    printf("\n");
}


 
int main() {
    MaxHeap heap;
    heap.size = 0;

    char c;
    do{
        scanf("%c",&c);
        if(c=='a'){
            int val;
            scanf("%d",&val);
            InsertKey(&heap,val);
        }
        if(c=='b'){
            printf("%d\n",FindMax(&heap));
        }
        if(c=='c'){
            int n=ExtractMax(&heap);
            if(n==-1){
                printf("-1\n");
            }
            else{
                printf("%d ",n);
                printHeap(&heap);
            }
        }
        if(c=='d'){
            int k;
            scanf("%d",&k);
            printf("%d\n",KthLargest(&heap,k));
        }
        if(c=='e'){
            int x;
            scanf("%d",&x);
            DeleteKey(&heap,x);
            printHeap(&heap);
        }
        if(c=='f'){
            int oke,nke;
            scanf("%d%d",&oke,&nke);
            if(ReplaceKey(&heap,oke,nke)){
                printHeap(&heap);
            }
        }
    }while(c!='g');

}