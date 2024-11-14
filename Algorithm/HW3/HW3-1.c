#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(long *a, long *b) {
        long temp = *a;
        *a = *b;
        *b = temp;
}

void maxHeapify(long arr[], int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if(left < n && arr[left] > arr[largest])
                largest = left;

        if(right < n && arr[right] > arr[largest])
                largest = right;

        if(largest != i) {
                swap(&arr[i], &arr[largest]);
                maxHeapify(arr, n, largest);
        }
}

void buildMaxHeap(long arr[], int n){
        for(int i=n/2-1; i>=0; i--)
                maxHeapify(arr, n, i);
}

long getMax(long arr[], int *n) {
        if(*n <= 0)
                return -1;

        long root = arr[0];
        arr[0] = arr[*n-1];
        (*n)--;
        maxHeapify(arr, *n, 0);

        return root;
}

int main() {
        int n, k;

        printf("Enter n (n >= 100000): ");
        scanf("%d", &n);
        printf("Enter k: ");
        scanf("%d", &k);

        srand(time(NULL));
        long *data = malloc(n * sizeof(long));

        for(int i=0; i<n; i++){
                data[i] = rand()%2147483647;
        }

        clock_t start = clock();

        buildMaxHeap(data, n);


        int heapSize = n;
        for(int i=0; i<k; i++){
                printf("%ld ", getMax(data, &heapSize));
        }

        clock_t end = clock();
        double time_result = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("\n Time Result: %f seconds\n", time_result);

        free(data);
        return 0;
}
                              