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
	int eCount, vCount;  // 간선과 정점의 개수
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

// edge의 연결리스트 만들기 위해 추가
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
	int i, least; // least: 단계별 min값의 index (기준값)
	Edge *p = G->eHead; // 간선 연결리스트를 따라다닐

	// 그대로 배열에 들어감
	for (i = 0; i < G->eCount; i++) {
		e[i] = p;
		p = p->next;
	}

	// 선택정렬을 이용해서 가중치에 따라 정렬
	for (i = 0; i < G->eCount - 1; i++) {
		least = i;
		for (int j = i + 1; j < G->eCount; j++) {
			if (e[j]->weight < e[least]->weight) {
				least = j;
			}
		}
		// 각 단계의 최소값 도출
		// swap
		p = e[least];
		e[least] = e[i];
		e[i] = p;
	}

	// 확인을 위해 출력
	//for (i = 0; i < G->eCount; i++) {
	//	printf("[%d%d(%d)]", e[i]->v1, e[i]->v2, e[i]->weight);
	//	printf("\n");
	//}

}

// 배열의 값이 -1인 경우: 아무것도 연결되어있지 않음 or 내 위에 아무것도 없다?
int vFind(int v[], int vNum) {
	if (v[vNum] == -1) {
		return vNum;
	}

	while (v[vNum] != -1) { // 연결되어 있음 = 같은 집합임을 의미
		vNum = v[vNum];
	}
	return vNum;
}

void vUnion(int v[], int vNum1, int vNum2) {
	int r1 = vFind(v, vNum1);
	int r2 = vFind(v, vNum2);

	// -1이 될 때까지 같은 집합안에 포함된 연결된 정점들의 인덱스를 받아와서
	// 나와 연결된 정점의 번호(= 같은 집합임을 판단)
	if (r1 != r2) {
		v[r2] = r1;
	}
}

void kruskal(Graph *G, Edge *e[], int v[]) {
	int eCnt = 0, i = 0;  // eCnt: 내가 몇개를 선택했는지
	int vNum1, vNum2, index; // 간선에 연결된 두 정점의 인덱스 (v배열에서의?)
	Edge *p;
	int total_weight = 0;
	// 어떤 정점과 union이 되어있는지를 v배열을 통해 알아낼 것임(인덱스를 통해)

	// eCnt는 n-1까지 돌아야함. 여기서는  n-2까지 돌게할것임. 왜인지 확인
	while (eCnt < G->vCount - 1) {
		p = e[i];
		// a와 f의 union을 알아야 함
		index = find_index(G, p->v1);
		vNum1 = vFind(v, index);// 해당 edge에 연결된 정점
		index = find_index(G, p->v2);
		vNum2 = vFind(v, index);

		// vNum과 vNum2 가 같은 경우, 싸이클을 의미하므로 아래 if문을 수행하지 않고 패스

		// 이 경우 해당 간선은 선택될 수 잇음
		// = 서로 다른 집합을 의미 = 싸이클이 아님을 의미
		if (vNum1 != vNum2) {
			printf(" %d", p->weight);
			total_weight += p->weight;
			// printf("%d. [%d%d (%d)]\n", eCnt + 1, p->v1, p->v2, p->weight);
			// 간선이 선택되어졌으므로
			eCnt++;
			// MST의 일원이 되었으므로 같은 집합으로 만들어야 함
			// = UNION
			vUnion(v, vNum1, vNum2);
		}
		i++; // 다음 간선
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

	// 유니온파인드에서 사용할 배열: 각 정점의 연결모습을 기억
	int *v;
	v = (int*)malloc(n * sizeof(int));

	// 정점 생성과 배열 초기화를 동시에
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

	// 간선의 집합 만들고 오름차순으로 정렬
	Edge* e;
	e = (Edge*)malloc(m * sizeof(Edge));
	incSort(&G, e); // e배열에 넣어서 정렬

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