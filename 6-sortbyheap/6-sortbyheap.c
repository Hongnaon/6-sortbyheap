#include <stdio.h>
#include <stdlib.h>

// 두 숫자 값 교환
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 힙 재정렬
void resortHeap(int inputData[], int n, int i) {

    int large = i;              // 현재 노드 가장 큰 값으로 가정
    int left = 2 * i + 1;       // 왼쪽 자식 노드 인덱스
    int right = 2 * i + 2;      // 오른쪽 자식 노드 인덱스

    // 왼쪽 자식 있고 값이 부모보다 클 때
    if (left < n && inputData[left] > inputData[large]) {
        large = left;
    }

    // 오른쪽 자식 있고 값이 지금 가장 큰 값보다 클 때
    if (right < n && inputData[right] > inputData[large]) {
        large = right;
    }

    // 가장 큰 값이 부모 노드가 아닐 때, 부모랑 교환 후 재정렬
    if (large != i) {
        swap(&inputData[i], &inputData[large]);
        resortHeap(inputData, n, large);
    }
}

// 배열을 최대 힙으로 만듦
void BuildMaxHeap(int inputData[], int size) {

    for (int i = size / 2 - 1; i >= 0; i--) {
        resortHeap(inputData, size, i);
    }
}

// 최대 힙 구축, 정렬 과정  출력
void BuildMaxHeapAndSort(int inputData[], int n) {

    // 1~n 증가하면서 배열 최대 힙으로 만들고 중간 결과를 출력 
    for (int i = 1; i <= n; i++) {
        BuildMaxHeap(inputData, i); // i 길이만큼 최대 힝ㅂ으로 변환

        // 각 단계에서 힙 현재 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }

    // 최대 힙을 이용한 힙 정렬 과정
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);     // 루트와 마지막 노드 교환
        resortHeap(inputData, i, 0);            // 교환 후 다시 정렬

        // 교환 후 힙 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}


//==============================================================================


int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}

