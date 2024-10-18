#include <stdio.h>
#include <stdlib.h>

// �� ���� �� ��ȯ
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �� ������
void resortHeap(int inputData[], int n, int i) {

    int large = i;              // ���� ��� ���� ū ������ ����
    int left = 2 * i + 1;       // ���� �ڽ� ��� �ε���
    int right = 2 * i + 2;      // ������ �ڽ� ��� �ε���

    // ���� �ڽ� �ְ� ���� �θ𺸴� Ŭ ��
    if (left < n && inputData[left] > inputData[large]) {
        large = left;
    }

    // ������ �ڽ� �ְ� ���� ���� ���� ū ������ Ŭ ��
    if (right < n && inputData[right] > inputData[large]) {
        large = right;
    }

    // ���� ū ���� �θ� ��尡 �ƴ� ��, �θ�� ��ȯ �� ������
    if (large != i) {
        swap(&inputData[i], &inputData[large]);
        resortHeap(inputData, n, large);
    }
}

// �迭�� �ִ� ������ ����
void BuildMaxHeap(int inputData[], int size) {

    for (int i = size / 2 - 1; i >= 0; i--) {
        resortHeap(inputData, size, i);
    }
}

// �ִ� �� ����, ���� ����  ���
void BuildMaxHeapAndSort(int inputData[], int n) {

    // 1~n �����ϸ鼭 �迭 �ִ� ������ ����� �߰� ����� ��� 
    for (int i = 1; i <= n; i++) {
        BuildMaxHeap(inputData, i); // i ���̸�ŭ �ִ� �������� ��ȯ

        // �� �ܰ迡�� �� ���� ���� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }

    // �ִ� ���� �̿��� �� ���� ����
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);     // ��Ʈ�� ������ ��� ��ȯ
        resortHeap(inputData, i, 0);            // ��ȯ �� �ٽ� ����

        // ��ȯ �� �� ���� ���
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

    // �� ���� ����
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // ���ĵ� ��� ���
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}

