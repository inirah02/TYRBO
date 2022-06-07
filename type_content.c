#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>  
#include"type_content.h"
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
    count=sim_type("What would you like to do today?:\n1)Move it Move it\n2)Ayyy Wassup Gayathri and Harini\n3)This pretty cool eh?\n4)Ok bye");
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