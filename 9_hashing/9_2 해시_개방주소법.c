#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 2. 개방주소법
// 배열을 이용 -> 충돌이 발생

// 원래는 이렇게 1차원배열로 사용하지 않음?


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
int getNextBucketLinear(int v, int i) {
	return (v + i) % M;
}

void insertItem(HashType *HT, int key) {
	int v = h(key);
	int i = 0;
	int count = 0;

	while (i < M) {
		count++;
		int b = getNextBucketLinear(v, i);

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

	// overflowException()
}

void findElement(HashType *HT, int key) {
	int v = h(key);
	int i = 0;
	while (i < M) {
		int b = getNextBucketLinear(v, i);
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

int main() {
	char cmd;
	int n, key, rank;

	scanf("%d %d", &M, &n);

	HashType HT;
	init(&HT);

	scanf("%c", &cmd);
	while (cmd != 'e') {

		if (cmd == 'i') {		// 삽입
			scanf("%d", &key);
			insertItem(&HT, key);
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			findElement(&HT, key);
		}
		else if (cmd == 'e') {	// 종료
			return;
		}
		scanf("%c", &cmd);
	}

}
