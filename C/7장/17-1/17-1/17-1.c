#include <stdio.h>
int IsPrime(int num);
int main(void)
{
	int arr[100] = { 0 };
	int i, cnt = 0;
	for (i = 2; cnt < 100; i++) 
	{        
		if (IsPrime(i))
		{
			arr[cnt++] = i;
		}
	}
	for (i = 0; i < 100; i++) 
	{          
		printf("%d ", arr[i]);
		if (i % 10 == 9)
		{
			printf("\n");
		}
	}
	system("PAUSE");
	return 0;
}
int IsPrime(int num)             
{
	int i;
	for (i = 2; i <= num / 2; i++) 
	{
		if (num % i == 0)
		{
			return 0;
		}
	}
	return 1;
}