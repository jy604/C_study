// 트리 순회 예제 실습
#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

// 배열을 트리 구조로 변경
typedef struct tree
{
    int value; // 값
    struct tree* left; // 왼쪽 자식 주소
    struct tree* right; // 오른쪽 자식 주소
} tree;

tree* setBinTree(int* arr, int size, int index) {
    int leftIdx, rightIndex;
    tree* newNode;

    newNode = (tree*)malloc(sizeof(tree));
    newNode ->value = arr[index];
    newNode ->left = newNode->right = NULL;
    // 각 노드가 최대 2개의 자식을 가지기 때문에 부모 노드 인덱스에 2를 곱함
    // +1은 배열이 0부터 시작하기때문에 왼쪽 자식 노드의 인덱스가 부모의 인덱스보다
    // 1이 더 커지기 위해서 보정하는 것
    leftIdx = 2 * index + 1; //왼쪽 자식의 인댁스
    rightIndex = leftIdx + 1;

    if (leftIdx < size) // 재귀호출 종료 조건
        newNode ->left = setBinTree(arr, size, leftIdx);

    if (rightIndex < size)
        newNode ->right = setBinTree(arr, size, rightIndex);

    return newNode;
}

// 중위 순회 출력 함수 왼쪽-루트-오른쪽
void displayInorder(tree* t) {
    if (t != NULL) {
        displayInorder(t->left);
        printf("%d", t->value);
        displayInorder(t->right);
    }
}

// 전위 순회 출력 함수 루트-왼쪽-오른쪽
void displaypreorder(tree* t) {
    if (t != NULL) {
        printf("%d", t->value);
        displaypreorder(t->left);
        displaypreorder(t->right);
    }
}


// 후위 순회 출력 함수 왼 오 루
void displaypostorder(tree* t) {
    if (t != NULL) {
        displaypostorder(t->left);
        displaypostorder(t->right);
        printf("%d", t->value);
    }
}

tree* memoryFree(tree* t) {
    // 후위 순회로 데이터를 제거
    // 후위 순회로 하는 이유 : 후위 순회는 자식을 먼저 제거하고 루트를 제거하기때문에
    // 메모리 누수를 막을 수 있음, 그러나 전위 순회로 제거할 경우, 전위 순회는
    // 부모를 먼저 제거하기때문에 부모가 사라지고 난 후에도 자식이 남아있어
    // 메모리 누수가 생길 수 있음, 후위나 중위로 지우기를 권장
    if (t != NULL) {
        memoryFree(t->left);
        memoryFree(t->right);
        printf("%d노드 제거\n", t->value);
        free(t);
    }
    return NULL;
}

//이진 트리의 노드 개수를 세는 함수
int getNodeCount(tree* t) {
    if (t != NULL) 
        return 1 + getNodeCount(t->left) + getNodeCount(t->right); //후위순회 방식
    return 0;
}

int main() {
    int count;
    int arr[] = {6, 4, 8, 2, 5, 7, 9, 1, 3};

    tree* root = NULL; // 트리의 시작 노드의 주소를 저장
    // setBinTree : 트리 구성 후 루트의 주소를 리턴
    root = setBinTree(arr, 9, 0); // 배열 주소, 배열의 크기, 루트 노드의 인덱스

    printf("tree inorder : ");
    displayInorder(root); //중위 순회 출력
    puts("");

    printf("tree preorder : ");
    displaypreorder(root); //전위 순회 출력
    puts("") ;

    printf("tree postorder : ");
    displaypostorder(root); //후회 순회 출력
    puts("");

    count = getNodeCount(root);
    printf("전체 노드의 개수는 %d개 입니다.\n", count);

    root = memoryFree(root);

    return 0;
}

// output
// tree inorder : 123456789
// tree preorder : 612345789
// tree postorder : 123457896
// 전체 노드의 개수는 9개 입니다.
// 1노드 제거
// 3노드 제거
// 2노드 제거
// 5노드 제거
// 4노드 제거
// 7노드 제거
// 9노드 제거
// 8노드 제거
// 6노드 제거