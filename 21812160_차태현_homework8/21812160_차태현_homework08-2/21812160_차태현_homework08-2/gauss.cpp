#include<stdio.h>
#include <math.h>
#include"mtrx.h"
#define EPSILON 0.000001

void fgetAugmentedMtrx(FILE* fin, double** dM, int size_N)//���Ϸκ��� ��İ� �޾ƿ���
{
	double data = 0.0;

	for (int i = 0; i < size_N; i++)
		for (int j = 0; j <= size_N; j++)
		{
			if (fscanf(fin, "%lf", &data) != EOF)
				dM[i][j] = data;
		}

}
void pivoting(double **augMtrx,int size_N,int p,int *piv)
{
	double max = 0.0;
	double temp;
	int max_row;

	max = fabs(augMtrx[p][p]);
	max_row = p;

	for (int i = p + 1; i < size_N; i++)
	{
		if (fabs(augMtrx[i][p]) > max)
		{
			max = fabs(augMtrx[i][p]);
			max_row = i;
		}
	}
	
	if (fabs(max) < EPSILON)
		*piv = 0;
	else
	{
		*piv = 1;
		if (max_row != p)
		{
			for (int j = p; j <= size_N; j++)
			{
				temp = augMtrx[p][j];
				augMtrx[p][j] = augMtrx[max_row][j];
				augMtrx[max_row][j] = temp;
			}
		}
	}
}

void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist)
{
	int  p = 0;
	double pivWeight, w;

	for (p = 0; ((*solExist) && (p < size_N)); p++)//solExist���̰� p�� �־��� ũ�⺸�� ������쿡 ����
	{
		fprintf(fout, "\nPivting at p= %d\n", p);
		pivoting(mtrxAug, size_N, p, solExist);//�ֻ��� �� ã�Ƽ� ��ġ ��ȯ
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);
		if (*solExist)
		{
			if (mtrxAug[p][p] != 1.0)
			{
				pivWeight = mtrxAug[p][p];
				mtrxAug[p][p] = 1.0;//���ذ���  1.0���� ��ȯ
				for (int i = p + 1; i <= size_N; i++)
				{
					mtrxAug[p][i] /= pivWeight; //������ ������ ���ذ����� �� ��������
				}

			}
		}
		else
			break;

		fprintf(fout, "\nAfter scaling at p = %d\n", p);
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);

		for (int j = 0; j < size_N; j++) //p,p ��° ������ ������ 0.0���� ����
		{
			if ((j != p) && (mtrxAug[j][p] != 0.0))
			{
				w = mtrxAug[j][p];
				mtrxAug[j][p] = 0.0;

				for (int k = p + 1; k <= size_N; k++)
				{
					mtrxAug[j][k] = mtrxAug[j][k] - w * mtrxAug[p][k]; //�������� ���ذ��� �ƴѰ��� 0.0 ���� ������ִ°��� ���࿡�ٰ� ����
				}
			}
		}

		fprintf(fout, "\nAfter diagonallzing at p = %d\n", p);
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);
	}
}