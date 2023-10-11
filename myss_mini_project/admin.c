#include<unistd.h>
//#include<fcntl.h>
#include<stdio.h>

int main(void) {
	struct Admin{
	char name[100];
	char emailId[100];
	char password[100];
}a;

	//int fd = open("admin", O_CREAT | O_RDWR, 0600);
	strcpy(a.name, "admin");
    strcpy(a.emailId, "adminiiitb@gmail.com");
    strcpy(a.password, "admpwd");
	//write(fd, &a, sizeof(struct Admin));
    printf("%s %s %s",a.name,a.emailId,a.password);
    //close(fd);
	return 0;
}