#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4


void randomizearr(int *ptr);

int main()
{
	#if SIZE <= 9
	srand(time(NULL));
	int num[SIZE]={0};
	int *ptr = num;
	randomizearr(ptr);
	
	int input, retry;
	int x;
	int cows=0, bulls=0, attempts = 0;

	printf("\t\tRule\n");
	printf("'cow'- you guessed the number, but not its position\n");
	printf("'bull' - you guessed both the number and position\n\n");
	printf(" (enter %d-digit number)\n", SIZE);
	
	while(1)
	{
		printf(": "); scanf("%d", &input);
		attempts++;
		for(int i=SIZE-1; i>=0; i--)
		{
			x = input%10;
			for(int j=0; j<SIZE; j++)
			{
				if(i==j && x==num[j])
				{
					bulls++;
				}
				else if(x==num[j])
				{
					cows++;
				}
			}
			input/=10;
		}
		if(bulls!=SIZE)
		{
			printf("Cows: %d\nBulls: %d\n\n", cows, bulls);
		}
		else
		{
			printf("You Win! {attemps: %d}\n", attempts);
			printf("1-new game   0-exit\n"); scanf("%d", &retry);
			if(retry)
			{
				printf("\nStart\n");
				attempts=0;
				randomizearr(ptr);
			}
			else
			{
				system("pause");
				break;
			}
		}
		cows=0; bulls=0;
	}
	#else
	printf("!!! SIZE must be < 10 !!!\n");
	#endif
	return 0;
}

void randomizearr(int *ptr)
{
	int rnum, isin;
	for(int i=0; i<SIZE;)
	{
		isin = 0;
		rnum = 1 + rand()%9;
		for(int j=0; j<SIZE; j++)
		{
			if(*ptr == rnum)
			{
				isin = 1;
			}
			ptr++;
		}
		ptr-=SIZE;
		if(!isin)
		{
			*(ptr+i) = rnum;
			i++;
		}
	}
}
