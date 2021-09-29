// 과제1. 6장 응용문제 힙의 마지막노드

/*원소의 개수를 10~20 사이의 수로 받음
원소의 개수만큼 난수를 입력 받아 최소힙을 구현
“응용문제 – 힙의 마지막 노드”에 따라 binaryExpansion, findLastNode를 활용하여
구현된 힙에서 비트 경로를 따라 마지막 노드를 반환*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int H[100];
int n, top;

void push(int *stack, int i) {
	top++;
	stack[top] = i;

}
int pop(int *stack) {
	int e;
	e = stack[top];
	top--;

	return e;
}
// 힙의 크기 n에 대한 이진수 표기 얻기
void binaryExpansion(int i, int *stack) { // i = n =10
	while (i >= 2) {
		push(stack, i % 2);
		i = i / 2;
	}
	push(stack, i);
}

int findLastNode(int index, int n) { // root=1, n의 개수
	int *stack, bit, key;
	stack = (int*)malloc(sizeof(int)*n);

	binaryExpansion(n, stack); // n의 이진수 표기를 저장

	top--;  // 최상위 비트 제거(pop)

	// stack 원소들이 가리키는 방향으로 이동해서 마지막 노드에 도달
	printf("Bit Route: ");
	while (top > -1) {
		bit = pop(stack);
		printf(" %d", bit); // 가리키는 방향 확인

		if (bit == 0) {
			index = index * 2;  // left child
			key = H[index];
		}
		else if (bit == 1) {
			index = index * 2 + 1;  // right child
			key = H[index];
		}
	}
	printf("\n");

	return key;
}

void upHeap(int index) {//힙 속성 복구
	int tmp;
	if (index == 1) {//루트인 경우
		return;
	}
	else if (H[index] > H[index / 2]) {//부모보다 큰 경우
		return;
	}
	else {//부모보다 작은 경우
		tmp = H[index];//교환
		H[index] = H[index / 2];
		H[index / 2] = tmp;
	}
	upHeap(index / 2);
}

void insertItem(int key) {//삽입
	n++;
	H[n] = key;
	upHeap(n);//속성 복구
}

int main()
{
	int lastNode, k, cnt;
	top = -1;

	srand(time(NULL));
	cnt = rand() % 11 + 10;  // 원소 개수  10~20개
	printf("원소 개수: %d\n", cnt);

	// Heap 삽입, 속성 복구 (최소힙)
	printf("난수 발생: ");
	srand(time(NULL)); //  매번 다른 시드값 생성
	for (int i = 0; i < cnt; i++)
	{
		k = rand() % 100; 
		insertItem(k);
		printf(" %d", k);
	}
	printf("\n");

	// 속성복구된 힙 출력
	printf("최소 Heap: ");
	for (int i = 1; i <= cnt; i++)
	{
		printf(" %d", H[i]); // 발생난수 출력
	}
	printf("\n");


	// 마지막 노드 반환
	lastNode = findLastNode(1, n); // root, 원소개수n
	printf("LastNode: %d", lastNode);
}
