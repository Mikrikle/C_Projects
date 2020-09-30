#include <stdio.h>

int main(int argc, char **argv)
{
	int min;
	int static_min;
	int max;
	int static_max;
	int middle;
	int attempt_counter;
	char input;
	
	start_game:
	printf(" Enter the limit at which the number will be guessed:\n");
	printf("  from: ");
	scanf("%d%*c", &min);
	printf("  to: ");
	scanf("%d%*c", &max);
	if(min>=max)
	{
		printf("invalid input!\n\n");
		goto start_game;
	}
	static_max = max; static_min = min;
	middle = (min+max)/2;
	attempt_counter = 0;
	
	
	printf(" guess the number in (%d:%d)\n", min, max);
	printf("   '='   Yes this is my number\n");
	printf("   '>'   My number is bigger\n");
	printf("   '<'   My number is smaller\n");
	printf("   '?'   Change limits\n");
	printf("   '0'   Exit\n\n");
	printf("\n Start\n");
	
	while(1)
	{
		printf("% d ? : ", middle);
		scanf("%c%*c", &input);
		if(input=='=')
		{
			printf("! your number %d was guessed in %d attempts !\n", middle, attempt_counter);
			printf("\n Start\n");
			min = static_min;
			max = static_max;
			middle = (min+max)/2;
			attempt_counter = 0;
		}
		else if(input=='>')
		{
			min = middle;
			middle = (max+min)/2;
			attempt_counter++;
		}
		else if(input=='<')
		{
			max = middle;
			middle = (max+min)/2;
			attempt_counter++;
		}
		else if(input=='?')
		{
			printf("\n\n");
			goto start_game;
		}
		else if(input=='0')
		{
			printf("Press Enter to exit\n");
			getchar();
			break;
		}	
		else
		{
			printf("! Unidentified action !\n");
		}
	}
	
	return 0;
}

