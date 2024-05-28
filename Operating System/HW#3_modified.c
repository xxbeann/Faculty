#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int MSD[10] = {0,}, N = 1000000;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* worker(void *param) {
    int tmp, k;

    srand(time(NULL));
    while (1) {
        pthread_mutex_lock(&lock);
        if (N <= 0) {
            pthread_mutex_unlock(&lock);
            break;
        }
        N--;
        pthread_mutex_unlock(&lock);

        do { tmp = rand(); } while (tmp == 0);
        do { k = tmp % 10; tmp /= 10; } while (tmp > 0);
        MSD[k]++;

    }
}

int main()
{
	char *cha[4] = {"100", "200", "300", "400"};	/* 사용하지 않은 매개변수임 */
	int i, sum = 0;

	pthread_t tid[4];
	pthread_attr_t attr[4];
	
	for( i = 0; i < 4; i++) {
		pthread_attr_init(&attr[i]);
		pthread_create(&tid[i], &attr[i], worker, cha[i]);
		printf("worker 스레드가 생성되었습니다.\n");
	}
	for( i = 0; i < 4; i++) {
		pthread_join(tid[i], NULL);
		printf("worker 스레드가 종료하였습니다.\n");
	}
	for( i = 0; i < 10; i++) {
		printf("MSD[%d] = %d\n", i, MSD[i]);
		sum += MSD[i];
	}
	printf("전체 개수와 최종 합: %d, %d\n", N, sum);
	return 0;
}
