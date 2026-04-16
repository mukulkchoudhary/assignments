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




Algorithm: NQueens(N)
Input: Integer N (board size and number of queens)
Output: All valid board configurations

// Data Structures Used:
// board[N][N] - 2D array where board[i][j] = 1 if queen present, 0 otherwise
// solutionCount - Global counter for number of solutions found

/////////////////////////////////////////////////////////////////////////////
// MAIN ALGORITHM
/////////////////////////////////////////////////////////////////////////////

Step 1: Initialize board[N][N] with all zeros
Step 2: Set solutionCount = 0
Step 3: Call SOLVE_UTIL(board, 0, N)
Step 4: If solutionCount == 0
            Print "No solution exists"
        Else
            Print "Total solutions: solutionCount"

/////////////////////////////////////////////////////////////////////////////
// RECURSIVE BACKTRACKING FUNCTION
/////////////////////////////////////////////////////////////////////////////

Function SOLVE_UTIL(board, col, N)
Input: 
    board - Current board state
    col   - Current column being processed (0 to N-1)
    N     - Board size
Output: 
    true if at least one solution found from this state, false otherwise

Begin
    // BASE CASE: All queens placed successfully
    If col >= N Then
        PRINT_SOLUTION(board, N)
        solutionCount++
        Return true    // Signal that solution exists
    End If
    
    foundSolution = false
    
    // RECURSIVE CASE: Try placing queen in current column
    For row = 0 to N-1 Do
        
        // CONSTRAINT CHECKING (Pruning Step)
        If IS_SAFE(board, row, col, N) Then
            
            // STEP 1: MAKE A CHOICE
            board[row][col] = 1
            
            // STEP 2: RECURSE TO NEXT DECISION POINT
            If SOLVE_UTIL(board, col + 1, N) = true Then
                foundSolution = true
                // Note: Do NOT return immediately if we want ALL solutions
            End If
            
            // STEP 3: UNDO THE CHOICE (BACKTRACK)
            board[row][col] = 0
            
        End If
    End For
    
    Return foundSolution
End Function

/////////////////////////////////////////////////////////////////////////////
// SAFETY CHECK FUNCTION
/////////////////////////////////////////////////////////////////////////////

Function IS_SAFE(board, row, col, N)
Input: 
    board - Current board state
    row   - Row being considered for queen placement
    col   - Column being considered
    N     - Board size
Output:
    true if position (row, col) is safe, false otherwise

Begin
    // Since we place queens left-to-right (col 0 to N-1),
    // we ONLY need to check positions in columns < current column
    
    // CHECK 1: Same Row (Horizontal Attack)
    For c = 0 to col-1 Do
        If board[row][c] == 1 Then
            Return false    // Another queen in same row to the left
        End If
    End For
    
    // CHECK 2: Upper-Left Diagonal Attack
    // Moving up and left from current position
    r = row
    c = col
    While r >= 0 AND c >= 0 Do
        If board[r][c] == 1 Then
            Return false    // Queen on upper-left diagonal
        End If
        r = r - 1
        c = c - 1
    End While
    
    // CHECK 3: Lower-Left Diagonal Attack
    // Moving down and left from current position
    r = row
    c = col
    While r < N AND c >= 0 Do
        If board[r][c] == 1 Then
            Return false    // Queen on lower-left diagonal
        End If
        r = r + 1
        c = c - 1
    End While
    
    // If all checks passed, position is safe
    Return true
End Function

/////////////////////////////////////////////////////////////////////////////
// PRINT FUNCTION
/////////////////////////////////////////////////////////////////////////////

Function PRINT_SOLUTION(board, N)
Begin
    Print "--- Solution " + solutionCount + " ---"
    For i = 0 to N-1 Do
        For j = 0 to N-1 Do
            If board[i][j] == 1 Then
                Print " Q "
            Else
                Print " . "
            End If
        End For
        Print newline
    End For
    Print newline
End Function



Step-by-Step Execution:

Column 0:
├─ Try Row 0: Place Q at (0,0) ✓
│  │
│  Column 1:
│  ├─ Try Row 0: Unsafe (same row)
│  ├─ Try Row 1: Unsafe (diagonal from (0,0))
│  ├─ Try Row 2: Place Q at (2,1) ✓
│  │  │
│  │  Column 2:
│  │  ├─ Try Row 0: Unsafe (diagonal from (2,1))
│  │  ├─ Try Row 1: Unsafe (diagonal from (0,0))
│  │  ├─ Try Row 2: Unsafe (same row)
│  │  ├─ Try Row 3: Unsafe (diagonal)
│  │  └─ No row works → BACKTRACK from Column 2
│  │
│  ├─ Try Row 3: Place Q at (3,1) ✓
│  │  │
│  │  Column 2:
│  │  ├─ Try Row 1: Place Q at (1,2) ✓
│  │  │  │
│  │  │  Column 3:
│  │  │  ├─ Try Row 0: Unsafe (diagonal)
│  │  │  ├─ Try Row 1: Unsafe (same row)
│  │  │  ├─ Try Row 2: Unsafe (diagonal)
│  │  │  ├─ Try Row 3: Unsafe (same column)
│  │  │  └─ No row works → BACKTRACK from Column 3
│  │  │
│  │  └─ BACKTRACK: Remove Q from (1,2)
│  │
│  └─ BACKTRACK: Remove Q from (3,1)
│
├─ Try Row 1: Place Q at (1,0) ✓
│  │
│  Column 1:
│  ├─ Try Row 3: Place Q at (3,1) ✓
│  │  │
│  │  Column 2:
│  │  ├─ Try Row 0: Place Q at (0,2) ✓
│  │  │  │
│  │  │  Column 3:
│  │  │  ├─ Try Row 2: Place Q at (2,3) ✓
│  │  │  │  │
│  │  │  │  └─ Column 4 >= 4 → SOLUTION FOUND #1!
│  │  │  │     Board:
│  │  │  │     . Q . .
│  │  │  │     . . . Q
│  │  │  │     Q . . .
│  │  │  │     . . Q .
│  │  │  │
│  │  │  └─ BACKTRACK: Remove Q from (2,3)
│  │  │
│  │  └─ BACKTRACK: Remove Q from (0,2)
│  │
│  └─ BACKTRACK: Remove Q from (3,1)
│
└─ Continue until all possibilities explored...

Final Result: 2 solutions found for N=4


Upper-Left Diagonal:
for (i=row, j=col; i>=0 && j>=0; i--, j--)

Lower-Left Diagonal:
for (i=row, j=col; i<N && j>=0; i++, j--)


                    [Start]
                       |
            __________col=0__________
           /      /       \          \
        (0,0)  (1,0)     (2,0)      (3,0)
          |      |         |          |
       col=1   col=1     col=1      col=1
       /   \     |         |          |
    (2,1)(3,1)(3,1)    (0,1)      (0,1)
      |    |     |        |          |
    col=2 col=2 col=2   col=2      col=2
      X    |     |        |          |
         (1,2) (0,2)   (2,2)      (1,2)
           |     |        |          |
         col=3 col=3    col=3      col=3
           X     |        |          |
              (2,3)    (3,3)      (3,3)
                 |        |          |
              SOL 1       X        SOL 2
