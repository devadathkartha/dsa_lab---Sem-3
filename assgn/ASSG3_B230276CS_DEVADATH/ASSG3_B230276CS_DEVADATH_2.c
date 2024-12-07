#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* next;
} Node;

typedef struct HashTable {
    int tableSize;
    Node** table;
} HashTable;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

HashTable* createHashTable(int tableSize) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->tableSize = tableSize;
    hashTable->table = (Node**)malloc(tableSize * sizeof(Node*));

    for (int i = 0; i < tableSize; i++) {
        hashTable->table[i] = NULL;
    }

    return hashTable;
}

int hashFunction(int key, int tableSize) {
    return key % tableSize;
}

void insert(HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->tableSize);
    Node* current = hashTable->table[index];
    Node* prev = NULL;

    while (current != NULL && current->key < key) {
        prev = current;
        current = current->next;
    }
    if (current != NULL && current->key == key) {
        printf("-1\n");
        return;
    }

    Node* newNode = createNode(key);
    if (prev == NULL) {
        newNode->next = hashTable->table[index];
        hashTable->table[index] = newNode;
    } else {
        newNode->next = prev->next;
        prev->next = newNode;
    }
}

void search(HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->tableSize);
    Node* current = hashTable->table[index];
    int position = 1;

    while (current != NULL && current->key != key) {
        current = current->next;
        position++;
    }

    if (current == NULL) {
        printf("-1\n");
    } else {
        printf("%d %d\n", index, position);
    }
}

void delete(HashTable* hashTable, int key) {
    int index = hashFunction(key, hashTable->tableSize);
    Node* current = hashTable->table[index];
    Node* prev = NULL;
    int position = 1;

    while (current != NULL && current->key != key) {
        prev = current;
        current = current->next;
        position++;
    }

    if (current == NULL) {
        printf("-1\n");
    } else {
        if (prev == NULL) {
            hashTable->table[index] = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        printf("%d %d\n", index, position);
    }
}

void update(HashTable* hashTable, int oldKey, int newKey) {
    int index = hashFunction(oldKey, hashTable->tableSize);
    Node* current = hashTable->table[index];
    Node* prev = NULL;
    int position = 1;

    while (current != NULL && current->key != oldKey) {
        prev = current;
        current = current->next;
        position++;
    }

    if (current == NULL) {
        printf("-1\n");
    } else {
        delete(hashTable, oldKey);
        insert(hashTable, newKey);
        printf("%d %d\n", index, position);
    }
}

void printElementsInChain(HashTable* hashTable, int index) {
    Node* current = hashTable->table[index];

    if (current == NULL) {
        printf("-1\n");
        return;
    }

    while (current != NULL) {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}


int main() {
    int tableSize;
    scanf("%d",&tableSize);
    HashTable* hashTable = createHashTable(tableSize);
    char c;
    do{
        scanf("%c",&c);
        if(c=='a'){
            int key;
            scanf("%d",&key);
            insert(hashTable,key);
        }
        if(c=='b'){
            int key;
            scanf("%d",&key);
            search(hashTable,key);
        }
        if(c=='c'){
            int key;
            scanf("%d",&key);
            delete(hashTable,key);
        }
        if(c=='d'){
            int okey,nkey;
            scanf("%d%d",&okey,&nkey);
            update(hashTable,okey,nkey);
        }
        if(c=='e'){
            int idx;
            scanf("%d",&idx);
            printElementsInChain(hashTable,idx);
        }
    }while(c!='f');
    return 0;
}
