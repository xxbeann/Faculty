#include <stdio.h>
#include <string.h>

int main(void)
{
	int i, count;
	char insert[1000];
	printf("���ڿ� �Է�:");
	gets(insert);
	count = strlen(insert);
	for (i = count; i >= 0; i--)
	{
		printf("%c", insert[i]);
	}
	system("PAUSE");
	return 0;
}