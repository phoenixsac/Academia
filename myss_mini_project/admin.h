#include<unistd.h>
#include<stdio.h>
#include "constants.h"
#include "utilities.h"
#include "student.h"


char send_buff[1024],recv_buff[1024];

struct Admin{
	char name[100];
	char emailId[100];
	char password[100];
}a;


void fill_admin(){
	strcpy(a.name, "admin");
    strcpy(a.emailId, "adminiiitb@gmail.com");
    strcpy(a.password, "admpwd");
    printf("%s %s %s",a.name,a.emailId,a.password);

}


int handleAdmin(int client_soc){
	//authentication with username and pass
	clear_buff(send_buff);

	write(client_soc,ADMIN_UN,strlen(ADMIN_UN));
	char username[20];
	clear_buff(recv_buff);
	int n1=read_line(client_soc, recv_buff, sizeof(recv_buff));
	str_cpy(username,recv_buff);

	char pwd[20];
	clear_buff(send_buff);

	write(client_soc,ADMIN_PWD,strlen(ADMIN_PWD));
	clear_buff(recv_buff);
	int n2=read_line(client_soc, recv_buff, sizeof(recv_buff));
	str_cpy(pwd,recv_buff);
	clear_buff(send_buff);



	fill_admin();
	int status=1;

	if (strcmp(a.name, username) == 0 && strcmp(a.password, pwd) == 0)
	{
		while(status){
			write(client_soc,ADMIN_MENU_MSG_CONST,sizeof(ADMIN_MENU_MSG_CONST));
			clear_buff(recv_buff);
			read_line(client_soc,recv_buff,sizeof(recv_buff));

			switch(atoi(recv_buff)){
				case 1 :add_stud(client_soc); 
						break;
				// case 2: view_stud_details(client_soc);
				// 		break;
				// case 3 :add_fac(client_soc);
				// 		break;
				// case 4 :view_fac_details(client_soc); 
				// 		break;
				// case 5 :activate_stud(client_soc);
				// 		break;
				// case 6 :block_stud(client_soc);
				// 		break;
				// case 7 :mod_stud_details(client_soc);
				// 		break;
				// case 8 :mod_fac_details(client_soc);
				// 		break;
				case 9 :write(client_soc, CONN_CLOSE_MSG, strlen(CONN_CLOSE_MSG));
                		status = 0;
                		break;
			}
		}
	}
	else{
		write(client_soc,INV_ADMIN,sizeof(INV_ADMIN));
	}


	return 0;
}


	


