#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


// ���ڸ� ��������
// ���� ū ���� ã�� ����
// ū ���� ã�Ƽ� �� �κк��� ����


void inPlaceSelectionSort(int* arr, int n) {

	for (int i = n - 1; i >= 1; i--) {  // n-1�� �ݺ� n-1~1 ���� �Ųٷ�
		int max = i;
		for (int j = 0; j < i; j++) { // 0~i-1���� i�� ��
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

