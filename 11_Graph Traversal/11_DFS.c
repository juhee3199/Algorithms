#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 1. 깊이우선탐색

#define FALSE 0
#define TRUE 1

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

// 정점 생성(Last)
void makeVertex(Graph* G, int vName) {
	Vertex *v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;
	v->iHead = NULL;   // 정점을 생성할 때마다 헤더노드는 null
	v->isVisit = FALSE; // isVisit

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

// 부착간선리스트에 간선 삽입 (오름차순으로) 
void insertIncidentEdge(Vertex *v, int aName) {
	IncidentEdge *p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->next = NULL;

	// 부착간선 리스트 순회
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

void dfs(Graph *G, int vName) {
	// 출발정점에서 방문 순서대로 정점 번호 출력
	// 트리간선과 후향간선은 따로 넣지 않음
	// 방문 순서 = 트리간선 순서

	Vertex *v = findVertex(G, vName);
	IncidentEdge *p;

	// 정점 방문 여부 판단
	if (v->isVisit == FALSE) {
		v->isVisit = TRUE;
		printf("%d \n", v->vName);
	}

	// 방문 정점의 인접리스트를 순회하면서 방문하지 않았으면 재귀호출하여 방문
	for (p = v->iHead; p != NULL; p = p->next) {
		v = findVertex(G, p->aName);
		if (v->isVisit == FALSE) {
			dfs(G, v->vName);    // 재귀호출
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
		makeVertex(&G, i+1); //오름차순으로 삽입됌
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);
		insertEdge(&G, v1, v2);
	}

	print(&G);
	dfs(&G, s); // 시작 정점
}

