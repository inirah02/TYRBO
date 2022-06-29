#include"tc.h"
int termsize(int *rows,int *columns)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void coord_details(int *rows,int *columns,int *x,int *y,int size)
{
    *rows=0;
    *columns=0;
    termsize(rows,columns);
    *x=(size>*columns)?0:((*columns-size)/2);
    *y=((*rows/2)>16)?(*rows/2):16;
}