#include <stdio.h>
#include <string.h>
//�����.���ڿ��� �� ��Ʈ�� �� �� �ִ��� Ư�� �迭, �б⹮�� ���� �� �ִ���, ���� Ȱ�뿩�� 

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
		//printf("�˻��� �̸�");
		//gets(findName);

		if (strcmp(findName, ".") == 0)
			break;//ū����ǥ�� ���ڿ�, ��������ǥ�� �ϳ�
			//��ü���ڿ��� ������ �񱳸� �ؾ���
			// ���ڿ�[0]�� �񱳸� �� �� ����.

		for (i = 0; i < count; i++)//������ ������ŭ ����
		{
			if (strcmp(findName, Book[i].name) == 0)
			{
				printf(": %s\n\n", Book[i].phone);
				break;
			}
				
		}

		if (i == count)
		{
			printf("������� ����~ ");
			scanf("%c", &ch);
			
			if (ch != 'y' && ch != 'Y')//Y,y�� �ƴҰ�쿡��
			{
				printf("\n");
				continue;
			}

			printf("��ȭ��ȣ �Է�");
			//scanf("%c", &ch); ���� ���Ͱ�
			gets(findPhone);

			strcpy(Book[count].name, findPhone);
			strcpy(Book[count].phone, findPhone);
			count++;

		}
	}
	return 0;
}
