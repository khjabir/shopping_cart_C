#include <stdio.h>

#define COUNT_LENGTH 4
#define CATALOG_FILE "catalog.txt"
#define CART_FILE "cart.txt"


char * addtocartserver(char buf[BUF_LENGTH])
{

	FILE *fp=fopen(CATALOG_FILE,"r+");
	char *token,*temp_name,*temp_description,*temp_rate;
	char *temp1_name, *temp1_description, *temp1_rate, *temp1_avail, *t_item_id, *t_item_id1, temp1[BUF_LENGTH],temp2[BUF_LENGTH];
	char *item_id,*count,temp[BUF_LENGTH],update_catalog[BUF_LENGTH],update_cart[BUF_LENGTH],*msg;
	char line[BUF_LENGTH],success[BUF_LENGTH] = "1,";
	int token_val,count_val,found_flag=0, found_flag1=0,token1,count1,reply;
	int rec_len;
	double total;

	token = strtok(buf,",");
	item_id = strtok(NULL,",");
	count = strtok(NULL,"\n");

	while(fgets(line,sizeof(line),fp)!=NULL)
	{
		strcpy(temp,line);
		token=strtok(line,",");

		if(strcasecmp(token,item_id)==0)
		{
			found_flag=1;
			temp_name=strtok(NULL,",");
			temp_description=strtok(NULL,",");
			temp_rate=strtok(NULL,",");
			token=strtok(NULL,",");
			rec_len = -strlen(temp);
			fseek(fp,rec_len,SEEK_CUR);
			token_val=atoi(token);
			count_val=atoi(count);

			if(count_val>token_val) 
			{
				printf("Sorry..!! Maximum %d can be added\n",token_val);
				return "Adding count exceeded\n";
			}

			else
			{
				token_val-=count_val;
				snprintf(token,sizeof(token),"%4d",token_val);
				sprintf(update_catalog,
					"%s,%s,%s,%s,%4d",
					item_id,temp_name,temp_description,temp_rate,token_val);
				fprintf(fp,"%s\n",update_catalog);
				sprintf(update_cart,
					"%s,%s,%s,%s,%4d",
					item_id,temp_name,temp_description,temp_rate,count_val);
				break;
			}
		}
	}
	
	fclose(fp);

	if(!found_flag)
	{
		printf("Item Not Found..!!\n");
		return "Item Not Found..!!\n";
	}
	else
	{
		printf("Catalog updated successfully..!!\n");
		strcat(success,update_cart);
		return(success);
	}

}
