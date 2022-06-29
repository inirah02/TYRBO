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


// metric scale for generating feedback wrt wpm

char* feedback_generator(float metric)
{
    
    if(metric>50 && metric<=85)
        return("Excellent, Your typing speed is par professional! ");
    else if(metric>40 && metric<=50)
        return("Great, Your typing speed is pretty commendable! ");
    else if(metric>30 && metric<=40)
        return("Average, Your typing speed is in tandem with the normal typing speed");
    else if(metric>20 && metric<=30)
        return("Poor, You must work on your typing speed and improve!");
    else
        return("\n Incorrect ");
    
   
}

// //menu of difficulty

//     printf("Choose difficulty level by entering appropriate index number: \n 1. Easy \n 2.Intermediate \n 3. Difficult  ");
//     scanf("%lf", &operation);

// char* level(int operation);
//     switch(operation)
//     {
//         case 1:
//             return("harry edward styles is an english singer songwriter and actor his musical career began as a solo contestant on the british music competition series the x factor following his elimination he was brought back to join the boy band one direction which went on to become one of the best selling boy bands of all time before going on an indefinite hiatus" );
//             break;

//         case 2:
//             return("harry edward styles is an english singer songwriter and actor his musical career began as a solo contestant on the british music competition series the x factor following his elimination he was brought back to join the boy band one direction which went on to become one of the best selling boy bands of all time before going on an indefinite hiatus. Styles released his self-titled debut solo album through Columbia Records in 2017. It debuted at number one in the UK and the US and was one of the world's top-ten best-selling albums of the year, while its lead single, Sign of the Times, topped the UK Singles Chart. Styles second album, Fine Line (2019), debuted atop the US Billboard 200 with the biggest ever first-week sales by an English male artist, and was the most recent album to be included in Rolling Stone's 500 Greatest Albums of All Time in 2020. Its fourth single, Watermelon Sugar, topped the US Billboard Hot 100. Featuring the chart-topping single As It Was, Styles third album, Harry's House (2022) was widely acclaimed and broke several records" );
//             break;

//         case 3:
//             return("Harry Edward Styles (born 1 February 1994) is an English singer, songwriter and actor. His musical career began in 2010 as a solo contestant on the British music competition series *[The X Factor](https://en.wikipedia.org/wiki/The_X_Factor_(UK_TV_series))*. Following his elimination, he was brought back to join the boy band [One Direction](https://en.wikipedia.org/wiki/One_Direction), which went on to become one of the [best-selling boy bands](https://en.wikipedia.org/wiki/Boy_band#Best-selling_boy_bands) of all time before going on an indefinite hiatus in 2016. Styles released his [self-titled debut solo album](https://en.wikipedia.org/wiki/Harry_Styles_(album)) through [Columbia Records](https://en.wikipedia.org/wiki/Columbia_Records) in 2017. It debuted at number one in the UK and the US and was one of the world's top-ten best-selling albums of the year, while its lead single, [Sign of the Times](https://en.wikipedia.org/wiki/Sign_of_the_Times_(Harry_Styles_song)), topped the [UK Singles Chart](https://en.wikipedia.org/wiki/UK_Singles_Chart). Styles second album, [Fine Line](https://en.wikipedia.org/wiki/Fine_Line_(album)) (2019), debuted atop the US [Billboard 200](https://en.wikipedia.org/wiki/Billboard_200) with the biggest ever first-week sales by an English male artist, and was the most recent album to be included in [Rolling Stone](https://en.wikipedia.org/wiki/Rolling_Stone)*'s [500 Greatest Albums of All Time](https://en.wikipedia.org/wiki/Rolling_Stone%27s_500_Greatest_Albums_of_All_Time) in 2020. Its fourth single, [Watermelon Sugar](https://en.wikipedia.org/wiki/Watermelon_Sugar), topped the US *[Billboard* Hot 100](https://en.wikipedia.org/wiki/Billboard_Hot_100). Featuring the chart-topping single [As It Was](https://en.wikipedia.org/wiki/As_It_Was), Styles' third album, *[Harry's House](https://en.wikipedia.org/wiki/Harry%27s_House)* (2022), was widely acclaimed and broke several records. Throughout his career, Styles has received several [accolades](https://en.wikipedia.org/wiki/List_of_awards_and_nominations_received_by_Harry_Styles), including two [Brit Awards](https://en.wikipedia.org/wiki/Brit_Award), a [Grammy Award](https://en.wikipedia.org/wiki/Grammy_Award), an [Ivor Novello Award](https://en.wikipedia.org/wiki/Ivor_Novello_Award), and an [American Music Award](https://en.wikipedia.org/wiki/American_Music_Award). Styles made his acting debut in [Christopher Nolan](https://en.wikipedia.org/wiki/Christopher_Nolan)'s 2017 [war film](https://en.wikipedia.org/wiki/War_film) *[Dunkirk](https://en.wikipedia.org/wiki/Dunkirk_(2017_film))*. Aside from music and acting, he is known for his flamboyant fashion. He is the first man to appear solo on the cover of *[Vogue](https://en.wikipedia.org/wiki/Vogue_(magazine))");
         
//     }

//     return 0;
// }

