#include <stdio.h>

#define BUF_LENGTH 1024
#define COUNT_LENGTH 4
#define CATALOG_FILE "catalog.txt"
#define CART_FILE "cart.txt"

void removefromcart()
{
	char item_id[COUNT_LENGTH],count[COUNT_LENGTH],line[BUF_LENGTH],*token;
	char temp[BUF_LENGTH],buf[BUF_LENGTH],*temp_name,*temp_description,*temp_rate,update_cart[BUF_LENGTH];
	int reply,rec_len,count1,token_temp=0,token1,found_flag = 0;
	FILE *fp;
	fp=fopen(CART_FILE,"r+");

	if(fp==NULL)
	{
		printf("\nYour Cart is empty..!!");
		return;
	}


	printf("Item id: ");
	scanf("%s",item_id);
	printf("Count: ");
	scanf("%s",count);


	while( fgets(line,sizeof(line),fp ) != NULL )
	{
		strcpy(temp,line);                                        /* Copying line to a temporary location */
		token=strtok(line,",");                                   /* Tokenizing starts */

		if( strcasecmp(token,item_id) == 0 )
		{    
			found_flag=1;
			temp_name=strtok(NULL,",");							  /* Tokenizing different fields */
			temp_description=strtok(NULL,",");
			temp_rate=strtok(NULL,",");
			token=strtok(NULL,"\n");
			rec_len = -strlen(temp);
			fseek(fp,rec_len,SEEK_CUR);
			token1=atoi(token);
			count1=atoi(count);

			if( (count1 > token1) && (token1 != 0) )              /* Checks whether count exceeds the limit */
			{
				printf("Max %d can be removed\n",token1);
				return;	
			}

	    	else if( token1 == 0 )
	    	{
		 		printf("Item Not Found..!!\n");
		 		return;
	    	}

	    	else												 /* To update cart */
	    	{
	    		token_temp=token1;
				token1-=count1;
				sprintf(update_cart,"%s,%s,%s,%s,%4d",item_id,temp_name,temp_description,temp_rate,token1);
				fprintf(fp,"%s\n",update_cart);
				break;
			}
		}   
    }

	if( !found_flag )
	{	 
		printf("Item Not Found..!!\n");
		return;

	}

	fclose(fp);

	sprintf(buf,"%s,%s,%s","removefromcart",item_id,count);
	reply = sendtoserver(buf);
	return;
}