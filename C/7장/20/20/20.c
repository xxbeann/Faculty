#include <stdio.h>
#include <string.h>

char* strcapitalize(char *str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (flag == 0)
		{
			str[i] -= 32;
			flag = 1;
		}
		if (str[i] == 32)
		{
			flag = 0;
		}
		i++;
	}
	return (str);
}

int main(void)
{
	char str[1000];
	printf("문자열을 입력하세요:");
	gets(str);
	strcapitalize(str);
	printf(str);
	system("PAUSE");
	return 0;
}