#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
	int arr[10] = { 15, 23, 7, 78, 34, 67, 45, 36, 90, 71 };
	int* pa = arr;
	int a;

	printf("[���� �迭]");
	for (int i = 0; i < 10; i++)
	{
		printf("%4d", pa[i]);
	}

	printf("\n");
	printf("�������� �Է��ϼ���: ");
	scanf("%d", &a);

	printf("[������ �迭]");
	for (int i = 0; i < 10; i++)
	{
		//pa[i] = pa[i] + a;
		pa[i] += a;
		printf("%4d", pa[i]);
	}

	system("PAUSE");
	return 0;
}