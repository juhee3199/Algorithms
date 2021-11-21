
/*
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

//����׷���-��������Ʈ(�迭�� ����)

// ť ����, inEdges(���԰���) ����

#define SIZE 99

typedef struct
{
	char elem[SIZE];  // ���� �̸�
	int front, rear;
}QueueType;


//���� ����ü
typedef struct edge {
	int st, end;
}Edge;

// �� ������ ���Ⱓ������Ʈ�� ���� ���� ���
typedef struct node {
	int edge;
	struct node *next;
	int data;
}Node;

//���� ����ü
typedef struct vertex {
	char name;
	Node *outEdges;
	int inDegree;
}Vertex;

//�׷��� ����ü
typedef struct graph {
	Vertex *verticies;//�����迭
	Edge *edges;//�����迭
	int nv, ne;//���� ��, ���� ��
}Graph;


int n, m;//���� ��, ���� ��
Graph *g;//�׷���
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




//�׷��� �ʱ�ȭ
void initGraph() {
	g = (Graph*)malloc(sizeof(Graph));
	g->verticies = NULL;
	g->edges = NULL;
}

//���� �߰�
Graph* insertVertex(char name, int i) {
	g->verticies[i].name = name;
	g->verticies[i].outEdges = (Node*)malloc(sizeof(Node));
	g->verticies[i].outEdges->next = NULL;
	g->verticies[i].inDegree = 0;
	return g;
}
//���� �ε��� ã��
int index(char name) {
	int i;
	for (i = 0; i < g->nv; i++) {
		if (g->verticies[i].name == name) {
			break;
		}
	}
	return i;
}
//��������Ʈ�� ù��°�� ��� ����
void addFirst(Node *H, int i) {
	Node *newnode;
	newnode = (Node *)malloc(sizeof(Node));
	newnode->edge = i;//��忡 ������ �ε��� ����
	newnode->next = H->next;
	H->next = newnode;
}
//���� �߰�
Graph* insertDirectedEdge(char st, char end, int i) {
	int u, w;

	//���� �߰�
	u = index(st);
	w = index(end);
	g->edges[i].st = u;
	g->edges[i].end = w;
	//��������Ʈ �߰�
	addFirst(g->verticies[u].outEdges, i);
	g->verticies[w].inDegree = g->verticies[w].inDegree + 1;
	return g;
}
//�׷��� ����
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

//���� ����
void topologicalSort() {
	int t, i, u, w;
	Node *tmp;

	// ������ ���� ť
	QueueType Q;
	initQueue(&Q);

	for (i = 0; i < n; i++) {
		in[i] = g->verticies[i].inDegree;
		if (in[i] == 0) {//���������� 0�� ���
			enqueue(&Q, i); // enqueue(&Q, i + 65);//������ �ε��� i�� ť�� ����
		}
	}

	t = 1;
	while (!isEmpty(&Q)) {//ť�� ���� ���� ����
		u = dequeue(&Q);//ť ����
		topOrder[t] = u;//topOrder�� ������ �ε��� ����
		t++;

		tmp = g->verticies[u].outEdges->next;
		while (tmp != NULL) {
			i = tmp->edge;
			w = g->edges[i].end;
			in[w] = in[w] - 1;
			if (in[w] == 0) {//���������� 0�̸�
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
	//������� or ���� ����Ŭ
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


