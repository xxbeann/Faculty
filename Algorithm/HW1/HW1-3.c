// 차이가 가장 작은 두 수를 찾는 알고리즘 Counting Sort
#include <stdio.h>
#include <limits.h>

#define MIN_VALUE 100000
#define MAX_VALUE 999999
#define RANGE (MAX_VALUE - MIN_VALUE + 1)

// 두 값의 차이가 가장 작은 두 수를 찾는 함수
void findMinDifference(int arr[], int n) {
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

    // 최소 차이를 찾기 위해 이전 숫자를 추적
    int prev = -1;
    int minDiff = INT_MAX;
    int num1 = 0, num2 = 0;

    // 카운팅 배열을 순회하면서 인접한 숫자들의 차이를 계산
    for (int i = 0; i < RANGE; i++) {
        if (count[i] > 0) {
            // 첫 번째 발견된 숫자
            if (prev != -1) {
                int diff = (i + MIN_VALUE) - prev;
                if (diff < minDiff) {
                    minDiff = diff;
                    num1 = prev;
                    num2 = i + MIN_VALUE;
                }
            }
            prev = i + MIN_VALUE;
        }
    }

    // 결과 출력
    printf("두 값의 차이가 가장 작은 두 수는 %d와 %d이며, 차이는 %d입니다.\n", num1, num2, minDiff);
}

int main() {
    int arr[] = {450000, 920000, 110000, 326000, 134000, 230000};
    int n = sizeof(arr) / sizeof(arr[0]);

    findMinDifference(arr, n);

    return 0;
}
