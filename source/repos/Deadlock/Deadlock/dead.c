#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int i, j, a;
int re[100]; // �ڿ��� �� ����, �ڿ�1�� ����, �ڿ�2�� ����..
int prn[100][100]; // ���μ��� ��ȣ, �ڿ�1 ��û ����, �ڿ�2 ��û ����..
int pan[100][100]; // ���μ��� ��ȣ, �ڿ�1 �Ҵ� ����, �ڿ�2 �Ҵ� ����..
int avai[100]; // �ڿ��� �� ����, �ڿ�1�� ��밡���� ���ҽ�..
int ar; // re[0]=�ڿ��� �� ����
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

	int ca; // ����� ��
	fscanf(fp, "%d", &ca);
	printf("����� �� : %d\n\n", ca);

	for (int a = 1; a <= ca; a++) { // ����� �� for
		printf("Case #%d:\n", a);

		int pr; // ���μ��� ��
		fscanf(fp, "%d", &pr);
		printf("%d\n", pr);

		int ar = 0; // �ڿ� ��, ar[0]
		fscanf(fp, "%d", &ar);
		printf("%d ", ar);

		for (int i = 1; i <= ar; i++) { // re�ڿ��� �� ������
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

		// �Ҵ� ���� ���μ��� ǥ��(marked) //�Ҵ�� �ڿ� == 0
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

		// avail�� ����Ͽ� W �ʱ�ȭ 
		printf("w = ( ");
		for (int j = 0; j < ar; j++) {
			w[j] = avai[j];
			printf("%d ", w[j]);
		}
		printf(")\n");

		// ��û�� W���� �۰ų� ���� ���μ����� ǥ���մϴ�. (���� �ڿ� - ��û)
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
						w[j - 1] += pan[i][j];   //���� + �Ҵ簪 == ������Ϳ� �Ҵ簪 �ݳ�
						printf("%d ", w[j - 1]);
					}
					i = -1;
					printf(")\n");
				}
			}
		}
		// ��ũ���� ���� ���μ����� �˻��Ѵ�. 
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
	}//ca�ݺ��� ������
	fclose(fp);
	return 0;
}