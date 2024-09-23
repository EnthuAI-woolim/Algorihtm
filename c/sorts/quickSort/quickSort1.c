#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int array[], int left, int right) {
    int mid = (left + right) / 2; // 중간 인덱스
    int pivot = array[mid]; // 피벗 값

    while (left <= right) {
        while (array[left] < pivot) {
            left++;
        }
        while (array[right] > pivot) {
            right--;
        }
        if (left <= right) {
            swap(&array[left], &array[right]);
            left++;
            right--;
        }
    }
    return left;
}

void quickSort(int array[], int left, int right) {
    if (left < right) {
        int pivotIdx = partition(array, left, right);
        quickSort(array, left, pivotIdx - 1);
        quickSort(array, pivotIdx, right);
    }
}

int main() {
    clock_t start, end;
    // 예시로 사용할 배열
    int array[] = {2, 5, 7, 6, 1, 8, 9, 3, 4, 10};
    int size = sizeof(array) / sizeof(array[0]);

    // 시간 측정 시작
    start = clock();
    quickSort(array, 0, size-1);
    end = clock();

    // 정렬된 배열 출력
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // 시간 출력
    printf("MS : %lf\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);
    
    return 0;
}
