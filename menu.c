#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include"type_content.h"
#include"user_manage.h"
#include"menu.h"
#include"tc.h"

char* level(int operation)
{
    switch(operation)
    {
        case 1:
            return("github inc is a provider of internet hosting for software development and version control using git which is an extremely useful tool for developers "  );
            break;

        case 2:
            return("The formula one series originated with Grand Prix Motor Racing. It consists of a set of rules that all participants' cars must meet. Each driver must hold a valid Super Licence, the highest class of racing license issued by the FIA. " );
            break;

        case 3:
            return("Harry eDwArd Styles is an EnGlish sInger soNgwRiter and actOr his musical career began as a solo contestant on the brItish muSic coMpetiTion seRies the x fActor. Aside frOm music and acting, he is knOwn for his flamboyant fashion. " );    
    }
    return 0;
}

int view_records()
{
    printf("Inside view_records");
    Sleep(2000);
    return 0;
}

void open_scorefile()
{
    char f_name[100];
    f_name[0]='\0';
    strcat(f_name,s[curr_user].usrn);
    strcat(f_name,".txt");
    char f_name1[100];
    f_name1[0]='\0';
    strcat(f_name1,"resources/score/");
    strcat(f_name1,f_name);
    score_fp=fopen(f_name1,"r");
    score_n=score_init();
    fclose(score_fp);
}
int write_score(int gmode,float *wpm,float *acc,float *net_wpm, int BBscore)
{
	// open file for appending
    char f_name[100];
    f_name[0]='\0';
    strcat(f_name,s[curr_user].usrn);
    strcat(f_name,".txt");
    char f_name1[100];
    f_name1[0]='\0';
    strcat(f_name1,"resources/score/");
    strcat(f_name1,f_name);
    score_fp=fopen(f_name1,"a");
	fprintf(score_fp,"%s,%s,%f,%f,%f,%d,%d\n",__DATE__,__TIME__,*wpm,*acc,*net_wpm,gmode,BBscore);
	fclose(score_fp);
	return 0;
}
int score_init()
{
    char l[100];
    fgets(l,100,score_fp);
    int i=0;	
    while(fgets(l,100,score_fp)!=NULL)
    {
        strcpy(scores[i].date,strtok(l,","));
        strcpy(scores[i].time,strtok(NULL,","));
        scores[i].wpm=atof(strtok(NULL,","));
        scores[i].accuracy=atof(strtok(NULL,","));
        scores[i].netwpm=atof(strtok(NULL,","));
        scores[i].gmode=atoi(strtok(NULL,"\n"));
        scores[i].BBscore=atoi(strtok(NULL,"\n"));
        i++;
    }
    return i;
}

void user_menu() 
{
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    printf("Welcome to TYRBO, %s\n",s[curr_user].name);
    printf("What would you like to do?\n\n"); //very informal
    printf("\n1. Game\n2. Archive\n3. Settings \n4. Gallery \n5. Credits\n6. Log Out\n7. Exit\n\n");
    char choice[20];
    fflush(stdin);
    scanf("%[^\n]s",choice);
    fflush(stdin);
    if(!strcmp(choice,"1")||!strcmpi(choice,"play")||!strcmpi(choice,"start")||!strcmpi(choice,"game")||!strcmpi(choice,"start game")||!strcmpi(choice,"Play Game")||!strcmpi(choice,"Go"))
    {
        if(!game_menu())
            user_menu();
    }
    else if(!strcmp(choice,"2")||!strcmpi(choice,"Archive")||!strcmpi(choice,"Viewarchive"))
    {
        if(!view_records())
            user_menu();
    }
    else if(!strcmp(choice,"3")||!strcmpi(choice,"settings"))
    {
        if(!user_settings())
            user_menu();
    }
    else if(!strcmp(choice,"4")||!strcmpi(choice,"Gallery")||!strcmpi(choice,"Gall"))
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
    else if(!strcmp(choice,"7")||!strcmpi(choice,"exit")||!strcmpi(choice,"leave"))
    {
        TC_CLRSCR();
        TC_MOVE_CURSOR(0,0);
        waterfall();
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
    printf("\nTYRBO GAMEMODES\n\nHello %s,\n what would you like to play ?\n",s[curr_user].name);
    printf("\n1. Standard\n2. Sudden Death\n3. Basketball\n4. Help \n5. Go Back\n\n"); //improve nomenclature
    char choice[20];
    fflush(stdin);
    scanf("%[^\n]s",choice);
    fflush(stdin);
    if(!strcmp(choice,"1")||!strcmpi(choice,"standard")||!strcmpi(choice,"std"))
    {
        //call normal test function
        //call difficulty level thing also
        game_mode(1);
        return 1;
    }
    else if(!strcmp(choice,"2")||!strcmpi(choice,"suddendeath")||!strcmpi(choice,"sudden death")||!strcmpi(choice,"sudden")||!strcmpi(choice,"death")||!strcmpi(choice,"play sudden death"))
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
        printf("STANDARD\n\n");
    if(mode==2)
        printf("SUDDEN DEATH\n\n");
    if(mode==3)
        printf("BASKETBALL\n\n");
    printf("1. Start\n2. Instructions\n3. Go Back\n\n");
    char choice[20];
    fflush(stdin);
    scanf("%[^\n]s",choice);
    fflush(stdin);
    if(!strcmp(choice,"1")||!strcmpi(choice,"start")||!strcmpi(choice,"start game")||!strcmpi(choice,"play")||!strcmpi(choice,"game")||!strcmpi(choice,"s"))
    {
        char *s;
        if(!(mode==3))
        {
            int flag;
            do
            {
                TC_CLRSCR();
                TC_MOVE_CURSOR(0,0);
                flag=0;
                printf("Choose a difficulty level : \n1. Easy\n2. Moderate\n3. Hard\n\n"); //string fetched on the basis of difficulty level chosen by the player
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
                    Sleep(1300);
                    flag=1;
                }
            } while(flag);
            if(mode==1)
                type_disp(s,strlen(s)-1,'n');
            else
                type_disp(s,strlen(s)-1,'d');
        }
        else
        {
            type_disp("Wikipedia is a multilingual free online encyclopedia written and maintained by a community of volunteers through open collaboration and a wiki-based editing system. Individual contributors, also called editors, are known as Wikipedians. ",237,'s');
        }
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
