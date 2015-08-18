#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>


#define SERVER_IP "192.168.1.188"
#define CART_FILE "cart.txt"
//#define SERVER_IP "127.0.0.1"
#define BUFLEN 1024
#define PORT 9930


void cart_err_msg(char *error_msg)
{
	perror(error_msg);
	return;
}

int viewcart()
{
	FILE *fp;
	float total=0.0;
	int rate,count,mul;

	char *token;
	char line[BUFLEN];

	fp = fopen(CART_FILE,"r");
	if(fp==NULL)
	{
		printf("Your cart is Empty..!!\n");
		return;
	}

	while(fgets(line,sizeof(line),fp ) != NULL)
	{
		token=strtok(line,",");
		while(token!=NULL)
		{
			printf("____________________________________________________________________________________________________________________________________________");
			printf("\nItem id\t\t:\t%s",token);
			token=strtok(NULL,",");
	
			printf("\nItem name\t:\t%s",token);
			token=strtok(NULL,",");

			printf("\nDescription\t:\t%s",token);
			token=strtok(NULL,",");

			rate=atoi(token);

			printf("\nRate\t\t:\t%s",token);
			token=strtok(NULL,",");

			count=atoi(token);
    		mul=rate*count;                              /* Multiplying rate of each item by count */ 
    		total=total+mul;

			printf("\nAvailability\t:\t%d\n",atoi(token));
			token=strtok(NULL,",");
		}
	}
	printf("____________________________________________________________________________________________________________________________________________");
	printf("\n\nTOTAL AMOUNT = %f\n",total);
}