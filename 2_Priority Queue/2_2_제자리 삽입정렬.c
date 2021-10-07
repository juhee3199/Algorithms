#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ���ڸ� ���� ����

void inPlaceInsertSort(int* arr, int n) {
	int save;

	for (int i = 1; i < n; i++) {  // n-1�� �ݺ�  
		save = arr[i];
		int j = i - 1;
		//pass �տ� �ִ� ������ ��(�ڿ��� ����)
		while ((j >= 0) && (arr[j] > save)) {
			arr[j + 1] = arr[j];
			j--;				// �ڿ������� ��
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

