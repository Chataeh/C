#include<stdio.h>
#include <math.h>
#include"mtrx.h"
#define EPSILON 0.000001

void fgetAugmentedMtrx(FILE* fin, double** dM, int size_N)//파일로부터 행렬값 받아오기
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

	for (p = 0; ((*solExist) && (p < size_N)); p++)//solExist참이고 p가 주어진 크기보다 작을경우에 실행
	{
		fprintf(fout, "\nPivting at p= %d\n", p);
		pivoting(mtrxAug, size_N, p, solExist);//최상위 행 찾아서 위치 변환
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);
		if (*solExist)
		{
			if (mtrxAug[p][p] != 1.0)
			{
				pivWeight = mtrxAug[p][p];
				mtrxAug[p][p] = 1.0;//기준값을  1.0으로 변환
				for (int i = p + 1; i <= size_N; i++)
				{
					mtrxAug[p][i] /= pivWeight; //나머지 값들은 기준값으로 다 나누어줌
				}

			}
		}
		else
			break;

		fprintf(fout, "\nAfter scaling at p = %d\n", p);
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);

		for (int j = 0; j < size_N; j++) //p,p 번째 값말고 나머지 0.0으로 만듦
		{
			if ((j != p) && (mtrxAug[j][p] != 0.0))
			{
				w = mtrxAug[j][p];
				mtrxAug[j][p] = 0.0;

				for (int k = p + 1; k <= size_N; k++)
				{
					mtrxAug[j][k] = mtrxAug[j][k] - w * mtrxAug[p][k]; //같은열에 기준값이 아닌값을 0.0 으로 만들어주는값을 각행에다가 빼줌
				}
			}
		}

		fprintf(fout, "\nAfter diagonallzing at p = %d\n", p);
		fprintMtrx(fout, mtrxAug, size_N, size_N + 1);
	}
}