#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int re[1000]; // 자원의 총 개수, 자원1의 개수, 자원2의 개수..
int prn[1000][1000]; // 프로세스 번호, 자원1 요청 개수, 자원2 요청 개수..
int pan[1000][1000]; // 프로세스 번호, 자원1 할당 개수, 자원2 할당 개수..
int avai[1000]; // 자원의 총 개수, 자원1의 사용가능한 리소스..
int mark[1000] = { 0, };
int w[1000];
int i, j, l, n;

void main() {
	FILE* fp = NULL;
	fp = fopen("deadlock_detection_1000.txt", "r");

	if (fp == NULL) {
		printf("error\n");
		exit(0);
	}

	int ca; // 경우의 수
	fscanf_s(fp, "%d", &ca);

	for (int a = 1; a <= ca; a++) {
		printf("Case #%d:\n", a);

		int pr; // 프로세스 수
		fscanf_s(fp, "%d", &pr);

		int ar; // 자원의 총 개수, ar[0], 
		fscanf_s(fp, "%d", &ar);

		for (int i = 1; i <= ar; i++)  // 각 자원의 총 개수들
			fscanf_s(fp, "%d", &re[i]);

		for (int i = 0; i < pr; i++) { // 요청행렬
			for (int j = 0; j <= ar; j++)
				fscanf_s(fp, "%d", &prn[i][j]);
		}

		for (int i = 0; i < pr; i++) { // 할당행렬
			for (int j = 0; j <= ar; j++)
				fscanf_s(fp, "%d", &pan[i][j]);
		}

		for (int i = 0; i < ar; i++) { // 가용벡터
			avai[i] = re[i + 1];
			for (int j = 0; j < pr; j++)
				avai[i] -= pan[j][i + 1];
		}

		// 할당 없는 프로세스 표시(marked)
		for (int i = 0; i < pr; i++) {
			int count = 0;
			for (int j = 1; j <= ar; j++) {
				if (pan[i][j] == 0)
					count++;
				else
					break;
			}

			if (count == ar) {
				mark[i] = 1;
				if (mark[i] == 1)
					printf("Marked = ( P%d ) ", i + 1); // 처음 0인 할당행렬 marked표시
			}
		}

		// avai의 값으로 W 초기화 
		printf("w = ( ");
		for (int i = 0; i < ar; i++) {
			w[i] = avai[i];
			printf("%d ", w[i]);
		}
		printf(")\n");

		// 요청이 W보다 작거나 같은 프로세스를 표시. (남은 자원 - 요청)
		for (int i = 0; i < pr; i++) {
			int canbeprocessed = 0;
			if (mark[i] == 0) {
				for (int j = 1; j <= ar; j++) {
					if (prn[i][j] <= w[j - 1])
						canbeprocessed = 1;
					else {
						canbeprocessed = 0;
						break;
					}
				}

				if (canbeprocessed) {
					mark[i] = 1;
					printf("Marked = ( ");
					for (int l = 0; l < pr; l++) {
						if (mark[l] == 1)
							printf("P%d ", l + 1);
					}
					printf(") w = ( ");

					for (int n = 1; n < ar + 1; n++) {
						w[n - 1] += pan[i][n];   // 가용 + 할당값 == 가용백터에 할당값 반납
						printf("%d ", w[n - 1]);
					}
					i = -1;
					printf(")\n");
				}
			}
		}

		// 마크되지 않은 프로세스를 검사 
		int dead = 0;
		for (int i = 0; i < pr; i++) {
			if (mark[i] == 0)
				dead = 1;
		}

		if (dead) {
			printf("Deadlock Detected!\n");
			printf("Deadlocked Processes = ( ");
			for (int i = 0; i < pr; i++) {
				if (mark[i] == 0)
					printf("P%d ", i + 1);
			}
			printf(") \n\n");
		}
		else
			printf("No Deadlock!\n\n");

		for (int i = 0; i < 100; i++)
			mark[i] = 0;
	}
	fclose(fp);
}