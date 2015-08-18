#include <stdio.h>

#define BUF_LENGTH 1024
#define COUNT_LENGTH 4
#define CATALOG_FILE "catalog.txt"

char count[COUNT_LENGTH],item_id[COUNT_LENGTH];

void addtocart()
{
	FILE *fp;
	char buf[BUF_LENGTH];
	int reply;

	printf("Item id: ");
	scanf("%s",item_id);
	printf("Count: ");
	scanf("%s",count);

	sprintf(buf,"%s,%s,%s\n","addtocart",item_id,count);
	reply = sendtoserver(buf);
	if(reply==0)
	{
		printf("Sorry..!!\n Count Exceeded..!!");
	}
	else if(reply==2)
	{
		printf("Item Not Found..!!\n");
	}
	else if(reply==3)
	{
		printf("Successfully added to cart\n");
	}
	else
	{
		printf("Error..!!\n");

	}
	return;

}