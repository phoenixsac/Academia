#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "constants.h"



int main() {
    int server_soc,client_soc;
    
    server_soc=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr,client_addr;

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    bind(server_soc,(struct sockaddr*)&server_addr,sizeof(server_addr));

    listen(server_soc,3);
    printf("Server up at port 8080...\n");

    int client_addr_len;
    client_soc=accept(server_soc,(struct sockaddr*)&client_addr,&client_addr_len);

    printf("Recieved connection request from a client\n");

    send(client_soc, SERVER_CONN_SUCCESS_MSG, sizeof(SERVER_CONN_SUCCESS_MSG),0);

    char client_response_buff[256];
    memset(client_response_buff, 0, sizeof(client_response_buff));
    int valread=read(server_soc,client_response_buff,sizeof(client_response_buff));
    printf("Client message : ",client_response_buff);

    close(client_soc);

    return 0;
}
