#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


// 제자리 선택정렬
// 가장 큰 값을 찾는 버전
// 큰 값을 찾아서 뒷 부분부터 정렬


void inPlaceSelectionSort(int* arr, int n) {

	for (int i = n - 1; i >= 1; i--) {  // n-1번 반복 n-1~1 까지 거꾸로
		int max = i;
		for (int j = 0; j < i; j++) { // 0~i-1까지 i와 비교
			if (arr[j] > arr[max]) {
				max = j;
			}
		}

		int temp = arr[i];
		arr[i] = arr[max];
		arr[max] = temp;

	}

}

int main() {
	int n, *arr;

	scanf("%d", &n);

	arr = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	inPlaceSelectionSort(arr, n); 

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

}

