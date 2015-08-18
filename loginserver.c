#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define REGISTER_FILE "signup.txt"
#define NAME_LENGTH 50
#define PASSWORD_LENGTH 8
#define BUF_LENGTH 1024


char * loginserver(char buf[BUF_LENGTH])
{
	FILE* fp;
	char *line = NULL;
	char *token;
	size_t len = 0;
	ssize_t read;
	int i;
	int uname_flag = 0, pwd_flag=0;
	char *returnMsg;

	fp=fopen(REGISTER_FILE,"r");

	if(fp==NULL)
		printf("Error in opening file..!!\n");

	else
	{
	}

	char *uname,*password,*fname;
	token = strtok(buf,",");
	token = strtok(NULL,",");
	uname = strdup(token);
	password = strtok(NULL,"\n");
	
	while ((read = getline(&line, &len, fp)) != -1)
	{
		i=0;
		token = strtok(line,",");

		while(token!=NULL)
		{
			i++;
			if(i==1)
			{
				if(strcmp(uname,token)==0)
				{
					uname_flag=1;
				}
				else
					token = strtok(NULL,",");
			}
			if( uname_flag==1 )
			{
				token = strtok (NULL, ",");
				if(strcmp(password,token)==0)
				{
					pwd_flag=1;
					token = strtok (NULL, ",");
					fname = strdup(token);
				}
				uname_flag=0;
			}
			token = strtok (NULL, ",");
		}
	}

	if(pwd_flag==1)
	{
		sprintf(returnMsg,"Login Successful\nHi %s, Welcome!!!\n",fname);
		printf("%s\n",returnMsg);
		return returnMsg;
	}

	else
	{
		sprintf(returnMsg,"Login Failed.\nPlease Try Again..!!\nIf you are a new user, use signup to continue\n");
		printf("%s\n",returnMsg );
		return returnMsg;
	}
}