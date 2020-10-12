#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>


#define COLS 60
#define ROWS 20

char map[COLS][ROWS];
char boxes[COLS][ROWS];

typedef struct // Ракетка
{
	int x,y;
	int width;
} TRacet;
TRacet racet;

typedef struct  // Мячик
{
	float x,y;
	int rx, ry;
	float alpha;
	float speed;
} TBall;
TBall ball;

// Счетчкики очков и уровня
int Hit_Counter = 0;
int Max_hit = 0;
int level = 1;

void setScreenSize();
void hidecursor();
void fillMap();
void printMap();
void initRacet();
void initBall();
void putRacet();
void putBall();
void moveRacet(int x);
void moveBall(float x, float y);
void autoMoveBall();
void setcur();
void initBoxes();


int main()
{
	long int ttime, fixtime, fps_counter; // FPS
	int run=0; // Начата ли игра
	setScreenSize();
	initRacet();
	initBall();
	initBoxes();
	hidecursor();

	fixtime = time(NULL);
	do
	{
		ttime = time(NULL);
		fps_counter++;
		setcur(); // сдвигаем курсор в начало
		fillMap(); // обнуляем карту
		putRacet(); // рисуем ракетку
		putBall(); // рисуем мяч
		printMap(); // рисуем карту
		// изменения сложности
		switch(Hit_Counter)
		{
			case 0:
			{
				racet.width = 11;
				ball.speed = 0.8;
				break;
			}
			case 3:
			{
				racet.width = 9;
				ball.speed = 1;
				break;
			}
			case 5:
			{
				ball.speed = 1.2;
				level = 2;
				break;
			}
			case 10:
			{
				racet.width = 7;
				ball.speed = 1;
				break;
			}
		}
		// Управление ракеткой
		if(GetKeyState('A') < 0)
			moveRacet(racet.x - 1);
		if(GetKeyState('D') < 0)
			moveRacet(racet.x + 1);
		// Движение мячика
		if(GetKeyState('W') < 0)
			run = 1;
		if(ball.ry > ROWS-2) // Если мячик улетел вниз
		{
			run = 0;
			if(Hit_Counter > Max_hit)
				Max_hit = Hit_Counter;
			Hit_Counter = 0;
			ball.alpha = -1;
			racet.x = COLS/2;
			level = 1;
			initBoxes();
		}	
		if(run)
			autoMoveBall();
		else // движение мячика вместе с ракетуой
			moveBall(racet.x + racet.width/2, racet.y-2);
		// Вывод основной информации
		printf("\n\nLevel: %d\nScore: %d   Speed:%.3f\nTop Score: %d\n", level, Hit_Counter, ball.speed, Max_hit);
		// FPS
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

void putRacet()
{
	for(int i=racet.x; i<(racet.width+racet.x); i++ )
	{
		map[i][ROWS-1] = '@';
	}
}


void putBall()
{
	map[ball.rx][ball.ry] = '*';
}


void moveRacet(int x)
{
	int old_x = racet.x;
	racet.x = x;
	// не позволяет ракетке вылететь с поля
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


void autoMoveBall()
{
	// привод угла к виду от 0 до 180
	if(ball.alpha < 0) 
		ball.alpha += M_PI * 2;
	if(ball.alpha > M_PI * 2)
		ball.alpha -= M_PI * 2;
	// сохранение начальной позиции мячика
	TBall oldball = ball;
	moveBall(ball.x + cos(ball.alpha)*ball.speed,
			ball.y + sin(ball.alpha)*ball.speed);
	// удары о поверхности	
	if(map[ball.rx][ball.ry]=='#' || map[ball.rx][ball.ry]=='@'|| map[ball.rx][ball.ry]=='0')
	{
		if (map[ball.rx][ball.ry]=='0')
		{
			boxes[ball.rx][ball.ry] = ' ';
			Hit_Counter++;
		}
			
		if((ball.rx!=oldball.rx)&&(ball.ry!=oldball.ry))
		{
			if(map[oldball.rx][ball.ry] == map[ball.rx][oldball.ry])
			{
				oldball.alpha = oldball.alpha + M_PI;
			}
			else
			{
				if(map[ball.rx][oldball.ry] == '#')
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
		autoMoveBall();
	}
}


void initBoxes()
{
	for(int row=3; row < 5; row++)
	{
		for(int col=4; col<COLS-4; col++)
		{
			boxes[col][row] = (rand()%2==1)?'0':' ';
		}
	}
}


void fillMap()
{
	for(int row=0; row<ROWS; row++)
	{
		for(int col=0; col<COLS; col++)
		{
			if(col==0||col==COLS-1||row==0)
				map[col][row] = '#';
			else
				map[col][row] = ' ';
		}
	}
	
	for(int row=3; row < 5; row++)
	{
		for(int col=4; col<COLS-4; col++)
		{
			map[col][row] = boxes[col][row];
		}
	}
	if(level==2)
	{
		for(int i=COLS/4; i<COLS/4*3; i++)
		{
			map[i][ROWS/2] = '#';
		}
	}
}


void printMap()
{
	for(int row=0; row<ROWS; row++)
	{
		for(int col=0; col<COLS; col++)
		{
			printf("%c", map[col][row]);
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


void setScreenSize()
{
	COORD crd = {COLS, ROWS+10};
	SMALL_RECT src = {0, 0, crd.X, crd.Y};
	SetConsoleScreenBufferSize (GetStdHandle (STD_OUTPUT_HANDLE), crd);
	SetConsoleWindowInfo (GetStdHandle (STD_OUTPUT_HANDLE), TRUE, &src);
}

