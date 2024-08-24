#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int Round();

int main() 
{
    printf("%d\n", Round());
    system("PAUSE");
    return 0;
}

int Round() 
{

    double r;

    printf("실수를 입력하세요: ");
    scanf("%lf", &r);

    if (r > 0) 
    {
        return (int)(r + 0.5);
    }
    return (int)(r - 0.5);
}