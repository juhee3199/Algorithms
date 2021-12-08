// �������α׷��� �����ذ�
// ȸ�翡�� �������� �ִ� ��� ���ϱ�

// 1. ��������� ����
// �ð��� �ʹ� �����ɸ��� ���� ����

// 2. �������α׷���
// ���� �ذ��ϴ� ��� = �������α׷���
// ��������� �ι����� Ǯ���. �ߺ������ ����

// ��ȭ���� ���� �迭�� ���� ����ϸ� �����


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define M 100
#define N 100

int map[M][N];
int path[M][N];

// 1. ��������� ����
// ��ü ����� ���� return
int num_path(int m, int n) {
	if (map[m][n] == 0) {
		return 0;
	}
	if (m == 0 && n == 0) {
		return 1;
	}
	// ��������� ����
	return ((m > 0) ? num_path(m - 1, n) : 0) + ((n > 0) ? num_path(m, n - 1) : 0);
}
// 2. �������α׷���
int calc_path(int m, int n) {
	int i, j;

	path[0][0] = map[0][0]; // �ʱ�ȭ

	// 1. j�� 0�� ��
	for (i = 1; i < m; i++) {
		if (map[i][0] == 0) {
			path[i][0] = 0;
		}
		else {
			path[i][0] = path[i - 1][0];
		}
	}

	// 2. i�� 0�� ��
	for (j = 1; j < m; j++) {
		if (map[0][j] == 0) {
			path[0][j] = 0;
		}
		else {
			path[0][j] = path[0][j-1];
		}
	}

	// 3. i, j�� 0���� Ŭ ��
	for (i = 1; i < m; i++) {
		for (j = 1; j < m; j++) {
			if (map[i][j] == 0) {
				path[i][j] = 0;
			}
			else {
				path[i][j] = path[i - 1][j] + path[i][j - 1];
			}
		}
	}

	return path[m - 1][n - 1];
}
void print(int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", path[i][j]);
		}
		printf("\n");
	}
}
int main() {
	int m, n;

	// 2���� �迭 �Է�
	scanf("%d %d", &m, &n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	// ��ͷ� �ִܰ�� ���ϱ�
	printf("��ͷ� �ִܰ�� ���ϱ�\n");
	printf("%d\n", num_path(m - 1, n - 1));

	// �������α׷���
	printf("�������α׷������� �ִܰ�� ���ϱ�\n");
	printf("%d\n", calc_path(m, n));
	print(m, n);
}



/*
// �տ��� ���÷� �� �迭

5 5
1 1 1 1 1
1 1 0 0 1
1 1 1 1 1
1 1 1 0 1
0 0 1 1 1
*/


// ��ο� ����ġ �ο��� ���
// �ִ� ��� �� ����ġ�� max�� ��츦 ã�� ����

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define M 100
#define N 100
#define max(x, y) ((x)>(y) ? (x) : (y))

int map[M][N];
int joy[M][N];

// �������α׷������� ����
// joy�迭�� ����
void calc_joy(int m, int n) {
	int i, j;

	joy[0][0] = map[0][0]; // �ʱ�ȭ

	// 1. j�� 0�� ��
	for (i = 1; i < m; i++) {
		joy[i][0] = joy[i - 1][0] + map[i][0];
	}

	// 2. i�� 0�� ��
	for (j = 1; j < m; j++) {
		joy[0][j] = joy[0][j-1] + map[0][j];
	}

	// 3. i, j�� 0���� Ŭ ��
	for (i = 1; i < m; i++) {
		for (j = 1; j < m; j++) {
			// �ִ밪�� ��� ã���� ��
			joy[i][j] = max(joy[i-1][j], joy[i][j-1]) + map[i][j]; 
		}
	}

}

void print(int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			printf("%02d ", joy[i][j]);
		}
		printf("\n");
	}
}
int main() {
	int m, n;

	// 2���� �迭 �Է�
	scanf("%d %d", &m, &n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	calc_joy(m, n);
	printf("\n");
	print(m, n);   // ��ȣ���� 22�� ��µǴ� ���� Ȯ��

	// �ְ��� ��ȣ�� 22�� ã���ִ� ��θ� ã�� �ڵ� �����غ���!

	return 0;
}


/*
// �Է°�

5 5
1 2 2 1 5
1 4 4 3 1
2 1 1 1 2
1 3 5 1 1
1 5 1 2 2
*/

/*
// ��� ��

01 03 05 06 11
02 07 11 14 15
04 08 12 15 17
05 11 17 18 19
06 16 18 20 22
*/