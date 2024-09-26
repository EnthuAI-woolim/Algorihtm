#include <assert.h>
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
    int capacity = 10; // 초기 배열 크기 설정
    numbers = (int*)malloc(capacity * sizeof(int));
    if (numbers == NULL) {
        fprintf(stderr, "메모리 할당 실패!\n");
        fclose(file);
        return NULL;
    }

    // 파일에서 숫자를 읽어서 배열에 저장
    while (fscanf(file, "%d", &num) == 1) {
        if (*size >= capacity) {
            capacity *= 2; // 배열 크기 두 배로 확장
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

// 배열을 파일에 쓰는 함수
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

// 두 정수를 교환하는 함수
void swap(int *first, int *second) {
    int temp = *first;
    *first = *second;
    *second = temp;
}

// 선택 정렬 알고리즘 구현
void selectionSort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i; // 현재 최소값의 인덱스
        for (int j = i + 1; j < size; j++) {
            if (arr[min_index] > arr[j]) {
                min_index = j; // 새로운 최소값 발견
            }
        }
        if (min_index != i) {
            swap(arr + i, arr + min_index); // 최소값을 제자리로 이동
        }
    }
}

int main(int argc, const char *argv[]) {
    int size;
    clock_t start, end;

    // 파일에서 숫자를 읽어옴
    int* arr = readNumbersFromFile("../input_sort.txt", &size);
    if (arr == NULL || size == 0) {
        return 1; // 파일이 비어 있거나 읽기 실패
    }

    // 선택 정렬 실행 시간 측정
    start = clock();
    selectionSort(arr, size);
    end = clock();

    // 소요 시간 출력 (밀리초 단위)
    printf("MS : %lf\n", (double)(end - start) / CLOCKS_PER_SEC * 1000.0);

    // 정렬된 배열을 파일로 출력
    writeArrayToFile("../output_selection_sort.txt", arr, size);

    // 50번째와 70번째 요소 출력
    printf("50번째 : %d\n", arr[49]);
    printf("70번째 : %d\n", arr[69]);

    // 동적 메모리 해제
    free(arr); 
    return 0;
}
