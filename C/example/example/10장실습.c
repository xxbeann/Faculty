#include <stdio.h>

int swap(int x, int y);

int main(void)
{
	//386 page

	//������ a,b�� ����Ǽ� swap�Լ��� ��
	//pointer����ؼ� �ּҸ� �Ѱ���/

	swap(&a, &b);

	return 0;
}

void swap(int* x, int* y)//�ܺο� �ִ� ���� �����Ҷ��� �����͸� ����Ѵ�.(main�� �ִ� ���� �����Ҷ���)
{
	int tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;


}

/*
392 page �Է����� 2���� ������� 2��

void GetSumProduct(int x, int y, int* sum, int* product);
�Լ��� �Ķ���Ϳ� &�� �� ��� �� �Լ��� ���� �ٲ��.

*/

/*
page 397
int* arr = int arr[]
�Լ��� ����� - �Ϲ������� �����ϵ��� �����.

print array ���
*(arr+i) - ���谭��

int�� ������ڷ� �ٲٱ� - ���迡 �� ���´�.
int -> void (int* arr, int size, int* total)

*total = 0;
for i()
 total += arr[i]

 y+2��� ���� - ������ é��

*/

/*
����Լ� GCD ���質���� ����
414page
*/

/*
�迭�� ������ڷ� ���� ���, ��̸� ������ڷ� ����� �� �ִ�.

void Reverse(int* arr1, int size, int* arr2)

int i;
for(i =0, i<size; i++)
arr2[size -1 -i] = arr1[i];


int main()
int arr1[5] = {7,1,3,4,5];
int arr2[5];
int i;
Reverse (arr1, 5, arr2);


*/

/*
ǥ�� ���̺귯�� �Լ� ���迡 Ȱ��
���ڿ��� �ι���
*/