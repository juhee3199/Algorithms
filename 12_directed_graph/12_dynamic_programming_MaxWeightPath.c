// 동적프로그래밍 문제해결
// 회사에서 집까지의 최단 경로 구하기

// 1. 재귀적으로 구현
// 시간이 너무 오래걸리는 문제 존재

// 2. 동적프로그래밍
// 빨리 해결하는 방법 = 동적프로그래밍
// 상향식으로 부문제를 풀어나감. 중복계산을 없앰

// 점화식을 따라서 배열의 값을 기록하며 계산함


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define M 100
#define N 100

int map[M][N];
int path[M][N];

// 1. 재귀적으로 구현
// 전체 경로의 개수 return
int num_path(int m, int n) {
	if (map[m][n] == 0) {
		return 0;
	}
	if (m == 0 && n == 0) {
		return 1;
	}
	// 재귀적으로 구현
	return ((m > 0) ? num_path(m - 1, n) : 0) + ((n > 0) ? num_path(m, n - 1) : 0);
}
// 2. 동적프로그래밍
int calc_path(int m, int n) {
	int i, j;

	path[0][0] = map[0][0]; // 초기화

	// 1. j가 0일 때
	for (i = 1; i < m; i++) {
		if (map[i][0] == 0) {
			path[i][0] = 0;
		}
		else {
			path[i][0] = path[i - 1][0];
		}
	}

	// 2. i가 0일 때
	for (j = 1; j < m; j++) {
		if (map[0][j] == 0) {
			path[0][j] = 0;
		}
		else {
			path[0][j] = path[0][j-1];
		}
	}

	// 3. i, j가 0보다 클 때
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

	// 2차원 배열 입력
	scanf("%d %d", &m, &n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	// 재귀로 최단경로 구하기
	printf("재귀로 최단경로 구하기\n");
	printf("%d\n", num_path(m - 1, n - 1));

	// 동적프로그래밍
	printf("동적프로그래밍으로 최단경로 구하기\n");
	printf("%d\n", calc_path(m, n));
	print(m, n);
}



/*
// 앞에서 예시로 든 배열

5 5
1 1 1 1 1
1 1 0 0 1
1 1 1 1 1
1 1 1 0 1
0 0 1 1 1
*/


// 경로에 가중치 부여한 경우
// 최단 경로 중 가중치가 max인 경우를 찾는 문제

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define M 100
#define N 100
#define max(x, y) ((x)>(y) ? (x) : (y))

int map[M][N];
int joy[M][N];

// 동적프로그래밍으로 구현
// joy배열을 만듦
void calc_joy(int m, int n) {
	int i, j;

	joy[0][0] = map[0][0]; // 초기화

	// 1. j가 0일 때
	for (i = 1; i < m; i++) {
		joy[i][0] = joy[i - 1][0] + map[i][0];
	}

	// 2. i가 0일 때
	for (j = 1; j < m; j++) {
		joy[0][j] = joy[0][j-1] + map[0][j];
	}

	// 3. i, j가 0보다 클 때
	for (i = 1; i < m; i++) {
		for (j = 1; j < m; j++) {
			// 최대값을 계속 찾도록 함
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

	// 2차원 배열 입력
	scanf("%d %d", &m, &n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	calc_joy(m, n);
	printf("\n");
	print(m, n);   // 선호도가 22로 출력되는 것을 확인

	// 최고의 선호도 22를 찾아주는 경로를 찾는 코드 생각해보기!

	return 0;
}


/*
// 입력값

5 5
1 2 2 1 5
1 4 4 3 1
2 1 1 1 2
1 3 5 1 1
1 5 1 2 2
*/

/*
// 출력 값

01 03 05 06 11
02 07 11 14 15
04 08 12 15 17
05 11 17 18 19
06 16 18 20 22
*/