#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>


#define COLS 60
#define ROWS 20


typedef struct
{
	int x,y;
	int width;
} TRacet;
TRacet racet;

typedef struct
{
	float x,y;
	int rx, ry;
	float alpha;
	float speed;
} TBall;
TBall ball;

int Hit_Counter = 0;
int Max_hit = 0;

void hidecursor();
void fillMap(char *ptr);
void printMap(char *ptr);
void initRacet();
void initBall();
void putRacet(char *ptr);
void putBall(char *ptr);
void moveRacet(int x);
void moveBall(float x, float y);
void autoMoveBall(char *ptr);



void setcur();

int main()
{
	long int ttime, fixtime, fps_counter; // FPS
	char map[COLS][ROWS];
	char *map_ptr = map[0];
	int run=0;
	initRacet();
	initBall();
	hidecursor();
	
	fixtime = time(NULL);
	do
	{
		ttime = time(NULL);
		fps_counter++;
		setcur();
		fillMap(map_ptr);
		putRacet(map_ptr);
		putBall(map_ptr);
		printMap(map_ptr);
		// Move Racet
		if(GetKeyState('A') < 0)
			moveRacet(racet.x - 1);
		if(GetKeyState('D') < 0)
			moveRacet(racet.x + 1);
		if(Hit_Counter == 3)
			racet.width=7;
		if(Hit_Counter == 10)
			racet.width=5;
		if(Hit_Counter == 15)
			racet.width=3;
		// Move ball
		if(GetKeyState('W') < 0)
			run = 1;
		if(ball.ry > ROWS-1)
		{
			run = 0;
			if(Hit_Counter > Max_hit)
				Max_hit = Hit_Counter;
			Hit_Counter = 0;
			ball.speed = 0.8;
		}	
		if(run)
			autoMoveBall(map_ptr);
		else
			moveBall(racet.x + racet.width/2, racet.y-2);
		printf("\n\nScore: %d   Speed:%.2f\nTop Score: %d\n", Hit_Counter, ball.speed, Max_hit);
		// Print FPS
		if(ttime == fixtime+1)
		{
			printf("FPS: %ld\n", fps_counter);
			fixtime = time(NULL);
			fps_counter = 0;
		}
		
	}
	while(GetKeyState(VK_ESCAPE) >= 0);
	
	return 0;
}


void initRacet()
{
	racet.width = 9;
	racet.x = (COLS - racet.width)/2;
	racet.y = ROWS;
}


void initBall()
{
	ball.x = 2.0;
	ball.y = 2.0;
	ball.rx = (int)round(ball.x);
	ball.ry = (int)round(ball.y);
	ball.alpha = -1;
	ball.speed = 0.8;
}

void putRacet(char *ptr)
{
	ptr+=(COLS*(ROWS-1));
	ptr+=racet.x;
	for(int i=0; i<racet.width; i++ )
	{
		*ptr = '@';
		ptr++;
	}
}


void putBall(char *ptr)
{
	ptr+=(COLS*ball.ry);
	ptr+=ball.rx;
	*ptr = '*';
}


void moveRacet(int x)
{
	int old_x = racet.x;
	racet.x = x;
	if((racet.x < 1)||(racet.x > (COLS-1-racet.width)))
	{
		racet.x = old_x;
	}
}


void moveBall(float x, float y)
{
	ball.x = x;
	ball.y = y;
	ball.rx = (int)round(x);
	ball.ry = (int)round(y);
}


void autoMoveBall(char *ptr)
{
	if(ball.alpha < 0) 
		ball.alpha += M_PI * 2;
	if(ball.alpha > M_PI * 2)
		ball.alpha -= M_PI * 2;
		
	TBall oldball = ball;
	moveBall(ball.x + cos(ball.alpha)*ball.speed,
			ball.y + sin(ball.alpha)*ball.speed);
			
	if( *(ptr+(COLS*ball.ry) + ball.rx)=='#' || *(ptr+(COLS*ball.ry) + ball.rx)=='@')
	{
		if (*(ptr+(COLS*ball.ry) + ball.rx)=='@')
		{
			Hit_Counter++;
			oldball.speed += 0.02;
		}
			
		if((ball.rx!=oldball.rx)&&(ball.ry!=oldball.ry))
		{
			if(*(ptr+(COLS*oldball.ry) + ball.rx) == *(ptr+(COLS*ball.ry) + oldball.rx))
			{
				oldball.alpha = oldball.alpha + M_PI;
			}
			else
			{
				if(*(ptr+(COLS*oldball.ry) + ball.rx) == '#')
				{
					oldball.alpha = (2 * M_PI - oldball.alpha) + M_PI;
				}
				else
				{
					oldball.alpha = (2 * M_PI - oldball.alpha);
				}
					
			}
		}
		else if(ball.ry == oldball.ry)
		{
			oldball.alpha = (2 * M_PI - oldball.alpha) + M_PI;
		}
		else
		{
			oldball.alpha = (2 * M_PI - oldball.alpha);
		}
		ball = oldball;
		autoMoveBall(ptr);
	}
}


void fillMap(char *ptr)
{
	for(int i=0; i<ROWS; i++)
	{
		for(int j=0; j<COLS; j++)
		{
			if(j==0||j==COLS-1||i==0)
				*ptr = '#';
			else
				*ptr = ' ';
			ptr++;
		}
	}
}


void printMap(char *ptr)
{
	for(int i=0; i<ROWS; i++)
	{
		for(int j=0; j<COLS; j++)
		{
			printf("%c", *ptr);
			ptr++;
		}
		printf("\n");
	}
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
