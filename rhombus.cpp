#include <iostream>
using namespace std;


void create_horizontal_line(int size)
{
	cout << ' ';
	for (int i = 0; i < size + 6; i++)
		cout << '-';
	cout << endl;
}


void create_main_line(int i, int size)
{
	int j;
	cout << " |";
	for (j = 0; j < (size - i / 2 - size / 2) + 1; j++)
		cout << ' ';
	for (j = 0; j < i; j++)
		cout << '*';
	for (j = 0; j < (size - i / 2 - size / 2) + 1; j++)
		cout << ' ';
	cout << '|' << endl;
}


int main()
{	
	int size;
	short color;
	while (true)
	{
		// rhombus size
		cout << "number from 3 to 100 (0 to exit)" << endl;
		cout << " Enter SIZE: ";
		cin >> size;
		cout << size << endl;
		if (size == 0)
			break;
		else if ((size < 0) || (size >= 1000))
		{
			cout << "! Enter correct size !" << endl;
			continue;
		}
		if (size % 2 == 0)
			size++;

		// rhombus color
		cout << "(1-Red, 2-Green, 3-Yellow, 4-Blue, 5-Magenta, 6-Cyan)" << endl;
		cout << " Select color: ";
		cin >> color;
		if (color < 1 || color > 6)
			color = 7;

		// draw
		cout << "\x1b[3" << color << 'm'; // set color
		create_horizontal_line(size);
		for (int i = 1; i <= size; i += 2)
		{
			create_main_line(i, size);
		}
		create_main_line(size+2, size);
		for (int i = size; i > 0; i -= 2)
		{
			create_main_line(i, size);
		}
		create_horizontal_line(size);
		cout << "\x1b[0m"; // set color to default
	}

	system("pause");
}
