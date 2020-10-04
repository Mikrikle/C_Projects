#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int FindDoor(int *ptr, int door);
void PrintDoor(int host_door, int player_door);

int main()
{
	srand(time(NULL));
	// |   1-'Выбрана игроком'  |  2-'Призовая'
    // |   3-'Выбрана ведущим'  |  4-'Призовая и выбрана игроком'
	int doors[3] = {0,0,0};
	int *doors_ptr = doors;
	int player_door;
	int prize_door;
	int hosts_door;
	int is_change_door;
	int looses = 0;
	int wins = 0;
	
	printf("0 - exit\n");
	while(1)
	{
		PrintDoor(0, 0);
		printf("Select door (1, 2, 3): "); scanf("%d", &player_door);
		if(!player_door){break;}  // Выход
		doors[player_door-1] = 1;
		
		// делаем случайную дверь призовой
		prize_door = rand()%3;
		if(doors[prize_door]!=1)
			{doors[prize_door] = 2;}
		else
			{doors[prize_door] = 4;}
		// дверь ведущего (пустая дверь)
		while(1)
		{
			hosts_door = rand()%3;
			if(doors[hosts_door]==0)
			{
				doors[hosts_door] = 3;
				break;
			}
		}
		printf("\nThe host opened the door №%d\n", (hosts_door+1));
		PrintDoor(hosts_door+1, player_door);
		
		printf("Change door? (1 - Yes, 0 - No): "); scanf("%d", &is_change_door);
		if(is_change_door) // игрок согласился поменять дверь
		{
			if(FindDoor(doors_ptr, 4))
			{
				printf("You Loose\n");
				looses++;
			}
			else
			{
				printf("You Win\n");
				wins++;
			}
		} 
		else // игрок отказался менять дверь
		{
			if(!FindDoor(doors_ptr, 4))
			{
				printf("You Loose\n");
				looses++;
			}
			else
			{
				printf("You Win\n");
				wins++;
			}
		}
		printf("-----\n|Wins: %2d   |\n|Looses: %2d |\n\n\n", wins, looses);
		doors[0] = 0; doors[1] = 0; doors[2] = 0;
	}
	return 0;
}


int FindDoor(int *ptr, int door)
{
	for(int i=0; i<3; i++)
	{
		if(*ptr==door)
			{return 1;}
		ptr++;
	}
	return 0;
}


void PrintDoor(int host_door, int player_door)
{
	
	void YourDoor(int doors_num, int player_num)
	{
		if(doors_num == player_num)
			printf("--Your-   ");
		else
			printf("-------   ");
	}

	
	if(host_door == 0)
	{
		printf("-------   -------   -------\n");
		printf("|  #  |   | ### |   | ### |\n");
		printf("| ##  |   | #  #|   |    #|\n");
		printf("|  #  |   |   # |   |  ## |\n");
		printf("|  #  |   |  #  |   |   # |\n");
		printf("| ### |   | ####|   | ### |\n");
		printf("-------   -------   -------\n");
	}
	else if(host_door == 1)
	{
		printf("-         "); YourDoor(2, player_door); YourDoor(3, player_door);
		printf("\n||        | ### |   | ### |\n");
		printf("||        | #  #|   |    #|\n");
		printf("||        |   # |   |  ## |\n");
		printf("||        |  #  |   |   # |\n");
		printf("||        | ####|   | ### |\n");
		printf("-         -------   -------\n");
	}
	else if(host_door == 2)
	{
		YourDoor(1, player_door);  printf("-         "); YourDoor(3, player_door);
		printf("\n|  #  |   ||        | ### |\n");
		printf("| ##  |   ||        |    #|\n");
		printf("|  #  |   ||        |  ## |\n");
		printf("|  #  |   ||        |   # |\n");
		printf("| ### |   ||        | ### |\n");
		printf("-------   -         -------\n");
	}
	else if(host_door == 3)
	{
		YourDoor(1, player_door); YourDoor(2, player_door); printf("-      ");
		printf("\n|  #  |   | ### |   ||     \n");
		printf("| ##  |   | #  #|   ||     \n");
		printf("|  #  |   |   # |   ||     \n");
		printf("|  #  |   |  #  |   ||     \n");
		printf("| ### |   | ####|   ||     \n");
		printf("-------   -------   -      \n");
	}
}
