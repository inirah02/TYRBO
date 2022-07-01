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
SCORE scores[100];
int score_n;
FILE *score_fp;
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
                /*  curr_user contains index corresponding to user's structure on successful login.
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
        caps_check();
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
                caps_check();
                ungetc('\n',stdin);
                ch=getc(stdin);
                count--;
                handle_wrong_case(fp,&b,&streak,&count,p,x,y,1);
                TC_CLRSCR();
                caps_check();
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
    if(gmode=='n')
    {
        score_save(1,&wpm,&acc,&netwpm,-1);
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
        score_save(2,&wpm,&acc,&netwpm,BBscore);
    }
    printf("\n%sPress any key to continue%s",TC_YEL,TC_NRM);
    Sleep(1500);
    getch();
    user_menu();
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
    caps_check();
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

void score_save(int mode, float *wpm, float *acc, float *netwpm, int BBscore)
{
    strcpy(scores[score_n].date,__DATE__);
    strcpy(scores[score_n].time,__TIME__);
    scores[score_n].gmode=mode;
    scores[score_n].wpm=*wpm;
    scores[score_n].accuracy=*acc;
    scores[score_n].netwpm=*netwpm;
    scores[score_n].BBscore=BBscore;
    score_n++;
    open_scorefile();
    write_score(mode,wpm,acc,netwpm,BBscore);
}

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
void caps_check()
{
    int rows=0,columns=0;
    termsize(&rows,&columns);
    if (GetKeyState(VK_CAPITAL) & 1)
    {
        TC_MOVE_CURSOR((columns-16)/2,(rows/2)+4);
        printf("CAPS LOCK IN ON");
    }
    else
    {
        TC_MOVE_CURSOR((columns-16)/2,(rows/2)+4);
        printf("               ");
    }
}
void waterfall()
{
    printf("\e[?25l");
    FILE *fp=fopen("resources/art/TYRBO.txt","r");
    char ch[200];
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
    //TC_MOVE_CURSOR(0,0);
    while(fgets(ch,105,fp)!=NULL)
    {
        printf("%s",ch);
        Sleep(36);
    }
    fclose(fp);
    TC_CLRSCR();
    TC_MOVE_CURSOR(0,0);
}
