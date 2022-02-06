#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int re[1000]; // �ڿ��� �� ����, �ڿ�1�� ����, �ڿ�2�� ����..
int prn[1000][1000]; // ���μ��� ��ȣ, �ڿ�1 ��û ����, �ڿ�2 ��û ����..
int pan[1000][1000]; // ���μ��� ��ȣ, �ڿ�1 �Ҵ� ����, �ڿ�2 �Ҵ� ����..
int avai[1000]; // �ڿ��� �� ����, �ڿ�1�� ��밡���� ���ҽ�..
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

	int ca; // ����� ��
	fscanf_s(fp, "%d", &ca);

	for (int a = 1; a <= ca; a++) {
		printf("Case #%d:\n", a);

		int pr; // ���μ��� ��
		fscanf_s(fp, "%d", &pr);

		int ar; // �ڿ��� �� ����, ar[0], 
		fscanf_s(fp, "%d", &ar);

		for (int i = 1; i <= ar; i++)  // �� �ڿ��� �� ������
			fscanf_s(fp, "%d", &re[i]);

		for (int i = 0; i < pr; i++) { // ��û���
			for (int j = 0; j <= ar; j++)
				fscanf_s(fp, "%d", &prn[i][j]);
		}

		for (int i = 0; i < pr; i++) { // �Ҵ����
			for (int j = 0; j <= ar; j++)
				fscanf_s(fp, "%d", &pan[i][j]);
		}

		for (int i = 0; i < ar; i++) { // ���뺤��
			avai[i] = re[i + 1];
			for (int j = 0; j < pr; j++)
				avai[i] -= pan[j][i + 1];
		}

		// �Ҵ� ���� ���μ��� ǥ��(marked)
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
					printf("Marked = ( P%d ) ", i + 1); // ó�� 0�� �Ҵ���� markedǥ��
			}
		}

		// avai�� ������ W �ʱ�ȭ 
		printf("w = ( ");
		for (int i = 0; i < ar; i++) {
			w[i] = avai[i];
			printf("%d ", w[i]);
		}
		printf(")\n");

		// ��û�� W���� �۰ų� ���� ���μ����� ǥ��. (���� �ڿ� - ��û)
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
						w[n - 1] += pan[i][n];   // ���� + �Ҵ簪 == ������Ϳ� �Ҵ簪 �ݳ�
						printf("%d ", w[n - 1]);
					}
					i = -1;
					printf(")\n");
				}
			}
		}

		// ��ũ���� ���� ���μ����� �˻� 
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