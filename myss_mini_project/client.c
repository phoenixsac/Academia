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

    char send_buff[256],recv_buff[256];
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
    int connect_status=connect(client_soc, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connect_status < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    else if(connect_status==0)
        printf("Connection was successful.");
    //printf("Client to server connection successfully established\n");

    //char server_response_buff[256];

    memset(send_buff, 0, sizeof(send_buff));
   // send_buff=HELLO_MSG_FROM_CLIENT;
    //send_buff = HELLO_MSG_FROM_CLIENT;
    strcpy(send_buff,"Hi from client side.");
    if(send(client_soc,&send_buff,strlen(send_buff), 0)!=-1)
        printf("\nMessage sent to the server\n");

    memset(recv_buff, 0, sizeof(recv_buff));
    int valread=read(client_soc,recv_buff,sizeof(recv_buff));
    if(valread!=-1)
        printf("Server response : ",recv_buff);

    return 0;
}
