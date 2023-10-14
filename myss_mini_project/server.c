#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "constants.h"
#include "menu.h"
#include "admin.h"
#include "utilities.h"

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



void process_command(const char *command) 
{
    printf("\nReceived command: %s\n", command);
}





char get_role(int client_soc) 
{   
    char buffer[1024];
    char command_buffer[1024];
    int buffer_index = 0;
    char role=' ';
    char *prompt=MAIN_MENU_MSG_CONST;
    for(int i=0;i<1;i++) 
    {
        
            send(client_soc,prompt,strlen(prompt),0);
            int bytes_received = recv(client_soc, buffer, sizeof(buffer), 0);
            if (bytes_received <= 0) 
            {
                break;
            }
    
        
        role=buffer[0];
    }
    return role;
}


void handle_client(int client_soc){
    int bytes_to_recv=256;
    int n;
    char buffer[256];

    
    char role=get_role(client_soc);
 
        
    switch(role){
        case '1': clear_buff(buffer);
                handleAdmin(client_soc);
                break;
        default:printf("\nEnter valid choice");
    }
}


int main() {
    int client_soc;
    char send_buff[256],recv_buff[256];

    int server_soc=init_server();

    struct sockaddr_in client_addr;


    int client_addr_len;
for(;;){
        client_soc = accept(server_soc,(struct sockaddr*)&client_addr,&client_addr_len);
        if (client_soc < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("Client connected\n");
        printf("Recieved connection request from a client\n");

        pid_t pid = fork();
        if (pid == -1) 
        {
            perror("Error creating child process");
            close(client_soc);
            continue; 
        }
        if (pid == 0) 
        {
            close(server_soc); 
            handle_client(client_soc);
            exit(EXIT_SUCCESS); 
        }
        close(client_soc);
}
return 0;
}

  

