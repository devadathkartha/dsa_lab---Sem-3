#include <stdio.h>

void shortestPath(int matrix[][100], int n) {
    int result[100][100];
    int a, b, c;

    for (a = 0; a < n; a++) {
        for (b = 0; b < n; b++) {
            if (matrix[a][b] == -1 && a != b) {
                result[a][b] = 1000000;
            } else {
                result[a][b] = matrix[a][b];
            }
        }
    }

    for (c = 0; c < n; c++) {
        for (a = 0; a < n; a++) {
            for (b = 0; b < n; b++) {
                if (result[a][c] + result[c][b]<result[a][b]){
                    result[a][b] = result[a][c] + result[c][b];
                }
            }
        }
    }

    for (a = 0; a < n; a++) {
        for (b = 0; b < n; b++) {
            if (result[a][b] == 1000000) {
                printf("-1 ");
            } else {
                printf("%d ", result[a][b]);
            }
        }
        printf("\n");
    }
}

int main() {
    int n, x, y;
    int adjMatrix[100][100];

    scanf("%d",&n);

    for (x = 0; x < n; x++) {
        for (y = 0; y < n; y++) {
            scanf("%d", &adjMatrix[x][y]);
        }
    }

    shortestPath(adjMatrix, n);

    return 0;
}
