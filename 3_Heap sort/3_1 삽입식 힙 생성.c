#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* �� ������ ���� */

// �ִ���
// ���������� ���� (�迭)


int  heap[100];
int n; // ��� �� = ���� ũ��

void downHeap(int index) {
	int left, right, bigger;
	left = 2 * index;
	right = 2 * index + 1;

	if ((left > n) && right > n) { // �ڽ��� ���� ���
		return;
	}

	bigger = left;
	if (right <= n) {// ������ �ڽ��� �ִ� ���
		if (heap[left] < heap[right])  // ������ �ڽ��� �� ū ���
			bigger = right;
	}
		
	if (heap[bigger] <= heap[index])  // �ڽ��� ������ ������ return
		return;

	// �ڽ��� ������ ũ�� swap
	int tmp = heap[index];
	heap[index] = heap[bigger];
	heap[bigger] = tmp;

	index = bigger;

	downHeap(index);
}


int removeMax() {
	int k, w;
	k = heap[1]; // ��ƮŰ
	w = heap[n]; // last node

	heap[1] = w; // ��Ʈ�� last node�� ��ü
	n--;		// last node ��ġ ����
	
	downHeap(1); // ��Ʈ

	return k;
}

void upHeap(int index) {

	if (index == 1)
		return;
	else if (heap[index] <= heap[index / 2]) // �θ� ������ ũ�� return 
		return;
	
	// �θ� ������ ������ �θ�� swap
	int tmp = heap[index];
	heap[index] = heap[index / 2];
	heap[index / 2] = tmp;
	
	index = index / 2;
	upHeap(index);
}
void insertItem(int k) {
	n++;
	heap[n] = k;

	upHeap(n);
}

void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", heap[i]);
	}
	printf("\n");
}

int main() {
	int k;
	char cmd;

	n = 0;

	while (1) {
		scanf("%c", &cmd);

		if (cmd == 'i') {		// ����
			scanf("%d", &k);
			insertItem(k);
			printf("0\n");
		}
		else if (cmd == 'd') {	// ����
			k = removeMax();
			printf("%d \n", k);
		}
		else if (cmd == 'p') {	// ���
			printHeap();
		}
		else if (cmd == 'q') {	// ����
			return;
		}
	}
}



