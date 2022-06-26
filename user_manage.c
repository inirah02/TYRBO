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
                    return -1;
            }
            getch();
        }
    }
    else
    {
        printf("\nSORRY, Username DOESN'T EXIST.\n");
        Sleep(1500);
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        return 0;
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
    printf("\nEnter your name: ");
    //scanf("%s",name);
    gets(name);
    printf("\nEnter security question: ");
    gets(sq);
    printf("\nEnter answer to security question: ");
    gets(sa);
    strcpy(s[n].pswd,password);
    strcpy(s[n].name,name);
    strcpy(s[n].usrn,username);
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
        getch();
        Sleep(1000);
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
    fp=fopen("userdetails.csv","w");
    fprintf(fp,"Username,Password,Name,SecurityQuestion,SecurityAnswer\n");
    int i;
    for(i=0;i<n;i++)
		fprintf(fp,"%s,%s,%s,%s,%s\n",encrypt(s[i].usrn),encrypt(s[i].pswd),encrypt(s[i].name),encrypt(s[i].sq),encrypt(s[i].sa));
    fclose(fp);
}
void openfile_user()
{
    fp=fopen("userdetails.csv","r");
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