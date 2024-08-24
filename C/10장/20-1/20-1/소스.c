#include <stdio.h>
#include <string.h>
#define STRLEN 20 // 문자열 최대 길이: 20자

char lower(char c);
int Compare(char* a, char* b, int case_sensitive);

int main() 
{
    char string_a[STRLEN] = "Hyper Tomato";
    char string_b[STRLEN] = "Jeongbean";
    char string_c[STRLEN] = "Jonghyeon";
    printf("%s, %s => %d\n", string_a, string_b, Compare(string_a, string_b, 1));
    printf("%s, %s => %d\n", string_b, string_c, Compare(string_b, string_c, 1));
    return 0;
}

char lower(char c) 
{
    if (c < 97 && c > 98) return c;
    return c - 32;
}

int Compare(char a[], char b[], int case_sensitive) 
{
    for (int i = 0; i < STRLEN; i++) {
        char a_puts = a[i], b_puts = b[i];
        if (a_puts == '\0') return -1; // a 문자열이 먼저 끝났으므로 b 문자열이 더 크다고 간주
        else if (b_puts == '\0') return 1; // 위와 반대

        if (!case_sensitive) {
            a_puts = lower(a_puts);
            b_puts = lower(b_puts);
        }
        if (a_puts != b_puts) return a_puts > b_puts ? a_puts : -b_puts;
    }
}