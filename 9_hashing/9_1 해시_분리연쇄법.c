#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


// 1. �и������

// �ܼ� ���Ḯ��Ʈ �̿�
// ���� ��, insertFirst�� �����ϴ� ���� ����

// �Է� Ű�� �ߺ��� ����!

int M;

typedef struct HashNode {
	int key;
	struct HashNode * next;
}HashType;

void initBucketArray(HashType *HT) { // �ؽ����̺� �ʱ�ȭ
	// ����ü�迭 ������ ����ִ� ���� ����Ʈ�� �����

	// �� �迭�� ��忪���̱⶧���� 
	// key���� �ʱ�ȭ�� �ʿ���� next�� �ʱ�ȭ
	for (int i = 0; i < M; i++) {
		HT[i].next = NULL;
	}
}
int h(int key) { // �ؽ��Լ�
	return key % M;
}
void insertItem(HashType *HT, int key) {
	int v = h(key);	// �ش� key���� ��ġ�� �ؽ��Լ��� ���� ã����
	HashType * node = (HashType*)malloc(sizeof(HashType));

	// �� �տ� ����
	node->key = key;
	node->next = HT[v].next;

	HT[v].next = node;
}

int findElement(HashType *HT, int key) {
	// key�� �ؽ����̺� ��� �ִ��� ����ϱ�� �ٲ�

	int v = h(key);
	int rank = 0;	// Ű�� ����� ������ �μ�

	HashType *p;
	for (p = HT[v].next; p != NULL; p = p->next) { // v��ġ���� ã�ƾ���
		rank++;
		if (p->key == key) {
			return rank;
		}
	}
	return 0;
}
int removeElement(HashType *HT, int key) {
	int v = h(key);
	int rank = 0;	// Ű�� ����� ������ �μ�

	HashType *p = &HT[v]; // ����� ����Ŵ
	HashType *q;

	while (p->next) { // p�� next�� ���� �ƴѵ���
		rank++;
		if (p->next->key == key) {
			q = p->next; // q�� �����ؾ���.
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
		// ���Ḯ��Ʈ ���
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
	HashType *HT;  // �ؽ�Ÿ���� ����ü �迭
	HT = (HashType*)malloc(sizeof(HashType)*M);
	initBucketArray(HT);

	scanf("%c", &cmd);
	while (cmd != 'e') {

		if (cmd == 'i') {		// ����
			scanf("%d", &key);
			insertItem(HT, key);
		}
		else if (cmd == 's') {  
			scanf("%d", &key);
			rank = findElement(HT, key);
			printf("%d\n", rank);
			// Ű�� ����� ������ �μ�. ������ 0�� �μ�
		}
		else if (cmd == 'd') {	// ����
			scanf("%d", &key);
			rank = removeElement(HT, key);
			printf("%d \n", rank);
		}
		else if (cmd == 'p') {	// ���
			printHash(HT);
		}
		else if (cmd == 'e') {	// ����
			return;
		}
		scanf("%c", &cmd);
	}
}
