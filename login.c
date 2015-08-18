#include <stdio.h>
#include <string.h>

#define REGISTER_FILE "signup.txt"
#define NAME_LENGTH 50
#define PASSWORD_LENGTH 8

int login()
{
	int reply = 0;
	char buf[BUF_LENGTH];

	char uname[NAME_LENGTH],password[PASSWORD_LENGTH];
	printf("Username: ");
	scanf("%s",uname);
	printf("Password: ");
	scanf("%s",password);

	sprintf(buf,"%s,%s,%s\n","login",uname,password);
	reply = sendtoserver(buf);
	if(reply==0)
		return 0;
	else
		return 1;
}