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

    printf("�Ǽ��� �Է��ϼ���: ");
    scanf("%lf", &r);

    if (r > 0) 
    {
        return (int)(r + 0.5);
    }
    return (int)(r - 0.5);
}