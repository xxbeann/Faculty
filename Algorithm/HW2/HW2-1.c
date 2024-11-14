// 재귀를 이용한 풀이
#include <stdio.h>

void find_permutations(int n, int k, int start, int permutation[], int index, int *count) {

    if (n == 0) {
        printf("(");
        for (int i = 0; i < index; i++) {
            printf("%d", permutation[i]);
            if (i < index - 1) printf(",");
        }
        printf(")\n");
        (*count)++;
        return;
    }


    for (int i = start; i <= k; i++) {
        if (n >= i) {  
            permutation[index] = i;
            find_permutations(n - i, k, i, permutation, index + 1, count);
        }
    }
}

int main() {
    int n, k;
    printf("Input n and K (example: 10 3): ");
    scanf("%d %d", &n, &k);

    if (k >= n || k <= 2) {
        printf("Invalid input . n > k > 2 you should follow this condition.\n");
        return 1;
    }

    int permutation[1000000];
    int count = 0;

    printf("Permutation:\n");
    find_permutations(n, k, 1, permutation, 0, &count);

    printf("All count: %d\n", count);

    return 0;
}
