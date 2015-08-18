#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFLEN 1024
#define CATALOG_FILE "catalog.txt"
#define CART_FILE "cart.txt"


char * removefromcartserver(char buf[BUFLEN])
{
	FILE *fp,*fp1;
	fp=fopen(CART_FILE,"r+");
	char line[BUFLEN],*item_id,temp1[BUFLEN],*count;
	char update_catalog[BUFLEN],*token;
	char *temp1_name,*temp1_description,*temp1_rate;
	int i=0,count1,token2,rec_len;

	token = strtok(buf,",");
	item_id = strtok(NULL,",");
	count = strtok(NULL,"\n");

	if( atoi(count) != 0 )
	{
    		fp1=fopen(CATALOG_FILE,"r+");

			if ( fp1 == NULL )
			{ 
				printf("\n Catalog file cannot be opened.. ");
			}

			else
			{
                /* To update catalog */
			    while( fgets( line,sizeof(line),fp1 ) != NULL)
				{
					strcpy(temp1,line);
					token=strtok(line,",");
				
					if( strcmp( token,item_id ) == 0 )
					{
						temp1_name=strtok(NULL,",");
						temp1_description=strtok(NULL,",");
						temp1_rate=strtok(NULL,",");
						token=strtok(NULL,",");
						rec_len = -strlen(temp1);
						fseek(fp1,rec_len,SEEK_CUR);
						count1=atoi(count);
						token2=atoi(token);
						token2+=count1;
						sprintf(update_catalog,"%s,%s,%s,%s,%4d",item_id,temp1_name,temp1_description,temp1_rate,token2);
						fprintf(fp1,"%s\n",update_catalog);
						fclose(fp1);
						printf("Successfully removed from cart\n");
				        return "Successfully removed from cart\n";
					}
				}
			}
	    }

	return "error";
}