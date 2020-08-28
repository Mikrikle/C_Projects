#include <iostream> 
#include <ctime>

using namespace std;


int randint(int b) // перегрузка для работы с 1 параметром
{
	if (b > 0)
	{
		return rand() % b; // диапазон [0; b)
	}
	else
	{
		return 0;
	}
}


int randint(int a, int b)
{
	if (b > a) 
	{
		return (rand() % (b - a)) + a; // диапазон [a; b)
	}
	else
	{
		return 0;
	}
	
}



int main()
{
	srand(time(NULL));

	for (int i = 0; i < 20; i++)
	{
		cout << "randint(1, 10) = " << randint(1, 10) << endl;
	}
	for (int i = 0; i < 20; i++)
	{
		cout << "randint(20) = " << randint(20) << endl;
	}

	return 0;
}