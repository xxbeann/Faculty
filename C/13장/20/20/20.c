#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct login_info LOGIN_INFO;
LOGIN_INFO newLoginInfo(char* id, char* passwd);

typedef struct login_info {
    char id[20];
    char passwd[20];
} LOGIN_INFO;

LOGIN_INFO newLoginInfo(char id[], char passwd[]) {
    LOGIN_INFO new = { "", "" };
    strcpy(new.id, id);
    strcpy(new.passwd, passwd);
    return new;
}

int main() {
    int n;
    FILE* fp = fopen("result", "rb");

    // 20
    fread(&n, sizeof(int), 1, fp);

    LOGIN_INFO* login_infos = malloc(sizeof(LOGIN_INFO) * n);

    for (int i = 0; i < n; i++) {
        char id[20];
        char passwd[20];
        fread(id, sizeof(char[20]), 1, fp);
        fread(passwd, sizeof(char[20]), 1, fp);
        *(login_infos + (i * sizeof(LOGIN_INFO))) = newLoginInfo(id, passwd);
    }

    // 20
    // Checking allocations
    /*
    for (int i = 0; i < n; i++) {
      printf("%s -> %s\n", (login_infos+(i*sizeof(LOGIN_INFO))) -> id, (login_infos+(i*sizeof(LOGIN_INFO))) -> passwd);
    }
    */
    int is_login_success, continue_login = 0;
    char get_id[20], get_pw[20];
    printf("패스워드 파일을 읽었습니다. %d명의 사용자 정보가 있습니다.\n", n);
    do {
        is_login_success = 0;
        printf("ID를 입력하세요 : ");
        scanf("%s", &get_id);
        printf("패스워드를 입력하세요 : ");
        scanf("%s", &get_pw);
        for (int i = 0; i < n; i++) {
            if (strcmp(get_id, (login_infos + (i * sizeof(LOGIN_INFO)))->id) == 0) {
                if (strcmp(get_pw, (login_infos + (i * sizeof(LOGIN_INFO)))->passwd) == 0) {
                    is_login_success = 1;
                }
            }
        }
        if (is_login_success) printf("LOGIN OK!\n");
        else printf("LOGIN FAILED!\n");
        int c;
        do { c = getchar(); } while (c != '\n' && c != EOF);
        printf("계속 하시겠습니까? (Y/N) ");
        scanf("%c", &continue_login);
    } while (continue_login == 89 || continue_login == 121);
}