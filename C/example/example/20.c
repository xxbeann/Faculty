#include <stdio.h>
#include <string.h>
//어려움.문자열을 잘 컨트롤 할 수 있는지 특히 배열, 분기문잘 나눌 수 있는지, 버퍼 활용여부 

typedef struct contact {
	char name[10];
	char phone[30];

}Contact;

int main(void)
{
	Contact Book[100];
	char findName[10];
	char findPhone[10];
	char ch;
	int i;
	int count = 0;

	while (1)
	{
		//printf("검색할 이름");
		//gets(findName);

		if (strcmp(findName, ".") == 0)
			break;//큰따옴표는 문자열, 작은따옴표는 하나
			//전체문자열이 같은지 비교를 해야함
			// 문자열[0]로 비교를 할 수 없음.

		for (i = 0; i < count; i++)//저장한 개수만큼 돌기
		{
			if (strcmp(findName, Book[i].name) == 0)
			{
				printf(": %s\n\n", Book[i].phone);
				break;
			}
				
		}

		if (i == count)
		{
			printf("저장되지 않은~ ");
			scanf("%c", &ch);
			
			if (ch != 'y' && ch != 'Y')//Y,y가 아닐경우에만
			{
				printf("\n");
				continue;
			}

			printf("전화번호 입력");
			//scanf("%c", &ch); 버퍼 엔터값
			gets(findPhone);

			strcpy(Book[count].name, findPhone);
			strcpy(Book[count].phone, findPhone);
			count++;

		}
	}
	return 0;
}
