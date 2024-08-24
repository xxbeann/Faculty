#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

char a;

bool IsLower(char a)
{

	return (int)a >= 97 && (int)a <= 122;


}
bool IsUpper(char a)
{
	return (int)a >= 65 && (int)a <= 90;

}

bool IsAlphabetic(char a)
{
	return IsLower(a) || IsUpper(a);
}

int main(void)
{
	printf("문자를 입력하세요.\n");
	scanf("%c", &a);

	printf("%d\n", IsLower(a));
	printf("%d\n", IsUpper(a));
	printf("%d\n", IsAlphabetic(a));

	system("PAUSE");
	return 0;

}