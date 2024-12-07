#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX_AMOUNT 1048575 // 최대 금액
#define MAX_COINS 7        // 동전 개수

int dp[1048576]; // 메모이제이션 배열
int coinUsed[1048576]; // 사용된 동전을 추적하기 위한 배열

// 메모이제이션을 활용한 재귀 함수
int coinChangeMemo(int coins[], int k, int amount) {
    if (amount == 0) return 0; // 0원을 만드는 데 필요한 동전 수는 0
    if (dp[amount] != -1) return dp[amount]; // 이미 계산된 값이면 반환

    int minCoins = INT_MAX;
    int selectedCoin = -1;

    for (int i = 0; i < k; i++) {
        if (amount >= coins[i]) {
            int subResult = coinChangeMemo(coins, k, amount - coins[i]);
            if (subResult != INT_MAX && subResult + 1 < minCoins) {
                minCoins = subResult + 1;
                selectedCoin = coins[i]; // 선택한 동전을 저장
            }
        }
    }

    dp[amount] = minCoins; // 최소 동전 수 저장
    coinUsed[amount] = selectedCoin; // 해당 금액에서 사용한 동전 저장
    return dp[amount];
}

// 결과 구성 함수
void buildResult(int coins[], int k, int amount, int result[]) {
    for (int i = 0; i < k; i++) result[i] = 0; // 결과 초기화

    while (amount > 0) {
        int usedCoin = coinUsed[amount];
        for (int i = 0; i < k; i++) {
            if (coins[i] == usedCoin) {
                result[i]++;
                break;
            }
        }
        amount -= usedCoin;
    }
}

int main() {
    int k = 7;
    int coins[MAX_COINS] = {600, 300, 100, 50, 25, 5, 1}; // 동전 세트
    srand(time(0)); // 랜덤 시드 초기화

    int amount = rand() % (MAX_AMOUNT - 100000 + 1) + 100000; // 10만 이상 랜덤 금액 생성
    int result[MAX_COINS] = {0}; // 결과 초기화
    clock_t start, end;

    // DP 배열 초기화
    for (int i = 0; i <= amount; i++) {
        dp[i] = -1;
        coinUsed[i] = -1;
    }

    // 메모이제이션 실행 및 시간 측정
    start = clock();
    coinChangeMemo(coins, k, amount);
    buildResult(coins, k, amount, result);
    end = clock();
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;

    // 결과 출력
    printf("Amount: %d\n", amount);
    printf("DP Result: ");
    for (int i = 0; i < k; i++) {
        printf("%d원: %d개 ", coins[i], result[i]);
    }
    printf("\n");
    printf("Total Time: %f sec\n", executionTime);

    return 0;
}

