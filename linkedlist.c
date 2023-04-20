#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element; //define과 같이 renaming하는 용도, 이식성과 수정효율성을 높여줌

typedef struct ListNode // 노드 타입을 구조체로 정의
{
    element data; // 데이터 필드
    struct ListNode* link; // 링크 필드 - 포인터로 사용 : next
}ListNode;

// 노드 삽입
ListNode* insert_first(ListNode* head, int value)
{
    ListNode* p = (ListNode*) malloc(sizeof(ListNode)); // 동적 할당
    p -> data = value;
    p -> link = head;
    head = p;
    return head;
}
// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p-> data = value;
    p -> link = pre -> link;
    pre -> link = p;
    return head;
}

//(1) 노드 마지막에 새로운 노드 삽입하는 함수
ListNode* insert_last(ListNode* head, int value) { //value값 원래는 var 타입이나, 오류로 int로 선언
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p ->data = value;
    if (head == NULL) {
        p ->link = head;
        head = p;
    }
    else {
        ListNode* q = head;
        while (q ->link != NULL) { q = q->link;}
        p ->link = q ->link;
        q ->link = p;
    }
    return head;
}

// (1)을 이용해 데이터 값이 오름차순으로 정렬된 두 단순 연결리스트를 병합하는 함수
ListNode* merge(ListNode* list1, ListNode* list2) {
    ListNode* result = NULL;
    ListNode* p1 = list1, *p2 = list2;
    if (p1 == NULL) return list2;
    if (p2 == NULL) return list1;
    while (p1 != NULL && p2 != NULL) {
        if (p1 ->data < p2 ->data) {
            result = insert_last(result, p1->data);
            p1 = p1->link;
        }
        else {
            result = insert_last(result, p2->data);
            p2 = p2 ->link;
        }
    }
    while (p1 != NULL) {
        result = insert_last(result, p1->data);
        p1 = p1->link;
    }
    while (p2 != NULL) {
        result = insert_last(result, p2->data);
        p2 = p2->link;
    }
    return result;
}

// 주어진 단순 연결 리스트에서 데이터 값이 홀수인 노드를 추출해서 새로운 연결리스트로 반환하는 함수
ListNode* odd_extract(ListNode* list) {
    ListNode* oddList = NULL;
    ListNode* p;
    for (p = list; p != NULL; p = p ->link) {
        if(p->data % 2 != 0) {// 홀수 판별
        oddList = insert_first(oddList, p->data);
        p = p ->link;
        }
    }
    return oddList;
}
// 앞부분의 노드 제거
ListNode* delete_first(ListNode* head)
{
    ListNode* removed; //지워질 노드를 가리키는 포인터 : old
    if (head == NULL) return NULL;
    removed = head; // head와 같은 노드를 가리키게 함
    head = removed->link; // head를 다음 노드로 옮김
    free(removed); // removed가 가리키는 노드 (원래는 head였던 노드) 삭제
    return head;
}

//pre가 가리키는 노드의 다음 노드를 삭제
ListNode* delete(ListNode* head, ListNode* pre)
{
    ListNode* removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

// 리스트 출력
void print_list(ListNode* head)
{
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL \n");
}
// 리스트 검색
ListNode* search_list(ListNode *head, element x) {
    ListNode *p = head;

    while(p != NULL) {
        if ( p -> data == x) return p;
        p = p -> link;
    }
    return NULL; // 탐색 실패
}

// 두 리스트를 연결하는 알고리즘
ListNode* concat_list(ListNode *head1, ListNode *head2) {
    if (head1 == NULL) return head2;
    else if (head2 == NULL) return head1;
    else {
        ListNode *p;
        p = head1;
        while (p -> link != NULL)
        {
            p = p->link;
        p ->link = head2;
        return head1;
        }
        
    }
}

// 리스트 역순회
// 10 > 20 > 30 > 40
// 10 < 20 < 30 < 40
ListNode* resverse(ListNode *head) {
    // 순회 포인터로 p, q, r을 사용
    ListNode *p, *q, *r;

    p = head; //p는 역순으로 만들 리스트
    q = NULL; //q는 역순으로 만들 노드
    while (p != NULL)
    {
        r = q; // r은 역순으로 된 리스트
        q = p;
        p = p ->link;
        q ->link = r; //q의 링크 방향을 바꾼다
    }
    return q;
    
}

// 단순연결리스트의 노드의 개수 구하는 함수
int get_length(ListNode* head) {
    int count = 0;
    for (ListNode* p = head; p != NULL; p = p ->link)
        count++;
    return count;
}

// 단순연결리스트의 노드의 데이터 값의 합을 구하는 함수
int get_sum(ListNode* head) {
    int sum = 0;
    for (ListNode* p = head; p != NULL; p = p->link)
        sum += p ->data;
    return sum;
}

// 노드의 데이터 값 중 최대값을 구하는 함수
int get_max(ListNode* head) {
    int maxNum = -32767; // INT_MIN
    for (ListNode* p = head; p != NULL; p = p ->link) {
        if (p ->data > maxNum)
            maxNum = p->data;
    }
    return maxNum;
}

// 특정한 데이터 값을 갖는 노드의 개수를 구하는 함수
int count(ListNode* head, int value) {
    int count = 0;
    for (ListNode* p = head; p != NULL; p = p ->link) {
        if (p ->data == value)
            count++;
    }
    return count;
}

// 특정 데이터 값을 갖는 노드를 삭제하는 함수
ListNode* delete_node(ListNode* head, int value) {
    ListNode* pre = NULL;

    for (ListNode *p = head; p != NULL; pre = p, p = p ->link) {
        if (p ->data == value) {
            if (p == head) {
                ListNode* removed = head;
                head = head -> link;
                free(removed);
                p = head; // 댓글에서 말한 부분
            }
            else {
                pre ->link = p ->link;
                free(p);
                p = pre;
            }
        }
    }
    return head;
}



int main() {
    ListNode *head = NULL;

    // for (int i = 0; i < 5; i++) {
    //     head = insert_first(head, i );
    //     print_list(head);
    // }
    // for (int i = 0; i < 5; i++) {
    //     head = delete_first(head);
    //     print_list(head);
    // }

    head = insert_first(head, 10);
    print_list(head);
    head = insert_first(head, 20);
    print_list(head);
    head = insert_first(head, 30);
    print_list(head);
    if (search_list(head, 30) != NULL)
        printf("리스트에서 30을 찾았습니다. \n");
    else
        printf("리스트에서 30을 찾지 못했습니다. \n");

    return 0;
}
//output
// 0->NULL 
// 1->0->NULL 
// 2->1->0->NULL 
// 3->2->1->0->NULL 
// 4->3->2->1->0->NULL 
// 3->2->1->0->NULL 
// 2->1->0->NULL 
// 1->0->NULL 
// 0->NULL 
// NULL 
