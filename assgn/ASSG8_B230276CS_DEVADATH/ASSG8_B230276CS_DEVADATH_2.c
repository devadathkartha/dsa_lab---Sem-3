#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int badCharTable[256];
char pattern[100];
int patternLength;
char mainText[500];
int textLength;

int max(int a, int b) {
    return (a > b) ? a : b;
}

void initializeBadCharTable() {
    for (int i = 0; i < 256; i++){
        badCharTable[i] = -1;
    } 
        
    for (int i = 0; i < patternLength; i++){
        badCharTable[(unsigned char)pattern[i]] = i;
    }
}

void boyerMooreSearch() {
    initializeBadCharTable();
    int shift = 0;
    while (shift <= textLength - patternLength) {
        int index = patternLength - 1;
        while (index >= 0 && pattern[index] == mainText[shift + index]) index--;
        if (index < 0) {
            printf("%d\n", shift);
            return;
        } else {
            int shiftAmount = index - badCharTable[(unsigned char)mainText[shift + index]];
            shift += max(shiftAmount, 1);
        }
    }
    printf("-1\n");
}

int main() {
    gets(mainText);
    gets(pattern);
    
    textLength = strlen(mainText);
    patternLength = strlen(pattern);

    boyerMooreSearch();

    return 0;
}
