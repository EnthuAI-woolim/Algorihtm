#include <time.h>
#include <stdio.h>

void swap(int* a, int* b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int A[], int l, int r) {
    int pivot, i, j;
    pivot = A[r];
    i = l - 1;
    for(j = l; j <= r-1; j++) {
        if(A[j] <= pivot) {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i+1], &A[r]);
    return i+1;
}

void quickSort(int A[], int l, int r) {
    if (l < r) {
        int pivotIdx = partition(A, l, r);
        quickSort(A, l, pivotIdx-1);
        quickSort(A, pivotIdx+1, r);
    }
}

int main() {
    clock_t start, end;
    int array[] = {2, 5, 7, 6, 1, 8, 9, 3, 4, 10};
    int size = sizeof(array) / sizeof(array[0]);

    start = clock();
    quickSort(array, 0, size-1);
    end = clock();

    // 정렬된 배열 출력
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("MS : %lf\n", (double)(end - start)/CLOCKS_PER_SEC*1000);
    
    return 0;
}