#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

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

Vertex* findVertex(Graph* G, int vName)
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


void incSort(Graph *G, Edge *e[]) {
	int i, least; // least: �ܰ躰 min���� index (���ذ�)
	Edge *p = G->eHead; // ���� ���Ḯ��Ʈ�� ����ٴ�

	// �״�� �迭�� ��
	for (i = 0; i < G->eCount; i++) {
		e[i] = p;
		p = p->next;
	}

	// ���������� �̿��ؼ� ����ġ�� ���� ����
	for (i = 0; i < G->eCount - 1; i++) {
		least = i;
		for (int j = i + 1; j < G->eCount; j++) {
			if (e[j]->weight < e[least]->weight) {
				least = j;
			}
		}
		// �� �ܰ��� �ּҰ� ����
		// swap
		p = e[least];
		e[least] = e[i];
		e[i] = p;
	}

	// Ȯ���� ���� ���
	//for (i = 0; i < G->eCount; i++) {
	//	printf("[%d%d(%d)]", e[i]->v1, e[i]->v2, e[i]->weight);
	//	printf("\n");
	//}

}

// �迭�� ���� -1�� ���: �ƹ��͵� ����Ǿ����� ���� or �� ���� �ƹ��͵� ����?
int vFind(int v[], int vNum) {
	if (v[vNum] == -1) {
		return vNum;
	}

	while (v[vNum] != -1) { // ����Ǿ� ���� = ���� �������� �ǹ�
		vNum = v[vNum];
	}
	return vNum;
}

void vUnion(int v[], int vNum1, int vNum2) {
	int r1 = vFind(v, vNum1);
	int r2 = vFind(v, vNum2);

	// -1�� �� ������ ���� ���վȿ� ���Ե� ����� �������� �ε����� �޾ƿͼ�
	// ���� ����� ������ ��ȣ(= ���� �������� �Ǵ�)
	if (r1 != r2) {
		v[r2] = r1;
	}
}

void kruskal(Graph *G, Edge *e[], int v[]) {
	int eCnt = 0, i = 0;  // eCnt: ���� ��� �����ߴ���
	int vNum1, vNum2, index; // ������ ����� �� ������ �ε��� (v�迭������?)
	Edge *p;
	int total_weight = 0;
	// � ������ union�� �Ǿ��ִ����� v�迭�� ���� �˾Ƴ� ����(�ε����� ����)

	// eCnt�� n-1���� ���ƾ���. ���⼭��  n-2���� �����Ұ���. ������ Ȯ��
	while (eCnt < G->vCount - 1) {
		p = e[i];
		// a�� f�� union�� �˾ƾ� ��
		index = find_index(G, p->v1);
		vNum1 = vFind(v, index);// �ش� edge�� ����� ����
		index = find_index(G, p->v2);
		vNum2 = vFind(v, index);

		// vNum�� vNum2 �� ���� ���, ����Ŭ�� �ǹ��ϹǷ� �Ʒ� if���� �������� �ʰ� �н�

		// �� ��� �ش� ������ ���õ� �� ����
		// = ���� �ٸ� ������ �ǹ� = ����Ŭ�� �ƴ��� �ǹ�
		if (vNum1 != vNum2) {
			printf(" %d", p->weight);
			total_weight += p->weight;
			// printf("%d. [%d%d (%d)]\n", eCnt + 1, p->v1, p->v2, p->weight);
			// ������ ���õǾ������Ƿ�
			eCnt++;
			// MST�� �Ͽ��� �Ǿ����Ƿ� ���� �������� ������ ��
			// = UNION
			vUnion(v, vNum1, vNum2);
		}
		i++; // ���� ����
	}

	printf("\n");
	printf("%d", total_weight);
}

int main()
{
	int n, m, w, v1, v2;
	Graph G;
	init(&G);

	scanf("%d %d", &n, &m);

	// ���Ͽ����ε忡�� ����� �迭: �� ������ �������� ���
	int *v;
	v = (int*)malloc(n * sizeof(int));

	// ���� ������ �迭 �ʱ�ȭ�� ���ÿ�
	for (int i = 1; i <= n; i++) {
		makeVertex(&G, i);
		v[i - 1] = -1;
	}
	getchar();
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		insertEdge(&G, v1, v2, w);
	}

	//print(&G);

	// ������ ���� ����� ������������ ����
	Edge* e;
	e = (Edge*)malloc(m * sizeof(Edge));
	incSort(&G, e); // e�迭�� �־ ����

	// kruskal
	kruskal(&G, e, v);
}



/*
6 9
1 2 3
1 3 20
2 4 25
2 5 17
3 4 34
3 5 1
3 6 12
4 5 5
5 6 37
*/

/*
5 7
1 2 75
1 4 95
1 3 51
2 4 9
4 3 19
4 5 42
3 5 31
*/