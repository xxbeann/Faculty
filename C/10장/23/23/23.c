#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct rect { //rect ����ü
	int left, top, right, bottom;
}r1;

struct point { //point ����ü
	int x, y;
}p1;

void InputRect(void); //���簢�� �����Է�

struct point CenterOfRect(struct rect r1); // �߽��� ���ϱ�

int main(void)
{
	InputRect();
	CenterOfRect(r1);
	printf("���簢���� �߽� : (%d, %d)", p1.x, p1.y);
	return 0;
}

void InputRect(void) //���簢�� �����Է�
{
	printf("�»����/���ϴ����� ��ǥ�� �Է��ϼ���(left, top, right, bottom ��)\n");
	scanf("%d %d %d %d", &r1.left, &r1.top, &r1.right, &r1.bottom);
	printf("�Էµ� ���簢��: �»���� = (%d, %d), ���ϴ��� = (%d, %d)\n", r1.left, r1.top, r1.right, r1.bottom);
}

struct point CenterOfRect(struct rect r1) //�߽��� ���ϱ�
{
	p1.x = (r1.left + r1.right) / 2;
	p1.y = (r1.top + r1.bottom) / 2;
	
	return p1;
}