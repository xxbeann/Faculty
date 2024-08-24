#include <stdio.h>
#define SIZE 5

int main(void)
{
	double ave = 0,sum = 0;
	double arr[SIZE] = { 50, 60, 70, 80, 90 };
	double* pa = arr;

	for (int i = 0; i < SIZE; i++)
	{
		sum = sum + pa[i];
	}

	ave = sum / SIZE;

	printf("Average = %lf\n", ave);
	system("PAUSE");

	return 0;
}