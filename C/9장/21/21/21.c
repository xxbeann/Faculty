#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct rect {
	int left, top, right, bottom;
}p1;

struct point {
	int x, y;
}r1;

int main(void)
{
	printf("�»����/���ϴ����� ��ǥ�� �Է��ϼ���(left, top, right, bottom ��)\n");
	scanf("%d %d %d %d", &p1.left, &p1.top, &p1.right, &p1.bottom);
	printf("�Էµ� ���簢��: �»���� = (%d, %d), ���ϴ��� = (%d, %d)\n", p1.left, p1.top, p1.right, p1.bottom);

	if (p1.left > p1.right || p1.top > p1.bottom)
	{
		if (p1.left > p1.right)
		{
			int tmp;
			tmp = p1.left;
			p1.left = p1.right;
			p1.right = tmp;
		}

		if (p1.top > p1.bottom)
		{
			int tmp;
			tmp = p1.top;
			p1.top = p1.bottom;
			p1.bottom = tmp;
		}
		printf("������ ���簢��: �»���� = (%d, %d), ���ϴ��� = (%d, %d)\n", p1.left, p1.top, p1.right, p1.bottom);
	}
	else
	{
		printf("������ ���� �����ϴ�.\n");
	}


	printf("������ ��ǥ�� �Է��ϼ���(x,y) :");
	scanf("%d %d", &r1.x, &r1.y);

	if (p1.left <= r1.x && r1.x <= p1.right && p1.top <= r1.y && p1.bottom >= r1.y)
	{
		printf("(%d, %d)�� ���簢�� ���ο� �ֽ��ϴ�.", r1.x, r1.y);
	}
	else
	{
		printf("(%d, %d)�� ���簢�� ���ο� �����ϴ�.", r1.x, r1.y);
	}

	return 0;
}