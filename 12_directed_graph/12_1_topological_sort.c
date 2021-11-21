// 교수님 코드에서 수정한 부분
// 1) find_index, find_name 사용 (아스키코드 x)
// 2) topOrder: 위상순서 저장[1~n]

// 이외 변경사항
// G->vCount 사용x --> n으로 사용
// 사이즈 99로 변경

/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 99  // n < 100

typedef struct
{
	char elem[SIZE];  // 정점 이름
	int front, rear;
}QueueType;

typedef struct IncidentEdge
{
	char aName;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex
{
	char vName;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;

typedef struct
{
	Vertex* vHead;
	int vCount;
}Graph;

char *topOrder; // 방향싸이클 여부와 위상순서 저장

int n;

void initQueue(QueueType* Q)
{
	Q->front = Q->rear = 0;
}

void init(Graph* G)
{
	G->vHead = NULL;
	G->vCount = 0;
}

int isEmpty(QueueType* Q)
{
	return Q->rear == Q->front;
}

int isFull(QueueType* Q)
{
	return (Q->rear + 1) % SIZE == Q->front;
}

void enqueue(QueueType* Q, char vName)
{
	if (isFull(Q))
	{
		printf("FULL\n");
		return;
	}
	Q->rear = (Q->rear + 1) % SIZE;
	Q->elem[Q->rear] = vName;
}

char dequeue(QueueType* Q)
{
	if (isEmpty(Q))
	{
		printf("EMPTY\n");
		return 0;
	}
	Q->front = (Q->front + 1) % SIZE;
	return Q->elem[Q->front];
}

void makeVertex(Graph* G, char vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->iHead = NULL;
	v->next = NULL;
	//G->vCount = G->vCount + 1;

	Vertex* q = G->vHead;
	if (q == NULL)
		G->vHead = v;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = v;
	}
}


//부착리스트의 첫번째에 삽입
void makeIncidentEdge(Vertex* v, char aName)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->next = NULL;

	IncidentEdge* q = v->iHead;
	if (q == NULL) {
		v->iHead = p;
	}
	else
	{
		// 부착리스트에서 새로 입력되는 간선을 맨 앞에 삽입
		p->next = q;
		v->iHead = p;

		//while (q->next != NULL)
		//	q = q->next;
		//q->next = p;

	}
}

Vertex* findVertex(Graph* G, char vName)
{
	Vertex* p = G->vHead;
	while (p->vName != vName)
		p = p->next;
	return p;
}

// 여기만 바뀜
void insertEdge(Graph* G, char v1, char v2)
{
	// 방향그래프 이므로
	Vertex* v = findVertex(G, v1);
	makeIncidentEdge(v, v2);
}

void print(Graph* G)
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

int find_index(Graph *G, char name) {
	int i=0;
	Vertex *p = G->vHead;
	for (; p != NULL; p = p->next) {
		if (p->vName == name) {
			break;
		}
		i++;
	}
	return i;
}

char find_name(Graph *G, int index) {
	int i = 0;
	char name;
	Vertex *p = G->vHead;
	for (; p != NULL; p = p->next) {
		if (index == i) {
			break;
		}
		i++;
	}
	return p->vName;
}

void inDegree(Graph *G, int in[]) {
	Vertex *p = G->vHead;
	IncidentEdge *q;
	int index;
	char name;

	// p가 각 정점을 방문
	for (; p != NULL; p = p->next) {
		// 하나의 정점에 대한 incidentEdge방문
		// edge를 방문하면서 각 edge의 진입간선 차수를 증가시키기
		for (q = p->iHead; q != NULL; q = q->next) {
			// 차수 증가
			index = find_index(G, q->aName);
			in[index]++;
		}
	}
}
void topologicalSort(Graph *G, int in[]) {
	// 정렬을 위한 큐
	QueueType Q;
	initQueue(&Q);
	// vertex와 incidentEdge를 돌아다닐 포인터 두개
	Vertex *p;
	IncidentEdge *q;

	// 각 정점의 차수 계산
	inDegree(G, in);

	char name;
	// 초기 그래프에서 진입차수가 0이면 큐에 넣기
	for (int i = 0; i < n; i++) {
		if (in[i] == 0) {
			name = find_name(G, i);
			enqueue(&Q, name);
		}
	}

	int index;

	int t = 1; // 위상순위
	// 큐가 빌때까지 처리
	while (!isEmpty(&Q)) {
		char vName = dequeue(&Q);

		topOrder[t] = vName;
		t++;
		//printf("%c ", vName);	// 해당 정점이 방문했음을 표시

		// 방문했으므로 다시 갈 수 없음
		// 부착간선의 차수를 감소시킴
		p = findVertex(G, vName);
		q = p->iHead;
		while (q != NULL) {
			index = find_index(G, q->aName);
			in[index]--;
			// 해당 정점의 차수를 확인
			// 차수가 0이면 큐에 삽입
			if (in[index] == 0) {
				enqueue(&Q, q->aName);  // 정점의 인덱스를 큐에 삽입
			}
			q = q->next;
		}
	}
	
	// 방향싸이클인 경우
	if (t <= n) {
		printf("0");
	}
	// 방향싸이클이 아닌 경우, 위상순서 출력
	// 1~n 사용 
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", topOrder[i]);
		}
	}
	
}

void main()
{

	int m;
	char v, v1, v2;
	Graph G;
	init(&G);

	scanf("%d", &n);
	getchar();
	for (int i = 0; i < n; i++) {
		scanf("%c", &v);
		getchar();
		makeVertex(&G, v);
	}
	scanf("%d", &m);
	getchar();
	for (int i = 0; i < m; i++) {
		scanf("%c %c", &v1, &v2);
		getchar();
		insertEdge(&G, v1, v2);
	}

	//print(&G);

	int in[99] = { 0 };

	topOrder = (char*)malloc((n +1) * sizeof(char)); 


	topologicalSort(&G, in);


	return 0;
}
*/