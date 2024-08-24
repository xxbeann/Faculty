#include <stdio.h>
#include <string.h>

void rm_space()
{
	char str[1000];
	printf("문자열을 입력하세요:");
	gets(str);
	int i;
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] != ' ')
			printf("%c", str[i]);

	}
}

int main(void)
{
	rm_space();
	system("PAUSE");
	return 0;
}