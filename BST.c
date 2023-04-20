// 이진검색트리 예제 구현
// min값 찾는 findmin함수에서 오류남
//나중에 고치기
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node* left;
    struct Node* right;
}Node;

// 데이터 삽입
Node* Insert(Node* node, int value) {
    if(node == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode ->value = value;
        newNode ->left = NULL;
        newNode ->right = NULL; // 노드 생성 후 오른쪽 왼쪽 null로 만듦 < 자식이 없다는 말

        return newNode;
    }
    else {
        if (node ->value > value) { // 현재 노드의 값이 들어오는 값보다 큰 경우 : 왼쪽 자식에 삽입
            node -> left = Insert(node ->left, value); // 재귀로 구현
        }
        else if (node ->value < value) {// 현재 노드 값이 들어오는 값보다 작음 : 오른쪽 자식에 삽입
            node ->right = Insert(node->right, value);
        }
        else {} //중복된 데이터는 허용하지 않으므로 추가하지 않음
    }
    return node; //재귀를 위해 한 단계 위의 노드에 현재 노드 값을 리턴해줌
}

//void형인 이유 : 입력값으로 찾아서 수정만 하기 때문에 반환값이 필요하지 않음
// 데이터 수정
void Modify(Node* node, int value, int newValue) {
    if (node = NULL) return; // 함수 종료 : NULL일경우 데이터를 찾을 수 없음
    if (node ->value == value) { // 현재 노드의 데이터와 찾고자 하는 데이터가 같은 경우
        node -> value = newValue;
    }
    // 현재 노드 값이 더 클 경우
    else {
        if (node ->value > value) {
        // 왼쪽 자식 탐색 (재귀)
        Modify(node->left,value,newValue);
        }
    else {
        Modify(node->right, value, newValue);
        }
    }
}

//데이터 탐색
Node *Search(Node* node, int value) {
    if (node == NULL) return NULL; // 찾고자 하는 데이터가 없을 경우 NULL 반환
    if (node->value == value) {
        return node;
    }
    else {
        if (node->value > value) {
            //왼쪽 자식 탐색
            return Search(node->left, value);
        }
        else {
            return Search(node->right, value);
        }
    }
}

// 최소값을 찾는 함수
// 이진검색트리에서 제일 작은 값은 왼쪽 값임

// Node * FindMidNode(Node* node, Node** minNode) {
//     if (node->left == NULL) {
//         *minNode = node;
//         node = node -> right;
//         return node;
//     }
//     else {
//         node->left = FindMidNode(node->left, minNode);
//         return node;
//     }
// }

Node* FindMidNode(Node* node, Node** minNode) {
    if (node->left == NULL) {
        *minNode = NULL;
        return node;
    } else {
        Node* leftChild = node->left;
        while (leftChild->left != NULL) {
            node = leftChild;
            leftChild = node->left;
        }
        *minNode = node;
        return leftChild;
    }
}
// 데이터 삭제
// 1. 삭제할 데이터 탐색
// 2. case(자식 0, 1, 2)에 따라 삭제 구현
Node* Delete(Node* node, int target) {
    if (node == NULL) return NULL;
    if (node->value == target) { //현재 노드가 지울 값일 경우 // 2. start
    // case 1, 2, 3에 따라 삭제 구현
        Node* deleteNode = node; //삭제할 노드를 가리키는 포인터 변수 선언
        // case 1: 자식 노드가 없는 경우
        if (node->left == NULL && node->right == NULL) {
            node = NULL; //삭제해버림
        }
        // case 2: 자식 노드가 1개인 경우
        // 왼쪽만 있는 경우
        else if (node->left != NULL && node->right == NULL) {
            node = node->left; //연결되어있는 왼쪽 노드를 반환함
        }
        // 오른쪽만 있는 경우
        else if (node->left == NULL && node->right != NULL) {
            node = node->right; //오른쪽 반환함
        }
        // case 3 : 자식 노드가 2개인 경우 
        // 왼쪽에서 최댓값을 찾거나, 오른쪽에서 최소값을 찾아서 삭제할 노드와 자리를 교환함
        // 이 코드에서는 오른쪽 노드에서 최소값을 찾아서 교환하는 로직임
        else {
            Node* minNode = NULL; //minNode 초기화
            node->right = FindMidNode(node->right, &minNode); //오른쪽 노드에서 최소값을 찾음
            minNode->left = deleteNode->left; // 삭제할 노드의 왼쪽 자식의 주소값을 대체할 노드의 왼쪽 자식 포인터에 대입
            minNode->right = deleteNode->right; // 삭제할 노드의 오른쪽 자식의 주소값을 대체할 노드의 오른쪽 자식 포인터에 대입
            node = minNode; // minnode를 현재 노드로 만듦
        }
        free(deleteNode); // 메모리 해제
        return node;
    }
    else { // 1.
        if (node->value > target) { // 현재 노드가 삭제할 데이터보다 클 경우 > 왼쪽으로 탐색
            node->left = Delete(node ->left, target);
        }
        else { // 현재 노드가 삭제할 데이터(target)보다 작을 경우 > 오른쪽 자식 탐색
            node->right = Delete(node->right, target);
        }
        return node;
    }
}

// 중위 순회 : 왼 루트 오
void ShowInOrder(Node* node) {
    if (node == NULL) return;
    ShowInOrder(node->left);
    printf("%d", node->value);
    ShowInOrder(node->right);
}

void main() {
    Node* root = NULL; //루트 선언
    //INSERT
    root = Insert(root, 20);
    root = Insert(root, 10);
    root = Insert(root, 32);
    root = Insert(root, 4);
    root = Insert(root, 13);
    root = Insert(root, 25);
    root = Insert(root, 55);
    //               내부 구조
    //                  20
    //          10              32
    //      4       13      25      55

    ShowInOrder(root);
    //결과 : 4 10 13 20 25 32 55
    
    //MODIFY
    Modify(root, 10, 12);
    ShowInOrder(root);
    //결과 : 4 12 13 20 25 32 55

    //SEARCH
    printf("%d", Search(root, 12) ->value);
    //결과 : 12

    //DELETE
    root = Delete(root, 32);
    //               내부 구조
    //                  20
    //          10              55
    //      4       13      25      
    ShowInOrder(root);
    //결과 : 4 12 13 20 25 55
}