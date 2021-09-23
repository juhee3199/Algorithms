#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/*
int main()
{
	int N, *arr, i, j, tmp;
	scanf("%d", &N);
	arr = (int*)malloc(sizeof(int)*N);
	for (i = 0; i < N; i++) {
		scanf("%d", arr + i);
	}

	for (i = 1; i < N; i++) {
		tmp = *(arr + i);
		j = i - 1;
		while ((j >= 0) && (*(arr + j) > tmp)) {
			*(arr + j + 1) = *(arr + j);
			j--;
		}
		*(arr + j + 1) = tmp;
	}

	for (i = 0; i < N; i++) {
		printf(" %d", *(arr + i));
	}
	free(arr);
}
*/


// ³»°¡ Ç¬ °Í! 100Á¡!
/*
int main()
{
	int n, *arr, save;
	scanf("%d", &n);

	arr = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	for (int i = 1; i < n; i++) {  // 1~n-1
		save = i;
		int tmp = arr[save];
		int j = i - 1;

		while ((j >= 0) && (arr[j] > tmp)) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j+1] = tmp;
	}

	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}

	free(arr);
}
*/