#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

void upper(char *ptr);


int main()
{
	printf("Welcome to upper programme\n");
	printf("Max str length = %d\n", MAX_SIZE);
	printf("Enter \"0\" for exit\n");
	printf("---------------------\n\n");
	
	char str[MAX_SIZE];
	char *pointer = str;
	
	while(1)
	{
		gets(str);
		if(strcmp(str, "0") == 0)
			break;
		upper(pointer);
		printf("%s\n\n", pointer);
	}
	return 0;
}


void upper(char *ptr)
{
	for(int i=0; i < MAX_SIZE; i++)
	{
		if(*ptr=='\0')
			break;
		else if((*ptr >= 'a')&&(*ptr <= 'z'))
			*ptr-=32;
		ptr++;
	}
}
