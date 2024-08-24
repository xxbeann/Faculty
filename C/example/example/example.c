#include <stdio.h>
//21번


int main(void)
{
	Rect R1;
	Point P1;
	printf("~~~");
	//scanf %d, &R1.left top right bottom

	if (R1.left > R1.right)
	{
		int tmp;
		tmp = R1.left;
		R1.left = R1.right;
		R1.right = tmp;
		//비교문
	}

	// top bottom if문 사용해서 마찬가지로.


	printf("좌표입력");
	//scanf 이용해서 받기 &p1.x, &P1.y

	if (R1.left <= P1.x && P1.x <= R1.right)
	{
		//printf("00000");
		//직사각형 판단문
	}
	return 0;
}