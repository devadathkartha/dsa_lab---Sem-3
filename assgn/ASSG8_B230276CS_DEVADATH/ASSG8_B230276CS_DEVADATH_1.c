#include <stdio.h>
#include <string.h>

void calculatePrefixArray(char *pattern, int patternLength, int *prefixArray) {
    int length = 0;
    prefixArray[0] = 0;     
    int index = 1;

    while (index < patternLength) {
        if (pattern[index] == pattern[length]) {
            length++;
            prefixArray[index] = length;
            index++;
        } else {
            if (length != 0) {
                length = prefixArray[length - 1];
            } else {
                prefixArray[index] = 0;
                index++;
            }
        }
    }
}

void patternSearch(char *text, char *pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    int prefixArray[patternLength];
    calculatePrefixArray(pattern, patternLength, prefixArray);

    int textIndex = 0;
    int patternIndex = 0;
    int lastPosition = -1;
    int occurrenceCount = 0;

    while (textIndex < textLength) {
        if (pattern[patternIndex] == text[textIndex]) {
            patternIndex++;
            textIndex++;
        }
        if (patternIndex == patternLength) {
            lastPosition = textIndex - patternIndex;
            occurrenceCount++;
            patternIndex = prefixArray[patternIndex - 1];
        } else if (textIndex < textLength && pattern[patternIndex] != text[textIndex]) {
            if (patternIndex != 0) {
                patternIndex = prefixArray[patternIndex - 1];
            } else {
                textIndex++;
            }
        }
    }
    if (occurrenceCount > 0) {
        printf("%d %d\n", lastPosition, occurrenceCount);
    } else {
        printf("-1\n");
    }
}

int main() {
    char text[1000001], pattern[100001];
    scanf("%s", text);
    scanf("%s", pattern);
    patternSearch(text, pattern);
    return 0;
}
