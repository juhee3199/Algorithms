#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 2. 개방주소법
// 배열을 이용 -> 충돌이 발생

int M;

// 구조체 안쓰고 그냥 1차원배열써서 사용해도 됌.
// key이외에 probeCount를 추가해줬음
typedef struct {
	int key;
	int probeCount; // 삽입 시 위치를 몇번 조사했는지
}Bucket;
typedef struct {
	Bucket A[100];
}HashType;

void init(HashType *HT) {
	for (int i = 0; i < M; i++) {
		HT->A[i].key = 0;
		HT->A[i].probeCount = 0;
	}
}
int isEmpty(HashType *HT, int b) {
	return HT->A[b].key == 0;    // key값이 0이면 empty로 판단
}
int h(int key) {
	return key % M;
}

//이중해싱
int h2(int key, int q) {
	return q - (key % q);
}
int getNextBucketDouble(int v, int i, int key, int q) {
	return (v + i * h2(key, q)) % M;
}

void insertItem(HashType *HT, int key, int q) {
	int v = h(key);
	int i = 0;
	int count = 0;

	while (i < M) {
		count++;
		int b = getNextBucketDouble(v, i, key, q);

		if (isEmpty(HT, b)) {
			HT->A[b].key = key;
			HT->A[b].probeCount = count;
			printf("%d\n", b);
			return;
		}

		else { // 충돌. 비어있지 않은 경우.
			printf("C");
			i++;
		}
	}
}

void findElement(HashType *HT, int key, int q) {
	int v = h(key);
	int i = 0;
	while (i < M) {
		int b = getNextBucketDouble(v, i, key, q);
		if (isEmpty(HT, b)) {
			printf("-1\n");
			return;
		}
		else if (HT->A[b].key == key) {
			printf("%d %d\n", b, key);
			return;
		}
		else { // 
			i++;
		}
	}
	printf("-1\n");
	return;
}

void printHash(HashType *HT) {
	for (int i = 0; i < M; i++) {
		printf(" %d", HT->A[i].key);
	}
	printf("\n");
}

int main() {
	char cmd;
	int n, q, key, rank;

	scanf("%d %d %d", &M, &n, &q);

	HashType HT;
	init(&HT);

	while (1){
		scanf("%c", &cmd);
		if (cmd == 'i') {		// 삽입
			scanf("%d", &key);
			insertItem(&HT, key, q);
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			findElement(&HT, key, q);
		}
		else if (cmd == 'p') {	// 출력
			printHash(&HT);
		}
		// 출력 후 종료
		else if (cmd == 'e') {	
			printHash(&HT);
			return;
		}
	}

}
