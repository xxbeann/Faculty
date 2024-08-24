#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct rect { //rect 구조체
	int left, top, right, bottom;
}r1;

struct point { //point 구조체
	int x, y;
}p1;

void InputRect(void); //직사각형 정보입력

struct point CenterOfRect(struct rect r1); // 중심점 구하기

int main(void)
{
	InputRect();
	CenterOfRect(r1);
	printf("직사각형의 중심 : (%d, %d)", p1.x, p1.y);
	return 0;
}

void InputRect(void) //직사각형 정보입력
{
	printf("좌상단점/우하단점의 좌표를 입력하세요(left, top, right, bottom 순)\n");
	scanf("%d %d %d %d", &r1.left, &r1.top, &r1.right, &r1.bottom);
	printf("입력된 직사각형: 좌상단점 = (%d, %d), 우하단점 = (%d, %d)\n", r1.left, r1.top, r1.right, r1.bottom);
}

struct point CenterOfRect(struct rect r1) //중심점 구하기
{
	p1.x = (r1.left + r1.right) / 2;
	p1.y = (r1.top + r1.bottom) / 2;
	
	return p1;
}