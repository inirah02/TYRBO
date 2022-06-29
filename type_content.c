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
            menu_type("Wait a minute... Do I know you?\n1)Yes\n2)No\n\n3)Exit Application\n\n");//this function prints information on screen in a typing like simulation
            scanf("%s",tmp);
            fflush(stdin);
            openfile_user(); //opens CSV file and stores user data into array of structures.
            if((!strcmpi("Yes",tmp))||(!strcmpi("1",tmp)))//allows user to enter "1" or "yes" to confirm
            {
                /*  user_n contains index corresponding to user's structure on successful login.
                    Contains -1 if login is unsuccessful.
                */
                curr_user=login(); //User defined function to access user details from the CSV file and log them in
                if(curr_user!=-1)
                   user_menu();
                else
                    menu_input(1);
            }
            else if((!strcmpi("No",tmp))||(!strcmpi("2",tmp)))//allows user to enter "2" or "no" to confirm
            {
                signup(); //User defined function to accept new user and store their details in CSV file
                menu_input(1);
            }
            else if(!strcmpi("3",tmp)||!strcmpi("Exit Application",tmp))
                exit(0);
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

void score_save(int *mode,float *wpm,float *acc,float *netwpm,float *time_taken)
{
    //dodo
}

char* level(int operation)
{
    switch(operation)
    {
        case 1:
            return("harry edward styles is an english singer songwriter and actor his musical career began as a solo contestant on the british music competition series the x factor following his elimination he was brought back to join the boy band one direction which went on to become one of the best selling boy bands of all time before going on an indefinite hiatus" );
            break;

        case 2:
            return("harry edward styles is an english singer songwriter and actor his musical career began as a solo contestant on the british music competition series the x factor following his elimination he was brought back to join the boy band one direction which went on to become one of the best selling boy bands of all time before going on an indefinite hiatus. Styles released his self-titled debut solo album through Columbia Records in 2017. It debuted at number one in the UK and the US and was one of the world's top-ten best-selling albums of the year, while its lead single, Sign of the Times, topped the UK Singles Chart. Styles second album, Fine Line (2019), debuted atop the US Billboard 200 with the biggest ever first-week sales by an English male artist, and was the most recent album to be included in Rolling Stone's 500 Greatest Albums of All Time in 2020. Its fourth single, Watermelon Sugar, topped the US Billboard Hot 100. Featuring the chart-topping single As It Was, Styles third album, Harry's House (2022) was widely acclaimed and broke several records" );
            break;

        case 3:
            return("Harry Edward Styles (born 1 February 1994) is an English singer, songwriter and actor. His musical career began in 2010 as a solo contestant on the British music competition series *[The X Factor](https://en.wikipedia.org/wiki/The_X_Factor_(UK_TV_series))*. Following his elimination, he was brought back to join the boy band [One Direction](https://en.wikipedia.org/wiki/One_Direction), which went on to become one of the [best-selling boy bands](https://en.wikipedia.org/wiki/Boy_band#Best-selling_boy_bands) of all time before going on an indefinite hiatus in 2016. Styles released his [self-titled debut solo album](https://en.wikipedia.org/wiki/Harry_Styles_(album)) through [Columbia Records](https://en.wikipedia.org/wiki/Columbia_Records) in 2017. It debuted at number one in the UK and the US and was one of the world's top-ten best-selling albums of the year, while its lead single, [Sign of the Times](https://en.wikipedia.org/wiki/Sign_of_the_Times_(Harry_Styles_song)), topped the [UK Singles Chart](https://en.wikipedia.org/wiki/UK_Singles_Chart). Styles second album, [Fine Line](https://en.wikipedia.org/wiki/Fine_Line_(album)) (2019), debuted atop the US [Billboard 200](https://en.wikipedia.org/wiki/Billboard_200) with the biggest ever first-week sales by an English male artist, and was the most recent album to be included in [Rolling Stone](https://en.wikipedia.org/wiki/Rolling_Stone)*'s [500 Greatest Albums of All Time](https://en.wikipedia.org/wiki/Rolling_Stone%27s_500_Greatest_Albums_of_All_Time) in 2020. Its fourth single, [Watermelon Sugar](https://en.wikipedia.org/wiki/Watermelon_Sugar), topped the US *[Billboard* Hot 100](https://en.wikipedia.org/wiki/Billboard_Hot_100). Featuring the chart-topping single [As It Was](https://en.wikipedia.org/wiki/As_It_Was), Styles' third album, *[Harry's House](https://en.wikipedia.org/wiki/Harry%27s_House)* (2022), was widely acclaimed and broke several records. Throughout his career, Styles has received several [accolades](https://en.wikipedia.org/wiki/List_of_awards_and_nominations_received_by_Harry_Styles), including two [Brit Awards](https://en.wikipedia.org/wiki/Brit_Award), a [Grammy Award](https://en.wikipedia.org/wiki/Grammy_Award), an [Ivor Novello Award](https://en.wikipedia.org/wiki/Ivor_Novello_Award), and an [American Music Award](https://en.wikipedia.org/wiki/American_Music_Award). Styles made his acting debut in [Christopher Nolan](https://en.wikipedia.org/wiki/Christopher_Nolan)'s 2017 [war film](https://en.wikipedia.org/wiki/War_film) *[Dunkirk](https://en.wikipedia.org/wiki/Dunkirk_(2017_film))*. Aside from music and acting, he is known for his flamboyant fashion. He is the first man to appear solo on the cover of *[Vogue](https://en.wikipedia.org/wiki/Vogue_(magazine))");    
    }
    return 0;
}

int view_records()
{
    printf("Inside view_records");
    Sleep(2000);
    return 0;
}
void user_menu() 
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    printf("Welcome to TYRBO, %s\n",s[curr_user].name);
    printf("What would you like to do?\n\n"); //very informal
    printf("\n1. Start Game\n2. View Archive\n3. User Settings \n4. View Gallery \n5. Credits\n6. Log Out\n7. Exit Application\n\n");
    char choice[20];
    fflush(stdin);
    scanf("%[^\n]s",choice);
    fflush(stdin);
    if(!strcmp(choice,"1")||!strcmpi(choice,"play")||!strcmpi(choice,"start")||!strcmpi(choice,"game")||!strcmpi(choice,"start game")||!strcmpi(choice,"Play Game")||!strcmpi(choice,"Go"))
    {
        if(!game_menu())
            user_menu();
    }
    else if(!strcmp(choice,"2")||!strcmpi(choice,"Archive")||!strcmpi(choice,"Viewarchive")||!strcmpi(choice,"view archive"))
    {
        if(!view_records())
            user_menu();
    }
    else if(!strcmp(choice,"3")||!strcmpi(choice,"Usersettings")||!strcmpi(choice,"User settings")||!strcmpi(choice,"settings"))
    {
        if(!user_settings())
            user_menu();
    }
    else if(!strcmp(choice,"4")||!strcmpi(choice,"ViewGallery")||!strcmpi(choice,"View Gallery")||!strcmpi(choice,"Gallery"))
    {
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        printf("Upcoming");
        Sleep(3000);
        user_menu();
    }
    else if(!strcmp(choice,"5")||!strcmpi(choice,"Credits"))
    {
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        printf("Upcoming");
        Sleep(3000);
        user_menu();
    }
    else if(!strcmp(choice,"6")||!strcmpi(choice,"logout")||!strcmpi(choice,"log out"))
    {
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        printf("Logging Out..");
        Sleep(1500);
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        menu_input(1);
    }
    else if(!strcmp(choice,"7")||!strcmpi(choice,"exit")||!strcmpi(choice,"exit application")||!strcmpi(choice,"exitapplication"))
    {
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        printf("It was a pleasure serving you.\nHope to see you soon.\n");
        Sleep(2000);
        exit(0);
    }
    else
    {
        int n=printf("Invalid Choice. Try Again");
        Sleep(1500);
        user_menu();
    }
}

int game_menu()
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    printf("\nTYRBO GAMEMODES\n\nHELLO %s\nChoose a game mode :\n",s[curr_user].name);
    printf("\n1. Normal Typing Test\n2. Sudden Death\n3. Basketball\n4. Help \n5. Go Back\n\n"); //improve nomenclature
    char choice[20];
    fflush(stdin);
    scanf("%[^\n]s",choice);
    fflush(stdin);
    if(!strcmp(choice,"1")||!strcmpi(choice,"Normal mode")||!strcmpi(choice,"Normal")||!strcmpi(choice,"Normal Typing Test"))
    {
        //call normal test function
        //call difficulty level thing also
        game_mode(1);
        return 1;
    }
    else if(!strcmp(choice,"2")||!strcmpi(choice,"suddendeath")||!strcmpi(choice,"sudden death")||!strcmpi(choice,"play sudden death"))
    {
        game_mode(2);
        return 1;
    }
    else if(!strcmp(choice,"3")||!strcmpi(choice,"Basketball")||!strcmpi(choice,"play basketball")||!strcmpi(choice,"BB")||!strcmpi(choice,"play BB"))
    {
        game_mode(3);
        return 1;
    }
    else if(!strcmp(choice,"4")||!strcmpi(choice,"help"))
    {
        //View instructions
        printf("Print Instructions Here");
        Sleep(2000);
        return 1;
    }
    else if(!strcmp(choice,"5")||!strcmpi(choice,"goback")||!strcmpi(choice,"go back")||!strcmpi(choice,"back"))
        return 0;
    else
    {
        printf("Invalid Choice. Try Again");
        Sleep(1500);
        return game_menu();
    }
}
void game_mode(int mode)
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    if(mode==1)
        printf("TYPING TEST\n\n");
    if(mode==2)
        printf("SUDDEN DEATH\n\n");
    if(mode==3)
        printf("BASKETBALL\n\n");
    printf("1. Start Game\n2. Instructions\n3. Go Back\n\n");
    char choice[20];
    fflush(stdin);
    scanf("%[^\n]s",choice);
    fflush(stdin);
    if(!strcmp(choice,"1")||!strcmpi(choice,"start")||!strcmpi(choice,"start game")||!strcmpi(choice,"play"))
    {
        /*for(int i=0;i<50;i++)
        {
            printf("\b \b");
        }
        */
        char *s;
        if(!(mode==3))
        {
            int flag;
            do
            {
                flag=0;
                printf("Choose Difficulty Level : \n1. Easy\n2. Moderate\n3. Hard\n\n"); //string fetched on the basis of difficulty level chosen by the player
                char choice[20];
                fflush(stdin);
                scanf("%[^\n]s",choice);
                fflush(stdin);
                if(!strcmp(choice,"1")||!strcmpi(choice,"Easy"))
                    s=level(1);
                else if(!strcmp(choice,"2")||!strcmpi(choice,"Moderate"))
                    s=level(2);
                else if(!strcmp(choice,"3")||!strcmpi(choice,"Hard"))
                    s=level(3);
                else
                {
                    printf("Invalid Choice.");
                    flag=1;
                }
            } while(flag);
        }
        //call function which starts the game
    }
    else if(!strcmp(choice,"2")||!strcmpi(choice,"instructions"))
    {
        print_instructions(mode);
        game_mode(mode);
    }
    else if(!strcmp(choice,"3")||!strcmpi(choice,"go back")||!strcmpi(choice,"back"))
        game_menu();
    else
    {
        printf("Invalid Choice.");
        Sleep(1500);
        return game_mode(mode);
    }
}

// metric scale for generating feedback wrt wpm
char* feedback_generator(float metric)
{
    if(metric>50 && metric<=85)
        return ("Excellent, Your typing speed is par professional! ");
    else if(metric>40 && metric<=50)
        return("Great, Your typing speed is pretty commendable! ");
    else if(metric>30 && metric<=40)
        return("Average, Your typing speed is in tandem with the normal typing speed");
    else if(metric>20 && metric<=30)
        return("Poor, You must work on your typing speed and improve!");
    else
        return("\n Incorrect ");
}

void print_instructions(int mode)
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    if(mode==1)
        printf("INSTRUCTIONS TO BE ADDED");
    else if(mode==2)
        printf("INSTRUCTIONS TO BE ADDED");
    else
        printf("INSTRUCTIONS TO BE ADDED");
    printf("\n\nPress B to Go back ");
    while(1)
        if(getch()=='B')
            break;
}