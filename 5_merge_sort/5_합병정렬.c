
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode
{
	int data;
	struct ListNode* link;
}ListNode;

typedef struct  ListType
{
	ListNode* head; // ��ü ���Ḯ��Ʈ�� ù��° ���


}ListType;


void init(ListType* L)
{
	L->head = NULL;
}

// �������  ���� �׻� ù��° �ڸ��� ����.
void insertFirst(ListType* L, int e)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));    // ���ο� ��� ����
	// ����� �ʵ尪 �ʱ�ȭ

	node->data = e;
	node->link = L->head; // ���� ù��° �ڸ��� �ִ� ���
	L->head = node;		  // ���� ���� ���ο� ��尡 ��

}

// ���Ḯ��Ʈ�� �� ����������� Ȯ��
void print(ListType* L)
{
	// ���Ḯ��Ʈ�� �Ѿƴٴ� 
	for (ListNode* p = L->head; p != NULL; p = p->link)   //  p = L�� ���. ���Ḯ��Ʈ�� ������ ����
		printf(" %d", p->data);

	printf("\n");
}

void merge(ListType* L, ListType* L1, ListType* L2)
{
	// L1, L2�� �Ѿƴٴ� listnode
	ListNode* a = L1->head;
	ListNode* b = L2->head;
	ListNode* p; // ��ü�� �Ѱ��� 

	//	��ü ���ĵȸ���Ʈ�� L�� ����ų ����
	//	L1�� L2�� ���ؼ� ���� ù��°�� �� �������� ������

	// l1, l2�� ���� ����� �� ���̳�

	if ((a == NULL) && (b == NULL))
		return;

	if (a->data <= b->data) {
		L->head = a;   // L�� ���� a
		a = a->link;   // ���� ���ҷ� �Ѿ
		p = L->head;   // p�� L�� head�� a�� ����Ű�� ����
	}
	else {
		L->head = b;
		b = b->link;
		p = L->head;
	}

	// ���⸦ ä��������
	while ((a != NULL) && (b != NULL)) {
		// Ű�� ���� ���Һ��� ū ���Ҽ����� �����ϸ� L�� �߰�
		if (a->data <= b->data) {  // L1�� ���Ұ� �� ���� ��
			p->link = a;
			a = a->link;
			p = p->link;
		}
		else {  // L2�� ���Ұ� �� ���� ��
			p->link = b;
			b = b->link;
			p = p->link;
		}
	}

	// �� �ݺ������� ó������ ���� L1 �Ǵ� L2�� ������ ���ҵ��� L�� �ݺ������� �߰�
	while (a != NULL) {
		p->link = a;
		a = a->link;
		p = p->link;

	}
	while (b != NULL) {
		p->link = b;
		b = b->link;
		p = p->link;

	}
}


void partition(ListType* L, ListType* L1, ListType* L2, int n)
{
	ListNode* p = L->head;  // ��带 �ϳ��� ����ٴ� �����͸� ����

	L1->head = p;

	// �ݺ��ؼ� p�� ��ġ�� �̵�
	for (int i = 1; i < (n / 2); i++) {
		p = p->link;
	}

	L2->head = p->link;
	p->link = NULL;
}



// mergeSort�� ��������� ȣ���ϸ鼭 �߶󳪰��鼭 ����� �ٿ���
// ���� �ڸ��� �κ��� partition�Լ��� ���
void mergeSort(ListType* L, int n)  // n = ���� ����� ����
{
	ListType L1, L2;

	if (n > 1) {

		partition(L, &L1, &L2, n);   // L, L1, L2�� �ּҸ� ����. L�� �̹� �ּ���(������ �ּҸ� ���� �޾���)

		if (n % 2 == 0) { // ¦��	
			mergeSort(&L1, n / 2);	// �ڸ� �� �ִµ����� �������� �ڸ�.  
			mergeSort(&L2, n / 2); 	// �� ���� �������� �ڸ�
		}
		else { // Ȧ��
			mergeSort(&L1, n / 2);// �ڸ� �� �ִµ����� �������� �ڸ�.  
			mergeSort(&L2, n / 2 + 1); // Ȧ���ϱ� +1�� �߰�
		}
		merge(L, &L1, &L2);
	}
}


int main()
{
	ListType L; // ����ִ� ����Ʈ�� ������ ����.
	init(&L);

	int n, elem;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &elem);
		insertFirst(&L, elem);
	}

	mergeSort(&L, n); // list type�� �ּҸ� ����

	print(&L);

	return 0;
}

