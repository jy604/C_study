#include <stdio.h>
#include <stdlib.h>

// void* malloc(size_t size) // malloc 함수 원형
// free(void* ptr) // free함수 원형
// void* calloc(size_t elt_count, size_t elt_size) // calloc 함수 원형
// void* realloc(void* memblock, size_t size); // realloc 함수 원형
int main() {
    int arr1[5]; // 배열 선언
    int *arr2; // 포인터 변수 선언
    
    for(int i = 0; i < 5; i++) {
        arr1[i] = i + 1; // 배열에 값 대입 
    }

    // arr2 = (int *) malloc(sizeof(int)*5); // 메모리 할당, 배열의 크기만큼 할당하기 위해 5를 곱함
    // arr2 = (int *) calloc(5, sizeof(int)); // size(int) 크기의 변수를 5개 저장할 수 있는 공간 할당
    arr2 = (int *) realloc(arr2, sizeof(int)*10); //arr2의 메모리를 40바이트로 할당
    
    for(int i = 0; i < 5; i++) {
        arr2[i] = arr1[i];
        printf("%d", arr2[i]);
    }

    free(arr2); //free함수를 사용해서 메모리 해제
    return 0;
}