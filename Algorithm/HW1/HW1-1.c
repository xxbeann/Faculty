#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// 비교 함수: qsort에 사용 (double형을 위한 비교 함수)
int compare(const void* a, const void* b) {
    double diff = (*(double*)a - *(double*)b);
    if (diff < 0) return -1;
    else if (diff > 0) return 1;
    else return 0;
}

// 두 값의 차이가 가장 작은 두 수를 찾는 함수 (실수형 배열에 적용)
void findMinDifference(double arr[], int n) {
    if (n < 2) {
        printf("배열에 적어도 두 개 이상의 숫자가 있어야 합니다.\n");
        return;
    }

    // 배열을 정렬
    qsort(arr, n, sizeof(double), compare);

    double minDiff = DBL_MAX;
    double num1, num2;

    // 인접한 두 수의 차이를 계산하며 최소값을 찾음
    for (int i = 0; i < n - 1; i++) {
        double diff = arr[i + 1] - arr[i];
        if (diff < minDiff) {
            minDiff = diff;
            num1 = arr[i];
            num2 = arr[i + 1];
        }
    }

    // 결과 출력
    printf("두 값의 차이가 가장 작은 두 실수는 %.10lf와 %.10lf이며, 차이는 %.10lf입니다.\n", num1, num2, minDiff);
}

int main() {
    double arr[] = { 4.5, 9.2, 1.1, 32.6, 13.4, 2.3 };
    int n = sizeof(arr) / sizeof(arr[0]);

    findMinDifference(arr, n);

    return 0;
}
