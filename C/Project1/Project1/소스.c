#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>


struct Phonebook {
    char name[10];
    char phone[20];
};

int main(void) {
    struct Phonebook p[100];
    int i, count = 0;
    char n[10], ph[10];
    char c;


    while (1) {
        printf("�˻��� �̸� : ");
        scanf("%s", n);

        if (strcmp(n, ".") == 0)
            break;

        for (i = 0; i <= count; i++) {
            if (strcmp(n, p[i].name) == 0)
            {
                printf("ã�� ��ȭ��ȣ : %s\n\n", p[i].phone);
                break;
            }

        }
        if (i == count + 1) 
        {
            printf("������� ���� ����ó�Դϴ�. �����Ͻðڽ��ϱ�? (Y/N) : ");
            scanf("%c", &c);
            if (c != 'y' && c != 'Y')
            {
                printf("\n");
                printf("��ȭ��ȣ �Է� : ");
                scanf("%s", ph);
                strcpy(p[count].phone, ph);
                strcpy(p[count].name, n);
                count++;
            }
        }

    }
    return 0;
}
