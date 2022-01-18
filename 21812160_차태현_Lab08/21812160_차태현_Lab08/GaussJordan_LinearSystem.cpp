#include<stdio.h>
#include <math.h>
#include<stdlib.h>
#include"Mtrx.h"
#define EPSILON 0.000001
void pivoting(double** augMtrx, int size_N, int p, int* piv_found)//행위치변환
{
	double max = 0, temp;
	int max_row;

	max = fabs(augMtrx[p][p]); 
	max_row=p;
	
	for (int i = p + 1; i < size_N; i++)
	{
		if (fabs(augMtrx[i][p]) > max) //각 행의 p번째 값의 최대값 찾기
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
			for (int j = p; j <= size_N; j++) //초기의 행위치와 다르다면 최대값을 가장상위행으로 보내줌
			{
				temp = augMtrx[p][j];
				augMtrx[p][j] = augMtrx[max_row][j];
				augMtrx[max_row][j] = temp;
			}
		}
	}

}
void getAugmentedMtrx(FILE* fin, double** dM, int size_N)//파일로부터 행렬값 받아오기
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

	for (p = 0; (*solExist) && (p < size_N); p++)//solExist참이고 p가 주어진 크기보다 작을경우에 실행
	{
		fprintf(fout, "\nPivting at p= %d\n", p);
		pivoting(mtrxAug, size_N, p, solExist);//최상위 행 찾아서 위치 변환
		fprintMtrx_double(fout, mtrxAug, size_N, size_N + 1);
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
		fprintMtrx_double(fout, mtrxAug, size_N, size_N + 1);

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
		mAUG[i] = (double*)calloc(size_N * 2, sizeof(double));//nx2n동적배열 생성
	}
	for (int j = 0; j < size_N; j++)
	{
		for (int k = 0; k < size_N; k++)//A행렬 복사
			mAUG[j][k] = mA[j][k];

		for (int k = size_N; k < size_N * 2; k++)//남은 2n부분에 단위행렬생성
			mAUG[j][k] = (k == (j + size_N)) ? 1.0 : 0.0;
	}

	for (p = 0; p < size_N; p++)//A행렬을 단위행렬로 만들어주는과정
	{
		if (mAUG[p][p] != 1.0)
		{
			pivwieght = mAUG[p][p];//pp번째 1.0으로 만들고 저장
			mAUG[p][p] = 1.0;
			for (int k = p + 1; k < size_N * 2; k++)
				mAUG[p][k] /= pivwieght;//같은 행에 나머지 값들을 pp번째 값으로 나누어줌
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
					mAUG[m][n] = mAUG[m][n] - w * mAUG[p][n];//값을 0.0으로 만들기 위해 같은행의 나머지값에도 0.0을 만들기위해 사용한 값들을 빼줌
			}
		}

		fprintf(fout, "After diagonalizing at p = %d\n", p);
		fprintMtrx_double(fout, mAUG, size_N, size_N * 2);
	}
	for (int i = 0; i < size_N; i++)
	{
		for (int j = 0; j < size_N; j++)
			inv_A[i][j] = mAUG[i][j + size_N];//기존 단위행렬자리에있던 행렬을 역행렬로저장
	}
}


