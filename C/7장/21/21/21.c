#include <stdio.h>
#include <string.h>

void check(char* arr);

int main(void)
{
	char s1[100];
	printf("문자열을 입력하세요:");
	gets(s1);
	check(s1);
	system("PAUSE");
	return 0;

}

void check(char* s1)
{
	int i;
	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != ' ')
		{
			printf("%c", s1[i]);
		}
	}
}
