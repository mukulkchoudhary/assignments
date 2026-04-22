#include <stdio.h>
#define MAX 20
#define INF 99999

void printMatrix(int dist[][MAX], int n, int step) {
    printf("\nA %d ", step);
    for (int i = 1; i <= n; i++)
        printf("%d ", i);
    printf("\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

void printPath(int dist[][MAX], int next[][MAX], int n) {
    printf("\nPath:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] != INF) {
                printf("%d->%d: ", i + 1, j + 1);
                int u = i;
                printf("%d", u + 1);
                while (u != j) {
                    u = next[u][j];
                    printf("->%d", u + 1);
                }
                printf(":%d\n", dist[i][j]);
            }
        }
    }
}

void floydWarshall(int dist[][MAX], int n) {
    int i, j, k;
    int next[MAX][MAX];
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (dist[i][j] != INF && i != j)
                next[i][j] = j;
            else
                next[i][j] = -1;
        }
    }
    
    printMatrix(dist, n, 1);
    
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
        if (k < n - 1)
            printMatrix(dist, n, k + 2);
    }
    
    printMatrix(dist, n, n);
    printPath(dist, next, n);
}

int main() {
    int n, edges;
    int dist[MAX][MAX];
    
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
        }
    }
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter edges in format: source destination weight\n");
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        dist[u-1][v-1] = w;
    }
    
    printf("\nInput Graph:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
    
    printf("\nOutput: Optimal solution with intermediate steps\n");
    floydWarshall(dist, n);
    
    return 0;
}
