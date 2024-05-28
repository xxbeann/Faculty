#include <stdio.h>
#include <unistd.h>
// POSIX 운영 체제 API를 제공하는 헤더 파일 fork()함수를 사용하기 위함
#include <sys/types.h>
// 시스템 타입 정의. 시스템 호출과 관련된 타입 정의
#include <stdlib.h>
// 메모리 할당, 프로그램 제어, 난수 생성 malloc, atoi함수
#include <math.h>

// Hello world를 출력하는 함수 정의.
void print_hello() {
	printf("Hello World\n");
}

int main()
{
	char s[12];
	// 동적으로 할당된 메모리 가리킴.
	int *ptr;
	int i;
	float a;
	
	// gets 함수 버퍼 오버플로우 취약점 주의.
	// fgets로 대체 가능
	gets(s);
	// malloc함수를 사용하여 int크기의 메모리 동적할당
	// 그 주소 ptr저장
	ptr = (int *)malloc(sizeof(int));
	/*
	atoi함수를 사용하여 문자열s를 정수로 변환하고, ptr이 가리키는 메모리 위치에 저장
	about atoi
	문자열은 정수로 되어있어야 하며 알파벳 영문자, 특수 문자가 포함되면
	해당 문자부터는 변환을 하지 않습니다.
	또한, 처음부터 숫자가 아니면 0으로 변환됩니다.
	*/
	*ptr = atoi(s);
	// sin함수를 사용하여 ptr이 가리키는 값의 사인 값을 계산
	a = sin(*ptr);
	// 문자열 s, ptr이 가리키는 정수 값, a 값
	printf("STR: %s, INT: %d, SIN(k): %f\n", s, *ptr, a);
	// 메모리 해제
	free(ptr);

	for(i = 0; i < 2; i++) {
		//fork 함수 두번 호출
		//fork 가 된 순간 동일한 코드를 실행하는 자식 프로세스가 생성되었다.
		fork();
		print_hello();
	}
}
