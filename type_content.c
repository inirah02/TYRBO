//This file contains the definitions of the functions defined in type_content.h
//Typing related functions can be found here
//For further details about a particular function, refer to documentation in respective header files.
#include<stdio.h>
#include<windows.h>//includes windows.h that contains functions like Sleep()
#include<conio.h>//includes conio.h that contains functions like getch()
#include<string.h> //includes string.h that contains string manipulation functions like strcmpi() strlen()
#include"type_content.h"//includes the user defined type_content.h header file
#include"user_manage.h"//includes the user defined user_manage.h header file
int menu_input(int n)//function that prints the various menus to be used throughout the program
{
    char tmp[10];
    switch(n)
    {
        case 1://prints login/signup page
            sim_type("Wait a minute... Do I know you?\n1)Yes\n2)No\n");//this function prints information on screen in a typing like simulation
            scanf("%s",tmp);
            if((!strcmpi("Yes",tmp))||(!strcmpi("1",tmp)))//allows user to enter "1" or "yes" to confirm
                login();//User defined function to access user details from the database and log them in
            else if((!strcmpi("No",tmp))||(!strcmpi("2",tmp)))//allows user to enter "2" or "no" to confirm
                signup();//User defined function to accept new user and store their details in database
            
    }
    return 0;
}
void print_menu()//function to print the Landing Page
{
    int count=sim_type("Welcome To Turb");
    Sleep(1000);//stops execution for time in ms specified in parameter
    for(int i=0;i<3;i++)
    {
        sim_del(1);
        Sleep(100);
    }
    sim_type("yrbo!!");
    Sleep(500);
    sim_del(count+3);
    Sleep(200);
    menu_input(1);
}
void sim_del(int count)//function to clear information from terminal in a typing like simulation(as though using backspace)
{
    for(int i=0;i<count;i++)
    {
        Sleep(30);
        printf("\b \b");
    }
}
int sim_type(const char *p)
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