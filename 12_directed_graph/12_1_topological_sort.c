// ������ �ڵ忡�� ������ �κ�
// 1) find_index, find_name ��� (�ƽ�Ű�ڵ� x)
// 2) topOrder: ������� ����[1~n]

// �̿� �������
// G->vCount ���x --> n���� ���
// ������ 99�� ����

/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 99  // n < 100

typedef struct
{
	char elem[SIZE];  // ���� �̸�
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

char *topOrder; // �������Ŭ ���ο� ������� ����

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


//��������Ʈ�� ù��°�� ����
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
		// ��������Ʈ���� ���� �ԷµǴ� ������ �� �տ� ����
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

// ���⸸ �ٲ�
void insertEdge(Graph* G, char v1, char v2)
{
	// ����׷��� �̹Ƿ�
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

	// p�� �� ������ �湮
	for (; p != NULL; p = p->next) {
		// �ϳ��� ������ ���� incidentEdge�湮
		// edge�� �湮�ϸ鼭 �� edge�� ���԰��� ������ ������Ű��
		for (q = p->iHead; q != NULL; q = q->next) {
			// ���� ����
			index = find_index(G, q->aName);
			in[index]++;
		}
	}
}
void topologicalSort(Graph *G, int in[]) {
	// ������ ���� ť
	QueueType Q;
	initQueue(&Q);
	// vertex�� incidentEdge�� ���ƴٴ� ������ �ΰ�
	Vertex *p;
	IncidentEdge *q;

	// �� ������ ���� ���
	inDegree(G, in);

	char name;
	// �ʱ� �׷������� ���������� 0�̸� ť�� �ֱ�
	for (int i = 0; i < n; i++) {
		if (in[i] == 0) {
			name = find_name(G, i);
			enqueue(&Q, name);
		}
	}

	int index;

	int t = 1; // �������
	// ť�� �������� ó��
	while (!isEmpty(&Q)) {
		char vName = dequeue(&Q);

		topOrder[t] = vName;
		t++;
		//printf("%c ", vName);	// �ش� ������ �湮������ ǥ��

		// �湮�����Ƿ� �ٽ� �� �� ����
		// ���������� ������ ���ҽ�Ŵ
		p = findVertex(G, vName);
		q = p->iHead;
		while (q != NULL) {
			index = find_index(G, q->aName);
			in[index]--;
			// �ش� ������ ������ Ȯ��
			// ������ 0�̸� ť�� ����
			if (in[index] == 0) {
				enqueue(&Q, q->aName);  // ������ �ε����� ť�� ����
			}
			q = q->next;
		}
	}
	
	// �������Ŭ�� ���
	if (t <= n) {
		printf("0");
	}
	// �������Ŭ�� �ƴ� ���, ������� ���
	// 1~n ��� 
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