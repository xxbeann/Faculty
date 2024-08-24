#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

void InputArray(double* target);
void PrintArray(double* target);
double Average(double* target);
double Variance(double* target);
double StandardDeviation(double* target);

int main() 
{
    double arr[5];
    InputArray(arr);
    PrintArray(arr);
    printf("�л� : %lf\n", Variance(arr));
    printf("ǥ������ : %lf\n", StandardDeviation(arr));
    return 0;
}

void InputArray(double* target) {
    printf("5���� �Ǽ��� �Է��ϼ��� : ");
    for (int i = 0; i < 5; i++) {
        scanf("%lf", &target[i]);
    }
}

void PrintArray(double* target) {
    printf("�迭 : ");
    for (int i = 0; i < 5; i++) {
        printf("%.2f  ", target[i]);
    }
    printf("\n");
}

double Average(double* target) {
    double sums = 0;
    for (int i = 0; i < 5; i++)
        sums += target[i];
    return sums / 5;
}

double Variance(double* target) {
    double average = Average(target);
    double d_sums = 0;
    for (int i = 0; i < 5; i++)
        d_sums += target[i] * target[i];
    return d_sums / 5 - average * average;
}

double StandardDeviation(double* target) {
    return sqrt(Variance(target));
}