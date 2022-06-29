//header file that contains the prototypes for functions that will be used for user management
typedef struct user
{
    char usrn[100];
    char pswd[100];
    char name[100];
    char email[100];
    char sq[100];
    char sa[100];
}USER;

/* Array of structures storing user details.
*/
extern USER s[100];

/* Stores array index corresponding to current user on successful login.
*/
extern int curr_user;

/*  User defined function to access user details from the CSV file and log them in
    Returns array index associated with the user on successful login.
    Returns -1 if login is unsuccessful.
*/
int login();

/*User defined function to accept new user and store their details in CSV file
*/
void signup();

int search_u(char []);

/*  Verifies identity of user and allows user to change their 
    password if verification is successful.
*/
void forgot_pswrd();

/*  Initializes array of structures */
int s_init();

/*  Writes data from an array of structures into a CSV file. */
void write();

/*  Opens the CSV file containing user details.
    Stores user data into an array of structures.
*/
void openfile_user();

/*  Encrpyts a string passed to it and returns a pointer to the
    encrypted string
*/
char* encrypt(char []);

/*  Decrypts an encrypted string passed to it and returns a pointer
    to the decrypted string
*/
char* decrypt(char []);

/*  Displays a list of available users along with their names and 
    usernames 
*/
void display_users();

/* Allows User to manage his/her account.
*/
int user_settings();

/* Allows User to delete his/her account.
*/
int delete_user();

/* Allows User to change details of his/her account.
*/
void change_user_details();
