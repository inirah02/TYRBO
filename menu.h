
FILE *score_fp;
int score_n;

int game_menu();
/*  Provides user with set of options such as to begin playing
    , change settings , exit application etc.
*/
void user_menu();
/*  Allows user to view previous records.
*/
int view_records();

// metric scale for generating feedback wrt wpm
char* feedback_generator(float);

char* level(int);

/*  Prints instructions of corresponding game mode.
*/
void print_instructions(int mode);

/*  Enters game mode passed as argument */
void game_mode(int mode);

typedef struct
{
char date[100];
char time[100];
float wpm;
float accuracy;
float netwpm;
int gmode;
int BBscore;
}SCORE;

extern SCORE scores[100];
extern int score_n;

void open_scorefile();
int score_init();

int write_score(int gmode,float *wpm,float *acc,float *net_wpm,int BBscore);
