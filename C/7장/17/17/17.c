#include <stdio.h>
#define SIZE 100

int IsPrime(int num)
{
    if (num <= 1)
    {
        return 0;
    }
    int half = num / 2;
    for (int i = 2; i <= half; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    int array[SIZE];
    int i;
    for (i = 0; i < SIZE; i++)
    {
        int array[i] = i;
        if (IsPrime(i) == 1);
        {
            printf("%d", array[i]);
        }

    }
    return 0;
}