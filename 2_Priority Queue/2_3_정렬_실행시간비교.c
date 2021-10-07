#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void inPlaceSelectionSort(int* arr, int n) {

	for (int i = 0; i <= n - 2; i++) {  // n-1번 반복
		int min = i;
		for (int j = i + 1; j <= n - 1; j++) { // i+1부터 마지막노드까지 비교
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}

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
		arr[j + 1] = save;
	}
}

int main() {
	int  n, *a, *b;

	scanf("%d", &n);

	a = (int*)malloc(n * sizeof(int));
	b = (int*)malloc(n * sizeof(int));

	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		a[i] = rand() % 100;
		b[i] = rand() % 100;
	}

	//for (int i = 0; i < n; i++) {
	//	printf(" %d", a[i]);
	//}
	//printf("\n");
	//for (int i = 0; i < n; i++) {
	//	printf(" %d", b[i]);
	//}
	//printf("\n");
	

	//// A. 정렬 안 된 데이터가 주어지는 경우
	printf("A. 정렬 안 된 데이터가 주어지는 경우 \n");
	// 선택 정렬
	clock_t Astart = clock();
	inPlaceSelectionSort(a, n);
	printf("%0.5f\n", (float)(clock() - Astart) / CLOCKS_PER_SEC);

	// 삽입 정렬
	clock_t Bstart = clock();
	inPlaceInsertSort(b, n);
	printf("%0.5f\n", (float)(clock() - Bstart) / CLOCKS_PER_SEC);

	
	//// B. 각 정렬의 입력으로 정렬된 데이터가 주어지는 경우
	// A에서 정렬된 배열을 입력데이터로 사용
	printf("B. 각 정렬의 입력으로 정렬된 데이터가 주어지는 경우 \n");
	// 선택 정렬
	Astart = clock();
	inPlaceSelectionSort(a, n);
	printf("%0.5f\n", (float)(clock() - Astart) / CLOCKS_PER_SEC);

	// 삽입 정렬
	Bstart = clock();
	inPlaceInsertSort(b, n);
	printf("%0.5f\n", (float)(clock() - Bstart) / CLOCKS_PER_SEC);



	//// C. 각 정렬의 입력으로 역순으로 정렬된 데이터가 주어지는 경우
	// B에서 정렬된 배열을 역순으로 정렬하여 사용
	printf("C. 각 정렬의 입력으로 역순으로 정렬된 데이터가 주어지는 경우 \n");
	for (int i = 0; i < n; i++) {
		int tmp = a[i];
		a[i] = a[n - 1 - i];
		a[n - 1 - i] = tmp;

		tmp = b[i];
		b[i] = b[n - 1 - i];
		b[n - 1 - i] = tmp;
	}

	// 선택 정렬
	Astart = clock();
	inPlaceSelectionSort(a, n);
	printf("%0.5f\n", (float)(clock() - Astart) / CLOCKS_PER_SEC);

	// 삽입 정렬
	Bstart = clock();
	inPlaceInsertSort(b, n);
	printf("%0.5f\n", (float)(clock() - Bstart) / CLOCKS_PER_SEC);
}

