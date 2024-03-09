#include <stdio.h>

// Function to perform Bubble Sort and count the number of swaps
int bubbleSort(int arr[], int n, int *individualSwaps) {
    int i, j, temp, swaps = 0;
    // Outer loop iterates over the array elements
    for (i = 0; i < n - 1; i++) {
        // Inner loop iterates over the unsorted portion of the array
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
                (*individualSwaps)++;
                printf("%d: %d times %d is swapped\n", arr[j + 1], *individualSwaps, arr[j + 1]);
            }
        }
    }
    return swaps;
}

// Function to perform Selection Sort and count the number of swaps
int selectionSort(int arr[], int n, int *individualSwaps) {
    int i, j, minIndex, temp, swaps = 0;
    // Outer loop iterates over the array elements
    for (i = 0; i < n - 1; i++) {
        minIndex = i;
        // Inner loop finds the index of the minimum element in the unsorted portion of the array
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            // Swap arr[i] and arr[minIndex]
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            swaps++;
            (*individualSwaps)++;
            printf("%d: %d times %d is swapped\n", arr[minIndex], *individualSwaps, arr[minIndex]);
        }
    }
    return swaps;
}

int main() {
    int array1[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int array2[] = {90, 80, 70, 60, 50, 40, 30, 20, 10};
    int n1 = sizeof(array1) / sizeof(array1[0]);
    int n2 = sizeof(array2) / sizeof(array2[0]);

    printf("array1:\n");
    int totalSwaps1 = 0;
    // Iterate over each element of array1
    for (int i = 0; i < n1; i++) {
        int individualSwaps = 0;
        // Sort array1 starting from index i and count individual swaps
        totalSwaps1 += bubbleSort(array1, n1 - i, &individualSwaps);
    }
    printf("Total number of swaps: %d\n\n", totalSwaps1);

    printf("array2:\n");
    int totalSwaps2 = 0;
    // Sort the entire array2
    int individualSwaps2 = 0;
    totalSwaps2 += bubbleSort(array2, n2, &individualSwaps2);
    printf("Total number of swaps: %d\n\n", totalSwaps2);

    return 0;
}
