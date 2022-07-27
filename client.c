//The client code that contains the main function
#include<stdio.h>
#include"type_content.h"//includes the user defined type_content.h header file
#include"tc.h"
int main()
{
    art_disp("resources/art/TYRBO.txt");
    print_menu();//calls function from type_content.h to print the Landing Page
    // type_disp("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa Wikipedia is a multilingual free online ",194,'s');
    return 0;
}
