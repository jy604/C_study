#include <stdio.h>

int main() {
    int *ptr; // 포인터 변수 선언
    int x; // 변수 선언

    ptr = &x; // ptr 포인터가 변수 x의 주소값으로 초기화
    // *ptr = &x; 포인터 변수 선언과 초기화 동시에 
    *ptr = 0; // &x에 저장된 데이터를 0으로 수정 쓰레기 값 > 0

    printf(" x = %d\n", x); // x = 0
    printf(" *ptr = %d\n", *ptr); // *ptr은 x와 동일, 따라서 *ptr = 0
    // ptr은 &x와 같다
    // *ptr은 x와 같다
    *ptr += 5; //(*ptr)++를 5번 한 것
    printf(" x = %d\n", x); // x = 5
    printf(" *ptr = %d\n", *ptr); // ptr = 5

    (*ptr)++; //*ptr로 들어가서 들어가있는 값 증가 후 반환 
    printf(" x = %d\n", x); // x = 6
    printf(" *ptr = %d\n", *ptr); //*ptr = x의 값, *ptr = 6

    return 0;
}