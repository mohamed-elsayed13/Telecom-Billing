// C program for the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
typedef  unsigned char uint8_t;
// Structure of the employee
typedef struct ST_recordData_t {
	uint8_t userName[30];
	uint8_t userPhonenumber[12];
	float	amountToBePaid;
	uint8_t userComplain[21];
}ST_recordData_t;
ST_recordData_t Billing_records_database;  
// size of the structure
long int size = sizeof(Billing_records_database);
  
// In the start coordinates
// will be 0, 0
COORD cord = { 0, 0 };
  
// function to set the
// coordinates
void gotoxy(int x, int y)
{
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        cord);
}
  
FILE *fp, *ft;
  
// Function to add the records
void addrecord()
{
    system("cls");
    fseek(fp, 0, SEEK_END);
    char another = 'y';
  
    while (another == 'y') {
        
		printf("\nEnter Name : ");
   		scanf("%s", &Billing_records_database.userName);
		
		printf("\nEnter Phone Number : ");
        scanf("%s", &Billing_records_database.userPhonenumber); 
          
        printf("\nEnter Amount to be paid : ");
        scanf("%f", &Billing_records_database.amountToBePaid);
		
		strcpy(Billing_records_database.userComplain," ");
        
		fwrite(&Billing_records_database, size, 1, fp);
  
        printf("\nWant to add another"
               " record (Y/N) : ");
        fflush(stdin);
  
        scanf("%c", &another);
    }
}
  
// Function to delete the records
void deleterecord()
{
    system("cls");
    char username[30];
    char another = 'y';
  
    while (another == 'y') {
        printf("\nEnter employee "
               "name to delete : ");
        scanf("%s", username);
		/*
		will use temp file to store records except the one
		we need to delete.		
		*/
        ft = fopen("temp.txt", "wb");
        //position will be the start of the file
		rewind(fp);
		//Read from file fp one by one
        while (fread(&Billing_records_database, size,
                     1, fp)
               == 1) {
            //store in temp all except the entered name
			if (strcmp(Billing_records_database.userName,
                       username)
                != 0)
                fwrite(&Billing_records_database, size, 1, ft);
        }
		// Close the files
        fclose(fp);
        fclose(ft);
		//remove the old database
        remove("data.txt");
		//Rename to be our new database 
        rename("temp.txt", "data.txt");
		//Open the new and right database again
        fp = fopen("data.txt", "rb+");
  
        printf("\nWant to delete another"
               " record (Y/N) :");
        fflush(stdin);
        another = getchar();
    }
}
  
// Function to display the record
void displayrecord()
{
    system("cls");
  
    // sets pointer to start
    // of the file
    rewind(fp);
  
    printf("\n========================="
           "==========================="
           "======");
    printf("\nNAME\t\t\tPhone\t\t\tBill\t"
           "\tComplains\n",
           Billing_records_database.userName, Billing_records_database.userPhonenumber,
           Billing_records_database.amountToBePaid, Billing_records_database.userComplain);
    printf("==========================="
           "==========================="
           "====\n");
  
    while (fread(&Billing_records_database, size, 1, fp) == 1)
        printf("\n%s\t\t%s\t\t%.2f\t%s",
               Billing_records_database.userName, Billing_records_database.userPhonenumber, Billing_records_database.amountToBePaid, Billing_records_database.userComplain);
  
    printf("\n\n\n\t");
    system("pause");
}
  
// Function to modify the record
void modifyrecord()
{
    system("cls");
    char username[50];
    char another = 'y';
  
    while (another == 'y') {
        printf("\nEnter user name"
               " to modify : ");
        scanf("%s", username);
  
        rewind(fp);
  
        // While File is open
        while (fread(&Billing_records_database, size, 1, fp) == 1) {
            // Compare the user name
            // with Billing_records_database userName
            if (strcmp(Billing_records_database.userName, username) == 0) {
                printf("\nEnter new name:");
                scanf("%s", Billing_records_database.userName);
                printf("\nEnter new phone :");
                scanf("%s", &Billing_records_database.userPhonenumber);
                printf("\nEnter new Bill Amount :");
                scanf("%f", &Billing_records_database.amountToBePaid);
                fseek(fp, -size, SEEK_CUR);
                fwrite(&Billing_records_database, size, 1, fp);
                break;
            }
        }
  
        // Ask for modifying another record
        printf("\nWant to modify another"
               " record (Y/N) :");
        fflush(stdin);
        scanf("%c", &another);
    }
}
// Function to View Payment amount
void viewPaymentRecord()
{
    system("cls");
    char username[30];
    char another = 'y';
  
    while (another == 'y') {
        printf("\nEnter user "
               "name to view payment : ");
        scanf("%s", username);
  
        //ft = fopen("temp.txt", "wb");
        rewind(fp);
  
        while (fread(&Billing_records_database, size,
                     1, fp)
               == 1) {
            if (strcmp(Billing_records_database.userName,
                       username)
                == 0)
                printf("Bill amount : %f",Billing_records_database.amountToBePaid);
        }
  
        fclose(fp);
		fp = fopen("data.txt", "rb+");
  
        printf("\nWant to delete another"
               " record (Y/N) :");
        fflush(stdin);
        another = getchar();
    }
}
// Function to Search records
void searchRecord()
{
    system("cls");
    char username[30];
    char another = 'y';
    while (another == 'y') {
		unsigned char indexZeroFlag=0;
		signed int indexCounter=-1;
		unsigned int countofrecords=0;
		printf("\nEnter user "
               "name to search records : ");
        scanf("%s", username);
        rewind(fp);
  
        while (fread(&Billing_records_database, size,
                     1, fp)
               == 1) {
				   countofrecords++;// To count total records
            if (strcmp(Billing_records_database.userName,
                       username)
                != 0)
				indexCounter++;
				//will be true if the search after index 0
				if(indexCounter+1==countofrecords){
				indexZeroFlag=1;
		}
        }
		if(indexCounter!=-1&&indexZeroFlag==1){
			indexCounter++;
			printf("The index of this name is %d",indexCounter);
		}
		// for index 0 
		else if(indexZeroFlag==0){
			indexCounter=0;
			printf("The index of this name is %d",indexCounter);
		}
		else{
			printf("This name does not exist in records.");
		}
        fclose(fp);
		fp = fopen("data.txt", "rb+");
  
        printf("\nWant to search another"
               " record (Y/N) :");
        fflush(stdin);
        another = getchar();
    }
}
// Function to Record a complain
void recordAcomplain()
{
    system("cls");
    char username[30];
    char another = 'y';
	char customerComplain[30]="Customer complaining";
    //signed int indexCounter=-1;
	while (another == 'y') {
		//signed int indexCounter=-1;
		printf("\nEnter user "
               "name to record a complain : ");
        scanf("%s", username);
  
        ft = fopen("temp.txt", "wb");
        rewind(fp);
		/*
		Will be like delete function but the diferrence is that 
		we edit the selected name before moving to temp.
		*/
        while (fread(&Billing_records_database, size, 1, fp)== 1) {
            if (strcmp(Billing_records_database.userName,username)!= 0)
				fwrite(&Billing_records_database, size, 1, ft);
				else{
				strcpy(Billing_records_database.userComplain,customerComplain);
				fwrite(&Billing_records_database, size, 1, ft);
				}					
			}
		fclose(fp);
        fclose(ft);
		remove("data.txt");
        rename("temp.txt", "data.txt");
        fp = fopen("data.txt", "rb+");
        printf("\nWant to search another"
               " record (Y/N) :");
        fflush(stdin);
        another = getchar();
    }
} 
// Driver code
int main()
{
    int choice;
  
    // opening the file
    fp = fopen("data.txt", "rb+");
  
    // showing error if file is
    // unable to open.
    if (fp == NULL) {
        fp = fopen("data.txt", "wb+");
        if (fp == NULL) {
            printf("\nCannot open file...");
            exit(1);
        }
    }
  
    system("Color 3F");
    printf("\n\n\n\n\t\t\t\t============="
           "============================="
           "===========");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~");
    printf("\n\t\t\t\t==================="
           "============================="
           "=====");
    printf("\n\t\t\t\t[|:::>:::>:::>::>  "
           "Billing System  <::<:::<:::"
           "<:::|]\t");
    printf("\n\t\t\t\t==================="
           "============================="
           "=====");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~");
    printf("\n\t\t\t\t====================="
           "==============================\n");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t"
           "Developer : @Mohamed_Elsayed"
           "\n\n\t\t\t\t");
  
    system("pause");
  
    while (1) {
        // Clearing console and asking the
        // user for input
        system("cls");
        gotoxy(30, 10);
        printf("\n1. ADD RECORD\n");
        gotoxy(30, 12);
        printf("\n2. DELETE RECORD\n");
        gotoxy(30, 14);
        printf("\n3. DISPLAY RECORDS\n");
        gotoxy(30, 16);
        printf("\n4. MODIFY RECORD\n");
        gotoxy(30, 18);
        printf("\n5. VIEW PAYMENT\n");
        gotoxy(30, 20);
		printf("\n6. SEARCH RECORDS\n");
        gotoxy(30, 22);
		printf("\n7. RECORD A COMPLAIN\n");
        gotoxy(30, 24);
		printf("\n8. EXIT\n");
        gotoxy(30, 26);
        printf("\nENTER YOUR CHOICE...\n");
        fflush(stdin);
        scanf("%d", &choice);
  
        // Switch Case
        switch (choice) {
        case 1:
  
            // Add the records
            addrecord();
            break;
  
        case 2:
  
            // Delete the records
            deleterecord();
            break;
  
        case 3:
  
            // Display the records
            displayrecord();
            break;
  
        case 4:
  
            // Modify the records
            modifyrecord();
            break;
		case 5:
			// View Amount to be paid 
			viewPaymentRecord();
			break;
		case 6:
			// Search records
			searchRecord();
			break;
		case 7:
			// Record a complain
			recordAcomplain();
			break;			

        case 8:
            fclose(fp);
            exit(0);
            break;
		        default:
            printf("\nINVALID CHOICE...\n");
        }
    }
  
    return 0;
}