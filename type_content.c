//This file contains the definitions of the functions defined in type_content.h
//Typing related functions can be found here
//For further details about a particular function, refer to documentation in respective header files.
#include<stdio.h>
#include<windows.h>//includes windows.h that contains functions like Sleep()
#include<conio.h>//includes conio.h that contains functions like getch()
#include<string.h> //includes string.h that contains string manipulation functions like strcmpi() strlen()
#include"type_content.h"//includes the user defined type_content.h header file
#include"user_manage.h"//includes the user defined user_manage.h header file
#include<time.h>
#include"tc.h"
int menu_input(int n)//function that prints the various menus to be used throughout the program
{
    char tmp[10];
    switch(n)
    {
        case 1://prints login/signup page
            menu_type("Wait a minute... Do I know you?\n1)Yes\n2)No\n");//this function prints information on screen in a typing like simulation
            scanf("%s",tmp);
            fflush(stdin);
            openfile_user(); //opens CSV file and stores user data into array of structures.
            if((!strcmpi("Yes",tmp))||(!strcmpi("1",tmp)))//allows user to enter "1" or "yes" to confirm
            {
                /*  user_n contains index corresponding to user's structure on successful login.
                    Contains -1 if login is unsuccessful.
                */
                int user_n=login(); //User defined function to access user details from the CSV file and log them in
                if(user_n!=-1)
                {
                   //NEXT
                }
                else
                    menu_input(1);
            }
            else if((!strcmpi("No",tmp))||(!strcmpi("2",tmp)))//allows user to enter "2" or "no" to confirm
            {
                signup(); //User defined function to accept new user and store their details in CSV file
                menu_input(1);
            }
    }
    return 0;
}
void print_menu()//function to print the Landing Page
{
    int count=menu_type("Welcome To Turb");
    Sleep(1000);//stops execution for time in ms specified in parameter
    for(int i=0;i<3;i++)
    {
        menu_del(1);
        Sleep(100);
    }
    menu_type("yrbo!!");
    Sleep(500);
    menu_del(count+3);
    Sleep(200);
    menu_input(1);
}
void menu_del(int count)//function to clear information from terminal in a typing like simulation(as though using backspace)
{
    for(int i=0;i<count;i++)
    {
        Sleep(30);
        printf("\b \b");
    }
}
int menu_type(const char *p)
{
    int count=0;
    if(p==NULL)
        return -1;
    while(*p)
    {
        printf("%c\xDB",*p++);//\xDB prints solid cursor
        Sleep(30);
        printf("\b \b"); 
        Sleep(30);
        count++;
    }
    return count;
}
void type_disp( char* p,int size)
{
    TC_CLRSCR();
    char tmp[size];
    strcpy(tmp,p);
    int rows=0;
    int columns=0;
    termsize(&rows,&columns);
    int x=(size>columns)?0:((columns-size)/2);
    int y=rows/2;
    TC_CLRSCR();
    TC_MOVE_CURSOR(x,y);
    if(p==NULL)
        return;
    for(int i=1;*p;i++)
    {
        if(i==columns-1)
        {
            i=1;
            y++;
            TC_MOVE_CURSOR(x,y);
            strcat(tmp,"  ");
        }
        printf("%c\xDB",*(p++));
        Sleep(30);
        printf("\b \b"); 
        //Sleep(30);
    }
    TC_MOVE_CURSOR(x,(rows/2));
    type_input(tmp,size,rows,columns);
}
void trimTrailing(char * str)
{
    printf("\e[?25l");
    int index, i;
    index = -1;//Set default index
    i = 0;//Find last index of non-white space character
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }
        i++;
    }
    str[index + 2] = '\0';//Mark next character to last non-white space character as NULL
}
void type_input(char* p,int size,int rows, int columns)
{
    printf("\e[?25l");
    clock_t t;
    char ch='a';
    int tmp=1;
    int count=0;
    int x=(size>columns)?0:((columns-size)/2);
    //int y=0;
    int y=rows/2;
    for(;((*(p+1))!='\0')&&(ch=getch());)
    {
        if(tmp)
        {
            t=clock();
            tmp--;
        }
        if(ch==*p)
        {
            TC_MOVE_CURSOR(x,y);
            printf("%s\b",p+1);
            p+=1;
            count+=1;
            trimTrailing(p);
        }
        else
        {  
            TC_MOVE_CURSOR(x,y); 
            if(*p==' ')
            {
                printf("%s%c%s%s\b",TC_RED,'_',TC_NRM,p+1);
                continue;
            }
            printf("%s%c%s%s\b",TC_RED,*(p),TC_NRM,p+1);
            count+=1;
        }
    }
    t = clock() - t;
    float time_taken = ((float)t)/CLOCKS_PER_SEC; // calculate the elapsed time
    score(time_taken,count,size);
}
void score(float time_taken,int count,int size)
{
    TC_MOVE_CURSOR(0,0);
    float wpm=((size/5)/(time_taken/60));
    float acc=((float)size/(float)count)*100;
    float netwpm=wpm*(acc/100);
    printf("\nTime Taken: %s%.2fs%s\nCharacters: %s%d/%d%s",TC_GRN,time_taken,TC_NRM,TC_GRN,++count,size,TC_NRM);
    printf("\nYour WPM was: %s%.1f%s",TC_GRN,wpm,TC_NRM);
    printf("\nYour net WPM was: %s%.1f%s",TC_GRN,netwpm,TC_NRM);
    if(acc==100.0)
    {
        printf("\nYour accuracy was: %s",TC_CYN);
    }
    else if(acc>=95.0)
    {
        printf("\nYour accuracy was: %s",TC_MAG);
    }
    else if(acc>=90.0 && acc<95.0)
    {
        printf("\nYour accuracy was: %s",TC_GRN);
    }
    else if(acc>=80.0 && acc<90.0)
    {
        printf("\nYour accuracy was: %s",TC_YEL);
    }
    else
    {
        printf("\nYour accuracy was: %s",TC_RED);
    }
    printf("%.1f%c%s",acc,'%',TC_NRM);
    getch();
    //score_save(&wpm,&acc,&netwpm,&time_taken);
}