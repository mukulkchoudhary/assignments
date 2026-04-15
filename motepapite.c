#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int solutionCount = 0;

void printSolution(int board[MAX][MAX], int N) {
    solutionCount++;
    printf("\n--- Solution %d ---\n", solutionCount);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 1)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

bool isSafe(int board[MAX][MAX], int row, int col, int N) {
    int i, j;
    
    for (j = 0; j < col; j++)
        if (board[row][j] == 1)
            return false;
    
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;
    
    for (i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j] == 1)
            return false;
    
    return true;
}

bool solveNQUtil(int board[MAX][MAX], int col, int N) {
    if (col >= N) {
        printSolution(board, N);
        return true;
    }
    
    bool res = false;
    
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col, N)) {
            board[i][col] = 1;
            
            if (solveNQUtil(board, col + 1, N))
                res = true;
            
            board[i][col] = 0;
        }
    }
    
    return res;
}

int main() {
    int N;
    int board[MAX][MAX] = {0};
    
    printf("Enter no. of queens: ");
    scanf("%d", &N);
    
    if (N <= 0 || N > MAX) {
        printf("Invalid input. N must be between 1 and %d\n", MAX);
        return 1;
    }
    
    solutionCount = 0;
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;
    
    printf("\nSolving %d-Queens Problem...\n", N);
    printf("=================================\n");
    
    bool found = solveNQUtil(board, 0, N);
    
    if (!found)
        printf("No solution exists for N = %d\n", N);
    else
        printf("\nTotal solutions found: %d\n", solutionCount);
    
    return 0;
}
