#include <stdio.h>
#include <string.h>
#define MAXLEN 256

int main()
{
	char user_str[MAXLEN];
	char inverse_str[MAXLEN];
	int char_counter;
	printf("\t__FLIPPING_A_LINE__\n\n");
	printf("0 = Exit\n-------\n");
	while(1)
	{
		char_counter=0;
		printf(":  ");
		fgets(user_str, MAXLEN, stdin);
		
		// выход
		if(user_str[0]=='0'){break;}
		
		// подсчет количества букв
		for(int i=0; i<MAXLEN; i++)
		{
			if(user_str[i]=='\0'){break;}
			char_counter++;	
		}
		
		// создане инвертированного массива
		for(int i=MAXLEN-1, j=0; i>=0; i--, j++)
		{
			inverse_str[i] = user_str[j];
		}
		
		// вывод
		printf("-> ");
		for(int i=char_counter-1; i>0; i--)
		{
			printf("%c", inverse_str[MAXLEN-i]);
		}
		printf("\n\n");	
	}
	return 0;
}
