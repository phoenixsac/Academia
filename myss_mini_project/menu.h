
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "constants.h"
char* StudentMenu(){
	char* student_menu_msg=(char*)malloc(256);
	strcpy(student_menu_msg,STUDENT_MENU_MSG_CONST);
	return student_menu_msg;
}
char* adminMenu(){
	char* admin_menu_msg=(char*)malloc(256);
	strcpy(admin_menu_msg,ADMIN_MENU_MSG_CONST);
	return admin_menu_msg;
}
char* get_faculty_menu(){
	char* faculty_menu_msg=(char*)malloc(256);
	strcpy(faculty_menu_msg,FAC_MENU_MSG_CONST);
	return faculty_menu_msg;
}
char* get_main_menu(){
	char* main_menu_msg=(char*)malloc(256);
	strcpy(main_menu_msg,MAIN_MENU_MSG_CONST);
	return main_menu_msg;
}
