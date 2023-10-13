//student.h
#ifndef STUDENT_H
#define STUDENT_H


struct Student{
	char name[100];
	char roll_no[20];
    int age;
	char email_id[25];
	char password[30];
    bool active_status;
	int status;
	struct Course course_enrolled[6];
}stud;

struct Course{
	char course_name[50];
}course;

int add_stud(int client_soc);
#endif
