#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "constants.h"

int main() {
    int client_soc;
    struct sockaddr_in server_addr;
    // char buffer[MAX_BUFFER_SIZE];
    // const char* message = "Hello from client";

    // Creating socket file descriptor
    if ((client_soc = socket(AF_INET, SOCK_STREAM,0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Client socket created successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server
    if (connect(client_soc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
   // printf("Client to server connection successfully established\n");

    char server_response_buff[256];
    memset(server_response_buff, 0, sizeof(server_response_buff));
    int valread=read(client_soc,server_response_buff,sizeof(server_response_buff));
    printf("Server response : ",server_response_buff);

    send(client_soc,HELLO_MSG_FROM_CLIENT ,strlen(HELLO_MSG_FROM_CLIENT), 0);
    printf("\nMessage sent to the server\n");

    return 0;
}
