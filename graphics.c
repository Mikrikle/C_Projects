#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <strings.h>
#include <math.h>


// размер экрана
#define COLS 100 
#define ROWS 40 
// задержка при рисовании графика
#define SLEEP 50
// количество графиков в програме
#define FUNCTIONSNUM 3
// символ которым будет рисоваться график
#define GRAPHFILL '0' 
// символ пересечения грфиков
#define INTERSECTION '8'

char map[ROWS][COLS+1];

void setScreenSize();
void hidecursor();
void fillMap();
void printMap();
void setcur();

// укажите функции графиков в
int f(int x, int fnum);


int main()
{
	setScreenSize();
	hidecursor();
	fillMap(); 
	int y, x, params, num;
	for(x=0; x<COLS/2; x++)
	{
		setcur(); 
		printMap();
		// одновременное рисование всех функций программы
		for(num = 1; num <= FUNCTIONSNUM; num++)
		{
			// необходим для рисования графика сразу в обе стороны от OY
			// возможно создание своего условия
			params = -x;
			do
			{
				y = f(params, num);
				// график не будет рисоваться за пределами поля
				if(y<ROWS/2 && y>-ROWS/2)
				{
					if(map[ROWS - y - ROWS/2][params + COLS/2] == GRAPHFILL)
						map[ROWS - y - ROWS/2][params + COLS/2] = INTERSECTION; // пересечения
					else
						map[ROWS - y - ROWS/2][params + COLS/2] = GRAPHFILL;
				}
				// params становится равен x
				params+=(x+x);
			}
			while(params<x*3);
		}
		Sleep(SLEEP);
	}
	printf("    Complete\n Press Enter to continue\n");
	getch();
	return 0;
}


int f(int x, int fnum)
{
	// количество блоков case должно совпадать с FUNCTIONSNUM
	switch(fnum)
	{
		case 1:
		{
			return sin(x)*2;
		}
		case 2:
		{
			return x*x/10;
		}
		case 3:
		{
			return -x/3;
		}
		default:
		{
			return 1;
		}
	}
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
