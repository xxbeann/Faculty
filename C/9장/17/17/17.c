#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct line {
	int x, y;
}line1, line2, line3, line4;

void PrintLine(struct line l, struct line p);

int main(void)
{
	int a, b;
	struct line line1 = { 10,20 };
	struct line line2 = { 50,60 };
	printf("���� �� ���� ���� : ");
	PrintLine(line1, line2);

	printf("x������ �̵��� �Ÿ��� �Է��ϼ��� : ");
	scanf("%d", &a);
	printf("y������ �̵��� �Ÿ��� �Է��ϼ��� : ");
	scanf("%d", &b);

	line3.x = line1.x + a;
	line3.y = line1.y + b;
	line4.x = line2.x + a;
	line4.y = line2.y + b;

	printf("���� �� ���� ���� : ");
	PrintLine(line3, line4);
	return 0;
}

void PrintLine(struct line l, struct line p)
{
	printf("������ = (%d, %d), ���� = (%d, %d)\n", l.x, l.y, p.x, p.y);
}