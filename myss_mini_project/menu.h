#ifndef MENU_H
#define MENU_H
#include<stdio.h>
void StudentMenu(){
	printf("################# Welcome to Student Menu #################\n");
	printf("1.View All Courses\n");
	printf("2.Enroll (pick) new Course\n");
	printf("3.Drop Course\n");
	printf("4.View Enrolled Course Details\n");
	printf("5.Change Password\n");
	printf("6.Logout and Exit\n");
	printf("Enter Your Choice:\n");
}
void AdminMenu(){
	printf("################# Welcome to Admin Menu #################\n");
	printf("1.Add Student\n");
	printf("2.View Student Details\n");
	printf("3.Add Faculty\n");
	printf("4.View Faculty Details\n");
	printf("5.Activate Student\n");
	printf("6.Block Student\n");
	printf("7.Modify Student Details\n");
	printf("8.Modify Faculty Details\n");
	printf("9.Logout and Exit\n");
	printf("Enter Your Choice:\n");
}
void FacultyMenu(){
	printf("################# Welcome to Faculty Menu #################\n");
	printf("1.View Offering Courses\n");
	printf("2.Add new Course\n");
	printf("3.Remove Course from Catalog\n");
	printf("4.Update Course Details\n");
	printf("5.Change Password\n");
	printf("6.Logout and Exit\n");
	printf("Enter Your Choice:\n");
}
void MainMenu(){
	printf("################# Welcome Back to Academia:: Course Registration #################\n");
	printf("Login Type\n");
	printf("Enter Your Choice{1.Admin , 2.Professor , 3.Student }:\n");
}
#endif