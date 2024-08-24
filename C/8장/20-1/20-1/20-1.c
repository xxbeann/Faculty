#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
//예시 입력1 : 1.2 3.4 5.6 7.8 9.8
//예시 출력1 : 5.56

//예시 입력2 : 5.1 5.6 8.7 4.5 3.1
//에시 출력2 : 5.40
*/

double arr5_average();

int main(void)
{
    double ans;

    //함수 이용해서 평균 출력
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

    // 배열 입력받기
    char strarr[1000] = { 0 };

    printf("arr[5] 입력 : ");
    gets(strarr);

    char* strarr_last = strtok(strarr, " ");

    while (strarr_last != NULL)
    {
        arr[i] = atof(strarr_last);
        strarr_last = strtok(NULL, " ");
        i++;
    }

    // 평균 구하기
    for (i = 0; i < 5; i++)
    {
        sum += (*pt)[i];
    }
    avg = (double)sum / 5;

    return avg;

}