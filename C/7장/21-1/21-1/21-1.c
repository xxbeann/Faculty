#include <stdio.h>
#include <string.h>

void rm_space()
{
	char str[1000];
	printf("���ڿ��� �Է��ϼ���:");
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