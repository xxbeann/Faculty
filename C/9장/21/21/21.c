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
	printf("좌상단점/우하단점의 좌표를 입력하세요(left, top, right, bottom 순)\n");
	scanf("%d %d %d %d", &p1.left, &p1.top, &p1.right, &p1.bottom);
	printf("입력된 직사각형: 좌상단점 = (%d, %d), 우하단점 = (%d, %d)\n", p1.left, p1.top, p1.right, p1.bottom);

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
		printf("수정된 직사각형: 좌상단점 = (%d, %d), 우하단점 = (%d, %d)\n", p1.left, p1.top, p1.right, p1.bottom);
	}
	else
	{
		printf("수정된 값이 없습니다.\n");
	}


	printf("한점의 좌표를 입력하세요(x,y) :");
	scanf("%d %d", &r1.x, &r1.y);

	if (p1.left <= r1.x && r1.x <= p1.right && p1.top <= r1.y && p1.bottom >= r1.y)
	{
		printf("(%d, %d)는 직사각형 내부에 있습니다.", r1.x, r1.y);
	}
	else
	{
		printf("(%d, %d)는 직사각형 내부에 없습니다.", r1.x, r1.y);
	}

	return 0;
}