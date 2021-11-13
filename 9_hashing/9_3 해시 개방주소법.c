#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 2. �����ּҹ�
// �迭�� �̿� -> �浹�� �߻�

int M;

// ����ü �Ⱦ��� �׳� 1�����迭�Ἥ ����ص� ��.
// key�̿ܿ� probeCount�� �߰�������
typedef struct {
	int key;
	int probeCount; // ���� �� ��ġ�� ��� �����ߴ���
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
	return HT->A[b].key == 0;    // key���� 0�̸� empty�� �Ǵ�
}
int h(int key) {
	return key % M;
}

//�����ؽ�
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

		else { // �浹. ������� ���� ���.
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
		if (cmd == 'i') {		// ����
			scanf("%d", &key);
			insertItem(&HT, key, q);
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			findElement(&HT, key, q);
		}
		else if (cmd == 'p') {	// ���
			printHash(&HT);
		}
		// ��� �� ����
		else if (cmd == 'e') {	
			printHash(&HT);
			return;
		}
	}

}
