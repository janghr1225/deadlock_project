#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int i, j, a;
int re[100]; // 자원의 총 개수, 자원1의 개수, 자원2의 개수..
int prn[100][100]; // 프로세스 번호, 자원1 요청 개수, 자원2 요청 개수..
int pan[100][100]; // 프로세스 번호, 자원1 할당 개수, 자원2 할당 개수..
int avai[100]; // 자원의 총 개수, 자원1의 사용가능한 리소스..
int ar; // re[0]=자원의 총 개수
int count;
int mark[100] = { 0. };
int w[100];

int main()
{
	FILE* fp = NULL;
	fp = fopen("deadlock_detection_1000.txt", "r");
	if (fp == NULL) {
		printf("error\n");
		exit(0);
	}

	int ca; // 경우의 수
	fscanf(fp, "%d", &ca);
	printf("경우의 수 : %d\n\n", ca);

	for (int a = 1; a <= ca; a++) { // 경우의 수 for
		printf("Case #%d:\n", a);

		int pr; // 프로세스 수
		fscanf(fp, "%d", &pr);
		printf("%d\n", pr);

		int ar = 0; // 자원 수, ar[0]
		fscanf(fp, "%d", &ar);
		printf("%d ", ar);

		for (int i = 1; i <= ar; i++) { // re자원의 총 개수들
			fscanf(fp, "%d", &re[i]);
			printf("%d ", re[i]);
		}
		printf("\n");

		for (int i = 0; i < pr; i++) {
			for (int j = 0; j <= ar; j++) {
				fscanf(fp, "%d", &prn[i][j]);
				printf("%d ", prn[i][j]);
			}
			printf("\n");
		}

		for (int i = 0; i < pr; i++) {
			for (int j = 0; j <= ar; j++) {
				fscanf(fp, "%d", &pan[i][j]);
				printf("%d ", pan[i][j]);
			}
			printf("\n");
		}

		printf("allocation vector : ");
		for (int i = 0; i < ar; i++) {
			avai[i] = re[i + 1];
			for (int j = 0; j < pr; j++)
				avai[i] -= pan[j][i + 1];
			printf("%d ", avai[i]);
		}
		printf("\n");

		// 할당 없는 프로세스 표시(marked) //할당된 자원 == 0
		for (int i = 0; i < pr; i++)
		{
			int count = 0;
			for (int j = 1; j <= ar; j++)
			{
				if (pan[i][j] == 0)
					count++;
				else
					break;
			}

			if (count == ar) {
				mark[i] = 1;   //i==3
				if (mark[i] == 1)
					printf("Marked = (P%d ), ", i + 1);
			}
		}

		// avail을 사용하여 W 초기화 
		printf("w = ( ");
		for (int j = 0; j < ar; j++) {
			w[j] = avai[j];
			printf("%d ", w[j]);
		}
		printf(")\n");

		// 요청이 W보다 작거나 같은 프로세스를 표시합니다. (남은 자원 - 요청)
		for (int i = 0; i < pr; i++)
		{
			int canbeprocessed = 0;
			if (mark[i] == 0)
			{
				for (int j = 1; j <= ar; j++)
				{
					if (prn[i][j] <= w[j - 1])
						canbeprocessed = 1;
					else
					{
						canbeprocessed = 0;
						break;
					}
				}
				if (canbeprocessed)
				{
					mark[i] = 1;
					printf("Marked = (P%d ), ", i + 1);
					printf("w = ( ");
					for (int j = 1; j < ar + 1; j++) {
						w[j - 1] += pan[i][j];   //가용 + 할당값 == 가용백터에 할당값 반납
						printf("%d ", w[j - 1]);
					}
					i = -1;
					printf(")\n");
				}
			}
		}
		// 마크되지 않은 프로세스를 검사한다. 
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
	}//ca반복문 마지막
	fclose(fp);
	return 0;
}