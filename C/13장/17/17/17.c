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
    scanf("%d", &n);

    LOGIN_INFO* login_infos = malloc(sizeof(LOGIN_INFO) * n);

    for (int i = 0; i < n; i++) {
        char id[20];
        char passwd[20];
        scanf("%s %s", id, passwd);
        *(login_infos + (i * sizeof(LOGIN_INFO))) = newLoginInfo(id, passwd);
    }

    // 17
    /*
    // Checking allocations
    for (int i = 0; i < n; i++) {
      printf("%s -> %s\n", (login_infos+(i*sizeof(LOGIN_INFO))) -> id, (login_infos+(i*sizeof(LOGIN_INFO))) -> passwd);
    }
    */
    FILE* fp = fopen("result.txt", "w");
    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s %s\n", (login_infos + (i * sizeof(LOGIN_INFO)))->id, (login_infos + (i * sizeof(LOGIN_INFO)))->passwd);
    }
}