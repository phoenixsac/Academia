#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "constants.h"
#include "menu.h"

int init_server(){
    int server_soc;
    
    server_soc=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr,client_addr;

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    bind(server_soc,(struct sockaddr*)&server_addr,sizeof(server_addr));

    listen(server_soc,3);
    printf("Server up at port 8080...\n");
    return server_soc;
}

int main() {
   int client_soc;
    char send_buff[256],recv_buff[256];

    int server_soc=init_server();

    struct sockaddr_in client_addr;


    int client_addr_len;
   // client_soc=accept(server_soc,(struct sockaddr*)&client_addr,&client_addr_len);
while(1){
    client_soc = accept(server_soc,(struct sockaddr*)&client_addr,&client_addr_len);
        if (client_soc < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Client connected\n");
        printf("Recieved connection request from a client\n");
        read(client_soc,send_buff,sizeof(send_buff));
        printf("Client message : %s",send_buff);
}
    memset(send_buff, 0, sizeof(send_buff));
   // send_buff="dasd";
    strcpy(send_buff,SERVER_CONN_SUCCESS_MSG);
    send(client_soc, &send_buff, sizeof(send_buff),0);

   // char client_response_buff[256];
   
    //memset(recv_buff, 0, sizeof(recv_buff));
    memset(send_buff, 0, sizeof(send_buff));
    read(client_soc,send_buff,sizeof(send_buff));
    printf("Client message : %s",send_buff);

    close(client_soc);

    return 0;
}
