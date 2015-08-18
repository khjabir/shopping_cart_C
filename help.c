#include <stdio.h>

void help()
{
	printf("____________________________________________________________________________________________________________________________________________\n");
	printf("\tsignup\t\t\t\t-\tFor a new user to register\n");
	printf("\tlogin\t\t\t\t-\tFor an existing user to login\n");
	printf("\tlogout\t\t\t\t-\tFor the user to logout\n");
	printf("\tviewcatalog\t\t\t-\tTo view the list of items and can choose what to buy.\n");
	printf("\tsearch\t\t\t\t-\tTo search a specific item in the catalogue using a keyword.\n");
	printf("\taddtocart <id><quantity>\t-\tTo select items using the product id and specify the quantity required\n");
	printf("\tviewcart\t\t\t-\tThe users can view the list of items they have added to their cart.\n");
	printf("\tremovefromcart <item id>\t-\tThe users can remove any item that they had already added to their cart\n");
	printf("\tcheckout\t\t\t-\tThe user can checkout the items in their cart and complete their transaction.\n");
	printf("\texit\t\t\t\t-\tExit\n");
	printf("____________________________________________________________________________________________________________________________________________\n");
}