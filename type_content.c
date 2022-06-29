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
#define CLEAR_INSTREAM FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE))
int menu_input(int n)//function that prints the various menus to be used throughout the program
{
    printf("\e[?25l");
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,0);
    char tmp[10];
    switch(n)
    {
        case 1://prints login/signup page
            TC_MOVE_CURSOR((columns-32)/2,(rows/2)-1);
            menu_type("Wait a minute... Do I know you?\n");//this function prints information on screen in a typing like simulation
            TC_MOVE_CURSOR((columns-6)/2,(rows/2));
            menu_type("1)Yes\n");
            TC_MOVE_CURSOR((columns-6)/2,(rows/2)+1);
            menu_type("2)No\n");
            TC_MOVE_CURSOR((columns-6)/2,(rows/2)+2);
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
    TC_CLRSCR();
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,0);
    TC_MOVE_CURSOR(((columns-32)/2),(rows/2)-1);
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
        printf("%c",*p++);
        Sleep(30);
        Sleep(30);
        count++;
    }
    return count;
}
int type_disp( char* p,int size, char gmode)
{
    TC_CLRSCR();
    char tmp[size];
    strcpy(tmp,p);
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,size);
    int ycopy=y;
    TC_CLRSCR();
    TC_MOVE_CURSOR(x,y);
    if(p==NULL)
        return -1;
    for(int i=1;*p;i++)
    {
        if(i==columns-1)
        {
            i=1;
            ycopy++;
            TC_MOVE_CURSOR(x,ycopy);
            strcat(tmp,"  ");
        }
        printf("%c\xDB",*(p++));
        //Sleep(30);
        printf("\b \b"); 
        //Sleep(30);
    }
    TC_MOVE_CURSOR(x,y);
    return type_input(tmp,size,gmode);
}
int type_input(char* p,int size,char gmode)
{
    CLEAR_INSTREAM;
    //time_t end =time(NULL)+5;
    printf("\e[?25l");
    clock_t t;
    char ch='a';
    int BBscore=0;
    int tmp=1;
    int count=0;
    int streak=0;
    int x=0,y=0,rows=0,columns=0;
    coord_details(&rows,&columns,&x,&y,size);
    FILE *fp;
    fp=fopen("resources/art/BB Launch.txt","r");
    char bball=fgetc(fp);
    int b=1;
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
            streak++;
        }
        else
        {  
            if(gmode=='b')
                return 0;
            if(gmode=='d')
            {
                size=count;
                break;
            }
            handle_wrong_case(fp,&b,&streak,&count,p,x,y,0);
        }
        if((gmode=='s') && (streak>0) && (streak%5==0))
        { 
            TC_MOVE_CURSOR(0,b);
            for(;bball!='\n';)
            {
                printf("%c",bball);
                bball=fgetc(fp);
            }
            b++;
            bball=fgetc(fp);
            if(streak==65)
            {

                if(bball_dunk())
                {
                    art_disp("resources/art/BB Dunk.txt");
                    BBscore+=25;
                }
                else
                {
                    art_disp("resources/art/OOF.txt");
                    BBscore+=5;
                }
                Sleep(1000);
                CLEAR_INSTREAM;
                TC_CLRSCR();
                ungetc('\n',stdin);
                ch=getc(stdin);
                count--;
                handle_wrong_case(fp,&b,&streak,&count,p,x,y,1);
                TC_CLRSCR();
                TC_MOVE_CURSOR(x,y);
                printf("%s",p);
            }
        }
    }
    if(gmode!='b')
    {    
        TC_CLRSCR();
        t = clock() - t;
        float time_taken = ((float)t)/CLOCKS_PER_SEC; // calculate the elapsed time
        score(time_taken,count,size,gmode,BBscore);
    }
    return 1;
}
void score(float time_taken,int count,int size,char gmode,int BBscore)
{
    printf("\e[?25l");
    TC_MOVE_CURSOR(0,0);
    count++;
    float wpm=((size/5)/(time_taken/60));
    float acc=((float)size/(float)count)*100;
    float netwpm=wpm*(acc/100);
    if(gmode!='d')
    {
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
    }
    if(gmode=='d')
    {
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        printf("\nTime Taken: %s%.2fs%s\nCharacters: %s%d%s",TC_GRN,time_taken,TC_NRM,TC_GRN,--count,TC_NRM);
    }
    else if(gmode=='s')
    { 
        printf("\nYour Score was: %s%d%s",TC_GRN,BBscore,TC_NRM);
    }
    getch();
    //score_save(&wpm,&acc,&netwpm,&time_taken);
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
int handle_wrong_case(FILE* fp,int* b,int* streak,int* count,char* p,int x,int y,int color)
{
    TC_CLRSCR();
    fseek(fp,0,SEEK_SET);
    *b=0;
    TC_MOVE_CURSOR(x,y); 
    if(*p==' ')
    {
        printf("%s%c%s%s\b",TC_RED,'_',TC_NRM,p+1);
        *streak=0;
        *count+=1;
        return 1;
    }
    printf("%s%c%s%s\b",TC_RED,*(p),TC_NRM,p+1);
    if(color)
    {
        TC_MOVE_CURSOR(x,y);
        printf("%s\b",p);

    }
    *streak=0;
    *count+=1;
    return 1;
}
void art_disp(char *filename)
{
    printf("\e[?25l");
    FILE *fp;
    fp=fopen(filename,"r");
    char ch;
    //fscanf(fp,"%c",&ch);
    ch=fgetc(fp);
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    while(ch!=EOF)
    {
        ch=fgetc(fp);
       // Sleep(1);
        printf("%s%c%s",TC_GRN,ch,TC_NRM);
    }
    fclose(fp);
}
int bball_dunk()
{
    FILE *frand;
    frand=fopen("resources/Dunk words.csv","r");
    srand(time(NULL));
    int r=0;
    while(!(r>0))
    {
        r=rand() % 213;
    }
    char ch[1100];
    char tmp[6];
    fgets(ch,1100,frand);
    strcpy(tmp,strtok(ch,","));
    for(int i=0;i<=r-1;i++)
    {
        strcpy(tmp,strtok(NULL,","));
    }
    TC_CLRSCR();
    art_disp("resources/art/BASKETBALL.txt");
    Sleep(750);
    fclose(frand);
    return type_disp(tmp,5,'b');
}