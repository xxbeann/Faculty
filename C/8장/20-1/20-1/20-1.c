#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
//���� �Է�1 : 1.2 3.4 5.6 7.8 9.8
//���� ���1 : 5.56

//���� �Է�2 : 5.1 5.6 8.7 4.5 3.1
//���� ���2 : 5.40
*/

double arr5_average();

int main(void)
{
    double ans;

    //�Լ� �̿��ؼ� ��� ���
    ans = arr5_average();
    printf("average : %.2lf\n", ans);
    system("PAUSE");
    return 0;
}


double arr5_average()
{
    double arr[5] = { 0 };
    double(*pt)[5] = &arr;
    double sum = 0.0;
    double avg = 0.0;
    int i = 0;

    // �迭 �Է¹ޱ�
    char strarr[1000] = { 0 };

    printf("arr[5] �Է� : ");
    gets(strarr);

    char* strarr_last = strtok(strarr, " ");

    while (strarr_last != NULL)
    {
        arr[i] = atof(strarr_last);
        strarr_last = strtok(NULL, " ");
        i++;
    }

    // ��� ���ϱ�
    for (i = 0; i < 5; i++)
    {
        sum += (*pt)[i];
    }
    avg = (double)sum / 5;

    return avg;

}