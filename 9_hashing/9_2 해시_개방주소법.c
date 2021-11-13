#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 2. �����ּҹ�
// �迭�� �̿� -> �浹�� �߻�

// ������ �̷��� 1�����迭�� ������� ����?


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

		else { // �浹. ������� ���� ���.
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

		if (cmd == 'i') {		// ����
			scanf("%d", &key);
			insertItem(&HT, key);
		}
		else if (cmd == 's') {
			scanf("%d", &key);
			findElement(&HT, key);
		}
		else if (cmd == 'e') {	// ����
			return;
		}
		scanf("%c", &cmd);
	}

}
