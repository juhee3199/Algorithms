#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void inPlaceSelectionSort(int* arr, int n) {

	for (int i = 0; i <= n - 2; i++) {  // n-1�� �ݺ�
		int min = i;
		for (int j = i + 1; j <= n - 1; j++) { // i+1���� ������������ ��
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

	for (int i = 1; i < n; i++) {  // n-1�� �ݺ�  
		save = arr[i];
		int j = i - 1;
		//pass �տ� �ִ� ������ ��(�ڿ��� ����)
		while ((j >= 0) && (arr[j] > save)) {
			arr[j + 1] = arr[j];
			j--;				// �ڿ������� ��
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
	

	//// A. ���� �� �� �����Ͱ� �־����� ���
	printf("A. ���� �� �� �����Ͱ� �־����� ��� \n");
	// ���� ����
	clock_t Astart = clock();
	inPlaceSelectionSort(a, n);
	printf("%0.5f\n", (float)(clock() - Astart) / CLOCKS_PER_SEC);

	// ���� ����
	clock_t Bstart = clock();
	inPlaceInsertSort(b, n);
	printf("%0.5f\n", (float)(clock() - Bstart) / CLOCKS_PER_SEC);

	
	//// B. �� ������ �Է����� ���ĵ� �����Ͱ� �־����� ���
	// A���� ���ĵ� �迭�� �Էµ����ͷ� ���
	printf("B. �� ������ �Է����� ���ĵ� �����Ͱ� �־����� ��� \n");
	// ���� ����
	Astart = clock();
	inPlaceSelectionSort(a, n);
	printf("%0.5f\n", (float)(clock() - Astart) / CLOCKS_PER_SEC);

	// ���� ����
	Bstart = clock();
	inPlaceInsertSort(b, n);
	printf("%0.5f\n", (float)(clock() - Bstart) / CLOCKS_PER_SEC);



	//// C. �� ������ �Է����� �������� ���ĵ� �����Ͱ� �־����� ���
	// B���� ���ĵ� �迭�� �������� �����Ͽ� ���
	printf("C. �� ������ �Է����� �������� ���ĵ� �����Ͱ� �־����� ��� \n");
	for (int i = 0; i < n; i++) {
		int tmp = a[i];
		a[i] = a[n - 1 - i];
		a[n - 1 - i] = tmp;

		tmp = b[i];
		b[i] = b[n - 1 - i];
		b[n - 1 - i] = tmp;
	}

	// ���� ����
	Astart = clock();
	inPlaceSelectionSort(a, n);
	printf("%0.5f\n", (float)(clock() - Astart) / CLOCKS_PER_SEC);

	// ���� ����
	Bstart = clock();
	inPlaceInsertSort(b, n);
	printf("%0.5f\n", (float)(clock() - Bstart) / CLOCKS_PER_SEC);
}

