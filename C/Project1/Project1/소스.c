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
        printf("검색할 이름 : ");
        scanf("%s", n);

        if (strcmp(n, ".") == 0)
            break;

        for (i = 0; i <= count; i++) {
            if (strcmp(n, p[i].name) == 0)
            {
                printf("찾은 전화번호 : %s\n\n", p[i].phone);
                break;
            }

        }
        if (i == count + 1) 
        {
            printf("저장되지 않은 연락처입니다. 저장하시겠습니까? (Y/N) : ");
            scanf("%c", &c);
            if (c != 'y' && c != 'Y')
            {
                printf("\n");
                printf("전화번호 입력 : ");
                scanf("%s", ph);
                strcpy(p[count].phone, ph);
                strcpy(p[count].name, n);
                count++;
            }
        }

    }
    return 0;
}
