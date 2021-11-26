
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct Edge
{
	int v1, v2;
	int weight;
	struct Edge* next;
}Edge;

typedef struct IncidentEdge
{
	int aName;
	Edge* e;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex
{
	int vName;
	int isVisit;
	IncidentEdge* iHead;
	struct Vertex* next;
}Vertex;

typedef struct
{
	Vertex* vHead;
	Edge* eHead;
	int eCount, vCount;  // ������ ������ ����
}Graph;

void init(Graph* G)
{
	G->vHead = NULL;
	G->eHead = NULL;
	G->vCount = G->eCount = 0;
}

void makeVertex(Graph* G, int vName)
{
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->isVisit = FALSE;

	v->iHead = NULL;
	v->next = NULL;
	G->vCount++;

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

void makeIncidentEdge(Vertex* v, int aName, Edge* e)
{
	IncidentEdge* p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->e = e;
	p->next = NULL;
	IncidentEdge* q = v->iHead;
	if (q == NULL)
		v->iHead = p;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = p;
	}
}

Vertex* findVertex(Graph* G, char vName)
{
	Vertex* v = G->vHead;
	while (v->vName != vName)
		v = v->next;
	return v;
}

// edge�� ���Ḯ��Ʈ ����� ���� �߰�
void insertEdge(Graph* G, int v1, int v2, int w)
{
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->weight = w;
	e->v1 = v1;
	e->v2 = v2;
	e->next = NULL;
	G->eCount++;

	Edge* q = G->eHead;
	if (q == NULL)
		G->eHead = e;
	else
	{
		while (q->next != NULL)
			q = q->next;
		q->next = e;
	}
	Vertex* v = findVertex(G, v1);
	makeIncidentEdge(v, v2, e);
	v = findVertex(G, v2);
	makeIncidentEdge(v, v1, e);
}

void print(Graph* G)
{
	Vertex* p = G->vHead;
	IncidentEdge* q;
	for (; p != NULL; p = p->next)
	{
		printf("[%d] : ", p->vName);
		for (q = p->iHead; q != NULL; q = q->next)
			printf("[%d, %d] ", q->aName, q->e->weight);
		printf("\n");
	}
	printf("\n");
}

int find_index(Graph *G, int name) {
	int i = 0;
	Vertex *p = G->vHead;
	for (; p != NULL; p = p->next) {
		if (p->vName == name) {
			break;
		}
		i++;
	}
	return i;
}


// �ּ� ����ġ�� ã��. 
// �迭 d���� �ּҰ��� ���� ������ ����
int getMinVertex(Graph*G, int d[]) {
	Vertex *p = G->vHead;
	int vName, index, min_index;

	// isVist�� false�� �� �� ����ġ �ּҰ��� ã��

	// �湮���� ���� ���� ã��
	for (; p != NULL; p = p->next) {
		if (p->isVisit == FALSE) {
			vName = p->vName;
			break;
		}
	}
	//	printf("�湮���� ���� ����: %d", vName);

		// �迭 d���� �ּҰ��� ���� ������ ����
	for (p = G->vHead; p != NULL; p = p->next) {
		index = find_index(G, p->vName);
		min_index = find_index(G, vName);

		if ((p->isVisit == FALSE) && (d[index] < d[min_index])) {
			vName = p->vName;
		}
	}

	return vName;
}

void prim(Graph *G, int vName, int d[]) {
	// ������ �� ���������� ���� ó��

	Vertex *p = findVertex(G, vName);
	IncidentEdge *q;
	int c, index, min;

	// MST �ѹ��Ը� ���ϴ� total_weight �߰�
	int total_weight = 0;  // MST �ѹ��� 

	// �������� = 1
	index = find_index(G, vName);
	d[index] = 0; // ���� ���� �ʱ�ȭ 

	// ��������
	for (int i = 0; i < G->vCount; i++) {
		// �ּ� ����ġ�� ã��
		// �迭 d���� �ּҰ��� ���� ������ ����
		c = getMinVertex(G, d);
		p = findVertex(G, c);

		p->isVisit = TRUE; // �湮
		printf(" %d", p->vName);

		index = find_index(G, p->vName);
		total_weight += d[index];

		// ���õ� ������ ������������ weight ������Ʈ
		for (q = p->iHead; q != NULL; q = q->next) {
			p = findVertex(G, q->aName);
			// weight�� �� ���� ��쿡�� ������Ʈ
			if (p->isVisit == FALSE) {
				index = find_index(G, q->aName);

				if (q->e->weight < d[index]) {
					d[index] = q->e->weight;
				}

		//		printf("(%d %d)", q->aName, d[q->aName - 1]);
			}
		}
		//	printf("\n");
	}
	printf("\n");
	//	printf("%d", total_weight);
}


int main()
{
	int n, m, w, v1, v2;
	Graph G;
	init(&G);

	scanf("%d %d", &n, &m);

	// distance �迭: �� ������ ����Ǿ��ִ� �������� ����ġ ���� ����ϴ� �迭
	int *d;
	d = (int*)malloc(n * sizeof(int));

	// ���� ������ �迭 �ʱ�ȭ�� ���ÿ�
	for (int i = 1; i <= n; i++) {
		makeVertex(&G, i);
		d[i - 1] = 1000;
	}
	getchar();
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		insertEdge(&G, v1, v2, w);
	}

	//print(&G);

	// ���� 1���� ����
	prim(&G, 1, d);


	int total = 0;
	for (int i = 0; i < n; i++) {
		//	printf("%d", d[i]);
		total += d[i];
	}
	//	printf("\n");
	printf("%d", total);

}



/*
6 9
1 2 2
1 3 6
1 5 7
2 3 5
2 4 7
3 4 9
3 5 8
4 6 4
5 6 3
*/

/*
5 7
1 2 1
1 4 2
1 5 4
2 5 7
4 5 3
3 5 5
2 3 6
*/