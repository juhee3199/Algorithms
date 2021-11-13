#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


// 1. 분리연쇄법

// 단순 연결리스트 이용
// 삽입 시, insertFirst로 구현하는 것이 쉬움

// 입력 키는 중복이 없음!

int M;

typedef struct HashNode {
	int key;
	struct HashNode * next;
}HashType;

void initBucketArray(HashType *HT) { // 해시테이블 초기화
	// 구조체배열 각각을 비어있는 연결 리스트로 만들기

	// 각 배열은 헤드역할이기때문에 
	// key값은 초기화할 필요없고 next만 초기화
	for (int i = 0; i < M; i++) {
		HT[i].next = NULL;
	}
}
int h(int key) { // 해시함수
	return key % M;
}
void insertItem(HashType *HT, int key) {
	int v = h(key);	// 해당 key값의 위치를 해시함수를 통해 찾아줌
	HashType * node = (HashType*)malloc(sizeof(HashType));

	// 맨 앞에 삽입
	node->key = key;
	node->next = HT[v].next;

	HT[v].next = node;
}

int findElement(HashType *HT, int key) {
	// key가 해시테이블에 몇개가 있는지 출력하기로 바꿈

	int v = h(key);
	int rank = 0;	// 키가 저장된 순위를 인쇄

	HashType *p;
	for (p = HT[v].next; p != NULL; p = p->next) { // v위치에서 찾아야함
		rank++;
		if (p->key == key) {
			return rank;
		}
	}
	return 0;
}
int removeElement(HashType *HT, int key) {
	int v = h(key);
	int rank = 0;	// 키가 저장된 순위를 인쇄

	HashType *p = &HT[v]; // 헤더를 가리킴
	HashType *q;

	while (p->next) { // p의 next가 널이 아닌동안
		rank++;
		if (p->next->key == key) {
			q = p->next; // q를 삭제해야함.
			p->next = q->next;
			free(q);
			return rank;
		}
		else {
			p = p->next;
		}
	}
	return 0;
}
void printHash(HashType * HT) {
	HashType *p;
	for (int i = 0; i < M; i++) {
		// 연결리스트 출력
		for (p = HT[i].next; p != NULL; p = p->next) {
			printf(" %d", p->key);
		}
	}
	printf("\n");
}

int main() {
	char cmd;
	int key, rank;

	scanf("%d", &M);
	HashType *HT;  // 해시타입의 구조체 배열
	HT = (HashType*)malloc(sizeof(HashType)*M);
	initBucketArray(HT);

	scanf("%c", &cmd);
	while (cmd != 'e') {

		if (cmd == 'i') {		// 삽입
			scanf("%d", &key);
			insertItem(HT, key);
		}
		else if (cmd == 's') {  
			scanf("%d", &key);
			rank = findElement(HT, key);
			printf("%d\n", rank);
			// 키가 저장된 순위를 인쇄. 없으면 0을 인쇄
		}
		else if (cmd == 'd') {	// 삭제
			scanf("%d", &key);
			rank = removeElement(HT, key);
			printf("%d \n", rank);
		}
		else if (cmd == 'p') {	// 출력
			printHash(HT);
		}
		else if (cmd == 'e') {	// 종료
			return;
		}
		scanf("%c", &cmd);
	}
}
