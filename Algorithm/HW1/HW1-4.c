// 차이가 가장 큰 두 수를 찾는 알고리즘 Counting Sort
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 6자리 정수의 범위 정의
#define MIN_VALUE 100000
#define MAX_VALUE 999999
#define RANGE (MAX_VALUE - MIN_VALUE + 1)

// 두 값의 차이가 가장 큰 두 수를 찾는 함수
void findMaxDifference(int arr[], int n) {
    if (n < 2) {
        printf("배열에 적어도 두 개 이상의 숫자가 있어야 합니다.\n");
        return;
    }

    // 카운팅 배열 초기화
    int count[RANGE] = {0};

    // 배열을 순회하며 각 숫자의 개수 카운팅
    for (int i = 0; i < n; i++) {
        count[arr[i] - MIN_VALUE]++;
    }

    // 정렬된 배열에서 가장 작은 값과 가장 큰 값을 찾기
    int minVal = -1, maxVal = -1;

    // 최소값 찾기
    for (int i = 0; i < RANGE; i++) {
        if (count[i] > 0) {
            minVal = i + MIN_VALUE;
            break;
        }
    }

    // 최대값 찾기
    for (int i = RANGE - 1; i >= 0; i--) {
        if (count[i] > 0) {
            maxVal = i + MIN_VALUE;
            break;
        }
    }

    // 차이 계산 및 결과 출력
    int maxDiff = maxVal - minVal;
    printf("두 값의 차이가 가장 큰 두 수는 %d와 %d이며, 차이는 %d입니다.\n", minVal, maxVal, maxDiff);
}

int main() {
    int arr[] = {450000, 920000, 110000, 326000, 134000, 230000};
    int n = sizeof(arr) / sizeof(arr[0]);

    findMaxDifference(arr, n);

    return 0;
}
