#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


// ��������
//���ڸ� (in place) ��������
/*
int main()
{
	int N, i, j, *arr, max, tmp;

	scanf("%d", &N);
	arr = (int*)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}


	for (i = N - 1; i > 0; i--) {
		max = i;
		for (j = i - 1; j >= 0; j--) {
			if (*(arr + j) > *(arr + max)) { 
				max = j;
			}
		}

		// �� ��ȯ ����
		tmp = *(arr + i);
		*(arr + i) = *(arr + max);
		*(arr + max) = tmp;
	}

	for (i = 0; i < N; i++) {
		printf(" %d", *(arr + i));
	}
	free(arr);
}
*/


// ���� Ǭ ��! 100��

/*
int main()
{
	int n, *arr, max;
	scanf("%d", &n);

	arr = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}



	for (int i = n-1; i > 0; i--) { // n-2 �� ����
		max = i; // key �� ����

		for (int j = i-1; j >= 0; j--) { // 0 ~ i-1 ���� �˻�
			if (arr[j] > arr[max])
				max = j; 
		}
		int tmp = arr[i];
		arr[i] = arr[max];
		arr[max] = tmp;
	}


	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	free(arr);
}
*/