#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>


#define SERVER_IP "192.168.1.188"
//#define SERVER_IP "127.0.0.1"
#define BUFLEN 1024
#define PORT 9930


void err_msg(char *error_msg)
{
	perror(error_msg);
	return;
}

int viewcatalog()
{
	int reply;

	char *token;
	char buf[BUFLEN];

	struct sockaddr_in serv_addr;
	int sockfd, i, slen=sizeof(serv_addr);
 
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
		err_msg("socket");

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_aton(SERVER_IP, &serv_addr.sin_addr)==0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		return 0;
	}

	strcpy(buf,"viewcatalog");

	if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
			err_msg("sendto()");


	while(1)
	{
		if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, &slen)==-1)
			err_msg("recvfrom()");

		if(buf[0]=='$')
			break;

		token=strtok(buf,",");
		while(token!=NULL)
		{
			printf("____________________________________________________________________________________________________________________________________________");
			printf("\nItem id\t\t:\t%s",token);
			token=strtok(NULL,",");
	
			printf("\nItem name\t:\t%s",token);
			token=strtok(NULL,",");

			printf("\nDescription\t:\t%s",token);
			token=strtok(NULL,",");

			printf("\nRate\t\t:\t%s",token);
			token=strtok(NULL,",");

			printf("\nAvailability\t:\t%d\n",atoi(token));
			token=strtok(NULL,",");
		}
	}
	printf("____________________________________________________________________________________________________________________________________________");
}
