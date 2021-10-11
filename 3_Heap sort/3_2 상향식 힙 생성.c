// 1. ��͹���
// 2. ����� ����


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 1. ���


int heap[100];
int n; // ��� �� = ���� ũ��

void downHeap(int index) {
	int left, right, bigger;
	left = 2 * index;
	right = 2 * index + 1;

	if ((left > n) && (right > n)) // �ڽ��� ���� ���
		return;

	bigger = left;
	if (right <= n) { // ������ �ڽ��� �ִ� ���
		if (heap[left] < heap[right]) // ������ �ڽ��� �� ū ���
			bigger = right;
	}

	if (heap[bigger] <= heap[index]) // �ڽ��� ������ ������ return
		return;

	// �ڽ��� ������ ũ�� swap
	int tmp = heap[index];
	heap[index] = heap[bigger];
	heap[bigger] = tmp;

	index = bigger;

	downHeap(index);
}

void rBuildHeap(int index) {
	int left, right;
	left = 2 * index;
	right = 2 * index + 1;

	if (index < n) {
		rBuildHeap(left);
		rBuildHeap(right);

		downHeap(index);
	}
}
void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", heap[i]);
	}
}

int main()
{
	int cnt;
	scanf("%d", &cnt);

	for (int i = 1; i <= cnt; i++) {
		scanf("%d", &heap[i]);
	}

	n = cnt;
	rBuildHeap(1);
	printHeap();
}





// 2. �����

// ���� ��� : n/2 = ���γ�带 ���� �ڽ����� ������ ���� ���� ���γ�� ��� ���� �����ʿ��� ����


int heap[100];
int n; // ��� �� = ���� ũ��

void downHeap(int index) {
	int left, right, bigger;
	left = 2 * index;
	right = 2 * index + 1;

	if ((left > n) && (right > n)) // �ڽ��� ���� ���
		return;

	bigger = left;
	if (right <= n) { // ������ �ڽ��� �ִ� ���
		if (heap[left] < heap[right]) // ������ �ڽ��� �� ū ���
			bigger = right;
	}

	if (heap[bigger] <= heap[index]) // �ڽ��� ������ ������ return
		return;

	// �ڽ��� ������ ũ�� swap
	int tmp = heap[index];
	heap[index] = heap[bigger];
	heap[bigger] = tmp;

	index = bigger;

	downHeap(index);
}

void BuildHeap() {
	int left, right;

	for (int i = n / 2; i >= 1; i--) {   // ���۳��� n/2
		downHeap(i);
	}
}
void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", heap[i]);
	}
}

int main()
{
	int cnt;
	scanf("%d", &cnt);

	for (int i = 1; i <= cnt; i++) {
		scanf("%d", &heap[i]);
	}

	n = cnt;
	BuildHeap(); 
	printHeap();
}
