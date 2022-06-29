//This file contains the definitions of the functions defined in user_manage.h
//User management related functions can be found here
//For further details about a particular function, refer to documentation in respective header files.
#include <stdio.h>
#include "tc.h"
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "user_manage.h" //includes the user_manage.h header file that contains the prototyes of the functions defined in this file
FILE *fp;
int curr_user;
USER s[100];
int n;
int login()
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    char username[30],password[20];
    printf("LOGIN:\n");
    display_users();
    printf("Please Enter your credentials below:-\n\n");
    printf("Username: ");
    fflush(stdin);
    gets(username);
    if(search_u(username))
    {
        int user_no=search_u(username)-1;
        printf("\nPassword: ");
        char ch;
        int i=0;
        while((ch=getch())!=13)
        {
            if(ch=='\b')
            {
                if(i<1)
			

                    continue;
                printf("\b \b");
                i--;
                continue;
            }
            
            password[i]=ch;
            i++;
            printf("*");
        }
        password[i]='\0';
        if(!strcmp(s[user_no].pswd,password))
        {
            printf("\nLogin Successful.");
            Sleep(1500);
            return user_no;
        }
        else
        {
            printf("\nIncorrect password.");
            while(1)
            {
                printf("\nForgot Password?\n1)Yes\n2)No\n");
                char ch[4];
                scanf("%s",ch);
                if(!strcmpi("Yes",ch)||!strcmpi("1",ch))
                {
                    forgot_pswrd(user_no);
                    return -1;
                }
                else if((!strcmpi("No",ch)||!strcmpi("2",ch)))
                {
                    return login();
                }
                else
                    continue;
            }
        }
    }
    else
    {
        printf("\nSORRY, Username DOESN'T EXIST.\n");
        printf("\nSign Up?\n1)Yes\n2)No\n");
        char che[4];
        scanf("%s",che);
        fflush(stdin);
        if(!strcmpi("Yes",che)||!strcmpi("1",che))
        {
            signup();
            return -1;
        }
        else if((!strcmpi("No",che)||!strcmpi("2",che)))
            return login();
        else
        {
            TC_CLRSCR();
            TC_MOVE_CURSOR(0,0);
            return -1;
        }
    }
}
void display_users()
{
    printf("\nAvailable Users: \n");
    printf("\n%10s\t\t%10s\n","NAME","USERNAME");
    for(int i=0;i<n;i++)
        printf("%10s\t\t%10s\n",s[i].name,s[i].usrn);
    printf("\n");
}

void signup()
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    char username[100];
    char password[100],password1[100];
    printf("SIGN UP\n");
    while(1)
    {
        printf("Create new username: ");
        gets(username);
        printf("\n");
        if(search_u(username))
            printf("\nUsername already in use.\n");
        else
        {
            printf("\nUsername available.");
            break;
        }
    }
    while(1)
    {
        printf("\nCreate password: ");
        char ch;
        int i=0;
        while((ch=getch())!=13)
        {
            if(ch=='\b')
            {
                if(i<1)
                    continue;
                printf("\b \b");
                i--;
                continue;
            }
            printf("*");
            password[i]=ch;
            i++;
        }
        password[i]='\0';
        i=0;
        printf("\nRe-enter password to confirm: ");
        while((ch=getch())!=13)
        {
            if(ch=='\b')
            {
                if(i<1)
                    continue;
                printf("\b \b");
                i--;
                continue;
            }
            password1[i]=ch;
            i++;
            printf("*");
        }
        password1[i]='\0';
        if(strcmp(password,password1)==0)
            break;
        else
        {
            TC_CLRSCR();
            TC_MOVE_CURSOR(0,0);
            printf("\nPasswords do not match.");
            password[0]='\0';
            password1[0]='\0';
        }
    }
    char name[100];
    char sq[100];
    char sa[100];
    char email[100];
    printf("\nEnter your name: ");
    //scanf("%s",name);
    gets(name);
    printf("\nEnter your email address: ");
    gets(email);
    printf("\nEnter security question: ");
    gets(sq);
    printf("\nEnter answer to security question: ");
    gets(sa);
    strcpy(s[n].pswd,password);
    strcpy(s[n].name,name);
    strcpy(s[n].usrn,username);
    strcpy(s[n].email,email);
    strcpy(s[n].sq,sq);
    strcpy(s[n].sa,sa);
    printf("\nNew user created successfully!");
    Sleep(1000);
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    ++n;
    write();
}
int search_u(char usrname[])
{
    for(int i=0;i<n;i++)
        if(strcmp(s[i].usrn,usrname)==0)
            return (i+1);
    return 0;
}
void forgot_pswrd(int no)
{
    int i=no;
    Sleep(1000);
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    fflush(stdin);
    printf("%s:\n",s[i].name);
    char sa[100];
    printf("\nVerify your Identity:\n%s\n",s[i].sq);
    printf("Answer: ");
    gets(sa);
    char password[20],password1[20];
    if(!strcmp(sa,s[i].sa))
    {
        while(1)
        {
            printf("\nCreate new password: ");
            char ch;
            int j=0;
            while((ch=getch())!=13)
            {
                if(ch=='\b')
                {
                    if(i<1)
                        continue;
                    printf("\b \b");
                    j--;
                    continue;
                }
                if(ch<33 || ch>126)
                    continue;
                password[j]=ch;
                j++;
                printf("*");
            }
            password[j]='\0';
            j=0;
            printf("\nRe-enter password to confirm: ");
            while((ch=getch())!=13)
            {
                if(ch=='\b')
                {
                    if(i<1)
                        continue;
                    printf("\b \b");
                    j--;
                    continue;
                }
                if(ch<33 || ch>126)
                    continue;
                password1[j]=ch;
                j++;
                printf("*");
            }
            password1[j]='\0';
            if(strcmp(password,password1)==0)
                break;
            else
            {
                printf("\nPasswords do not match.");
                for(int l=0;l<20;l++)
                {
                    password[l]='\0';
                    password1[l]='\0';
                }
            }
        }
        strcpy(s[i].pswd,password);
        write();
        printf("\nPassword changed successfully.");
        Sleep(1500);
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
    }
    else
    {
        printf("\nVerification Failed\n");
        Sleep(1300);
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
    }  
}
int s_init()
{
    char l[100];
    fgets(l,100,fp);
    int i=0;	
    while(fgets(l,100,fp)!=NULL)
    {
        strcpy(s[i].usrn,decrypt(strtok(l,",")));
        strcpy(s[i].pswd,decrypt(strtok(NULL,",")));
        strcpy(s[i].name,decrypt(strtok(NULL,",")));
        strcpy(s[i].sq,decrypt(strtok(NULL,",")));
        strcpy(s[i].sa,decrypt(strtok(NULL,"\n")));
        i++;
    }
    return i;
}
void write()
{
    fp=fopen("resources/userdetails.csv","w");
    fprintf(fp,"Username,Password,Name,SecurityQuestion,SecurityAnswer\n");
    int i;
    for(i=0;i<n;i++)
		fprintf(fp,"%s,%s,%s,%s,%s\n",encrypt(s[i].usrn),encrypt(s[i].pswd),encrypt(s[i].name),encrypt(s[i].sq),encrypt(s[i].sa));
    fclose(fp);
}
void openfile_user()
{
    fp=fopen("resources/userdetails.csv","r");
    n=s_init(fp);
    fclose(fp);
}
char* encrypt(char s[])
{
    int i=0;
    for(;i<strlen(s);i++)
        s[i]=s[i]+2*i+4;
    s[i]='\0';
    return s;
}
char* decrypt(char s[])
{
    int i=0;
    for(;i<strlen(s);i++)
        s[i]=s[i]-2*i-4;
    s[i]='\0';
    return s;
}

void change_user_details()
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    printf("CHANGE USER DETAILS\n");
    printf("\n1. Change Name\n2. Change Security Question and Answer  \n3. Change email address  \n4. Reset Scores\n5. Go Back\n\n");
    char choice[20];
    fflush(stdin);
    scanf("%[^\n]s",choice);
 +  fflush(stdin);
    if(!(!strcmp(choice,"5")||!strcmpi(choice,"Go Back")))
    {
        if(!strcmp(choice,"1")||!strcmpi(choice,"change name"))
        {
            TC_CLRSCR();
            TC_MOVE_CURSOR(0,0);
            int flag=0;
            do
            {
                flag=0;
                printf("Current Name : %s", s[curr_user].name);
                printf("\nDo you want to change your Name?\n1. Yes\n2. No\n\n");
                char ch[10];
                gets(ch);
                strlen(ch);
                if((!strcmpi("Yes",ch))||(!strcmpi("1",ch)))
                {
                    printf("\n Enter New Name : ");
                    gets(s[curr_user].name);
                    printf("\n Your Name has been updated successfully.\n");
                    Sleep(1500);
                    change_user_details();
                }
                else if((!strcmpi("No",ch))||(!strcmpi("2",ch)))
                    change_user_details();
                else
                {
                    printf("Invalid choice.");
                    Sleep(1300);
                    TC_CLRSCR();
                    TC_MOVE_CURSOR(0,0);
                    flag=1;
                }
            }
            while(flag==1);
        }
        else if(!strcmp(choice,"2")||!strcmpi(choice,"change Security Question and Answer"))
        {
            TC_CLRSCR();
            TC_MOVE_CURSOR(0,0);
            int flag=0;
            do
            {
                flag=0;
                printf("Current Security Question And Answer :\n Security Question : %s  \n Security Answer : %s\n", s[curr_user].sq,s[curr_user].sa);
                printf("\nDo you want to change your Verification Details?\n1. Yes\n2. No\n\n");
                char ch[10];
                gets(ch);
                strlen(ch);
                if((!strcmpi("Yes",ch))||(!strcmpi("1",ch)))
                {
                    printf("\n Enter New Security Question : ");
                    gets(s[curr_user].sq);
                    printf("\n Enter Answer : ");
                    gets(s[curr_user].sa);
                    printf("\n Your Verification Details have been updated successfully.\n");
                    Sleep(1500);
                    change_user_details();
                }
                else if((!strcmpi("No",ch))||(!strcmpi("2",ch)))
                    change_user_details();
                else
                {
                    printf("Invalid choice.");
                    TC_CLRSCR();
                    TC_MOVE_CURSOR(0,0);
                    flag=1;
                }
            }
            while(flag==1);
        }
        else if(!strcmp(choice,"3")||!strcmpi(choice,"change email address"))
        {
            TC_CLRSCR();
            TC_MOVE_CURSOR(0,0);
            int flag=0;
            do
            {
                flag=0;
                printf("Current Email Address : %s", s[curr_user].email);
                printf("\nDo you want to change your email address?\n1. Yes\n2. No\n\n");
                char ch[10];
                gets(ch);
                strlen(ch);
                if((!strcmpi("Yes",ch))||(!strcmpi("1",ch)))
                {
                    printf("\n Enter New Email Address : ");
                    gets(s[curr_user].email);
                    printf("\n Your Email Address has been changed successfully.\n");
                    Sleep(1500);
                    change_user_details();
                }
                else if((!strcmpi("No",ch))||(!strcmpi("2",ch)))
                    change_user_details();
                else
                {
                    printf("Invalid choice.");
                    TC_CLRSCR();
                    TC_MOVE_CURSOR(0,0);
                    flag=1;
                }
            }
            while(flag==1);
        }
        else if(!strcmp(choice,"4")||!strcmpi(choice,"Reset scores"))
        {
            TC_CLRSCR();
            TC_MOVE_CURSOR(0,0);
            printf("FUNCTIONALITY YET TO BE ADDED.");
            Sleep(1500);
            change_user_details();
        }
        write();
    }
}
int user_settings()
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    printf("USER SETTINGS\n\n");
    printf("Welcome %s\n",s[curr_user].name);
    printf("What changes would you like to make to your account?\n");
    printf("\n1. View User Details\n2. Change Password\n3. Change Other User Details  \n4. Go Back  \n5. Delete This User\n\n");
    char choice[20];
    scanf("%[^\n]s",choice);
    fflush(stdin);
    if(!strcmp(choice,"1")||!strcmpi(choice,"View User Details"))
    {
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        printf("Your Details :\n\n");
        printf("NAME : %s",s[curr_user].name);
        printf("\nUSERNAME : %s",s[curr_user].usrn);
        printf("\nEMAIL ADDRESS : %s",s[curr_user].email);
        printf("\n\nPress B to Go Back. ");
        while(1)
            if(getch()=='B')
                return user_settings();
    }
    else if(!strcmp(choice,"2")||!strcmpi(choice,"changepassword")||!strcmpi(choice,"change password"))
    {
        forgot_pswrd(curr_user);
        return user_settings();
    }
    else if(!strcmp(choice,"3")||!strcmpi(choice,"changeotheruserdetails")||!strcmpi(choice,"change other user details"))
    {
        change_user_details();
        return user_settings();
    }
    else if(!strcmp(choice,"4")||!strcmpi(choice,"back")||!strcmpi(choice,"go back")||!strcmpi(choice,"goback"))
    {
        return 0;
    }
    else if(!strcmp(choice,"5")||!strcmpi(choice,"delete user")||!strcmpi(choice,"delete account"))
    {
        if(!delete_user())
            return user_settings();
        else 
        {
            Sleep(1000);
            exit(0);
        }
    }
    else
    {
        int n=printf("Invalid Choice. Try Again");
        Sleep(1500);
        return user_settings();
    }
}
int count=0;
int delete_user()
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    printf("DELETE USER\n");
    printf("\nEnter your password to carry on with this action.\n");
    char password[20];
    gets(password);
    if(strcmp(password,s[curr_user].pswd)==0)
    {
        printf("\n\n%s , Are you SURE you want to delete your account?\nAre you sure you won't regret this decision?\n",s[curr_user].name);
        printf("1. Yes,I'm sure.\n2. No,I have changed my mind.\n\n");
        char choice[20];
        scanf("%[^\n]s",choice);
        fflush(stdin);
        if(!strcmpi(choice,"1")||!strcmpi(choice,"Yes")||!strcmpi(choice,"Sure")||!strcmpi(choice,"Yes,I'm sure."))
        {
            for(int i=curr_user;i<n;i++)
                s[i]=s[i+1];
            s[n].email[0]='\0';
            s[n].name[0]='\0';
            s[n].pswd[0]='\0';
            s[n].sa[0]='\0';
            s[n].sq[0]='\0';
            n--;
            write();
            printf("Your account has been successfuly deleted. It has been a pleasure serving you. May you succeed in life.");
            return 1;
        }
        else if(!strcmpi(choice,"2")||!strcmpi(choice,"No")||!strcmpi(choice,"No,I have changed my mind."))
        {
            return 0;
        }
    }
    else
    {
        int n=printf("Incorrect password entered. Try again");
        count++;
        if(count<2)
        {
            Sleep(1500);
            return delete_user();
        }
        else
        {
            n+=printf("?\n1.Yes\n2. No , Go Back\n\n");
            char ch[10];
            gets(ch);
            if(!strcmpi(ch,"1")||!strcmpi(ch,"Yes")||!strcmpi(ch,"Try again"))
            {
                Sleep(1500);
                return delete_user();
            }
            else
                return 0;
        }
    }
}