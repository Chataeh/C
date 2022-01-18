#include <stdio.h>
#include <stdlib.h>
double** inputMtrx(FILE* fin, int* row_size, int* col_size)//파일로 부터 행렬값받아오기 
{
	double** dM;
	double data = 0;
	
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

	dM = (double**)calloc(row_size, sizeof(double*));
	for (int i = 0; i < col_size; i++)
	{
		dM[i] = (double*)calloc(col_size, sizeof(double));
	}
	return dM;
}

void deleteMtrx(double** ppM, int row_size, int col_size)//동적배열 반환
{
	for (int i = 0; i < row_size; i++)//생성과의 반대순서
	{
		free(ppM[i]);
	}
	free(ppM);
}

void pirintMtrx(double** ppM, int row_size, int col_size)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2; //확장 완성형코드
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
			if ((i == 0) && (j == 0))
				printf("%c%c%8.2lf", a6, a3, ppM[i][j]);
			else if ((i == 0) && (j == col_size - 1))
				printf("%8.2lf %c%c", ppM[i][j], a6, a4); //  ㄱ 표시하기 
			else if ((i > 0) && (i < row_size - 1) && (j == 0))
				printf("%c%c%8.2lf", a6, a2, ppM[i][j]); // ㅣ 표시하기  
			else if ((i > 0) && (i < row_size - 1) && (j == col_size - 1))
				printf("%8.2lf %c%c", ppM[i][j], a6, a2); // ㅣ 표시하기
			else if ((i == row_size - 1) && (j == 0))
				printf("%c%c%8.2lf", a6, a6, ppM[i][j]); // ㄴ 표시하기
			else if ((i == row_size - 1) && (j == col_size - 1))
				printf("%8.2lf %c%c", ppM[i][j], a6, a5); // 」 표시하기
			else
				printf("%8.2lf", ppM[i][j]);
	
		printf("\n");
	}
	

}

double **addMtrx(double** A, double** B, int row_size, int col_size)//행렬의 합
{
	double** C;

	C = creat(row_size, col_size);
	
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			C[i][j] = A[i][j] + B[i][j];

	return C;
}

double **subMtrx(double** A, double** B,  int row_size, int col_size)//행렬의 차
{
	
	double** C;
	
	C = creat(row_size, col_size);
	
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			C[i][j] = A[i][j] - B[i][j];

	return C;
}

double** mulMtrx(double** A, double** B, int row_size, int col_size)//행렬의 곱셈
{
	double** C;

	C = creat(row_size, col_size);

	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
		{
			for (int k = 0; k < row_size; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}

	return C;
}