#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
	//declare node data
	int itemNo;
	char itemName[20];
	char supplierName[20];
	int contactNo;
	int reorderLimit;
	int unitNum;
	float unitCost;
	int day;
	int month;
	int year;
	int q1Ans;
	int q2Ans;
	int q3Ans;
	int q4Ans;
	struct node* next;
}stock;

typedef struct login {
	char name[30];
	char password[30];
	struct login* next;
}loginT;

//declare a universal variable *output for genStat*
float calBelowOffice = 0;
float calBelowTwiceOffice = 0;
float calAboveOffice = 0;
float calBelowMan = 0;
float calBelowTwiceMan = 0;
float calAboveMan = 0;
//declare method
void readInFile(struct login**top);
void readList(struct node**top);
void printListToFile(struct node * top);
void addData( struct node** top2);
void addAtEnd(struct node * top);
void displayAll(struct node * top);
void displaySpec(struct node * top);
void updateDetail(struct node * top);
void deleteItem(struct node * top);
void deleteAtStart(struct node ** top);
void genStat(struct node * top);
void printOnFile(struct node * top);
void listOrder(struct node * top);
void menu(struct node * top);

void main()
{
	//declare headPointer & variable
	struct node * headPtr = NULL;
	struct login* login = NULL;
	//call method for login authentication
	
	readInFile(&login);
	readList(&headPtr);
	menu(headPtr);
}


void readInFile(struct login**top)
{
	//declare variable
	FILE*file;
	
	struct login* newNode;

	file = fopen("user.txt", "r");
	int check=0;
	char user[30];
	char pass[30];
	char ch;
	int i=0;
	

	printf("Please enter Username\n");
	scanf("%s", user);

	printf("Please enter Password\n");
	for (i = 0; i < 7; i++)
	{
		ch = getch();
		pass[i] = ch;
		ch = '*';
		printf("%c", ch);
	}

	pass[i - 1] = '\0';

	if (file == NULL)
	{
		printf("Sorry the file could not be open\n");
	}
	else
	{
		while (!feof(file))
		{
			newNode = (struct login*)malloc(sizeof(struct login));

			fscanf(file,"%s %s \n", newNode->name,newNode->password);

			if (strcmp(newNode->name, user) == 0)
			{
				if (strcmp(newNode->password,pass)==0)
				{
					check++;
				}
			}
			*top = newNode;
			newNode->next = *top;
		}
	}
	fclose(file);

	i = 0;
	if (check>0)
	{
		printf("\nLog in succesful!\n");
		return;
	}
	else if (check <= 0) 
	{

		printf("\nThe User Name And Password You Have entered are incorrect\n");

		printf("\nPlease try again!\n\n");

		readInFile(top);

	}
}

void readList(struct node**top)
{
	
	struct node* temp;
	FILE* filep;
	filep = fopen("stock.txt", "r");

	if (filep == NULL)
	{
		printf("Sorry nothing was added to the list\n");
	}
	else
	{
		while (!feof(filep))
		{
			temp = (struct node*)malloc(sizeof(node));

			fscanf(filep, " %d %s %s %d %d %d %f %d %d %d %d %d %d %d ", &temp->itemNo, temp->itemName, temp->supplierName,
				&temp->contactNo, &temp->reorderLimit, &temp->unitNum,&temp->unitCost,&temp->day,&temp->month,
				&temp->year, &temp->q1Ans, &temp->q2Ans, &temp->q3Ans, &temp->q4Ans);

			temp->next = *top;
			*top = temp;
		}
		printf("The list is successfully added\n");
		fclose(filep);
	}
}
void printListToFile(struct node * top)
{
	FILE* file;
	struct node*temp = top;

	file = fopen("stock.txt","w");

	if (file == NULL)
	{
		printf("Sorry can't open the file\n");
	}
	else
	{
		while (temp != NULL)
		{
			fprintf(file, "%d %s %s %d %d %d %f %d %d %d %d %d %d %d\n", temp->itemNo, temp->itemName, temp->supplierName,
			temp->contactNo, temp->reorderLimit, temp->unitNum, temp->unitCost, temp->day, temp->month,
			temp->year, temp->q1Ans, temp->q2Ans, temp->q3Ans, temp->q4Ans);

			temp = temp->next;
		}
		printf("The file is up-to-date!\n");
		fclose(file);
		return;
	}
	

}
void addData(struct node** top2)
{
	//declare variable
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	
	printf("Please enter the new stock number\n");
	scanf("%d", &newNode->itemNo);
	//then ask question
	printf("Please enter Stock item name\n");
	scanf(" %s", newNode->itemName);
	printf("Please enter the supplier name\n");
	scanf(" %s", newNode->supplierName);
	printf("Please enter the supplier contact number\n");
	scanf(" %d", &newNode->contactNo);
	printf("Please enter re-order limit\n");
	scanf(" %d", &newNode->reorderLimit);
	printf("Please enter number of units\n");
	scanf(" %d", &newNode->unitNum);
	printf("Please enter cost per unit\n");
	scanf(" %f", &newNode->unitCost);
	//do while for qusetion protection
	do {
		printf("Please enter last order date (space between day, month,and year)\n");
		scanf("%d %d %d", &newNode->day, &newNode->month, &newNode->year);
	} while ((newNode->day < 1 || newNode->day>31) || (newNode->month < 1 || newNode->month>12) || (newNode->year > 2020 || newNode->year < 2000));

	do {
		printf("Does this item need to be stored in a hazardous chemical store?(1.Yes, 2.No)\n");
		scanf("%d", &newNode->q1Ans);
	} while (newNode->q1Ans < 1 || newNode->q1Ans>2);

	do {
		printf("Which Department does this stock item belong to?(1.Office, 2. Maintenance)\n");
		scanf("%d", &newNode->q2Ans);
	} while (newNode->q2Ans < 1 || newNode->q2Ans>2);
	do {
		printf("Which of the following months do items need to re-order?(1.No Specified Month, 2.Feb, 3.August)\n");
		scanf("%d", &newNode->q3Ans);
	} while (newNode->q3Ans < 1 || newNode->q3Ans > 3);
	do {
		printf("Which of the following people need to authorise the purchase?(1.Managing Director, 2.Financial Controller, 3.Department Manager\n)");
		scanf("%d", &newNode->q4Ans);
	} while (newNode->q4Ans < 1 || newNode->q4Ans > 3);
	//then have "Next" to be address of the headPtr
	newNode->next = *top2;
	*top2 = newNode;
	
}//end of addData(add at start)
void addAtEnd(struct node * top)
{
	//declare node to link with top that pass the value from main
	struct node* temp = top;
	struct node* temp2 = top;
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	int itemNum = 0;
	int choice;
	//ask for item no
	printf("Please enter the new stock number\n");
	scanf("%d", &itemNum);
	//check if the number unique


	while (temp2 != NULL)
	{

		if (temp2->itemNo != itemNum)
		{
			//then ask question
			temp2 = temp2->next;
			
		}
		else
		{
			//else the input and the item number in the list is the same
			printf("Do you want to update the detail? 1 for yes, 2 for return to menu\n");
			scanf("%d",&choice);
			//if user input 1 then go to updateDetail function
			if (choice == 1)
			{
				updateDetail(temp);
				return;
			}
			else
			{
				//else return to menu
				return;
			}
			
		}
		
	}
	newNode->itemNo = itemNum;
	printf("Please enter Stock item name\n");
	scanf(" %s", newNode->itemName);
	printf("Please enter the supplier name\n");
	scanf(" %s", newNode->supplierName);
	printf("Please enter the supplier contact number\n");
	scanf(" %d", &newNode->contactNo);
	printf("Please enter re-order limit\n");
	scanf(" %d", &newNode->reorderLimit);
	printf("Please enter number of units\n");
	scanf(" %d", &newNode->unitNum);
	printf("Please enter cost per unit\n");
	scanf(" %f", &newNode->unitCost);
	do {
		printf("Please enter last order date (space between day, month,and year)\n");
		scanf("%d %d %d", &newNode->day, &newNode->month, &newNode->year);
	} while ((newNode->day < 1 || newNode->day>31) || (newNode->month < 1 || newNode->month>12) || (newNode->year > 2020 || newNode->year < 2000));

	do {
		printf("Does this item need to be stored in a hazardous chemical store?(1.Yes, 2.No)\n");
		scanf("%d", &newNode->q1Ans);
	} while (newNode->q1Ans < 1 || newNode->q1Ans>2);

	do {
		printf("Which Department does this stock item belong to?(1.Office, 2. Maintenance)\n");
		scanf("%d", &newNode->q2Ans);
	} while (newNode->q2Ans < 1 || newNode->q2Ans>2);
	do {
		printf("Which of the following months do items need to re-order?(1.No Specified Month, 2.Feb, 3.August)\n");
		scanf("%d", &newNode->q3Ans);
	} while (newNode->q3Ans < 1 || newNode->q3Ans > 3);
	do {
		printf("Which of the following people need to authorise the purchase?(1.Managing Director, 2.Financial Controller, 3.Department Manager)\n");
		scanf("%d", &newNode->q4Ans);
	} while (newNode->q4Ans < 1 || newNode->q4Ans > 3);

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	newNode->next = NULL;
	temp->next = newNode;
}
	

void displayAll(struct node * top)
{
	struct node* temp = top;
	//while there a node then output them

	while (temp != NULL)
	{
		printf("The item number: %d\n",temp->itemNo);
		printf("The item name: %s\n",temp->itemName);
		printf("The supplier name: %s\n",temp->supplierName);
		printf("The supplier contact: %d\n",temp->contactNo);
		printf("Reorder-Limit: %d\n",temp->reorderLimit);
		printf("Number of Units: %d\n",temp->unitNum);
		printf("Cost per units: %f\n",temp->unitCost);
		printf("Last Order Date: %d/%d/%d\n",temp->day,temp->month,temp->year);
		if (temp->q1Ans == 1)
		{
			printf("This item need to be stored in a hazardous chemical store.\n");
		}
		else
		{
			printf("This item doesn't need to be stored in a hazardous chemical store.\n");
		}
		if (temp->q2Ans == 1)
		{
			printf("This item belong to Office department.\n");
		}
		else
		{
			printf("This item belong to Maintenance department.\n");
		}
		if (temp->q3Ans == 1)
		{
			printf("There is no specified month for it need to be re-ordered.\n");
		}
		else if (temp->q3Ans == 2)
		{
			printf("This item need to be re-ordered in February.\n");
		}
		else
		{
			printf("This item need to be re-ordered in August.\n");
		}
		if (temp->q4Ans == 1)
		{
			printf("Managing Director need to authorized to purchase this item.\n");
		}
		else if (temp->q4Ans == 2)
		{
			printf("Financial Controller need to authorized to purchase this item.\n");
		}
		else
		{
			printf("Department Manager need to authorized to puchase this item.\n");
		}
		printf("===================================================================\n\n");
		//continue to next node
		temp = temp->next;
	}
}
void displaySpec(struct node * top)
{
	struct node* temp = top;
	int i = 0;
	int input=0;
	char inputName[20];
	int menu=0;
	//choice for user to choose
	printf("Please choose if you want to search using 1.stock number or 2.stock name\n");
	scanf("%d", &menu);

	if (menu == 1)
	{
		printf("Please enter the stock number you want it to display\n");
		scanf("%d", &input);
		
		while (temp->itemNo != input)
		{
			i++;
			temp = temp->next;

			if (temp == NULL)
			{
				printf("Invalid Stock Item number entered.\n");
				return;
			}
		}
		
		printf("The stock is in %d position\n", i);
		if (temp->itemNo == input)
		{
			printf("The item number: %d\n", temp->itemNo);
			printf("The item name: %s\n", temp->itemName);
			printf("The supplier name: %s\n", temp->supplierName);
			printf("The supplier contact: %d\n", temp->contactNo);
			printf("Reorder-Limit: %d\n", temp->reorderLimit);
			printf("Number of Units: %d\n", temp->unitNum);
			printf("Cost per units: %lf\n", temp->unitCost);
			printf("Last Order Date: %d/%d/%d\n", temp->day, temp->month, temp->year);
			if (temp->q1Ans == 1)
			{
				printf("This item need to be stored in a hazardous chemical store.\n");
			}
			else
			{
				printf("This item doesn't need to be stored in a hazardous chemical store.\n");
			}
			if (temp->q2Ans == 1)
			{
				printf("This item belong to Office department.\n");
			}
			else
			{
				printf("This item belong to Maintenance department.\n");
			}
			if (temp->q3Ans == 1)
			{
				printf("There is no specified month for it need to be re-ordered.\n");
			}
			else if (temp->q3Ans == 2)
			{
				printf("This item need to be re-ordered in February.\n");
			}
			else
			{
				printf("This item need to be re-ordered in August.\n");
			}
			if (temp->q4Ans == 1)
			{
				printf("Managing Director need to authorized to purchase this item.\n");
			}
			else if (temp->q4Ans == 2)
			{
				printf("Financial Controller need to authorized to purchase this item.\n");
			}
			else
			{
				printf("Department Manager need to authorized to puchase this item.\n");
			}
		}
	}
	else if(menu == 2)
	{
		printf("Please enter the stock name you want it to display\n");
		scanf("%s", inputName);

		while (strcmp(temp->itemName,inputName) != 0)
		{
			i++;
			temp = temp->next;
			
			if (temp == NULL)
			{
				printf("Invalid Stock Item number entered.\n");
				return;
			}
		}
		printf("The stock is in %d position\n", i);
		if (strcmp(temp->itemName, inputName) == 0)
		{
			printf("The item number: %d\n", temp->itemNo);
			printf("The item name: %s\n", temp->itemName);
			printf("The supplier name: %s\n", temp->supplierName);
			printf("The supplier contact: %d\n", temp->contactNo);
			printf("Reorder-Limit: %d\n", temp->reorderLimit);
			printf("Number of Units: %d\n", temp->unitNum);
			printf("Cost per units: %lf\n", temp->unitCost);
			printf("Last Order Date: %d/%d/%d\n", temp->day, temp->month, temp->year);
			if (temp->q1Ans == 1)
			{
				printf("This item need to be stored in a hazardous chemical store.\n");
			}
			else
			{
				printf("This item doesn't need to be stored in a hazardous chemical store.\n");
			}
			if (temp->q2Ans == 1)
			{
				printf("This item belong to Office department.\n");
			}
			else
			{
				printf("This item belong to Maintenance department.\n");
			}
			if (temp->q3Ans == 1)
			{
				printf("There is no specified month for it need to be re-ordered.\n");
			}
			else if (temp->q3Ans == 2)
			{
				printf("This item need to be re-ordered in February.\n");
			}
			else
			{
				printf("This item need to be re-ordered in August.\n");
			}
			if (temp->q4Ans == 1)
			{
				printf("Managing Director need to authorized to purchase this item.\n");
			}
			else if (temp->q4Ans == 2)
			{
				printf("Financial Controller need to authorized to purchase this item.\n");
			}
			else
			{
				printf("Department Manager need to authorized to puchase this item.\n");
			}
		}
	}
	else
	{
		printf("The number/name you enter is wrong\n");

		displaySpec(temp);
	}
}
void updateDetail(struct node * top)
{
	struct node* temp = top;
	int i = 0;
	int input;
	char inputName[20];
	int menu;
	int choice;
	char newSuppName[20];
	int newContactNum;
	int newReorder;

	do
	{
		printf("Please give us the information about the stock by give us it's 1.stock number or 2.stock name\n");
		scanf("%d", &menu);
	}while(menu <1 || menu > 2);

	if (menu == 1)
	{
		printf("Please enter the stock number\n");
		scanf("%d", &input);

		while (temp != NULL)
		{
			if (temp->itemNo == input)
			{
				printf("Please enter new supplier name\n");
				scanf("%s", newSuppName);

				strcpy(temp->supplierName,newSuppName);

				printf("Please enter new supplier contact no.\n");
				scanf("%d", &newContactNum);

				temp->contactNo = newContactNum;

				printf("Please enter new re-order threshold limit\n");
				scanf("%d", &newReorder);

				temp->reorderLimit = newReorder;
			}
			else if (temp == NULL)
			{
				printf("your number is wrong\n");
				return;
			}
			temp = temp->next;
		}
	}
	else if (menu == 2)
	{
		printf("Please enter the stock name\n");
		scanf("%s", inputName);

		while (temp != NULL)
		{
			if (strcmp(temp->itemName,inputName)==0)
			{
				printf("Please enter new supplier name\n");
				scanf("%s", newSuppName);

				strcpy(temp->supplierName, newSuppName);

				printf("Please enter new supplier contact no.\n");
				scanf("%d", &newContactNum);

				temp->contactNo = newContactNum;

				printf("Please enter new re-order threshold limit\n");
				scanf("%d", &newReorder);

				temp->reorderLimit = newReorder;
			}
			else if(temp == NULL)
			{
				printf("Your input name is wrong\n"); 
				return;
			}
			temp = temp->next;
		}

	}
}
void deleteItem(struct node * top)
{
	int i=0;
	struct node* prev_temp;
	struct node* temp = top;
	int input2;
	
	do {
		printf("Please enter the Stock Item number that you want to Delete\n");
		scanf("%d", &input2);
	} while (input2 < 2);

	while (temp->itemNo != input2)
	{
		prev_temp = temp;
		temp = temp->next;

		if (temp->itemNo == input2)
		{
			prev_temp->next = temp->next;
			free(temp);
			printf("The item has been deleted\n");
		}//if
		if (temp == NULL)
		{
			printf("Invalid stock Item Number");
			return;
		}
		
	}
	
}
void deleteAtStart(struct node ** top)
{
	struct node* temp;
	temp = *top;
	*top = temp->next;

	free(temp);

	printf("Deleted !\n");
}
void genStat(struct node * top)
{
	struct node* temp = top;
	int counterBelow =0;
	int counterBelowTwice =0;
	int counterAboveTwice=0;
	int counterBelow1=0;
	int counterBelowTwice1=0;
	int counterAboveTwice1=0;
	int totalOff=0;
	int totalMan=0;
	int choice;

	FILE*file;

	//if on which department
		if (temp->q2Ans == 1)
		{
			if (temp->reorderLimit > temp->unitNum)
			{
				counterBelow++;
			}
			else if (temp->unitNum > temp->reorderLimit && temp->unitNum < (temp->reorderLimit * 2))
			{
				counterBelowTwice++;
			}
			else
			{
				counterAboveTwice++;
			}
			totalOff = counterAboveTwice + counterBelow + counterBelowTwice;
			calBelowOffice = 100 * (counterBelow / totalOff);
			calBelowTwiceOffice = 100 * (counterBelowTwice / totalOff);
			calAboveOffice = 100 * (counterAboveTwice / totalOff);
		}
		else if (temp->q2Ans == 2)
		{
			if (temp->reorderLimit > temp->unitNum)
			{
				counterBelow1++;
			}
			else if (temp->unitNum > temp->reorderLimit && temp->unitNum < (temp->reorderLimit * 2))
			{
				counterBelowTwice1++;
			}
			else
			{
				counterAboveTwice1++;
			}
			totalMan = counterAboveTwice1 + counterBelow1 + counterBelowTwice1;
			calBelowMan = 100 * (counterBelow1 / totalMan);
			calBelowTwiceMan = 100 * (counterBelowTwice1 / totalMan);
			calAboveMan = 100 * (counterAboveTwice1 / totalMan);
		}//elseif
	
	printf("The Maintenance Department detail:\n");
	printf("\n===============================\n");
	printf("There are %.2f percent of stock items below the re-order threshold limit\n", calBelowMan);
	printf("There are %.2f percent of stock items below twice the re-order threshold limit\n", calBelowTwiceMan);
	printf("There are %.2f percent of stock items  above twice the re-order threshold limit\n", calAboveMan);
	printf("\n===============================\n");
		
	printf("The Office Department detail:\n");
	printf("\n===============================\n");
	printf("There are %.2f percent of stock items below the re-order threshold limit\n", calBelowOffice);
	printf("There are %.2f percent of stock items below twice the re-order threshold limit\n", calBelowTwiceOffice);
	printf("There are %.2f percent of stock items  above twice the re-order threshold limit\n", calAboveOffice);
	printf("\n===============================\n");
	
}
void printOnFile(struct node * top)
{
	struct node* temp = top;
	FILE*file;
	//open the file
	
	file = fopen("Report.txt", "w");

	while (temp != NULL)
	{
		fprintf(file, "Stock Item Number: %d\n", temp->itemNo);
		fprintf(file, "Stock Item Name: %s\n", temp->itemName);
		fprintf(file, "Stock Item Supplier Name: %s\n", temp->supplierName);
		fprintf(file, "Stock Item Supplier Number: %d\n", temp->contactNo);
		fprintf(file, "Re-order threshold limit: %d\n", temp->reorderLimit);
		fprintf(file, "Number of unit: %d\n", temp->unitNum);
		fprintf(file, "Cost per unit: %.2f\n", temp->unitCost);
		fprintf(file, "Last order date: %d/%d/%d\n", temp->day, temp->month, temp->year);
		if (temp->q1Ans == 1)
		{
			fprintf(file, "This item need to be stored in a hazardous chemical store.\n");
		}
		else
		{
			fprintf(file, "This item doesn't need to be stored in a hazardous chemical store.\n");
		}
		if (temp->q2Ans == 1)
		{
			fprintf(file, "This item belong to Office department.\n");
		}
		else
		{
			fprintf(file, "This item belong to Maintenance department.\n");
		}
		if (temp->q3Ans == 1)
		{
			fprintf(file, "There is no specified month for it need to be re-ordered.\n");
		}
		else if (temp->q3Ans == 2)
		{
			fprintf(file, "This item need to be re-ordered in February.\n");
		}
		else
		{
			fprintf(file, "This item need to be re-ordered in August.\n");
		}
		if (temp->q4Ans == 1)
		{
			fprintf(file, "Managing Director need to authorized to purchase this item.\n");
		}
		else if (temp->q4Ans == 2)
		{
			fprintf(file, "Financial Controller need to authorized to purchase this item.\n");
		}
		else
		{
			fprintf(file, "Department Manager need to authorized to puchase this item.\n");
		}

		fprintf(file, "\nThe Maintenance Department detail:\n");
		fprintf(file, "\n===============================\n");
		fprintf(file, "There are %.2f percent of stock items below the re-order threshold limit\n", calBelowMan);
		fprintf(file, "There are %.2f percent of stock items below twice the re-order threshold limit\n", calBelowTwiceMan);
		fprintf(file, "There are %.2f percent of stock items  above twice the re-order threshold limit\n", calAboveMan);
		fprintf(file, "\n===============================\n");

		fprintf(file, "The Office Department detail:\n");
		fprintf(file, "\n===============================\n");
		fprintf(file, "There are %.2f percent of stock items below the re-order threshold limit\n", calBelowOffice);
		fprintf(file, "There are %.2f percent of stock items below twice the re-order threshold limit\n", calBelowTwiceOffice);
		fprintf(file, "There are %.2f percent of stock items  above twice the re-order threshold limit\n", calAboveOffice);
		fprintf(file, "\n===============================\n");

		temp = temp->next;
	}
	
	fclose(file);
}
void listOrder(struct node * top)
{
	struct node* temp = top;
	struct node* temp2 = top;
	float monValue = 0;
	float monValue2 = 0;
	
	while (temp != NULL)
	{
		monValue = temp->unitNum*temp->unitCost;
		printf("The monetary value of %s is %.2f\n", temp->itemName,monValue);
		temp = temp->next;
	}

}
void menu(struct node * top)
{
	int option;
	int input;
	struct node* temp = top;
	do
	{
		printf("Please enter 1 to Add the stock item\n");
		printf("Please enter 2 to display all item in the List\n");
		printf("Please enter 3 to display specific item in the List\n");
		printf("Please enter 4 to update the stock detail\n");
		printf("Please enter 5 to delete an item\n");
		printf("Please enter 6 to generate a statistic based on department\n");
		printf("Please enter 7 to print all stock in to a file\n");
		printf("Please enter 8 to List all the stock items in order of their total monetary value\n");
		printf("Please enter 9 to update the list to stock\n");
		printf("Please enter -1 to exit the program\n");
		scanf("%d", &option);
	} while (option > 9 || option < -1 || option == 0);

	while (option != -1)
	{

		if (option == 1)
		{
			if (temp == NULL)
			{
				addData(&temp);
			}
			else
			{
				addAtEnd(temp);
			}
		}
		else if (option == 2)
		{
			if (temp == NULL)
			{
				printf("There is nothing to be displayed!\n");
			}
			else
			{
				displayAll(temp);
			}
		}
		else if (option == 3)
		{
			if (temp == NULL)
			{
				printf("There is nothing to be displayed!\n");
			}
			else
			{
				displaySpec(temp);
			}
		}
		else if (option == 4)
		{
			if (temp == NULL)
			{
				printf("There is nothing to be updated!\n");
			}
			else
			{
				updateDetail(temp);
			}

		}
		else if (option == 5)
		{
			if (temp == NULL)
			{
				printf("There is nothing to be delete!\n");
			}
			else
			{
				do {
					printf("Please enter 1 to delete first one or 2 to delete the other one\n");
					scanf("%d", &input);
				} while (input < 1 || input >2);
				if (input == 1)
				{
					deleteAtStart(&temp);
				}
				else
				{
					deleteItem(temp);
				}
			}
		}
		else if (option == 6)
		{
			if (temp == NULL)
			{
				printf("There is no stat to be generated!\n");
			}
			else
			{
				genStat(temp);
			}
		}
		else if (option == 7)
		{
			if (temp == NULL)
			{
				printf("There is nothing to be printed!\n");
			}
			else
			{
				printOnFile(temp);
			}
		}
		else if (option == 8)
		{
			if (temp == NULL)
			{
				printf("There is nothing to be listed!\n");
			}
			else
			{
				listOrder(temp);
			}
		}
		else if (option == 9)
		{
			printListToFile(temp);
		}
	
		do
		{
			printf("Please enter 1 to Add the stock item\n");
			printf("Please enter 2 to display all item in the List\n");
			printf("Please enter 3 to display specific item in the List\n");
			printf("Please enter 4 to update the stock detail\n");
			printf("Please enter 5 to delete an item\n");
			printf("Please enter 6 to generate a statistic based on department\n");
			printf("Please enter 7 to print all stock in to a file\n");
			printf("Please enter 8 to  List all the stock items in order of their total monetary value\n");
			printf("Please enter 9 to update the list to stock\n");
			printf("Please enter -1 to exit the program\n");
			scanf("%d", &option);
		} while (option > 9 || option < -1 || option == 0);
	}

}
