#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int findPivot(int *L, int l, int r) {
	int k;

	srand(time(NULL)); // �Ź� ���ο� ��

	k = rand() % (r - l + 1) + l;
	// rand()%(b-a+1)+a ==> a���� b�� ����

	return k;
}

int inPlacePartition(int* L, int l, int r, int k) {
	int p, i, j, tmp;

	p = L[k];
	L[k] = L[r];
	i = l;
	j = r - 1;

	while (i <= j) {
		while (i <= j && L[i] <= p) {
			i++;
		}
		while (j >= i && L[j] >= p) {
			j--;
		}
		if (i < j) {
			tmp = L[i];
			L[i] =L[j];
			L[j] = tmp;
		}
	}

	// pivot�� �����ڸ���
	L[r] = L[i];
	L[i] = p; 
	

	return i; // a, b �ڸ� (�ᱹ i = p = a = b)
}

void inPlaceQuickSort(int *L, int l, int r) {
	int k, index, a, b;

	if (l >= r)
		return;

	k = findPivot(L, l, r); 

	index = inPlacePartition(L, l, r, k);
	
	a = index;
	b = index;

	inPlaceQuickSort(L, l, a -1); // P���� ���� ���ҵ�
	inPlaceQuickSort(L, b+1, r);  // P���� ū ���ҵ�
}

int main() {
	int n, *L;

	scanf("%d", &n);

	L = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &L[i]);
	}

	inPlaceQuickSort(L, 0, n-1);

	for (int i = 0; i < n; i++) {
		printf(" %d", L[i]);
	}

}
