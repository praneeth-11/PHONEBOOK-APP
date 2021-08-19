#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#define RED "\x1b[31m"
#define RESET   "\x1b[0m"

// 1.Add contact   2.View       3.Delete
// 4.Search        5.Modify     6.Exit

// main() is initialized here because its called in below functions
int main();
// function to check if the array contains only numbers
// used in adding MOBILE NUMBER in add()
int digits_only(const char *s)
{
    while (*s) {
        if (isdigit(*s++) == 0) return 0;
    }

    return 1;
}

// function to check if a given name is already present in a file
// used in adding NAME in add()
int checkname(char *sname)
{
    int check =0;
    FILE *fp;
    fp=fopen("contact.txt","r");
    char name[50],mob[11];char gender; char email[50]; char city[20];
    while(fscanf(fp,"%s\t%s\t%c\t%s\t%s\n",name,mob,&gender,email,city)!=EOF)
    { 
      if ( strncmp(sname, name, strlen(name)) == 0)
      {
        check =1;
      }     
    }
    return check;
}


//function to add a contact
void add()
{
    system("clear");
    FILE *fp;
    fp=fopen("contact.txt","a+");
    printf("*****ADD CONTACT*****\n");

    // NAME
    printf("\nName    :-");
    fflush(stdin);
    char name[50];   
    scanf("%s",name);
    while( checkname(name) == 1)
    {
        printf(RED"\nContact name already exists !"RESET"\nEnter new name : ");
        scanf("%s",name);
    }
    
    // MOBILE NUMBER
    printf("\nMob No. :-" );
    char mob[11];
    scanf("%s",mob);
    while ( strlen(mob)<10 || strlen(mob)>10 )
    { printf(RED"\nenter a valid 10 digit number : "RESET);
      scanf("%s",mob);
    }
    while (digits_only(mob) == 0)
    {
      printf(RED"\nenter the number containg only digits : "RESET);
      scanf("%s",mob);
    }

    // GENDER
    printf("\nenter the gender(M/F) : ");
    fflush(stdin);
    char gender;
    scanf("%c",&gender);
    while ( !( gender=='M' || gender=='F' ))
    {
        printf(RED"\nenter only either M or F as input : "RESET);
        fflush(stdin);
        scanf("%c",&gender);
    }

    // EMAIL
    printf("\nenter email id : ");
    char email[50];
    scanf("%s", email);

    // CITY
    printf("\nenter city/village name : ");
    char city[20];
    scanf("%s",city); 
    fflush(stdin);

    // Add details to file using fprintf
    fprintf(fp,"%s\t%s\t%c\t%s\t%s\n",name,mob,gender,email,city);

    fclose(fp);
    printf("\nPRESS ANY KEY TO CONTINUE");
    getchar();
    system("clear");
    main();
}


// View all contacts
void view()
{
    system("clear");
    FILE *fp;
    fp=fopen("contact.txt","r");
    printf("*****ALL CONTACTS*****");
    char name[50],mob[11];char gender; char email[50]; char city[20];
    while(fscanf(fp,"%s\t%s\t%c\t%s\t%s\n",name,mob,&gender,email,city)!=EOF)
    {
        printf("\nNAME    :-  %s",name);
        printf("\nMOBILE NUMBER. :-  %s",mob);
        printf("\nGENDER :-  %c",gender);
        printf("\nEMAIL :-  %s",email);
        printf("\nCITY :-  %s",city);
        printf("\n");
    }
    fclose(fp);
    fflush(stdin);
    printf("\nPRESS ANY KEY TO CONTINUE\n");
    getchar();
    system("clear");
    main();
}


// function for finding the line number of a file if a given name matches
// with the contact name in a file
// used in deleteLine()
int linenumber(char delname[])
{
    FILE *fp = fopen("contact.txt","r");
    int lno=0; int count=0;
    
    char name[50],mob[11];char gender; char email[50]; char city[20];
    while(fscanf(fp,"%s\t%s\t%c\t%s\t%s\n",name,mob,&gender,email,city)!=EOF)
    { 
      lno++;
      if ( strncmp(delname, name, strlen(name)) == 0)
      {
         count =1;
         break;
      }     
    }
    // lno is the line number of the contact to delete
    fclose(fp);
    if (count == 1)
    return lno; 
    else return 0;
}

// function for deleting the line of a file for a given line number
void deleteLine(const int line)
{
    FILE *srcFile = fopen("contact.txt","r");
    FILE *tempFile = fopen("temp.txt","w");
    char str[1000];
    int count = 1;
    
    while ((fgets(str, 1000, srcFile)) != NULL)
    {
        /* If current line is not the line user wanted to remove */
        if (line != count)
            fputs(str, tempFile);

        count++;
    }
        /* Close all open files */
    fclose(srcFile);
    fclose(tempFile);


    /* Delete src file and rename temp file as src */
    remove("contact.txt");
    rename("temp.txt", "contact.txt");
}


// final function to delete using deleteLine() and linenumber()
void delete()
{
  system("clear");
  printf("\nenter the name to delete : ");
  char delname[50];
  scanf("%s",delname);
  if (linenumber(delname) != 0)
        {
            deleteLine(linenumber(delname));
            printf("\ncontact deleted successfully !");
        }
  else printf(RED"\nname not found !"RESET);
  fflush(stdin);
  printf("\nPRESS ANY KEY TO CONTINUE\n");
  getchar();
  system("clear");
  main();
}

// used in SEARCH
// Function to display contact detials based on the line number
void readline(int x)
{
    FILE *fp;
    fp=fopen("contact.txt","r");
    char name[50],mob[11];char gender; char email[50]; char city[20];
    int lno = 0;
    while(fscanf(fp,"%s\t%s\t%c\t%s\t%s\n",name,mob,&gender,email,city)!=EOF)
    {
        lno++;
        if (lno==x)
        {
        printf("\nNAME    :-  %s",name);
        printf("\nMOBILE NUMBER. :-  %s",mob);
        printf("\nGENDER :-  %c",gender);
        printf("\nEMAIL :-  %s",email);
        printf("\nCITY :-  %s",city);
        printf("\n");
        }
    }
}


void search()
{
    system("clear");
    FILE *fp = fopen("contact.txt","r");
    char str[1000]; char sname[50];
    printf("enter the name you want to search : ");
    scanf("%s",sname);
    char name[50],mob[11];char gender; char email[50]; char city[20];
    
    int lno=0, count=0;
    printf("\nnames with match : ");
    while(fscanf(fp,"%s\t%s\t%c\t%s\t%s\n",name,mob,&gender,email,city)!=EOF)
    { 
      lno++;
      if ( strncmp(sname, name, strlen(sname)) == 0)
      {
        count =1;
        printf("\n%d. %s",lno,name);
      }     
    }
    if (count == 1)
    {
    printf("\nenter which number contact to display :");
    int x;
    scanf("%d",&x);
    readline(x);
    }

    else printf(RED"\nno matching contact found !"RESET);

    fclose(fp);
    fflush(stdin);
    printf("\nPRESS ANY KEY TO CONTINUE\n");
    getchar();
    system("clear");
    main();
}


// used in modify()
// Function similar to add() but with already given details
void adding(char *name,char *mob,char gender, char *email, char *city)
{
    FILE *fp;
    fp=fopen("contact.txt","a+");
    fprintf(fp,"%s\t%s\t%c\t%s\t%s\n",name,mob,gender,email,city);
    fclose(fp);
}

void modify()
{
   system("clear");
   FILE *fp = fopen("contact.txt","r");
   char name[50], mob[11], gender, email[50], city[20];
   char mname[50]; int choice;
   printf("enter the name of the contact to modify : ");
   scanf("%s",mname);
   int count=0;
   while(fscanf(fp,"%s\t%s\t%c\t%s\t%s\n",name,mob,&gender,email,city)!=EOF)
    { 
      if ( strncmp(mname, name, strlen(name)) == 0)
      {
        count = 1;
        printf("\n1. NAME    :-  %s",name);
        printf("\n2. MOBILE NUMBER. :-  %s",mob);
        printf("\n3. GENDER :-  %c",gender);
        printf("\n4. EMAIL :-  %s",email);
        printf("\n5. CITY :-  %s",city); 
        printf("\n6. Go back to main menu");
        printf("\nenter which detail you want to modify : ");
        scanf("%d",&choice);

        fflush(stdin);
        switch (choice)
        {
        case 1:
          printf("\nenter new name : ");
          scanf("%s", name);
          break;
        case 2:
          printf("\nenter new mobile number : ");
          scanf("%s", mob);
          break;
        case 3:
          printf("\nenter the gender : ");
          scanf("%c", &gender);
          break;
        case 4:
          printf("\nenter the new email : ");
          scanf("%s", email);
          break;
        case 5:
          printf("\nenter the new city : ");
          scanf("%s", city);
          break;
        case 6:
          main();
        default:
          break;
        }

        deleteLine(linenumber(mname));
        adding(name, mob, gender, email, city);
      }
    }
    if (count==0) printf(RED"\nno contact found !"RESET);
    fclose(fp);
    printf("\nPRESS ANY KEY TO CONTINUE\n");
    getchar();
    system("clear");
    main();
}


int main()
{
    int n;
    printf("1.Add contact \n2.View \n3.Delete \n4.Search \n5.Modify \n6.Exit \n");
    scanf("%d",&n);

    switch (n)
    {
    case 1:
        add();
        break;   
    case 2:
        view();
        break;
    case 3:
        delete();
        break;
    case 4:
        search();
        break;   
    case 5:
        modify();
        break;
    case 6:
        exit(0);
    }
}
