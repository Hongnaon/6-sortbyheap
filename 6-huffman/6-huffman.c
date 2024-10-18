#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool 타입 추가
#define MAX_ELEMENT 200

// 트리 노드 정의 구조체
typedef struct TreeNode {
    int weight;                 // 빈도수
    char ch;                    // 문자
    struct TreeNode* left;      // 왼쪽
    struct TreeNode* right;     // 오른쪽
} TreeNode;

// 힙 요소 정의 구조체
typedef struct {
    TreeNode* ptree;            // 트리 노드 포인터
    char ch;                    // 문자
    int key;                    // 힙 키 값 (빈도수)
} element;

// 합 정의 구조체
typedef struct {
    element heap[MAX_ELEMENT];  // 힙 배열
    int heap_size;              // 현재 힙 크기
} HeapType;

// 힙 생성
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}

// 힙 초기화
void init(HeapType* h) {
    h->heap_size = 0;
}

// 힙 출력
void print_heap(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// 최소 힙에 요소 추가
void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    // 최소 힙 구조 유지하며 삽입/
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// 요소 삭제
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1];                  // 루트 노드 추출
    temp = h->heap[(h->heap_size)--];   // 마지막 노드를 루트에 넣음
    parent = 1;
    child = 2;

    // 최소 힙 구조 유지하며 재배치
    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
            child++;
        if (temp.key < h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;

    return item;
}

// 우선순위 젤 높은 노드 합쳐서 트리 노드 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->left = left;
    node->right = right;
    return node;
}

// 트리 삭제 함수
void destroy_tree(TreeNode* root) {
    if (root == NULL) return;
    destroy_tree(root->left);  // 왼쪽 자식 없앰
    destroy_tree(root->right); // 오른쪽 자식 없앰
    free(root);
}

// 리프노드인지 확인
int is_leaf(TreeNode* root) {
    return !(root->left) && !(root->right);
}

// 베열 출력
void print_array(int codes[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// 허프만 트리에서 각 문자의 코드 출력
void printCodes(TreeNode* root, int arr[], int top) {
    if (root->left) { // 왼쪽
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) { // 오른쪽
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    if (is_leaf(root)) { // 리프노드면 문자, 코드 출력
        printf("%c: ", root->ch);
        print_array(arr, top);
    }
}

// 허프만 코드 생성
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    int i;
    TreeNode* node, * x;
    HeapType* heap;
    element e, e1, e2;
    int codes[100];                             // 코드 저장 배열
    int top = 0;

    // 중복 출력 방지
    bool first_print = true;

    heap = create();                            // 힙 생성
    init(heap);                                 // 초기화
    for (i = 0; i < size; i++) {
        node = make_tree(NULL, NULL);           // 새로운 리프 노드 생성
        e.ch = node->ch = characters[i];        // 문자 설정
        e.key = node->weight = frequencies[i];  // 빈도수 설정
        e.ptree = node;
        insert_min_heap(heap, e);               // 힙에 넣음

        // 각 삽입 후 힙 상태 출력
        print_heap(heap);
    }

    for (i = 1; i < size; i++) {
        e1 = delete_min_heap(heap);             // 최소 요소 삭제
        e2 = delete_min_heap(heap);             // 그다음 삭제
        x = make_tree(e1.ptree, e2.ptree);      // 합침
        e.key = x->weight = e1.key + e2.key;    // 빈도수 합침
        e.ptree = x;

        // 노드 결합하고 출력
        printf("///%d + %d -> %d\n", e1.key, e2.key, e.key);
        insert_min_heap(heap, e);               // 새로운 노드를 힙에 넣음

        // 힙 상태 출력 (중복 체크)
        if (first_print || heap->heap_size != 6) { // 크기가 6일 떄까찌만 출력
            print_heap(heap);
            first_print = false;                // 중복 출력 방지
        }
    }

    e = delete_min_heap(heap);                  // 최종 루트 추출
    printCodes(e.ptree, codes, top);            // 허프만 코드 출력
    destroy_tree(e.ptree);                      // 트리 메모리를 헤제
    free(heap);                                 // 힙 메모리를 ㅊ해제
}

int main(void) {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);

    GenerateHuffmanCodes(characters, frequencies, size);

    return 0;
}
