#include <stdio.h>
#include <stdlib.h>


double** fGetMtrx(FILE* fin, int* row_size, int* col_size)//파일로 부터 행렬값받아오기 
{
	double** dM;
	double data = 0;

	fscanf(fin, "%d %d", &*row_size, &*col_size);

	dM = (double**)calloc(*row_size, sizeof(double*));// 2차원 동적배열생성
	for (int i = 0; i < *row_size; i++)
	{
		dM[i] = (double*)calloc(*col_size, sizeof(double));
	}
	
	for (int i = 0; i < *row_size; i++)
	{
		for (int j = 0; j < *col_size; j++)
		{
			if (fscanf(fin, "%lf", &data) != EOF)//파일이EOF가 아닐시 입력을 받아옴
				dM[i][j] = data;
		}
	}
	return dM;
}
double** creat(int row_size, int col_size)// 2차원 동적배열 생성함수
{
	double** dM;

	dM = (double**)calloc(row_size, sizeof(double*) + 1);
	for (int i = 0; i < col_size; i++)
	{
		dM[i] = (double*)calloc(col_size, sizeof(double));
	}
	return dM;
}
void deleteMtrx(double** dM, int row_size, int col_size)//동적배열 반환
{
	for (int i = 0; i < row_size; i++)
	{
		free(dM[i]); //반환은 거꾸로 그냥 포인터부터 반환
	}
	free(dM);
}
void printMtrx(double** dM, int row_size, int col_size)
{
		unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2; //확장 완성형코드
		unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;


		for (int i = 0; i < row_size; i++)
		{
			for (int j = 0; j < col_size; j++)
			{

				if ((i == 0) && (j == 0))
				{
					if (row_size == 1)
						printf("%8.2lf", dM[i][j]);
					else
						printf("%c%c%8.2lf", a6, a3, dM[i][j]);
					if (col_size == 1)//열의 값이 1일시ㄱ  표시
						printf("%c%c", a6, a4);
				}

				else if ((i == 0) && (j == col_size - 1))
				{
					if (row_size == 1)
						printf("%8.2lf", dM[i][j]);
					else
						printf("%8.2lf %c%c", dM[i][j], a6, a4); //  ㄱ 표시하기

				}
				else if ((i > 0) && (i < row_size - 1) && (j == 0))
				{
					printf("%c%c%8.2lf", a6, a2, dM[i][j]); // ㅣ 표시하기  
					if (col_size == 1)//열의 값이 1일시 전부 l표시
						printf("%c%c", a6, a2);
				}
				else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1)))
					printf("%8.2lf %c%c", dM[i][j], a6, a2); // ㅣ 표시하기
				else if ((i == (row_size - 1)) && (j == 0))
				{
					printf("%c%c%8.2lf", a6, a6, dM[i][j]); // ㄴ 표시하기
					if (col_size == 1)//열의 값이 1일경우 」표시
						printf("%c%c", a6, a5);
				}
				else if ((i == (row_size - 1)) && (j == (col_size - 1)))
					printf("%8.2lf %c%c", dM[i][j], a6, a5); // 」 표시하기
				else
					printf("%8.2lf", dM[i][j]);
			}
			printf("\n");
		}

}
void fprintMtrx(FILE* fout,double** dM, int row_size, int col_size)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2; //확장 완성형코드
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;


	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
		{

			if ((i == 0) && (j == 0))
			{
				if (row_size == 1)
					fprintf(fout,"%8.2lf", dM[i][j]);
				else
					fprintf(fout,"%c%c%8.2lf", a6, a3, dM[i][j]);
				if (col_size == 1)//열의 값이 1일시ㄱ  표시
					fprintf(fout,"%c%c", a6, a4);
			}

			else if ((i == 0) && (j == col_size - 1))
			{
				if (row_size == 1)
					fprintf(fout,"%8.2lf", dM[i][j]);
				else
					fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a4); //  ㄱ 표시하기

			}
			else if ((i > 0) && (i < row_size - 1) && (j == 0))
			{
				fprintf(fout,"%c%c%8.2lf", a6, a2, dM[i][j]); // ㅣ 표시하기  
				if (col_size == 1)//열의 값이 1일시 전부 l표시
					fprintf(fout,"%c%c", a6, a2);
			}
			else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1)))
				fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a2); // ㅣ 표시하기
			else if ((i == (row_size - 1)) && (j == 0))
			{
				fprintf(fout,"%c%c%8.2lf", a6, a6, dM[i][j]); // ㄴ 표시하기
				if (col_size == 1)//열의 값이 1일경우 」표시
					fprintf(fout,"%c%c", a6, a5);
			}
			else if ((i == (row_size - 1)) && (j == (col_size - 1)))
				fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a5); // 」 표시하기
			else
				fprintf(fout,"%8.2lf", dM[i][j]);
		}
		fprintf(fout,"\n");
	}

}

void addMtrx(double** mA, double** mB, double** mD, int row_size, int col_size)//행렬의 합
{
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			mD[i][j] = mA[i][j] + mB[i][j];

}

void subMtrx(double** mA, double** mB, double** mR, int row_size, int col_size)//행렬의 차
{
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			mR[i][j] = mA[i][j] - mB[i][j];

}

void mutiplyMtrx(double** mA, double** mB, double** mR, int arow_size, int acol_size, int bcol_size)//행렬의 곱
{
	for (int i = 0; i < arow_size; i++)
		for (int j = 0; j < bcol_size; j++)
		{
			mR[i][j] = 0;
			for (int k = 0; k < acol_size; k++)//3중 반복문 사용 (행렬의 곱 특성상)
				mR[i][j] += mA[i][k] * mB[k][j];

		}

}

void inverseMtrx(double** mA, double** invA, int size_N)
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

	}
	for (int i = 0; i < size_N; i++)
	{
		for (int j = 0; j < size_N; j++)
			invA[i][j] = mAUG[i][j + size_N];//기존 단위행렬자리에있던 행렬을 역행렬로저장
	}
}