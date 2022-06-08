#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>  
#include"type_content.h"
#include"user_manage.h"
int menu_input(int n)
{
    char tmp[10];
    switch(n)
    {
        case 1:
            sim_type("Wait a minute... Do I know you?\n1)Yes\n2)No\n");
            scanf("%s",tmp);
            if((!strcmpi("Yes",tmp))||(!strcmpi("1",tmp)))
                login();
            else if((!strcmpi("No",tmp))||(!strcmpi("2",tmp)))
                signup();
            
    }
    return 0;
}
void print_menu()
{
    int count=sim_type("Welcome To Turb");
    Sleep(1000);
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
void sim_del(int count)
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
        printf("%c\xDB",*p++);
        Sleep(30);
        printf("\b \b"); 
        Sleep(30);
        count++;
    }
    return count;
}