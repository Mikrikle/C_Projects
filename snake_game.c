#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define COLS 60
#define ROWS 30

char window[ROWS][COLS+1];
int food[2] = {ROWS/2-ROWS/4, COLS/2 };
int SLEEP = 100;
int GAME = 1;
int score = 0;

typedef struct
{
	int x;
	int y;
} Segment;


typedef struct
{
	int len;
	Segment segments[100];
} Snake;

Snake snake = {4, {{COLS/2, ROWS/2-3}, {COLS/2, ROWS/2-2}, {COLS/2, ROWS/2-1}, {COLS/2, ROWS/2}}};

void setScreenSize();
void hidecursor();
void fillWindow();
void printWindow();
void setcur();
void putSnake();
void moveSnake(int dx, int dy);


int main()
{
	srand(time(NULL));
	setScreenSize();
	hidecursor();
	fillWindow();
	int direction[2] = {0, -1};
	do
	{
		Sleep(SLEEP/4);
		setcur();
		Sleep(SLEEP/4);
		fillWindow();
		for(int i=0; i<snake.len; i++)
		{
			window[snake.segments[i].y][snake.segments[i].x] = '@';
		}
		
		printWindow();
		printf("\tScore: s%d\n", score);
		Sleep(SLEEP/4);
		if(GAME)
		{
			moveSnake(direction[0], direction[1]);
				
			if(GetKeyState('A') < 0 && direction[0] != 1)
			{
				direction[0] = -1; direction[1] = 0;
			}
			else if(GetKeyState('D') < 0 && direction[0] != -1)
			{
				direction[0] = 1; direction[1] = 0;
			}
			else if(GetKeyState('W') < 0 && direction[1] != 1)
			{
				direction[0] = 0; direction[1] = -1;
			}
			else if(GetKeyState('S') < 0 && direction[1] != -1)
			{
				direction[0] = 0; direction[1] = 1;
			}
		}
		Sleep(SLEEP/4);
	}
	while(GetKeyState(VK_ESCAPE) >= 0);
}


void moveSnake(int dx, int dy)
{
	int old_x = snake.segments[0].x;
	int old_y = snake.segments[0].y;
	snake.segments[0].x += dx;
	snake.segments[0].y += dy;
	
	if(window[snake.segments[0].y][snake.segments[0].x] == '@'
		|| window[snake.segments[0].y][snake.segments[0].x] == '#')
	{
		printf("\t\nYou loose\n");
		GAME = 0;
	}
	else
	{
		int current_x;
		int current_y;

		for(int i=1; i<snake.len; i++)
		{
			current_x = snake.segments[i].x;
			current_y = snake.segments[i].y;
			snake.segments[i].x = old_x;
			snake.segments[i].y = old_y;
			old_x = current_x;
			old_y = current_y;
		}
		if(window[snake.segments[0].y][snake.segments[0].x] == '*')
		{
			window[snake.segments[0].y][snake.segments[0].x] = ' ';
			score++;
			Segment s;
			s.x = old_x; s.y = old_y;
			snake.segments[snake.len] = s;
			snake.len+=1;
			int randpos_row, randpos_col;
			while(1)
			{
				randpos_row = 3 + rand()%(ROWS-6);
				randpos_col = 3 + rand()%(COLS-6);
				if(window[randpos_row][randpos_col] == ' ')
					break;
			}
			food[0] = randpos_row;
			food[1] = randpos_col;
		}
	}

}


void fillWindow()
{
	for(int row=0; row<ROWS; row++)
	{
		for(int col=0; col<COLS; col++)
		{
			if(col==0||col==COLS-1||row==0||row==ROWS-1)
				window[row][col] = '#';
			else
				window[row][col] = ' ';
		}
		window[row][COLS] = '\0';
	}
	window[food[0]][food[1]] = '*';
}


void printWindow()
{
	for(int row=0; row < ROWS; row++)
		printf(" %s\n", window[row]);
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
	COORD crd = {COLS+2, ROWS+1};
	SMALL_RECT src = {0, 0, crd.X, crd.Y};
	SetConsoleScreenBufferSize (GetStdHandle (STD_OUTPUT_HANDLE), crd);
	SetConsoleWindowInfo (GetStdHandle (STD_OUTPUT_HANDLE), TRUE, &src);
}
