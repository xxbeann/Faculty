#include <stdio.h>
#include <float.h>  // 실수형 한계를 정의한 헤더 파일

// 두 값의 차이가 가장 큰 두 수를 찾는 함수
void findMaxDifference(double arr[], int n) {
    if (n < 2) {
        printf("배열에 적어도 두 개 이상의 숫자가 있어야 합니다.\n");
        return;
    }

    // 초기값 설정
    double minVal = DBL_MAX;
    double maxVal = -DBL_MAX;

    // 배열을 순회하면서 최솟값과 최댓값을 찾음
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    // 결과 출력
    double maxDiff = maxVal - minVal;
    printf("두 값의 차이가 가장 큰 두 수는 %.10lf와 %.10lf이며, 차이는 %.10lf입니다.\n", minVal, maxVal, maxDiff);
}

int main() {
    double arr[] = {4.5, 9.2, 1.1, 32.6, 13.4, 2.3};
    int n = sizeof(arr) / sizeof(arr[0]);

    findMaxDifference(arr, n);

    return 0;
}