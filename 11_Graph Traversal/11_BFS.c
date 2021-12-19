
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define SIZE 100

typedef struct
{
	int elem[SIZE];  // 정점의 이름을 저장
	int front, rear;
}QueueType;


// 각 정점에서 incidentEdge를 관리
// 그래프의 가중치가 필요한 경우 추가
typedef struct IncidentEdge {
	int aName; //adjVertex;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	int vName;
	int isVisit; // 1이면 방문함
	struct Vertex* next;
	IncidentEdge * iHead; // 각 정점에서 incidentEdge를 관리
}Vertex;

typedef struct {
	Vertex *vHead;
}Graph;


void init(Graph* G) {
	G->vHead = NULL;
}

void initQueue(QueueType* Q)
{
	Q->front = Q->rear = 0;
}

int isEmpty(QueueType* Q)
{
	return Q->rear == Q->front;
}

int isFull(QueueType* Q)
{
	return (Q->rear + 1) % SIZE == Q->front;
}

void enqueue(QueueType* Q, int vName)
{
	if (isFull(Q))
	{
		printf("FULL\n");
		return;
	}
	Q->rear = (Q->rear + 1) % SIZE;
	Q->elem[Q->rear] = vName;
}
// front에서 dequeue
int dequeue(QueueType* Q)
{
	if (isEmpty(Q))
	{
		printf("EMPTY\n");
		return 0;
	}
	Q->front = (Q->front + 1) % SIZE;
	return Q->elem[Q->front];
}

// 단순 연결리스트 만들기
// insert Last로 구현
void makeVertex(Graph* G, int vName) {
	Vertex *v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->isVisit = FALSE; // isVisit
	v->next = NULL;
	v->iHead = NULL;   // 정점을 생성할 때마다 헤더노드는 null

	// 정점리스트 순회
	Vertex * q = G->vHead;

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

// av: 인접정점
// 오름차순으로 간선을 삽입 
void insertIncidentEdge(Vertex *v, int aName) {
	IncidentEdge *p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->next = NULL;

	// 순회를 위한 
	IncidentEdge *q = v->iHead;
	// 첫 노드인 경우. = p는 헤드
	if (q == NULL) {
		v->iHead = p;
	}
	// aName이 첫 노드보다 작을경우 자신이 첫 노드가 됌
	else if (q->aName > aName) {
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
		q->next = p;
	}
}
// 그래프에서 vName을 갖는 주소를 찾기
Vertex * findVertex(Graph *G, int vName) {
	Vertex *p = G->vHead;
	while (p->vName != vName) {
		p = p->next;
	}
	return p;
}
// 정점을 연결할 간선 만들기
void insertEdge(Graph *G, int v1, int v2) {

	// 무방향 그래프이므로 v1, v2모두 
	// v1을 기준으로
	Vertex *v = findVertex(G, v1);
	insertIncidentEdge(v, v2);
	//v2를 기준으로
	v = findVertex(G, v2);
	insertIncidentEdge(v, v1);
}

// 재귀를 사용하지 않음
// 방문 정점을 큐에 넣고 
// dequeue한 후, 해당 정점의 인접정점을 순회(인접정점을 큐에 넣기)
void bfs(Graph *G, int vName) {
	Vertex *v = findVertex(G, vName);
	IncidentEdge *p;
	QueueType Q;
	initQueue(&Q);

	// 방문했을리가 없으므로 if문 없이.
	v->isVisit = TRUE;
	printf("%d\n", v->vName);
	enqueue(&Q, v->vName);

	while (!isEmpty(&Q)) {
		v = findVertex(G, dequeue(&Q));

		// 각 정점의 인접정점을 순회하기 위함
		for (p = v->iHead; p != NULL; p = p->next) {
			v = findVertex(G, p->aName);
			if (v->isVisit == FALSE) {
				v->isVisit = TRUE;
				printf("%d\n", v->vName);
				enqueue(&Q, v->vName);
			}
		}
	}
}
// 정점을 기준으로 돌아다녀야 함
void print(Graph *G) {
	Vertex*p = G->vHead;
	IncidentEdge * q;
	for (; p != NULL; p = p->next) {
		printf(" %d :", p->vName);
		for (q = p->iHead; q != NULL; q = q->next) {
			printf(" [%d] ", q->aName);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	Graph G;
	init(&G);

	int n, m, s, v1, v2;

	scanf("%d %d %d", &n, &m, &s);
	for (int i = 0; i < n; i++) {
		makeVertex(&G, i + 1);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);
		insertEdge(&G, v1, v2);
	}

	//print(&G);
	bfs(&G, s);
}
