
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
	ListNode* head; // 전체 연결리스트의 첫번째 노드


}ListType;


void init(ListType* L)
{
	L->head = NULL;
}

// 만들어진  노드는 항상 첫번째 자리로 들어옴.
void insertFirst(ListType* L, int e)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));    // 새로운 노드 생성
	// 노드의 필드값 초기화

	node->data = e;
	node->link = L->head; // 원래 첫번째 자리에 있던 노드
	L->head = node;		  // 이제 내가 새로운 헤드가 됌

}

// 연결리스트가 잘 만들어졌는지 확인
void print(ListType* L)
{
	// 연결리스트를 쫓아다닐 
	for (ListNode* p = L->head; p != NULL; p = p->link)   //  p = L의 헤드. 연결리스트의 마지막 까지
		printf(" %d", p->data);

	printf("\n");
}

void merge(ListType* L, ListType* L1, ListType* L2)
{
	// L1, L2를 쫓아다닐 listnode
	ListNode* a = L1->head;
	ListNode* b = L2->head;
	ListNode* p; // 전체를 총괄할 

	//	전체 정렬된리스트를 L에 기억시킬 것임
	//	L1과 L2를 비교해서 누가 첫번째가 될 것인지를 결정함

	// l1, l2중 누가 헤더를 할 것이냐

	if ((a == NULL) && (b == NULL))
		return;

	if (a->data <= b->data) {
		L->head = a;   // L의 헤드는 a
		a = a->link;   // 다음 원소로 넘어감
		p = L->head;   // p는 L의 head인 a를 가리키고 있음
	}
	else {
		L->head = b;
		b = b->link;
		p = L->head;
	}

	// 여기를 채워나가기
	while ((a != NULL) && (b != NULL)) {
		// 키가 작은 원소부터 큰 원소순으로 삭제하며 L에 추가
		if (a->data <= b->data) {  // L1의 원소가 더 작을 때
			p->link = a;
			a = a->link;
			p = p->link;
		}
		else {  // L2의 원소가 더 작을 때
			p->link = b;
			b = b->link;
			p = p->link;
		}
	}

	// 위 반복문에서 처리되지 못한 L1 또는 L2의 나머지 원소들을 L에 반복적으로 추가
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
	ListNode* p = L->head;  // 노드를 하나씩 따라다닐 포인터를 정의

	L1->head = p;

	// 반복해서 p의 위치를 이동
	for (int i = 1; i < (n / 2); i++) {
		p = p->link;
	}

	L2->head = p->link;
	p->link = NULL;
}



// mergeSort가 재귀적으로 호출하면서 잘라나가면서 사이즈를 줄여감
// 실제 자르는 부분은 partition함수를 사용
void mergeSort(ListType* L, int n)  // n = 현재 노드의 개수
{
	ListType L1, L2;

	if (n > 1) {

		partition(L, &L1, &L2, n);   // L, L1, L2의 주소를 전달. L은 이미 주소임(이전에 주소를 전달 받았음)

		if (n % 2 == 0) { // 짝수	
			mergeSort(&L1, n / 2);	// 자를 수 있는데까지 왼쪽으로 자름.  
			mergeSort(&L2, n / 2); 	// 그 이후 오른쪽을 자름
		}
		else { // 홀수
			mergeSort(&L1, n / 2);// 자를 수 있는데까지 왼쪽으로 자름.  
			mergeSort(&L2, n / 2 + 1); // 홀수니까 +1을 추가
		}
		merge(L, &L1, &L2);
	}
}


int main()
{
	ListType L; // 비어있는 리스트가 생성된 것임.
	init(&L);

	int n, elem;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &elem);
		insertFirst(&L, elem);
	}

	mergeSort(&L, n); // list type의 주소를 전달

	print(&L);

	return 0;
}

