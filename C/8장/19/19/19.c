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

	printf("첫번째 문자열 입력:");
	gets(str1);
	printf("두번째 문자열 입력:");
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
		printf("%s 와(과) %s 는(은) 같습니다.", s1, s2);
	else
		printf("%s 와(과) %s 는(은) 다릅니다.", s1, s2);

	return 0;
}
