#include <stdio.h>

#define SERVER_IP "192.168.1.188"
//#define SERVER_IP "127.0.0.1"
#define BUFLEN 1024
#define PORT 9930
#define NAME_LENGTH 50
#define BUF_LENGTH 1024


int search()
{

	char *token;
	int found_flag=0,reply;
	char keyword[NAME_LENGTH],temp[BUF_LENGTH];
	printf("Search:\n");
	scanf("%s",keyword);
	char buf[BUF_LENGTH];

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

	sprintf(buf,"%s,%s","search",keyword);

	if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
		err_msg("sendto()");

	while(1)
	{
		if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, &slen)==-1)
			err_msg("recvfrom()");

		if(buf[0]=='$')
			break;

		found_flag = 1;

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
			token=strtok(NULL,"\n");
		}
	}
	printf("____________________________________________________________________________________________________________________________________________\n");

	if( found_flag == 0 )
		printf("Sorry, No Results Found..!!\n");
}