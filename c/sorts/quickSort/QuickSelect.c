#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 파일에서 숫자를 읽어와 배열로 반환하는 함수
int* readNumbersFromFile(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다!\n");
        return NULL;
    }

    int* numbers = NULL;
    int num;
    *size = 0;
    int capacity = 10; // 초기 용량 설정
    numbers = (int*)malloc(capacity * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "메모리 할당 실패!\n");
        fclose(file);
        return NULL;
    }

    // 파일에서 숫자를 읽어 배열에 저장
    while (fscanf(file, "%d", &num) == 1) {
        if (*size >= capacity) {
            capacity *= 2; // 용량 두 배로 증가
            numbers = (int*)realloc(numbers, capacity * sizeof(int));
            if (numbers == NULL) {
                fprintf(stderr, "메모리 할당 실패!\n");
                fclose(file);
                return NULL;
            }
        }
        numbers[*size] = num;
        (*size)++;
    }
    
    fclose(file);
    return numbers;
}

// 배열을 파일에 쓰는 함수 (현재 사용되지 않음)
void writeArrayToFile(const char* filename, int* arr, int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "파일을 열 수 없습니다!\n");
        return;
    }

    // 배열의 모든 요소를 파일에 저장
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}

// 배열의 두 요소를 교환하는 함수
void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// 배열을 분할하여 피벗의 위치를 찾는 함수 (퀵 셀렉션과 퀵 정렬에 사용)
int partition(int *arr, int first, int r) {
    int mid = (first + r) / 2;
    int pivot = arr[mid];
    int l = first + 1;

    swap(arr, first, mid); // 피벗을 배열의 처음으로 이동
    while (l <= r) {
        while (l <= r && arr[l] < pivot) l++;  // 피벗보다 작은 요소 탐색
        while (l <= r && arr[r] > pivot) r--;  // 피벗보다 큰 요소 탐색

        if (l < r) {
            swap(arr, l, r);  // 두 요소 교환
            l++;
            r--;
        }
    }
    swap(arr, first, r);  // 피벗을 제자리로 이동
    return r;
}

// 퀵 셀렉션을 사용하여 배열의 k번째 작은 수를 찾는 함수
void quickSelect(int* arr, int l, int r, int k) {
    int pivot = partition(arr, l, r);
    int s_len = pivot - l;

    if (k <= s_len) quickSelect(arr, l, pivot - 1, k);  // 왼쪽 부분에서 찾기
    else if (k > s_len + 1) quickSelect(arr, pivot + 1, r, k - s_len - 1);  // 오른쪽 부분에서 찾기
}

int main(int argc, const char *argv[]) {
    int size;
    clock_t start, end;

    // 파일에서 숫자를 읽어옴
    int* arr = readNumbersFromFile("../input_sort.txt", &size);
    if (arr == NULL || size == 0) {
        return 1;  // 파일이 비어 있거나 읽기 실패
    }

    // 50번째 요소 선택 (퀵 셀렉션 사용)
    start = clock();
    quickSelect(arr, 0, size - 1, 50);
    end = clock();
    printf("50번째 소요 시간: %lf ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000.0);

    // 70번째 요소 선택 (퀵 셀렉션 사용)
    start = clock();
    quickSelect(arr, 0, size - 1, 70);
    end = clock();
    printf("70번째 소요 시간: %lf ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000.0);

    // 50번째와 70번째 요소 출력
    printf("50번째 : %d\n", arr[49]);
    printf("70번째 : %d\n", arr[69]);

    free(arr);  // 동적 메모리 해제
    return 0;
}
