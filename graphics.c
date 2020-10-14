#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>


#define COLS 100 
#define ROWS 40 
#define SLEEP 100 

char map[ROWS][COLS+1];


void setScreenSize();
void hidecursor();
void fillMap();
void printMap();
void setcur();

int f(int x);


int main()
{
	srand(time(NULL));
	setScreenSize();
	hidecursor();
	fillMap(); 
	int y, x, params;
	int isexit=0;
	for(x=0; x<COLS/2&&isexit!=1; x++)
	{
		setcur(); 
		printMap();
		for(params = -x; params<x*3; params+=(x+x) )
		{
			y = f(params);
			if(y>ROWS/2 || y<-ROWS/2)
			{
				isexit=1;
				printf(" Complete\n");
				break;
			}
			map[ROWS - y - ROWS/2][params + COLS/2] = '0';
		}
		Sleep(SLEEP);
	}
	return 0;
}

int f(int x)
{
	return (x*x*x*0.4)/100;
}


void fillMap()
{
	for(int row=0; row<ROWS; row++)
	{
		for(int col=0; col<COLS; col++)
		{
			if(col==0||col==COLS-1||row==0||row==ROWS-1)
				map[row][col] = '#';
			else if(row==ROWS/2)
				map[row][col] = '-';
			else if(col==COLS/2)
				map[row][col] = '|';
			else
				map[row][col] = ' ';
		}
		map[row][COLS] = '\0';
	}
}


void printMap()
{
	for(int row=0; row < ROWS; row++)
		printf(" %s\n", map[row]);
}


void setcur()
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , coord);
}


void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}


void setScreenSize()
{
	COORD crd = {COLS+2, ROWS+10};
	SMALL_RECT src = {0, 0, crd.X, crd.Y};
	SetConsoleScreenBufferSize (GetStdHandle (STD_OUTPUT_HANDLE), crd);
	SetConsoleWindowInfo (GetStdHandle (STD_OUTPUT_HANDLE), TRUE, &src);
}
