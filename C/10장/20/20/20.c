#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int Compare(char* s1, char* s2);

int main(void)
{
	char s1[20];
	char s2[20];
	printf("ù��° ���ڸ� �Է��ϼ���: ");
	gets(s1);
	printf("�ι�° ���ڸ� �Է��ϼ���: ");
	gets(s2);
	Compare(s1, s2);

	return 0;
}

int Compare(char* s1, char* s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 > *s2)
			return 1;
		else if (*s1 < *s2)
			return -1;
		else {
			s1++;
			s2++;
		}
	}
	return 0;
}