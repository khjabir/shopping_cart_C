#include <stdio.h>
#include <string.h>
//#include "sendtoserver.c"

#define NAME_LENGTH 50
#define ADDRESS_LENGTH 128
#define PASSWORD_LENGTH 8
#define MOB_NUM_LENGTH 10
#define BUF_LENGTH 1024
#define REGISTER_FILE "signup.txt"

void signup()
{

	int reply = 0;
	char buf[BUF_LENGTH];

	char fname[NAME_LENGTH], lname[NAME_LENGTH], uname[NAME_LENGTH], password[PASSWORD_LENGTH], cpassword[PASSWORD_LENGTH];
	char address[ADDRESS_LENGTH], mob[MOB_NUM_LENGTH];
	int pwd_flag=0;

	getchar();
	printf("First Name: ");
	scanf("%s",fname);

	printf("Last Name: ");
	scanf("%s",lname);

	printf("Username (e-mail address): ");
	scanf("%s",uname);

	do
	{

		if( pwd_flag>0 )
			printf("Password Mismatch..!!\nPlease try again..!!\n");

		printf("Password: ");
		scanf("%s",password);

		printf("Confirm Password: ");
		scanf("%s",cpassword);
		pwd_flag++;
	} while( strcmp( password,cpassword ) !=0 );

	printf("Address: ");
	getchar();
	scanf("%[^\n]",address);

	printf("Contact Number: ");
	scanf("%s",mob);

	sprintf(buf,"%s,%s,%s,%s,%s,%s,%s\n","signup",uname,password,fname,lname,address,mob);
	reply = sendtoserver(buf);

	if(reply==1)
		printf("Registration Succesfull, Login to continue\n");
	else
		printf("Registration Failed, Please Try Again..!!\n");

}