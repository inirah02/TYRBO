//The client code that contains the main function
#include<stdio.h>
#include"type_content.h"//includes the user defined type_content.h header file
#include"tc.h"
int main()
{
    print_menu();//calls function from type_content.h to print the Landing Page
    type_disp("Wikipedia is a multilingual free online encyclopedia written and maintained by a community of volunteers through open collaboration and a wiki-based editing system. Individual contributors, also called editors, are known as Wikipedians.Wikipedia is a multilingual free online encyclopedia written and maintained by a community of volunteers through open collaboration and a wiki-based editing system. Individual contributors, also called editors, are known as Wikipedians. ",473);
    return 0;
}
