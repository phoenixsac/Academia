#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "constants.h"
#include "utilities.c"
#include "read_line.c"

int client_soc;
char send_buff[1024],recv_buff[1024];

int connect_client(){
   
    struct sockaddr_in server_addr;

    // Creating socket file descriptor
    if ((client_soc = socket(AF_INET, SOCK_STREAM,0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Client socket created successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    return connect(client_soc, (struct sockaddr *)&server_addr, sizeof(server_addr));
}

// void clear_buff(char* buff_to_clr){
//     memset(buff_to_clr, 0, sizeof(buff_to_clr));
// }

// void send_to_server(){
    
//     clear_buff(send_buff);
//     ssize_t usr_inp_len=read(STDIN_FILENO, send_buff, sizeof(send_buff));

//     if (usr_inp_len <= 0) {
//         perror("Input read error");
//         break; // Exit the loop if there's an error
//     }

//     if (send_buff[usr_inp_len - 1] == '\n') {
//         send_buff[usr_inp_len - 1] = '\0';
//         usr_inp_len--; // Adjust the length to exclude the newline
//     }

//     write(client_soc, send_buff, usr_inp_len);
// }





int main() {
     
    // Connect to the server
    int connect_status=connect_client();
    if (connect_status < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    else if(connect_status==0)
        printf("Connection was successful.");

    while(read(client_soc, recv_buff, sizeof(recv_buff)) > 0) {   
        
        write(STDOUT_FILENO, recv_buff, strlen(recv_buff));
        clear_buff(send_buff); 

        // ssize_t usr_inp_len=read(STDIN_FILENO, send_buff, sizeof(send_buff));
        // if (usr_inp_len <= 0) {
        // perror("Input read error");
        // break; // Exit the loop if there's an error
        // }

        // if (send_buff[usr_inp_len - 1] == '\n') {
        //     send_buff[usr_inp_len - 1] = '\0';
        //     usr_inp_len--; // Adjust the length to exclude the newline
        // }

        int n=read_line(STDIN_FILENO, send_buff, sizeof(send_buff));
        printf("read_line out",n);
        write(client_soc, send_buff, strlen(send_buff));

        //clear_buff(recv_buff);
    } 

    close(client_soc);
}
