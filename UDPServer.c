#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "signupserver.c"
#include "loginserver.c"
#include "addtocartserver.c"
#include "removefromcartserver.c"

#define CATALOG_FILE "catalog.txt"
#define CART_FILE "cart.txt"
#define BUFLEN 1024
#define FILE_LENGTH 30
#define PORT 9930

struct sockaddr_in my_addr, cli_addr;
int sockfd;
socklen_t slen=sizeof(cli_addr);                                            /* length of client  ip address */
char buf[BUFLEN],temp[BUFLEN],*returnMsg,*add_returnMsg;

void err_server(char *error_msg)
{
	perror(error_msg);
	return;
}

void createconnection()
{

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)            /* creation of server socket */
		err_server("Error in creating socket");
	else
		printf("Socket created successfully\n");
 
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 
	if (bind(sockfd, (struct sockaddr* ) &my_addr, sizeof(my_addr))==-1)
		err_server("bind");
	else
		printf("bind successful\n");
}
 
 int checkval(char *header)
 {
 	int ch=0;
 	if(strcmp(header,"signup")==0)
 		ch=1;
 	else if(strcmp(header,"login")==0)
 		ch=2;
 	else if(strcmp(header,"logout")==0)
 		ch=3;
 	else if(strcmp(header,"viewcatalog")==0)
 		ch=4;
 	else if(strcmp(header,"search")==0)
 		ch=5;
 	else if(strcmp(header,"addtocart")==0)
 		ch=6;
 	else if(strcmp(header,"removefromcart")==0)
 		ch=8;
 	else if(strcmp(header,"checkout")==0)
 		ch=9;
 	return ch;
 }

int main()
{
	DIR* pdir;
	FILE *fp,*fp1;
	char *header,*token,temp_checkout[BUF_LENGTH];
	char line[BUFLEN],*keyword,*dollar="$",dir_name[BUF_LENGTH],choice[1];
	int ch,check;
	time_t now;
	struct tm *tm;
	char file_name[FILE_LENGTH],path[FILE_LENGTH],content,*del_address;

	createconnection();
	printf("connection created successfully\n");

	while(1)
	{
		if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&cli_addr, &slen)==-1)
			err_server("recvfrom()");
		printf("Received packet from %s:%d\nData: %s\n\n",
			inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), buf);
		strcpy(temp,buf);
		header = strtok(buf,",");

		ch = checkval(header);

		switch(ch)
		{
			case 1:
				returnMsg = signupserver(temp);
				break;

			case 2:
				returnMsg = loginserver(temp);
				break;

			case 3:
				returnMsg = "Logout successful\n";
				break;

			case 4:
				fp=fopen(CATALOG_FILE,"r");
				if(fp==NULL)
				{
					printf("Error in opening file..!!\n");
					break;
				}

				while(fgets(line,sizeof(line),fp)!=NULL)
				{
					if (sendto(sockfd, line, BUFLEN, 0, (struct sockaddr*)&cli_addr, slen)==-1)
					{
						err_server("sendto()");
						break;
					}
				}
				if (sendto(sockfd, "$", BUFLEN, 0, (struct sockaddr*)&cli_addr, slen)==-1)
				{
					err_server("sendto()");
					break;
				}
				fclose(fp);
				break;

			case 5:
				keyword = strtok(NULL,"\n");
				printf("keyword = %s\n", keyword);
				fp=fopen(CATALOG_FILE,"r");
				if(fp==NULL)
					printf("Error in opening file..!!\n");
				else
				{
					while(fgets(line,sizeof(line),fp)!=NULL)
					{
						strcpy(temp,line);
						token=strtok(line," ,-.");
						while(token!=NULL)
						{
							if(strcasecmp(token,keyword)==0)
								if (sendto(sockfd, temp, BUFLEN, 0, (struct sockaddr*)&cli_addr, slen)==-1)
									err_server("sendto()");
							token=strtok(NULL," ,-.");
						}
					}
				}
				fclose(fp);

				if (sendto(sockfd, "$", BUFLEN, 0, (struct sockaddr*)&cli_addr, slen)==-1)
					err_server("sendto()");
				break;

			case 6:
				returnMsg = addtocartserver(temp);
				break;

			case 8:
				returnMsg = removefromcartserver(temp);
				break;

			case 9:
				now = time(0);

				if ((tm = localtime (&now)) == NULL)
				{
					 printf("Error extracting time stuff\n");
					 break;
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
						err_server("recvfrom()");

					strcpy(temp_checkout,buf);

					token = strtok(buf,",");

					if(strcmp(token,"DA")==0)
					{
						fprintf(fp,"%s\n",temp_checkout);
						break;
					}

					fprintf(fp,"%s",temp_checkout);
				}

				fclose(fp);
				break;

			default:
				printf("Error..!!\n");
		}

		if(ch!=4||ch!=5||ch!=7)
		{
			if (sendto(sockfd, returnMsg, BUFLEN, 0, (struct sockaddr*)&cli_addr, slen)==-1)
				err_server("sendto()");
		}
		
	}

	close(sockfd);
	return 0;
}