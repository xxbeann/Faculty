#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_AMOUNT 1048575 // 최대 금액
#define MAX_COINS 7        // 동전 개수

void coinChangeGreedy(int coins[], int k, int amount, int result[]) {
    for (int i = 0; i < k; i++) {
        result[i] = amount / coins[i];
        amount %= coins[i];
    }
}

int main() {
    int k = 7;
    int coins[MAX_COINS] = {600, 300, 100, 50, 25, 5, 1}; // 동전 세트
    srand(time(0)); // 랜덤 시드 초기화

    int amount = rand() % (MAX_AMOUNT - 100000 + 1) + 100000; // 10만 이상 랜덤 금액 생성
    int result[MAX_COINS];
    clock_t start, end;

    // Greedy 실행 및 시간 측정
    start = clock();
    coinChangeGreedy(coins, k, amount, result);
    end = clock();
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;

    // 결과 출력
    printf("Amount: %d\n", amount);
    printf("Greedy Result: ");
    for (int i = 0; i < k; i++) {
        printf("%d원: %d개 ", coins[i], result[i]);
    }
    printf("\n");
    printf("Total Time: %f sec\n", executionTime);

    return 0;
}