#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str1[20];
	char str2[20];
	char s1[20];
	char s2[20];

	char* p1 = str1;
	char* p2 = str2;

	printf("ù��° ���ڿ� �Է�:");
	gets(str1);
	printf("�ι�° ���ڿ� �Է�:");
	gets(str2);

	strcpy(s1, str1);
	strcpy(s2, str2);

	int len = strlen(str1);

	for (int i = 0; i < len; i++)
	{
		if (p1[i] >= 'A' && p1[i] <= 'Z')
			p1[i] += 32;
		if (p2[i] >= 'A' && p2[i] <= 'Z')
			p2[i] += 32;
	}

	printf("%s, %s, %d", p1, p2, len);
	printf("\n");

	if (strcmp(str1, str2) == 0)
		printf("%s ��(��) %s ��(��) �����ϴ�.", s1, s2);
	else
		printf("%s ��(��) %s ��(��) �ٸ��ϴ�.", s1, s2);

	return 0;
}
