#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 색분리 25p
// 5주차 수업내용과 동일

// 리스트 char 형으로 전달하는 거 잊지 말기!!
void inPlacePartition(char* L, int i, int j) { 
	int tmp;

	while (i <= j) {
		while ((i <= j) && (L[i] == 'B')) {
			i++;
		}
		while ((j >= i) && (L[j] == 'R')) {
			j--;
		}
		if (i < j) { // swap
			tmp = L[i];
			L[i] = L[j];
			L[j] = tmp;
		}
	}
}

int main()
{
	int n = 10;
	char list[10];

	// 무순 리스트 생성
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		if (rand() % 2 == 0) { // 짝수면 파랑
			list[i] = 'B';
		}
		else { // 홀수면 빨강
			list[i] = 'R';	
		}
	}
	// 배열 확인
	for (int i = 0; i < n; i++) {
		printf(" %c", list[i]);
	}
	printf("\n"); 


	getchar();
	inPlacePartition(list, 0, n - 1); // 왼쪽끝, 오른쪽끝

	for (int i = 0; i < n; i++) {
		printf(" %c", list[i]);
	}
	printf("\n");
	return 0;
}
