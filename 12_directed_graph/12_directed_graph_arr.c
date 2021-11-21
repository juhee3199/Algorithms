
/*
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//방향그래프-인접리스트(배열로 구현)

// 큐 수정, inEdges(진입간선) 삭제

#define SIZE 99

typedef struct
{
	char elem[SIZE];  // 정점 이름
	int front, rear;
}QueueType;


//간선 구조체
typedef struct edge {
	int st, end;
}Edge;

// 각 정점의 진출간선리스트를 위한 간선 노드
typedef struct node {
	int edge;
	struct node *next;
	int data;
}Node;

//정점 구조체
typedef struct vertex {
	char name;
	Node *outEdges;
	int inDegree;
}Vertex;

//그래프 구조체
typedef struct graph {
	Vertex *verticies;//정점배열
	Edge *edges;//간선배열
	int nv, ne;//정점 수, 간선 수
}Graph;


int n, m;//정점 수, 간선 수
Graph *g;//그래프
int *Q;
int *topOrder;
int *in;



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




//그래프 초기화
void initGraph() {
	g = (Graph*)malloc(sizeof(Graph));
	g->verticies = NULL;
	g->edges = NULL;
}

//정점 추가
Graph* insertVertex(char name, int i) {
	g->verticies[i].name = name;
	g->verticies[i].outEdges = (Node*)malloc(sizeof(Node));
	g->verticies[i].outEdges->next = NULL;
	g->verticies[i].inDegree = 0;
	return g;
}
//정점 인덱스 찾기
int index(char name) {
	int i;
	for (i = 0; i < g->nv; i++) {
		if (g->verticies[i].name == name) {
			break;
		}
	}
	return i;
}
//부착리스트의 첫번째에 노드 삽입
void addFirst(Node *H, int i) {
	Node *newnode;
	newnode = (Node *)malloc(sizeof(Node));
	newnode->edge = i;//노드에 간선의 인덱스 저장
	newnode->next = H->next;
	H->next = newnode;
}
//간선 추가
Graph* insertDirectedEdge(char st, char end, int i) {
	int u, w;

	//간선 추가
	u = index(st);
	w = index(end);
	g->edges[i].st = u;
	g->edges[i].end = w;
	//부착리스트 추가
	addFirst(g->verticies[u].outEdges, i);
	g->verticies[w].inDegree = g->verticies[w].inDegree + 1;
	return g;
}
//그래프 구축
Graph* buildGraph() {
	int i;
	char name, st, end;

	initGraph();
	scanf("%d", &n);
	getchar();
	g->nv = n;
	g->verticies = (Vertex*)malloc(n * sizeof(Vertex));
	in = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++) {
		scanf("%c", &name);
		getchar();
		g = insertVertex(name, i);
	}

	scanf("%d", &m);
	getchar();
	g->ne = m;
	g->edges = (Edge*)malloc(m * sizeof(Edge));
	for (i = 0; i < m; i++) {
		scanf("%c %c", &st, &end);
		getchar();
		g = insertDirectedEdge(st, end, i);
	}
	topOrder = (int*)malloc((n + 1) * sizeof(int));
	return g;
}

//위상 정렬
void topologicalSort() {
	int t, i, u, w;
	Node *tmp;

	// 정렬을 위한 큐
	QueueType Q;
	initQueue(&Q);

	for (i = 0; i < n; i++) {
		in[i] = g->verticies[i].inDegree;
		if (in[i] == 0) {//진입차수가 0인 경우
			enqueue(&Q, i); // enqueue(&Q, i + 65);//정점의 인덱스 i를 큐에 삽입
		}
	}

	t = 1;
	while (!isEmpty(&Q)) {//큐가 비지 않은 동안
		u = dequeue(&Q);//큐 삭제
		topOrder[t] = u;//topOrder에 정점의 인덱스 저장
		t++;

		tmp = g->verticies[u].outEdges->next;
		while (tmp != NULL) {
			i = tmp->edge;
			w = g->edges[i].end;
			in[w] = in[w] - 1;
			if (in[w] == 0) {//진입차수가 0이면
				enqueue(&Q, w); // enqueue(&Q, q->aName); 
			}
			tmp = tmp->next;
		}
	}

	if (t <= n) {
		topOrder[0] = 0;
	}
	else {
		topOrder[0] = 1;
	}
}

void main() {
	int i, u;

	g = buildGraph();
	topologicalSort();
	//위상순서 or 방향 싸이클
	if (topOrder[0] == 0) {
		printf("0\n");
	}
	else {
		for (i = 1; i <= n; i++) {
			u = topOrder[i];
			printf("%c ", g->verticies[u].name);
		}
	}
}

*/


