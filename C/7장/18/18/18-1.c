#include <stdio.h>
#include <string.h>
#define SIZE 100

void str_upper(char* s)
{
	int i;
	int count = 0;
	for (i = 0; i < strlen(s); i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] - 'a' + 'A';

	}
}

int main(void)
{
	char str[SIZE];
	printf("���ڿ��� �Է��Ͻÿ�:");
	gets(str);
	str_upper(str);
	printf("%s", str);
	return 0;
}