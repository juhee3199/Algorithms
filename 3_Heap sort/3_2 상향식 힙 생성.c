// 1. 재귀버전
// 2. 비재귀 버전


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 1. 재귀


int heap[100];
int n; // 노드 수 = 힙의 크기

void downHeap(int index) {
	int left, right, bigger;
	left = 2 * index;
	right = 2 * index + 1;

	if ((left > n) && (right > n)) // 자식이 없는 경우
		return;

	bigger = left;
	if (right <= n) { // 오른쪽 자식이 있는 경우
		if (heap[left] < heap[right]) // 오른쪽 자식이 더 큰 경우
			bigger = right;
	}

	if (heap[bigger] <= heap[index]) // 자식이 나보다 작으면 return
		return;

	// 자식이 나보다 크면 swap
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





// 2. 비재귀

// 시작 노드 : n/2 = 내부노드를 왼쪽 자식으로 가지는 가장 깊은 내부노드 가운데 가장 오른쪽에서 시작


int heap[100];
int n; // 노드 수 = 힙의 크기

void downHeap(int index) {
	int left, right, bigger;
	left = 2 * index;
	right = 2 * index + 1;

	if ((left > n) && (right > n)) // 자식이 없는 경우
		return;

	bigger = left;
	if (right <= n) { // 오른쪽 자식이 있는 경우
		if (heap[left] < heap[right]) // 오른쪽 자식이 더 큰 경우
			bigger = right;
	}

	if (heap[bigger] <= heap[index]) // 자식이 나보다 작으면 return
		return;

	// 자식이 나보다 크면 swap
	int tmp = heap[index];
	heap[index] = heap[bigger];
	heap[bigger] = tmp;

	index = bigger;

	downHeap(index);
}

void BuildHeap() {
	int left, right;

	for (int i = n / 2; i >= 1; i--) {   // 시작노드는 n/2
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
