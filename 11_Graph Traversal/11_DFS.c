#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 1. ���̿켱Ž��

#define FALSE 0
#define TRUE 1

// �� �������� incidentEdge�� ����
// �׷����� ����ġ�� �ʿ��� ��� �߰�
typedef struct IncidentEdge {
	int aName; //adjVertex;
	struct IncidentEdge* next;
}IncidentEdge;

typedef struct Vertex {
	int vName;
	int isVisit; // 1�̸� �湮��
	struct Vertex* next;
	IncidentEdge * iHead; // �� �������� incidentEdge�� ����
}Vertex;

typedef struct {
	Vertex *vHead;
}Graph;


void init(Graph* G) {
	G->vHead = NULL;
}

// ���� ����(Last)
void makeVertex(Graph* G, int vName) {
	Vertex *v = (Vertex*)malloc(sizeof(Vertex));
	v->vName = vName;
	v->next = NULL;
	v->iHead = NULL;   // ������ ������ ������ ������� null
	v->isVisit = FALSE; // isVisit

	// ��������Ʈ ��ȸ
	Vertex * q = G->vHead;

	if (q == NULL) { // ����Ʈ�� ����ִ� ���
		G->vHead = v;
	}
	else {
		while (q->next != NULL) { // ������ ��忡�� ���߱�
			q = q->next;
		}
		q->next = v; // ������ ���� ��
	}
}

// ������������Ʈ�� ���� ���� (������������) 
void insertIncidentEdge(Vertex *v, int aName) {
	IncidentEdge *p = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	p->aName = aName;
	p->next = NULL;

	// �������� ����Ʈ ��ȸ
	IncidentEdge *q = v->iHead;
 
	// ù ����� ���. = p�� ���
	if (q == NULL) { 
		v->iHead = p;
	}
	// aName�� ù ��庸�� ������� �ڽ��� ù ��尡 ��
	else if (q->aName > aName) {
			v->iHead = p;
			p->next = q;
	}
	else {
		while (q->next != NULL) {   
			if (q->next->aName > p->aName) { // ���� ��尡 ������ ũ�� ���� ��带 �о�� ���� �� �ڸ�
				p->next = q->next;
				q->next = p;
				return;
			}
			q = q->next;
		}
		q->next = p;
	}
}

// �׷������� vName�� ���� �ּҸ� ã��
Vertex * findVertex(Graph *G, int vName) {
	Vertex *p = G->vHead;
	while (p->vName != vName) {
		p = p->next;
	}
	return p;
}
// ������ ������ ���� �����
void insertEdge(Graph *G, int v1, int v2) {

	// ������ �׷����̹Ƿ� v1, v2��� 
	// v1�� ��������
	Vertex *v = findVertex(G, v1);
	insertIncidentEdge(v, v2);
	//v2�� ��������
	v = findVertex(G, v2);
	insertIncidentEdge(v, v1);
}

void dfs(Graph *G, int vName) {
	// ����������� �湮 ������� ���� ��ȣ ���
	// Ʈ�������� ���Ⱓ���� ���� ���� ����
	// �湮 ���� = Ʈ������ ����

	Vertex *v = findVertex(G, vName);
	IncidentEdge *p;

	// ���� �湮 ���� �Ǵ�
	if (v->isVisit == FALSE) {
		v->isVisit = TRUE;
		printf("%d \n", v->vName);
	}

	// �湮 ������ ��������Ʈ�� ��ȸ�ϸ鼭 �湮���� �ʾ����� ���ȣ���Ͽ� �湮
	for (p = v->iHead; p != NULL; p = p->next) {
		v = findVertex(G, p->aName);
		if (v->isVisit == FALSE) {
			dfs(G, v->vName);    // ���ȣ��
		}
	}
}

// ������ �������� ���ƴٳ�� ��
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
		makeVertex(&G, i+1); //������������ ���ԉ�
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);
		insertEdge(&G, v1, v2);
	}

	print(&G);
	dfs(&G, s); // ���� ����
}

