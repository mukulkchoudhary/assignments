#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 20

// ==================== QUEUE FOR BFS ====================
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isQueueEmpty(struct Queue* q) {
    return q->front == -1;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX - 1) {
        printf("Queue is full!\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        return -1;
    }
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

// ==================== STACK FOR DFS ====================
struct Stack {
    int items[MAX];
    int top;
};

struct Stack* createStack() {
    struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
    s->top = -1;
    return s;
}

bool isStackEmpty(struct Stack* s) {
    return s->top == -1;
}

void push(struct Stack* s, int value) {
    if (s->top == MAX - 1) {
        printf("Stack is full!\n");
        return;
    }
    s->top++;
    s->items[s->top] = value;
}

int pop(struct Stack* s) {
    if (isStackEmpty(s)) {
        return -1;
    }
    int item = s->items[s->top];
    s->top--;
    return item;
}

// ==================== BFS FUNCTION ====================
void bfs(int graph[MAX][MAX], int vertices, int start) {
    bool visited[MAX] = {false};
    struct Queue* q = createQueue();
    
    visited[start] = true;
    enqueue(q, start);
    
    printf("BFS Traversal: ");
    
    while (!isQueueEmpty(q)) {
        int current = dequeue(q);
        printf("%d ", current);
        
        for (int i = 0; i < vertices; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(q, i);
            }
        }
    }
    printf("\n");
    free(q);
}

// ==================== DFS FUNCTIONS ====================
void dfsRecursiveHelper(int graph[MAX][MAX], int vertices, int current, bool visited[]) {
    visited[current] = true;
    printf("%d ", current);
    
    for (int i = 0; i < vertices; i++) {
        if (graph[current][i] == 1 && !visited[i]) {
            dfsRecursiveHelper(graph, vertices, i, visited);
        }
    }
}

void dfsRecursive(int graph[MAX][MAX], int vertices, int start) {
    bool visited[MAX] = {false};
    printf("DFS Traversal (Recursive): ");
    dfsRecursiveHelper(graph, vertices, start, visited);
    printf("\n");
}

void dfsIterative(int graph[MAX][MAX], int vertices, int start) {
    bool visited[MAX] = {false};
    struct Stack* s = createStack();
    
    visited[start] = true;
    push(s, start);
    
    printf("DFS Traversal (Iterative): ");
    
    while (!isStackEmpty(s)) {
        int current = pop(s);
        printf("%d ", current);
        
        for (int i = vertices - 1; i >= 0; i--) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                push(s, i);
            }
        }
    }
    printf("\n");
    free(s);
}

// ==================== MAIN MENU DRIVEN PROGRAM ====================
int main() {
    int graph[MAX][MAX] = {0};
    int vertices, edges, u, v, start, choice, algo_choice, dfs_choice;
    
    printf("========================================\n");
    printf("   BFS AND DFS TRAVERSAL PROGRAM       \n");
    printf("========================================\n\n");
    
    // Input graph
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    printf("\nEnter edges (u v format, 0-indexed):\n");
    for (int i = 0; i < edges; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
            graph[u][v] = 1;
            graph[v][u] = 1; // Undirected graph
        } else {
            printf("Invalid vertices! Enter again.\n");
            i--;
        }
    }
    
    // Main menu loop
    do {
        printf("\n========================================\n");
        printf("              MAIN MENU                \n");
        printf("========================================\n");
        printf("1. Display Adjacency Matrix\n");
        printf("2. Perform BFS Traversal\n");
        printf("3. Perform DFS Traversal\n");
        printf("4. Compare BFS vs DFS\n");
        printf("5. Exit\n");
        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\nAdjacency Matrix (%d x %d):\n", vertices, vertices);
                printf("    ");
                for (int i = 0; i < vertices; i++)
                    printf("%2d ", i);
                printf("\n    ");
                for (int i = 0; i < vertices; i++)
                    printf("---");
                printf("\n");
                for (int i = 0; i < vertices; i++) {
                    printf("%2d |", i);
                    for (int j = 0; j < vertices; j++) {
                        printf(" %2d", graph[i][j]);
                    }
                    printf("\n");
                }
                break;
                
            case 2:
                printf("\n--- BFS TRAVERSAL ---\n");
                printf("Enter starting vertex (0 to %d): ", vertices - 1);
                scanf("%d", &start);
                if (start >= 0 && start < vertices) {
                    bfs(graph, vertices, start);
                } else {
                    printf("Invalid starting vertex!\n");
                }
                break;
                
            case 3:
                printf("\n--- DFS TRAVERSAL ---\n");
                printf("1. Recursive DFS\n");
                printf("2. Iterative DFS (using Stack)\n");
                printf("Choose method: ");
                scanf("%d", &dfs_choice);
                
                printf("Enter starting vertex (0 to %d): ", vertices - 1);
                scanf("%d", &start);
                
                if (start >= 0 && start < vertices) {
                    if (dfs_choice == 1) {
                        dfsRecursive(graph, vertices, start);
                    } else if (dfs_choice == 2) {
                        dfsIterative(graph, vertices, start);
                    } else {
                        printf("Invalid choice!\n");
                    }
                } else {
                    printf("Invalid starting vertex!\n");
                }
                break;
                
            case 4:
                printf("\n========== BFS vs DFS COMPARISON ==========\n");
                printf("Enter starting vertex for comparison: ");
                scanf("%d", &start);
                if (start >= 0 && start < vertices) {
                    printf("\n--- Using same graph and start vertex %d ---\n\n", start);
                    bfs(graph, vertices, start);
                    dfsRecursive(graph, vertices, start);
                    dfsIterative(graph, vertices, start);
                    
                    printf("\n--- OBSERVATION ---\n");
                    printf("BFS explores level by level (breadth-wise)\n");
                    printf("DFS explores depth-wise before backtracking\n");
                } else {
                    printf("Invalid starting vertex!\n");
                }
                break;
                
            case 5:
                printf("\nExiting program. Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
    
    return 0;
}
