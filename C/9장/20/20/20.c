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
		printf("�˻��� �̸� : ");
		scanf("%s", name);
		//gets(name);

		if (strcmp(name, ".") == 0)
			break;

	
		for (i = 0; i < count; i++)
		{
			if (strcmp(name, p[i].name) == 0)
			{
				printf("ã�� ��ȭ��ȣ : %s\n\n", p[i].phone);
				break;
			}

		}

		if (0 == count)
		{
			printf("������� ���� ����ó�Դϴ�. �����Ͻðڽ��ϱ�? (Y/N) : ");
			scanf("%s", &ch);

			if (ch != 'y' && ch != 'Y')
			{
				printf("\n");
				continue;
			}

			printf("��ȭ��ȣ �Է� : ");
			scanf("%s", &ch);
			//gets(p[i].phone);

			strcpy(p[count].name, name);
			strcpy(p[count].phone, ch);
			count++;
		}
	}

	return 0;
}