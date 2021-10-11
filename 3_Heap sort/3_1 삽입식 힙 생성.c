#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 힙 생성과 삭제 */

// 최대힙
// 순차힙으로 구현 (배열)


int  heap[100];
int n; // 노드 수 = 힙의 크기

void downHeap(int index) {
	int left, right, bigger;
	left = 2 * index;
	right = 2 * index + 1;

	if ((left > n) && right > n) { // 자식이 없는 경우
		return;
	}

	bigger = left;
	if (right <= n) {// 오른쪽 자식이 있는 경우
		if (heap[left] < heap[right])  // 오른쪽 자식이 더 큰 경우
			bigger = right;
	}
		
	if (heap[bigger] <= heap[index])  // 자식이 나보다 작으면 return
		return;

	// 자식이 나보다 크면 swap
	int tmp = heap[index];
	heap[index] = heap[bigger];
	heap[bigger] = tmp;

	index = bigger;

	downHeap(index);
}


int removeMax() {
	int k, w;
	k = heap[1]; // 루트키
	w = heap[n]; // last node

	heap[1] = w; // 루트를 last node로 대체
	n--;		// last node 위치 후퇴
	
	downHeap(1); // 루트

	return k;
}

void upHeap(int index) {

	if (index == 1)
		return;
	else if (heap[index] <= heap[index / 2]) // 부모가 나보다 크면 return 
		return;
	
	// 부모가 나보다 작으면 부모와 swap
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

		if (cmd == 'i') {		// 삽입
			scanf("%d", &k);
			insertItem(k);
			printf("0\n");
		}
		else if (cmd == 'd') {	// 삭제
			k = removeMax();
			printf("%d \n", k);
		}
		else if (cmd == 'p') {	// 출력
			printHeap();
		}
		else if (cmd == 'q') {	// 종료
			return;
		}
	}
}



