#include <stdio.h>
#include <stdlib.h>
#define EMPTY -1

int isPrime(int k) {
    if (k == 2) return 1;
    for (int i=2;i<k;i++) if (k%i == 0) return 0;
    return 1;
}

void linearProbing(int N, int keys[], int m) {
    int hashTable[N];
    for (int i = 0; i < N; i++) {
        hashTable[i] = EMPTY; 
    }
    int collisions = 0;
    for (int i = 0; i < m; i++) {
        int c = 0;
        int key = keys[i];
        int index = key % N;
        int originalIndex = index;
        while (hashTable[index] != EMPTY) {
            c++;
            index = (key%N + c)%N;
        }
        hashTable[index] = key;
        printf("%d ", index);
        collisions += c;
    }
    printf("\n%d\n", collisions);
}

void quadraticProbing(int N, int keys[], int m) {
    int hashTable[N];
    for (int i = 0; i < N; i++) {
        hashTable[i] = EMPTY;  
    }
    int collisions = 0;
    for (int i = 0; i < m; i++) {
        int key = keys[i];
        int index = key % N;
        int c = 0;
        while (hashTable[index] != EMPTY) {
            c++;
            index = (key + c * c) % N;
        }
        hashTable[index] = key;
        printf("%d ",index);
        collisions += c;
    }
    printf("\n%d\n", collisions);
}

void doubleHashing(int N, int keys[], int m) {
    int hashTable[N];
    for (int i = 0; i < N; i++) {
        hashTable[i] = EMPTY;  
    }
    int collisions = 0;
    int r = 0;
    for (int i = N-1;i>0;i--) {
        if (isPrime(i)) {
            r = i;
            break;
        }
    }
    for (int i = 0; i < m; i++) {
        int key = keys[i];
        int index1 = key%N;
        int index2 = r - key%r;
        int j = 0;
        int index = index1;
        while (hashTable[index] != EMPTY) {
            j++;
            index = (index1 + j * index2) % N;
        }
        hashTable[index] = key;
        printf("%d ", index);
        collisions += j;
    }
    printf("\n%d\n", collisions);
}


int main() {
    int N, m;
    scanf("%d %d", &N, &m);
    int keys[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &keys[i]);
    }

    char operation;
    while (1) {
        scanf(" %c", &operation);
        switch (operation) {
            case 'a':
                linearProbing(N, keys, m);
                break;
            case 'b':
                quadraticProbing(N, keys, m);
                break;
            case 'c': {
                doubleHashing(N, keys, m);
                break;
            }
            case 'd':
                return 0;
            default:
                printf("Invalid operation! Please try again.\n");
                break;
        }
    }
    return 0;
}
