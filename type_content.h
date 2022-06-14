//header file that contains the prototypes for functions that will be used for typing related actions
void print_menu();//function to print the Landing Page
int menu_type(const char *p);//function to print information on terminal in a typing like simulation
void menu_del(int);//function to clear information from terminal in a typing like simulation(as though using backspace)
int menu_input(int);/*function that prints the various menus to be used throughout the program. Different codes passed to this
function implies different menus to be printed:
1)Login/Signup Page*/
void type_disp(char* ,int );//function to display text to be typed.Parameters:(string,size of string)
void type_input(char*,int,int,int);//function that takes input from user to play the game and tracks right and wrong inputs.Parameters:(string,size of string,rows,columns)
void score(float,int,int);//function to calculate the user score.Parameters:(time_taken,total characters input by user,size of string)
