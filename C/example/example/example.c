#include <stdio.h>
//21��


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
		//�񱳹�
	}

	// top bottom if�� ����ؼ� ����������.


	printf("��ǥ�Է�");
	//scanf �̿��ؼ� �ޱ� &p1.x, &P1.y

	if (R1.left <= P1.x && P1.x <= R1.right)
	{
		//printf("00000");
		//���簢�� �Ǵܹ�
	}
	return 0;
}