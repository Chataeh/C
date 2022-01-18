#include <stdio.h>
#include <stdlib.h>


double** fGetMtrx_double(FILE* fin, int* row_size, int* col_size)//파일로 부터 행렬값받아오기 
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
void deleteMtrx(double** dM, int row_size, int col_size)//동적배열 반환
{
	for (int i = 0; i < row_size; i++)
	{
		free(dM[i]); //반환은 거꾸로 그냥 포인터부터 반환
	}
	free(dM);
}
void printMtrx_double(double** dM, int row_size, int col_size)
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
			if(row_size==1)
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

void fprintMtrx_double(FILE* fout, double** dM, int row_size, int col_size)
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
				if (col_size == 1)
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
				if (col_size == 1)
					fprintf(fout,"%c%c", a6, a2);
			}
			else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1)))
				fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a2); // ㅣ 표시하기
			else if ((i == (row_size - 1)) && (j == 0))
			{
				fprintf(fout,"%c%c%8.2lf", a6, a6, dM[i][j]); // ㄴ 표시하기
				if (col_size == 1)
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

double** creat(int row_size, int col_size)// 2차원 동적배열 생성함수
{
	double** dM;

	dM = (double**)calloc(row_size, sizeof(double*)+1);
	for (int i = 0; i < col_size; i++)
	{
		dM[i] = (double*)calloc(col_size, sizeof(double));
	}
	return dM;
}

double** addMtrx_double(double** A, double** B, int row_size, int col_size)//행렬의 합
{
	double** C;

	C = creat(row_size, col_size);

	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)//같은위치의 값들끼리 더하기
			C[i][j] = A[i][j] + B[i][j];

	return C;
}

double** subtractMtrx_double(double** A, double** B, int row_size, int col_size)//행렬의 차
{

	double** C;

	C = creat(row_size, col_size);

	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)//같은 위치의 값들끼리 빼기
			C[i][j] = A[i][j] - B[i][j];

	return C;
}

double** multiplyMtrx_double(double** A, double** B, int row_size, int col_size, int bcol_size)//행렬의 곱셈
{
	double** C;

	C = creat(row_size, col_size);

	for (int i = 0; i < row_size; i++)//a행렬을 행
	{
		for (int j = 0; j < bcol_size; j++)//b행렬의 열
		{
			for (int k = 0; k < col_size; k++)//a행렬의 열
				C[i][j] += A[i][k] * B[k][j];
		}
	}

	return C;
}
