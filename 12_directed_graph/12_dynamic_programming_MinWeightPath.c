#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define N 100
#define min(x, y) ((x)<(y) ? (x) : (y))  

int minArr[N][N]; //�ּ� ��ȭ��

// �������α׷���(������) ���� ����
int sinsity(int A[][8], int n) {
	int i, j, minright, mindown, cost;

	minArr[0][0] = A[0][0]; // �ʱ�ȭ

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {

			if ((i == 0) && (j == 0)) {
				continue;
			}

			minright = 10000;
			for (int k = j - 1; k >= 0; k--) {
				cost = minArr[i][k] + A[i][j];
				minright = min(minright, cost);
			}

			mindown = 10000;
			for (int k = i - 1; k >= 0; k--) {
				cost = minArr[k][j] + A[i][j];
				mindown = min(mindown, cost);
			}

			minArr[i][j] = min(minright, mindown);
		}
	}
	return minArr[n - 1][n - 1];
}

void print(int A[][8], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%02d ", minArr[i][j]);
		}
		printf("\n");
	}
}
int main() {
	int n = 8;

	// 2���� �迭 ����
	int A[8][8]= {
	   { 1, 3, 7, 2, 11, 17, 16, 25},
	   {6, 2, 3, 4, 7, 2, 12, 15},
	   {11, 4, 6, 8, 8, 1, 9, 14},
	   {20, 8, 8, 11, 6, 3, 3, 9},
	   {0, 10, 9, 8, 7, 15, 17, 22},
	   {17, 12, 7, 10, 3, 1, 8, 13},
	   {19, 25, 10, 15, 14, 11, 3, 3},
	   {21, 18, 16, 20, 15, 13, 19, 0} };

	sinsity(A, n);
	print(A, n);   

	printf("\n ���� �� �ִ� ��ȭ�� �ּҷ�: ");
	printf("%d\n", minArr[n-1][n-1]);  // ��ȭ�� �ּҷ��� 20

	return 0;
}
