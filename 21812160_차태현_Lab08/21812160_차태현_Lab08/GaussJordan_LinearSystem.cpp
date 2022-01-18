#include<stdio.h>
#include <math.h>
#include<stdlib.h>
#include"Mtrx.h"
#define EPSILON 0.000001
void pivoting(double** augMtrx, int size_N, int p, int* piv_found)//����ġ��ȯ
{
	double max = 0, temp;
	int max_row;

	max = fabs(augMtrx[p][p]); 
	max_row=p;
	
	for (int i = p + 1; i < size_N; i++)
	{
		if (fabs(augMtrx[i][p]) > max) //�� ���� p��° ���� �ִ밪 ã��
		{
			max = fabs(augMtrx[i][p]);
			max_row = i;
		}
	}
	if (fabs(max) < EPSILON)
		*piv_found = 0;
	else
	{
		*piv_found = 1;
		if (max_row != p)
		{
			for (int j = p; j <= size_N; j++) //�ʱ��� ����ġ�� �ٸ��ٸ� �ִ밪�� ������������� ������
			{
				temp = augMtrx[p][j];
				augMtrx[p][j] = augMtrx[max_row][j];
				augMtrx[max_row][j] = temp;
			}
		}
	}

}
void getAugmentedMtrx(FILE* fin, double** dM, int size_N)//���Ϸκ��� ��İ� �޾ƿ���
{
	double data = 0.0;

	for (int i = 0; i < size_N; i++)
		for (int j = 0; j <= size_N; j++)
		{
			if (fscanf(fin, "%lf", &data) != EOF)
				dM[i][j] = data;
		}

}

void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist)
{
	int  p = 0;
	double pivWeight, w;

	for (p = 0; (*solExist) && (p < size_N); p++)//solExist���̰� p�� �־��� ũ�⺸�� ������쿡 ����
	{
		fprintf(fout, "\nPivting at p= %d\n", p);
		pivoting(mtrxAug, size_N, p, solExist);//�ֻ��� �� ã�Ƽ� ��ġ ��ȯ
		fprintMtrx_double(fout, mtrxAug, size_N, size_N + 1);
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
		fprintMtrx_double(fout, mtrxAug, size_N, size_N + 1);

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
		fprintMtrx_double(fout, mtrxAug, size_N, size_N + 1);
	}
}
void invMtrxGaussJordanElim_FileOut(FILE* fout, double** mA, double** inv_A, int size_N)
{
	int p = 0;
	double pivwieght, w;
	double** mAUG;

	mAUG = (double**)calloc(size_N, sizeof(double*));
	for (int i = 0; i < size_N; i++)
	{
		mAUG[i] = (double*)calloc(size_N * 2, sizeof(double));//nx2n�����迭 ����
	}
	for (int j = 0; j < size_N; j++)
	{
		for (int k = 0; k < size_N; k++)//A��� ����
			mAUG[j][k] = mA[j][k];

		for (int k = size_N; k < size_N * 2; k++)//���� 2n�κп� ������Ļ���
			mAUG[j][k] = (k == (j + size_N)) ? 1.0 : 0.0;
	}

	for (p = 0; p < size_N; p++)//A����� ������ķ� ������ִ°���
	{
		if (mAUG[p][p] != 1.0)
		{
			pivwieght = mAUG[p][p];//pp��° 1.0���� ����� ����
			mAUG[p][p] = 1.0;
			for (int k = p + 1; k < size_N * 2; k++)
				mAUG[p][k] /= pivwieght;//���� �࿡ ������ ������ pp��° ������ ��������
		}
		fprintf(fout, "After scaling at p = %d\n", p);
		fprintMtrx_double(fout, mAUG, size_N, size_N * 2);

		for (int m = 0; m < size_N; m++)
		{
			if ((m != p) && (mAUG[m][p]) != 0.0)
			{
				w = mAUG[m][p];
				mAUG[m][p] = 0.0;
				for (int n = p + 1; n < size_N * 2; n++)
					mAUG[m][n] = mAUG[m][n] - w * mAUG[p][n];//���� 0.0���� ����� ���� �������� ������������ 0.0�� ��������� ����� ������ ����
			}
		}

		fprintf(fout, "After diagonalizing at p = %d\n", p);
		fprintMtrx_double(fout, mAUG, size_N, size_N * 2);
	}
	for (int i = 0; i < size_N; i++)
	{
		for (int j = 0; j < size_N; j++)
			inv_A[i][j] = mAUG[i][j + size_N];//���� ��������ڸ����ִ� ����� ����ķ�����
	}
}


