#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

#define BUF_LENGTH 1024
#define FILE_LENGTH 30
#define CATALOG_FILE "catalog.txt"
#define CART_FILE "cart.txt"

void err_checkout(char *error_msg)
{
	perror(error_msg);
	return;
}

char * checkoutserver (char buf[BUF_LENGTH])
{
	FILE *fp,*fp1;	
	DIR* pdir;
	int check;
	time_t now;
	struct tm *tm;
	char dir_name[BUF_LENGTH],choice[1];
	char file_name[FILE_LENGTH],*token;
	char path[FILE_LENGTH],content,*msg1,*msg2,*msg3;
	char line[BUF_LENGTH],*del_address;

	now = time(0);

	if ((tm = localtime (&now)) == NULL)
	{
		return "Error extracting time stuff\n";
	}

	sprintf (dir_name,"%02d-%02d-%04d",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900);
	sprintf (file_name,"%02d%02d%04d%02d%02d%02d",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900,tm->tm_hour, tm->tm_min, tm->tm_sec);
	chdir("Server");
	pdir=opendir(dir_name);

	if(pdir==NULL)
	{
		mkdir(dir_name,0777);
	}

	strcat(dir_name,"/");
	strcat(dir_name,file_name);
	fp=fopen(dir_name,"a+");
	
	while(1)
	{
		if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen)==-1)
			err_checkout("recvfrom()");
		token = strtok(buf,",");
		if(strcmp(token,"DA")==0)
		{
			fprintf(fp,"%s\n",buf);
			return;
		}

		fprintf(fp,"%s\n",buf);
	}

	fclose(fp);
	return "Checkout Successful";
}