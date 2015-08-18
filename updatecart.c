#include <stdio.h>
#include <string.h>

#define BUFLEN 1024
#define CART_FILE "cart.txt"

void updatecart(char *update_cart)
{

	char *token,*temp_name,*temp_description,*temp_rate;
	char *temp1_name, *temp1_description, *temp1_rate, *temp1_avail, t_item_id[4], *t_item_id1, temp1[BUFLEN],temp2[BUFLEN];
	char temp[BUFLEN];
	char line[BUFLEN];
	int token_val,count_val,found_flag=0, found_flag1=0,token1,count1,reply;
	int rec_len;
	double total;


	FILE *fp=fopen(CART_FILE,"r+");
	if(fp==NULL)
	{
		printf("Cart File not available, Creating a new one..!!\n");
		fp = fopen(CART_FILE,"w");
	}

	while( fgets( line,sizeof(line),fp ) != NULL )
	{
		strcpy(temp1,line);
		t_item_id1=strtok(line,",");

		if(strcasecmp(item_id,t_item_id1)==0)
		{
			found_flag1=1;
			break;
		}

	}
	if( found_flag1==0 )
	{
		fprintf(fp,"%s\n",update_cart);
	}
				
	else
	{
		strcpy(temp2,temp1);
		t_item_id1=strtok(temp1,",");
		temp1_name=strtok(NULL,",");
		temp1_description=strtok(NULL,",");
		temp1_rate=strtok(NULL,",");
		temp1_avail=strtok(NULL,",");
		rec_len = -strlen(temp2);
		fseek(fp,rec_len,SEEK_CUR);
		token1=atoi(temp1_avail);
		count1=atoi(count);
		token1=token1+count1;

		sprintf(update_cart,"%s,%s,%s,%s,%4d",t_item_id1,temp1_name,temp1_description,temp1_rate,token1);
		fprintf(fp,"%s\n",update_cart);
	}
	fclose(fp);
}