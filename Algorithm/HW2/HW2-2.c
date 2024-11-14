// Dynamic Programming을 이용한 풀이
#include <stdio.h>
#include <string.h>

#define MAX_N 10000
#define MAX_K 10

// dp 테이블: dp[i][j]는 i를 j 이하의 수로 나누는 방법의 수를 저장 (long long 타입으로 변경)
long long dp[MAX_N + 1][MAX_K + 1];

// n을 k 이하의 수로 표현하는 경우의 수를 동적 계획법으로 계산
long long find_combinations(int n, int k) {
    // dp 테이블 초기화
    memset(dp, 0, sizeof(dp));
    
    // 기본 경우: n = 0일 때는 경우의 수 1개 (아무것도 선택하지 않는 경우)
    for (int i = 1; i <= k; i++) {
        dp[0][i] = 1;
    }
    
    // 동적 계획법으로 dp 테이블 채우기
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            // dp[i][j]는 i를 j 이하의 수로 표현하는 경우의 수
            // 이전 값(dp[i][j-1]) + j를 하나 더 사용하는 경우(dp[i-j][j])
            dp[i][j] = dp[i][j-1];
            if (i - j >= 0) {
                dp[i][j] += dp[i - j][j];
            }
        }
    }

    // n을 k 이하의 수로 표현하는 경우의 수 반환
    return dp[n][k];
}

int main() {
    int n, k;
    printf("Input n and k (example: 10000 10): ");
    scanf("%d %d", &n, &k);

    if (k >= n || k <= 2) {
        printf("Invalid input. n > k > 2 should follow this condition.\n");
        return 1;
    }

    long long result = find_combinations(n, k);

    printf("Total count: %lld\n", result);

    return 0;
}
