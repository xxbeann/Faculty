#include <stdio.h>
#include <stdlib.h>

// Function to maintain the heap property
void heapify(int arr[], int n, int i) {
    int largest = i;    // Initialize largest as root
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Function to build a max heap from the array
void buildMaxHeap(int arr[], int n) {
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Function to print the array (to display the Max-Heap)
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to perform heap sort
void heapSort(int arr[], int n) {
    // Build max heap (rearrange array)
    buildMaxHeap(arr, n);

    // Print the Max-Heap
    printf("Max-Heap: ");
    printArray(arr, n);

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to the end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    int n;

    // Input the size of the array
    printf("Enter the number of elements to sort: ");
    scanf("%d", &n);

    // Input the array elements
    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Perform heap sort
    heapSort(arr, n);

    // Print the sorted array
    printf("Sorted array: ");
    printArray(arr, n);

    // Free the dynamically allocated memory
    free(arr);

    return 0;
}
