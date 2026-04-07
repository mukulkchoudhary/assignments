#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char response[BUFFER_SIZE];
    char operation[10];
    double num1, num2, result;
    
    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    
    // Listen
    listen(server_fd, 3);
    printf("Calculator Server Started. Waiting for client...\n");
    printf("Supported operations: +, -, *, /, %%\n\n");
    
    while(1) {
        // Accept client
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        printf("Client connected!\n");
        
        while(1) {
            memset(buffer, 0, BUFFER_SIZE);
            
            // Receive calculation request from client
            if(read(new_socket, buffer, BUFFER_SIZE) <= 0) {
                printf("Client disconnected!\n");
                break;
            }
            
            // Remove newline character
            buffer[strcspn(buffer, "\n")] = 0;
            
            printf("Client request: %s\n", buffer);
            
            // Check for exit command
            if(strcmp(buffer, "exit") == 0) {
                printf("Exit command received. Disconnecting client...\n");
                send(new_socket, "Goodbye!", 8, 0);
                break;
            }
            
            // Parse input: operand1 operator operand2
            if(sscanf(buffer, "%lf %s %lf", &num1, operation, &num2) == 3) {
                
                // Perform calculation based on operator
                if(strcmp(operation, "+") == 0) {
                    result = num1 + num2;
                    sprintf(response, "%.2lf + %.2lf = %.2lf", num1, num2, result);
                }
                else if(strcmp(operation, "-") == 0) {
                    result = num1 - num2;
                    sprintf(response, "%.2lf - %.2lf = %.2lf", num1, num2, result);
                }
                else if(strcmp(operation, "*") == 0) {
                    result = num1 * num2;
                    sprintf(response, "%.2lf * %.2lf = %.2lf", num1, num2, result);
                }
                else if(strcmp(operation, "/") == 0) {
                    if(num2 != 0) {
                        result = num1 / num2;
                        sprintf(response, "%.2lf / %.2lf = %.2lf", num1, num2, result);
                    } else {
                        sprintf(response, "Error: Division by zero!");
                    }
                }
                else if(strcmp(operation, "%") == 0) {
                    if((int)num2 != 0) {
                        result = (int)num1 % (int)num2;
                        sprintf(response, "%.0lf %% %.0lf = %.0lf", num1, num2, result);
                    } else {
                        sprintf(response, "Error: Modulo by zero!");
                    }
                }
                else {
                    sprintf(response, "Error: Invalid operator! Use +, -, *, /, %%");
                }
            }
            else {
                sprintf(response, "Error: Invalid format! Use: number operator number\nExample: 10 + 5");
            }
            
            send(new_socket, response, strlen(response), 0);
            printf("Sent result to client\n");
        }
        
        close(new_socket);
        printf("Client disconnected. Waiting for next connection...\n\n");
    }
    
    close(server_fd);
    return 0;
}





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char request[BUFFER_SIZE];
    
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    // Connect
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed!\n");
        return -1;
    }
    
    printf("Connected to Calculator Server!\n");
    printf("Format: number operator number\n");
    printf("Operators: + (add), - (subtract), * (multiply), / (divide), %% (modulo)\n");
    printf("Type 'exit' to disconnect\n\n");
    
    while(1) {
        printf("Enter calculation: ");
        fgets(request, BUFFER_SIZE, stdin);
        
        // Remove newline
        request[strcspn(request, "\n")] = 0;
        
        // Send request to server
        send(sock, request, strlen(request), 0);
        
        // Receive response
        memset(buffer, 0, BUFFER_SIZE);
        if(read(sock, buffer, BUFFER_SIZE) <= 0) {
            printf("Server disconnected!\n");
            break;
        }
        
        printf("Result: %s\n\n", buffer);
        
        // If exit command, break
        if(strcmp(request, "exit") == 0) {
            break;
        }
    }
    
    close(sock);
    return 0;
}
