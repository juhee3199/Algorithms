#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 제자리 삽입 정렬

void inPlaceInsertSort(int* arr, int n) {
	int save;

	for (int i = 1; i < n; i++) {  // n-1번 반복  
		save = arr[i];
		int j = i - 1;
		//pass 앞에 있는 값들을 비교(뒤에서 부터)
		while ((j >= 0) && (arr[j] > save)) {
			arr[j + 1] = arr[j];
			j--;				// 뒤에서부터 비교
		}
		arr[j+1] = save;
	}
}

int main() {
	int n, *arr;
	scanf("%d", &n);

	arr = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	inPlaceInsertSort(arr, n);

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
}

