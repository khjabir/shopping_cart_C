#include <stdio.h>
#include <string.h>
#include "signup.c"
#include "viewcatalog.c"
#include "search.c"
#include "login.c"
#include "addtocart.c"
#include "help.c"
#include "sendtoserver.c"
#include "viewcart.c"
#include "removefromcart.c"
#include "checkout.c"

#define NAME_LENGTH 50
#define PASSWORD_LENGTH 8
#define MOB_NUM_LENGTH 10
#define BUF_LENGTH 1024
#define COUNT_LENGTH 4
#define COMMAND_LENGTH 15
#define REGISTER_FILE "signup.txt"
#define CATALOG_FILE "catalog.txt"
#define CART_FILE "cart.txt"


int login_session = 0;

int choiceValue(char command[COMMAND_LENGTH])
{
	int ch;
	if(strcasecmp(command,"help")==0)
		ch=1;
	else if(strcasecmp(command,"signup")==0)
		ch=2;
	else if(strcasecmp(command,"login")==0)
		ch=3;
	else if(strcasecmp(command,"logout")==0)
		ch=4;
	else if(strcasecmp(command,"viewcatalog")==0)
		ch=5;
	else if(strcasecmp(command,"search")==0)
		ch=6;
	else if(strcasecmp(command,"addtocart")==0)
		ch=7;
	else if(strcasecmp(command,"viewcart")==0)
		ch=8;
	else if(strcasecmp(command,"removefromcart")==0)
		ch=9;
	else if(strcasecmp(command,"checkout")==0)
		ch=10;
	else if(strcasecmp(command,"exit")==0)
		ch=11;
	return ch;
}

int main()
{
	int condition;
	printf("Enter 'help' to view available options: ");
	
	int ch=0,reply,status,checkout_flag=0;
	char command[COMMAND_LENGTH],buf[BUF_LENGTH],choice[1];

	while(1)
	{
		printf("\n>");
		scanf("%s",command);
		ch=choiceValue(command);
		switch(ch)
		{
			case 1:
					help();
					break;

			case 2:
					if(login_session==1)
						printf("Already logged in..!!");
					else
						signup();
					break;

			case 3:
					if(login_session==1)
						printf("Already logged in..!!");
					else
						login_session = login();
					break;

			case 4:
					if(login_session==0)
						printf("Not yet logged in..!!");
					else
					{
						if(checkout_flag==0)
						{
							printf("\nYour cart file will be deleted..Do you want to logout(y/n)??");
							scanf("%s",choice);
							if((choice[0]=='y')||(choice[0]=='Y'))
							{
								status = remove(CART_FILE);
								
								login_session=0;
								strcpy(buf,"logout");
								reply = sendtoserver(buf);
 
 								if( status == 0 )
 									printf("Cart file deleted.\n");
 								else
 								{
 									printf("Cart file is already deleted.\n");
 								}
 							}
 							else 
								continue;
						}
						else
						{
							login_session=0;
							strcpy(buf,"logout");
							reply = sendtoserver(buf);

						}
						
					}
					break;

			case 5:
					if(login_session==0)
						printf("Please login to view catalog..!!");
					else
						viewcatalog();
					break;

			case 6:
					if(login_session==0)
						printf("Please login to search an item..!!");
					else
						search();
					break;

			case 7:
					if(login_session==0)
						printf("Please login to add an item..!!");
					else
						addtocart();
					break;

			case 8:
					if(login_session==0)
						printf("Please login to view your cart..!!");
					else
						viewcart();
					break;

			case 9:
					if(login_session==0)
						printf("Please login to remove an item from your cart..!!");
					else
						removefromcart();
					break;

			case 10:
					if(login_session==0)
						printf("Please login to checkout your cart..!!");
					else
					{
						checkout();
						checkout_flag = 1;
					}
					break;

			case 11:
					return 0;

			default:
					printf("Invalid Command\n");
		}
	}
}