#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>

struct phonebook {
	char name[10];
	char phone[20];
};

int main(void)
{
	struct phonebook p[100];
	char ch;
	char name[10];
	int i, count = 0;

	while (1)
	{
		printf("검색할 이름 : ");
		scanf("%s", name);
		//gets(name);

		if (strcmp(name, ".") == 0)
			break;

	
		for (i = 0; i < count; i++)
		{
			if (strcmp(name, p[i].name) == 0)
			{
				printf("찾은 전화번호 : %s\n\n", p[i].phone);
				break;
			}

		}

		if (0 == count)
		{
			printf("저장되지 않은 연락처입니다. 저장하시겠습니까? (Y/N) : ");
			scanf("%s", &ch);

			if (ch != 'y' && ch != 'Y')
			{
				printf("\n");
				continue;
			}

			printf("전화번호 입력 : ");
			scanf("%s", &ch);
			//gets(p[i].phone);

			strcpy(p[count].name, name);
			strcpy(p[count].phone, ch);
			count++;
		}
	}

	return 0;
}