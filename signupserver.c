#include <stdio.h>

#define REGISTER_FILE "signup.txt"
#define BUF_LENGTH 1024


char * signupserver(char buf[BUF_LENGTH])
{
	FILE *fp;
	char *returnMsg,*token;
	
	fp=fopen(REGISTER_FILE,"a");
	if(fp==NULL)
	{
		returnMsg = "Error in opening file..!!\nRegistration Failed..!!";
		return returnMsg;
	}
	token = strtok(buf,",");
	token = strtok(NULL,"\n");
	fprintf(fp,"%s\n",token);
	fclose(fp);
	return "Registration Successful";
}