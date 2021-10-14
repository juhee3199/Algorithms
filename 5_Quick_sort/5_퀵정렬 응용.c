#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ���и� 25p
// 5���� ��������� ����

// ����Ʈ char ������ �����ϴ� �� ���� ����!!
void inPlacePartition(char* L, int i, int j) { 
	int tmp;

	while (i <= j) {
		while ((i <= j) && (L[i] == 'B')) {
			i++;
		}
		while ((j >= i) && (L[j] == 'R')) {
			j--;
		}
		if (i < j) { // swap
			tmp = L[i];
			L[i] = L[j];
			L[j] = tmp;
		}
	}
}

int main()
{
	int n = 10;
	char list[10];

	// ���� ����Ʈ ����
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		if (rand() % 2 == 0) { // ¦���� �Ķ�
			list[i] = 'B';
		}
		else { // Ȧ���� ����
			list[i] = 'R';	
		}
	}
	// �迭 Ȯ��
	for (int i = 0; i < n; i++) {
		printf(" %c", list[i]);
	}
	printf("\n"); 


	getchar();
	inPlacePartition(list, 0, n - 1); // ���ʳ�, �����ʳ�

	for (int i = 0; i < n; i++) {
		printf(" %c", list[i]);
	}
	printf("\n");
	return 0;
}
