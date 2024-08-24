#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[100];
	printf("문자열을 입력하세요:");
	gets(str);
	int num = strlen(str);
	int i;
	for (i = 0; i <= num; i++)
	{
		if ((int)str[i] >= 97 && (int)str[i] <= 122)
		{
			printf("%c", (int)str[i], (int)str[i] - 32);
		}
	}

}