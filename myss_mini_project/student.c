//#include "student.h"
//#include "config.h"
#include "headers.h"
#include <stdbool.h>
#include "utilities.c"
#include "student.h"



int add_stud(int client_soc){
   

    struct Student stud, tmp_stud;
    struct Course course, tmp_corse;
    int fd = open("data_files/student_data.txt", O_RDWR);
    char recv_buff[20], roll_no[20] = "MT2023";
    int n, status = 0;
    char *str;

    clear_buff(recv_buff);
 //   memset(recv_buff, 0, sizeof(recv_buff));
    str = "Name: ";
    write(client_soc, str, strlen(str));
    n = read_line(client_soc, recv_buff, sizeof(recv_buff));
    str_cpy(stud.name, recv_buff);

    clear_buff(recv_buff);
//    memset(recv_buff, 0, sizeof(recv_buff));
    str = "Roll number(in the format MT2023001[Enter last 3 digits]): ";
    write(client_soc, str, strlen(str));
    n = read_line(client_soc, recv_buff, sizeof(recv_buff));
    stud.age = atoi(recv_buff);

    clear_buff(recv_buff);
//    memset(recv_buff, 0, sizeof(recv_buff));
    str = "Age: ";
    write(client_soc, str, strlen(str));
    n = read_line(client_soc, recv_buff, sizeof(recv_buff));
    stud.age = atoi(recv_buff);

    clear_buff(recv_buff);
//    memset(recv_buff, 0, sizeof(recv_buff));
    str = "Email: ";
    write(client_soc, str, strlen(str));
    n = read_line(client_soc, recv_buff, sizeof(recv_buff));
    str_cpy(stud.email_id, recv_buff);

    clear_buff(recv_buff);
//    memset(recv_buff, 0, sizeof(recv_buff));
    str = "Password: ";
    write(client_soc, str, strlen(str));
    n = read_line(client_soc, recv_buff, sizeof(recv_buff));
    str_cpy(stud.password, recv_buff);

    stud.active_status=true;

   

    //char* buff=(char*)malloc(sizeof(stud));
    //lseek(fd,(recordno-1)*sizeof(stud),SEEK_SET);

    int bytesWrote=write(fd,&stud, sizeof(stud));
    write(fd,"\n",1);
    
    printf("\nStudent added succesfully.");
	

    return status;
}

// int view_stud_details(int client_soc){
//     int status;

//      struct faculty st;
//     int fd = open("student_details", O_RDWR);
//     char recv_buff[20], roll_no[10];
//     int n, status = 0;
//     char *str;
    
//     memset(recv_buff, 0, sizeof(recv_buff));
//     str = "Roll Number: ";
//     write(client_soc, str, strlen(str));
//     n = read_line(client_soc, recv_buff, sizeof(recv_buff));
//     my_strcpy(roll_no, recv_buff);
//     while(1) {
//         n = read(fd, &st, sizeof(struct faculty));
//         if(n < 0) {
//             perror("read");
//             _exit(EXIT_FAILURE);
//         }
//         if(n == 0) break;
//         if(strcmp(stud.roll_no, roll_no) == 0) {
//             str = "Name: ";
//             send(client_soc, str, strlen(str), MSG_DONTWAIT);
//             send(client_soc, stud.name, strlen(stud.name), MSG_DONTWAIT);

//             str = "\nAge: ";
//             send(client_soc, str, strlen(str), MSG_DONTWAIT);
//             my_itoa(stud.age, buff, 10);
//             send(client_soc, buff, strlen(buff), MSG_DONTWAIT);

//             str = "\nEmail: ";
//             send(client_soc, str, strlen(str), MSG_DONTWAIT);
//             send(client_soc, stud.email, strlen(stud.email), MSG_DONTWAIT);

//             str = "\nAddress: ";
//             send(client_soc, str, strlen(str), MSG_DONTWAIT);
//             send(client_soc, stud.address, strlen(stud.address), MSG_DONTWAIT);

//             str = "\nLogin-id: ";
//             send(client_soc, str, strlen(str), MSG_DONTWAIT);
//             send(client_soc, stud.roll_no, strlen(stud.roll_no), MSG_DONTWAIT);

//             write(client_soc, "\n", 1);

//             status = 1;
//             break;
//         }
//     }
//     if(!status) {
//         str = "Student not found\n";
//         write(client_soc, str, strlen(str));
//     }
//     close(fd);


//     return status;
// }

int activate_stud(int client_soc){
    int status;
    return status;
}

int block_stud(int client_soc){
    int status;
    return status;
}

int mod_stud_details(int client_soc){
    int status;
    return status;
}



int viewStudent(int client_socket) {
   
}