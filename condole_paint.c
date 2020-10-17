#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


#define COLS 100 //down menu will be hidden when COLS < 90
#define ROWS 40
#define BORDER '#'
#define CANVAS ' '

typedef struct
{
	int x;
	int y;
} XY;

typedef struct
{
	XY pos;
	XY size;
}Brush;


char window[ROWS][COLS+1];
Brush brush = {{COLS/2, ROWS/2}, {3,3}};
char pattern = '@';
int SLEEP = 30;

void setScreenSize();
void hidecursor();
void fillWindow();
void printWindow();
void setcur();
void putBrush();
void moveBush(int dx, int dy, int draw);
void drawBrush(int draw);
void drawInfo();



int main()
{
	setScreenSize();
	hidecursor();
	fillWindow();
	int draw=0;
	char current_chars[COLS * ROWS];
	do
	{
		

		setcur();
		for(int i=0; i<brush.size.y; i++)
		{
			for(int j=0; j<brush.size.x; j++)
			{
				current_chars[i*ROWS + j] = window[brush.pos.y+i][brush.pos.x+j];
				window[brush.pos.y+i][brush.pos.x+j] = pattern;
			}
		}
		printWindow();
		if(!draw)
		{
			for(int i=0; i<brush.size.y; i++)
			{
				for(int j=0; j<brush.size.x; j++)
				{
					window[brush.pos.y + i][brush.pos.x + j] = current_chars[i*ROWS + j];
				}
			}
		}
		if(GetKeyState(VK_SPACE) < 0)
			draw = 1;
		else
			draw = 0;
			
		if(GetKeyState('A') < 0 )
			moveBush(-1, 0, draw);
		if(GetKeyState('D') < 0)
			moveBush(1, 0, draw);
		if(GetKeyState('W') < 0)
			moveBush(0, -1, draw);
		if(GetKeyState('S') < 0)
			moveBush(0, 1, draw);
			
		if(GetKeyState('1') < 0)
			pattern = '@';
		if(GetKeyState('2') < 0)
			pattern = '#';
		if(GetKeyState('3') < 0)
			pattern = '*';
		if(GetKeyState('4') < 0)
			pattern = '0';
		if(GetKeyState('5') < 0)
			pattern = '+';
		if(GetKeyState('0') < 0)
			pattern = CANVAS;
			
		if(GetKeyState('C') < 0)
			fillWindow();
		
		if(GetKeyState('E') < 0)
		{
			if(brush.size.x < COLS-3&&brush.size.y < ROWS-3
			   &&brush.pos.x+brush.size.x < COLS-1
			   &&brush.pos.y+brush.size.y < ROWS-1)
			{
			brush.size.x++;
			brush.size.y++;
			}
		}
		if(GetKeyState('Q') < 0)
		{
			if(brush.size.x > 1&&brush.size.y > 1)
			{
				brush.size.x--;
				brush.size.y--;
			}
		}
		if(GetKeyState('T') < 0)
		{
			if(SLEEP < 100)
				SLEEP += 5;
		}
		if(GetKeyState('Y') < 0)
		{
			if(SLEEP >= 5)
				SLEEP -= 5;
		}
		drawInfo();
		Sleep(SLEEP);
	}
	while(GetKeyState(VK_ESCAPE) >= 0);
}

void fillWindow()
{
	for(int row=0; row<ROWS; row++)
	{
		for(int col=0; col<COLS; col++)
		{
			if(col==0||col==COLS-1||row==0||row==ROWS-1)
				window[row][col] = BORDER;
			else
				window[row][col] = CANVAS;
		}
		window[row][COLS] = '\0';
	}
}

void moveBush(int dx, int dy, int draw)
{
	int source_x=brush.pos.x, source_y=brush.pos.y;
	brush.pos.x += dx;
	brush.pos.y += dy;
	if(brush.pos.x<1||brush.pos.x>COLS-brush.size.x-1||brush.pos.y<1||brush.pos.y>ROWS-brush.size.y-1)
	{
		brush.pos.x = source_x;
		brush.pos.y = source_y;
	}
}


void printWindow()
{
	for(int row=0; row < ROWS; row++)
		printf(" %s\n", window[row]);
}


void drawInfo()
{
	#if COLS>=90
	char tabulation[(COLS-80)/2+2];
	for(int i=0; i<(COLS-80)/2+1; i++)
		tabulation[i] = ' ';
	tabulation[(COLS-80)/2+1]='\0';


	printf("\n%s________________M_E_N_U________________", tabulation);
	printf("  ________________I_N_F_O________________\n");
	printf("%s|Brush speed = %03d                       ", tabulation, (100-SLEEP));
	printf(" 'Y':Speed++  'T':Speed--             |\n");
	printf("%s|Brush size = %03dx%03d                    ", tabulation, brush.size.x, brush.size.y );
	printf(" 'E':Size++   'Q':Size--              |\n");
	printf("%s|                                         ", tabulation);
	printf("'C':Clean                            |\n"); 
	printf("%s|--------------------------------------  --------------------------------------|\n", tabulation);
	printf("%s|Brush char = '%c'                         ", tabulation, pattern );
	printf(" 1:'@'  2:'#'  3:'*'  4:'0'  5:'+'   |\n");
	printf("%s|                                         ", tabulation);
	printf(" 0:Eraser                            |\n");  
	printf("%s|                                         ", tabulation);
	printf(" hold down the 'Space' to draw       |\n");
	#endif
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
