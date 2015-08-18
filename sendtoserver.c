#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include "updatecart.c"

#define SERVER_IP "192.168.1.188"
//#define SERVER_IP "127.0.0.1"
#define BUFLEN 1024
#define PORT 9930
 
void err(char *error_msg)
{
	perror(error_msg);
	return;
}
 
int sendtoserver(char buf[BUFLEN])
{
	char *token;
	struct sockaddr_in serv_addr;
	int sockfd, i, slen=sizeof(serv_addr);
 
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		err("socket");

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_aton(SERVER_IP, &serv_addr.sin_addr)==0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		return 0;
	}

//-------------------------data sending to the server----------------------------

		if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
			err("sendto()");

//-------------------------data received from the server-------------------------
		if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, &slen)==-1)
			err("recvfrom()");
		else
		{
			printf("Received packet from %s:%d\nData: %s\n\n",
				inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port), buf);

			if(strcmp(buf,"Login Failed.\nPlease Try Again..!!\nIf you are a new user, use signup to continue\n")==0)
				return 0;
			else if(strcmp(buf,"Adding count exceeded\n")==0)
				return 0;
			else if(strcmp(buf,"Item Not Found..!!\n")==0)
				return 2;
			else if(buf[0]=='1')
			{
				token = strtok(buf,",");
				token = strtok(NULL,"\n");

				updatecart(token);
				return 3;
			}
			else
				return 1;
		}
//-------------------------------------------------------------------------------
 
	close(sockfd);
	return 0;
}