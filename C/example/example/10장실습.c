#include <stdio.h>

int swap(int x, int y);

int main(void)
{
	//386 page

	//스왑이 a,b에 복사되서 swap함수에 들어감
	//pointer사용해서 주소를 넘겨줌/

	swap(&a, &b);

	return 0;
}

void swap(int* x, int* y)//외부에 있는 값을 변경할때는 포인터를 사용한다.(main에 있는 값을 변경할때는)
{
	int tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;


}

/*
392 page 입력인자 2개와 출력인자 2개

void GetSumProduct(int x, int y, int* sum, int* product);
함수의 파라미터에 &가 들어갈 경우 이 함수의 값은 바뀐다.

*/

/*
page 397
int* arr = int arr[]
함수를 만든다 - 일반적으로 동작하도록 만든다.

print array 출력
*(arr+i) - 시험강조

int를 출력인자로 바꾸기 - 시험에 잘 나온다.
int -> void (int* arr, int size, int* total)

*total = 0;
for i()
 total += arr[i]

 y+2라는 개념 - 포인터 챕터

*/

/*
재귀함수 GCD 시험나온적 있음
414page
*/

/*
배열을 출력인자로 쓰는 경우, 어레이를 출력인자로 사용할 수 있다.

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
표준 라이브러리 함수 시험에 활용
문자열은 널문자
*/