#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define SIZE 10
typedef struct
{
	char elem[SIZE];
	int top;
}StackType;
void initStack(StackType* S)
{
	S->top = -1;
}
int isStackEmpty(StackType* S)
{
	return S->top == -1;
}
int isStackFull(StackType* S)
{
	return S->top == SIZE - 1;
}
void push(StackType* S, char c) {
	if (isStackFull(S)) {
		printf("Stack FULL \n");
		return;
	}
	S->top++;
	S->elem[S->top] = c;
}
char pop(StackType* S) {
	if (isStackEmpty(S)){
		printf("Stack EMPTY\n");
		return 0;
	}
	char e = S->elem[S->top];
	S->top--;
	return e;
}


typedef struct IncidentEdge
{
	char aName;
	struct IncidentEdge* next;
}IncidentEdge;
typedef struct Vertex
{
	char vName;
	int isVisit;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;
typedef struct
{
	Vertex* vHead;
}GraphType;
void initGraph(GraphType* G)
{
	G->vHead = NULL;
}
// ���� ����: insert Last�� ����
void makeVertex(GraphType* G, char vName)
{
	Vertex *v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;
	v->iHead = NULL;

	v->isVisit = FALSE;

	// ��������Ʈ ��ȸ
	Vertex *q = G->vHead;
	if (q == NULL) { // ����Ʈ�� ����ִ� ���
		G->vHead = v;
	}
	else {
		while (q->next != NULL) { // ������ ��忡�� ���߱�
			q = q->next;
		}
		q->next = v; // ������ ���� ��
	}
}

// ������������Ʈ�� ���� ���� (������������) 
void makeIncidentEdge(Vertex *v, char av) {
	IncidentEdge *p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = av; // ��������
	p->next = NULL;

	// �������� ����Ʈ ��ȸ
	IncidentEdge *q = v->iHead;
	if (q == NULL) {  	// ù ����� ���. = p�� ���
		v->iHead = p;
	}
	// aName�� ù ��庸�� ������� �ڽ��� ù ��尡 ��
	else if (q->aName > av) {
		v->iHead = p;
		p->next = q;
	}
	else {
		while (q->next != NULL) {
			if (q->next->aName > p->aName) { // ���� ��尡 ������ ũ�� ���� ��带 �о�� ���� �� �ڸ�
				p->next = q->next;
				q->next = p;
				return;
			}
			q = q->next;
		}
		q->next = p; // �� �ڿ� ����
	}
}
// �׷������� vName�� ���� �ּҸ� ã��
Vertex * findVertex(GraphType *G, char vName) {
	Vertex *p = G->vHead;
	while (p->vName != vName) {
		p = p->next;
	}
	return p;
}
void insertEdge(GraphType* G, char v1, char v2)
{
	Vertex* v = findVertex(G, v1);
	makeIncidentEdge(v, v2);
	v = findVertex(G, v2);
	makeIncidentEdge(v, v1);
}
void print(GraphType* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
	{
		printf("(%c) : ", p->vName);
		for (q = p->iHead; q != NULL; q = q->next)
			printf("(%c) ", q->aName);
		printf("\n");
	}
	printf("\n");
}

//������� dfs. ���� ���
void stack_dfs(GraphType *G, char vName) {
	Vertex *v, *av;
	IncidentEdge *p;

	StackType S;
	initStack(&S);

	v = findVertex(G, vName);
	v->isVisit = TRUE;
	push(&S, vName);
	printf(" %c", vName);

	while (!isStackEmpty(&S)) {
		char c = pop(&S);
		v = findVertex(G, c);
//		printf(" %c", c);

		for (p = v->iHead; p != NULL; p = p->next) {
			av = findVertex(G, p->aName);
			if (av->isVisit == FALSE) {
				av->isVisit = TRUE;
				push(&S, av->vName);
				printf(" %c", av->vName);
			}
		}
	}
}
void dfs(GraphType *G, char vName) {
	// ����������� �湮 ������� ���� ��ȣ ���
	// Ʈ�������� ���Ⱓ���� ���� ���� ����
	// �湮 ���� = Ʈ������ ����

	Vertex *v = findVertex(G, vName);
	IncidentEdge *p;
	Vertex *av;

	// ���� �湮 ���� �Ǵ�
	if (v->isVisit == FALSE) {
		v->isVisit = TRUE;
		printf(" %c", v->vName);
	}

	// �湮 ������ ��������Ʈ�� ��ȸ�ϸ鼭 �湮���� �ʾ����� ���ȣ���Ͽ� �湮
	for (p = v->iHead; p != NULL; p = p->next) {
		av = findVertex(G, p->aName);
		if (av->isVisit == FALSE) {
			dfs(G, av->vName);    // ���ȣ��
		}
	}
}

int main()
{
	GraphType G;
	initGraph(&G);

	//
	//makeVertex(&G, 'a'); makeVertex(&G, 'b'); makeVertex(&G, 'c');
	//makeVertex(&G, 'd'); makeVertex(&G, 'e'); makeVertex(&G, 'f');
	//makeVertex(&G, 'g');
	//insertEdge(&G, 'a', 'b'); insertEdge(&G, 'a', 'f');
	//insertEdge(&G, 'b', 'c'); insertEdge(&G, 'b', 'g');
	//insertEdge(&G, 'c', 'd'); insertEdge(&G, 'd', 'e');
	//insertEdge(&G, 'd', 'g'); insertEdge(&G, 'e', 'f');
	//insertEdge(&G, 'e', 'g');
	//

	
	makeVertex(&G, 'a');  makeVertex(&G, 'b'); makeVertex(&G, 'c');
	makeVertex(&G, 'd');  makeVertex(&G, 'e'); 
	insertEdge(&G, 'a', 'b');  insertEdge(&G, 'a', 'd'); insertEdge(&G, 'a', 'c');
	insertEdge(&G, 'a', 'e');  insertEdge(&G, 'b', 'c');  insertEdge(&G, 'c', 'd');
	insertEdge(&G, 'c', 'e');  
	
	print(&G);

	//dfs1(&G, 'c');
	stack_dfs(&G, 'd');
	printf("\n");

	initGraph(&G);
	makeVertex(&G, 'a');  makeVertex(&G, 'b'); makeVertex(&G, 'c');
	makeVertex(&G, 'd');  makeVertex(&G, 'e');
	insertEdge(&G, 'a', 'b');  insertEdge(&G, 'a', 'd'); insertEdge(&G, 'a', 'c');
	insertEdge(&G, 'a', 'e');  insertEdge(&G, 'b', 'c');  insertEdge(&G, 'c', 'd');
	insertEdge(&G, 'c', 'e');
	dfs(&G, 'd');
}
*/
// makeVertex, makeIncidentEdge, findVertex �߰�


// g b a f e d c

// (b) (a) (c) (e) (f) (d)


// 6�� ���� a���� �湮



// a ���� �湮.  a b f e d g c

/*

//������� dfs. ���� ���
void stack_dfs(GraphType *G, char vName) {
	Vertex *v, *av;
	IncidentEdge *p;

	StackType S;
	initStack(&S);

	push(&S, vName);
//	printf(" %c", vName);

	while (!isStackEmpty(&S)) {
		char c = pop(&S);
		v = findVertex(G, c);
		v->isVisit = TRUE;
		printf(" %c", c);

		for (p = v->iHead; p != NULL; p = p->next) {
			av = findVertex(G, p->aName);
			if (av->isVisit == FALSE) {
				av->isVisit = TRUE;
				push(&S, av->vName);
//				printf(" %c", av->vName);
			}
		}
	}

}
*/


/*
//������� dfs. ���� ���
void stack_dfs(GraphType *G, char vName) {
	Vertex *v, *av;
	IncidentEdge *p;

	StackType S;
	initStack(&S);

	push(&S, vName);
//	printf(" %c", vName);

	while (!isStackEmpty(&S)) {
		char c = pop(&S);
		v = findVertex(G, c);
		v->isVisit = TRUE;
		printf(" %c", c);

		for (p = v->iHead; p != NULL; p = p->next) {
			av = findVertex(G, p->aName);
			if (av->isVisit == FALSE) {
//				av->isVisit = TRUE;
				push(&S, av->vName);
//				printf(" %c", av->vName);
			}
		}
	}

}

void dfs1(GraphType *G) {
	Vertex *p = G->vHead;
	for (; p != NULL; p = p->next) {
		if (p->isVisit == FALSE) {
			stack_dfs(G, p->vName);
		}
	}
}
