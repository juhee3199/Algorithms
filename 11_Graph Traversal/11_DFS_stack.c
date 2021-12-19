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
// 정점 생성: insert Last로 구현
void makeVertex(GraphType* G, char vName)
{
	Vertex *v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;
	v->iHead = NULL;

	v->isVisit = FALSE;

	// 정점리스트 순회
	Vertex *q = G->vHead;
	if (q == NULL) { // 리스트가 비어있는 경우
		G->vHead = v;
	}
	else {
		while (q->next != NULL) { // 마지막 노드에서 멈추기
			q = q->next;
		}
		q->next = v; // 마지막 노드는 나
	}
}

// 부착간선리스트에 간선 삽입 (오름차순으로) 
void makeIncidentEdge(Vertex *v, char av) {
	IncidentEdge *p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = av; // 인접정점
	p->next = NULL;

	// 부착간선 리스트 순회
	IncidentEdge *q = v->iHead;
	if (q == NULL) {  	// 첫 노드인 경우. = p는 헤드
		v->iHead = p;
	}
	// aName이 첫 노드보다 작을경우 자신이 첫 노드가 됌
	else if (q->aName > av) {
		v->iHead = p;
		p->next = q;
	}
	else {
		while (q->next != NULL) {
			if (q->next->aName > p->aName) { // 다음 노드가 나보다 크면 다음 노드를 밀어내고 내가 그 자리
				p->next = q->next;
				q->next = p;
				return;
			}
			q = q->next;
		}
		q->next = p; // 맨 뒤에 삽입
	}
}
// 그래프에서 vName을 갖는 주소를 찾기
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

//비재귀적 dfs. 스택 사용
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
	// 출발정점에서 방문 순서대로 정점 번호 출력
	// 트리간선과 후향간선은 따로 넣지 않음
	// 방문 순서 = 트리간선 순서

	Vertex *v = findVertex(G, vName);
	IncidentEdge *p;
	Vertex *av;

	// 정점 방문 여부 판단
	if (v->isVisit == FALSE) {
		v->isVisit = TRUE;
		printf(" %c", v->vName);
	}

	// 방문 정점의 인접리스트를 순회하면서 방문하지 않았으면 재귀호출하여 방문
	for (p = v->iHead; p != NULL; p = p->next) {
		av = findVertex(G, p->aName);
		if (av->isVisit == FALSE) {
			dfs(G, av->vName);    // 재귀호출
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
// makeVertex, makeIncidentEdge, findVertex 추가


// g b a f e d c

// (b) (a) (c) (e) (f) (d)


// 6개 정점 a먼저 방문



// a 먼저 방문.  a b f e d g c

/*

//비재귀적 dfs. 스택 사용
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
//비재귀적 dfs. 스택 사용
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
