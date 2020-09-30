#include <stdio.h>

void printarr(int *ptr);
char charplayer(int);
void nullfield(int *ptr);
int iswin(int *ptr);

int main()
{
	// игровое поле
	int field[3][3] = {
		{0,0,0},
		{0,0,0},
		{0,0,0},
	};
	int *pfield = field[0]; // указатель на игровое поле
	
	int win=0; // выйграл ли кто-то из игроков
	int xo; // координаты клетки 
	int player = 1; // O = 1; X = -1
	int Owins=0; int Xwins=0; // победы игроков
	printf("START GAME\nEnter '0' to Exit\n\n");
	printf("[11] [12] [13]\n[21] [22] [23]\n[31] [32] [33]\nfor exmaple: 13 22 21\n\n");
	while(1)
	{
		printf("player: %c \n", charplayer(player)); // ход текущего игрока
		printf("[row][column]: "); scanf("%d", &xo);
		if(!xo){break;} // при вводе 0 - выход
		if(xo<11||xo>33)
		{
			printf("! non-existent cell !\n");
			continue;
		}
		
		// проверка на занятость клетки
		if(field[(xo/10)-1][(xo%10)-1] == 0)
		{
			
			field[(xo/10)-1][(xo%10)-1] = player;
			(player==1)?(player = -1):(player = 1); // смена игрока
			printarr(pfield);
			win = iswin(pfield);
			if(win)
			{
				nullfield(pfield);
				if(win==1){Xwins++;}
				if(win==-1){Owins++;}
				printf("statistic:\nX: %d wins\nY: %d wins\n", Xwins, Owins);
				printf("New game\n\n");
			}
		}
		else
			printf("! this cell is occupied! Try again !\n");
	}
	return 0;
}

char charplayer(int player)
{	// возвращает символ игрока X или O
	char s;
	s = player==0?'-':player==-1?'O':'X';
	return s;
}


void nullfield(int *arr)
{	// сброс игрового поля
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			*arr = 0;
			arr++;
		}
	}
}

int iswin(int *arr)
{ 	// победил ли один из игроков
	int ff[9];
	
	// создание плоского поля из 2xмерного
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			ff[i*3+j] = *arr;
			arr++;
		}
	}
	
	// проверки на победу
	
	for(int i=0; i<6; i+=3)
	{
		// проверка победы по строкам
		if((ff[0+i]==ff[1+i]&&ff[0+i]==ff[2+i])&&ff[0+i]!=0)
		{
			printf("\nplayer %c is WIN (by %d row)\n", charplayer(ff[0+i]), ((i/2)+1));
			return ff[0+i];
		}
	}
	for(int i=0; i<3; i++)
	{
		// проверка победы по столбцам
		if((ff[0+i]==ff[3+i]&&ff[0+i]==ff[6+i])&&ff[0+i]!=0)
		{
			printf("\nplayer %c is WIN (by %d column)\n", charplayer(ff[0+i]), (i+1));
			return ff[0+i];
		}
	}
	// проверка диагоналей
	if((ff[0]==ff[4]&&ff[0]==ff[8])&&ff[0]!=0)
	{
		printf("\nplayer %c is WIN (by \\ column)\n", charplayer(ff[0]));
		return ff[0];
	}
	if((ff[2]==ff[4]&&ff[2]==ff[6])&&ff[2]!=0)
	{
		printf("\nplayer %c is WIN (by / column)\n", charplayer(ff[0]));
		return ff[2];
	}
	// проверка заполнения поля
	int isFieldFull = 1;
	for(int i=0; i<9; i++)
	{
		if(ff[i] == 0){ isFieldFull = 0;}
	}
	if(isFieldFull)
	{
		printf("\nNobody wins\n");
		return 2;
	}


	return 0;
}


void printarr(int *arr)
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			printf("%c ", charplayer(*arr));
			arr++;
		}
		printf("\n");
	}
}
