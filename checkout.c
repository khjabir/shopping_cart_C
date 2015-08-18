#include <stdio.h>

#define BUF_LENGTH 1024
#define COUNT_LENGTH 4
#define CATALOG_FILE "catalog.txt"
#define CART_FILE "cart.txt"

void checkout()
{
	char buf[BUF_LENGTH],del_address[BUF_LENGTH],choice[1],line[BUF_LENGTH];
	int reply,status;
	time_t now;
	struct tm *tm;
	FILE *fp;

	struct sockaddr_in serv_addr;
	int sockfd, i, slen=sizeof(serv_addr);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
	{
		err("socket");
		return;
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_aton(SERVER_IP, &serv_addr.sin_addr)==0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		return;
	}

	fp=fopen(CART_FILE,"r+");

	if(fp==NULL)
	{
		printf("Cannot open file\n");
		return;
	}

	sprintf(buf,"%s,","checkout");

	if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
			err("sendto()");

	while(fgets(line,sizeof(line),fp)!=NULL)
	{
		if (sendto(sockfd, line, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
			err("sendto()");
	}

	printf("Enter delivery address: \n");	
	scanf("%s",del_address);
	sprintf(buf,"%s,%s\n","DA",del_address);
	if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*)&serv_addr, slen)==-1)
			err("sendto()");

	status = remove(CART_FILE);
 
 	if( status == 0 )
 		printf("Cart checked out.\n");
 	else
 	{
 		printf("Cart file is not available.\n");
 		//perror("Error");
 	}

	return;
}