#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char date_time[BUFFER_SIZE];
    
    // Create socket file descriptor
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket options to reuse address
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind socket to port
    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Start listening for connections
    if(listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Date & Time Server Started...\n");
    printf("Server listening on port %d\n", PORT);
    printf("Waiting for client connections...\n\n");
    
    while(1) {
        // Accept client connection
        if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }
        
        printf("Client connected from %s:%d\n", 
               inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        
        // Get current date and time
        time_t current_time;
        struct tm *time_info;
        
        time(&current_time);
        time_info = localtime(&current_time);
        
        // Format date and time
        strftime(date_time, sizeof(date_time), 
                 "Current Date and Time: %A, %B %d, %Y\nTime: %I:%M:%S %p", 
                 time_info);
        
        printf("Sending date and time to client...\n");
        printf("%s\n\n", date_time);
        
        // Send date and time to client
        send(new_socket, date_time, strlen(date_time), 0);
        
        // Close client connection
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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    // Create socket file descriptor
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 address from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/Address not supported\n");
        return -1;
    }
    
    // Connect to server
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }
    
    printf("Connected to Date & Time Server\n");
    printf("Requesting current date and time...\n\n");
    
    // Receive date and time from server
    int valread = read(sock, buffer, BUFFER_SIZE);
    
    if(valread > 0) {
        printf("Server Response:\n");
        printf("=================================\n");
        printf("%s\n", buffer);
        printf("=================================\n");
    } else {
        printf("Failed to receive data from server\n");
    }
    
    // Close connection
    close(sock);
    printf("\nConnection closed. Exiting...\n");
    
    return 0;
}
