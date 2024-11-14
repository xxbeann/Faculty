// 경우의 수 파일에 출력
#include <stdio.h>
#include <string.h>

#define MAX_N 10000
#define MAX_K 10

long long dp[MAX_N + 1][MAX_K + 1];

// n을 k 이하의 수로 표현하는 경우의 수를 동적 계획법으로 계산
long long find_combinations(int n, int k, FILE *fp) {
    // dp 테이블 초기화
    memset(dp, 0, sizeof(dp));

    // 기본 경우: n = 0일 때는 경우의 수 1개 (아무것도 선택하지 않는 경우)
    for (int i = 1; i <= k; i++) {
        dp[0][i] = 1;
    }

    // 동적 계획법으로 dp 테이블 채우기
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = dp[i][j-1];
            if (i - j >= 0) {
                dp[i][j] += dp[i - j][j];
            }
        }
    }

    // n을 k 이하의 수로 표현하는 경우의 수 반환
    return dp[n][k];
}

// 재귀적으로 조합 출력
void print_combinations(int n, int k, int start, int combination[], int index, FILE *fp) {
    if (n == 0) {
        fprintf(fp, "(");
        for (int i = 0; i < index; i++) {
            fprintf(fp, "%d", combination[i]);
            if (i < index - 1) fprintf(fp, ",");
        }
        fprintf(fp, ")\n");
        return;
    }

    for (int i = start; i <= k; i++) {
        if (n >= i) {
            combination[index] = i;
            print_combinations(n - i, k, i, combination, index + 1, fp);
        }
    }
}

int main() {
    int n, k;
    printf("Input n and k (example: 10000 10): ");
    scanf("%d %d", &n, &k);

    if (k >= n || k <= 2) {
        printf("Invalid input. n > k > 2 should follow this condition.\n");
        return 1;
    }

    FILE *fp = fopen("combinations.txt", "w");
    if (fp == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }

    int combination[MAX_N];
    long long result = find_combinations(n, k, fp);

    fprintf(fp, "Total count: %lld\n", result);

    // 모든 조합 출력
    print_combinations(n, k, 1, combination, 0, fp);

    fclose(fp);

    printf("All combinations are saved in 'combinations.txt'.\n");
    return 0;
}
