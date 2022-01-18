#include <stdio.h>
#include <stdlib.h>
double** inputMtrx(FILE* fin, int* row_size, int* col_size)//���Ϸ� ���� ��İ��޾ƿ��� 
{
	double** dM;
	double data = 0;
	
	dM = (double**)calloc(*row_size, sizeof(double*));// 2���� �����迭����
	for (int i = 0; i < *row_size; i++)
	{
		dM[i] = (double*)calloc(*col_size, sizeof(double));
	}
	

	for (int i = 0; i < *row_size; i++)
	{
		for (int j = 0; j < *col_size; j++)
		{
			if (fscanf(fin, "%lf", &data) != EOF)//������EOF�� �ƴҽ� �Է��� �޾ƿ�
				dM[i][j] = data;
		}
	}
	return dM;
}

double** creat(int row_size, int col_size)// 2���� �����迭 �����Լ�
{
	double** dM;

	dM = (double**)calloc(row_size, sizeof(double*));
	for (int i = 0; i < col_size; i++)
	{
		dM[i] = (double*)calloc(col_size, sizeof(double));
	}
	return dM;
}

void deleteMtrx(double** ppM, int row_size, int col_size)//�����迭 ��ȯ
{
	for (int i = 0; i < row_size; i++)//�������� �ݴ����
	{
		free(ppM[i]);
	}
	free(ppM);
}

void pirintMtrx(double** ppM, int row_size, int col_size)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2; //Ȯ�� �ϼ����ڵ�
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;

	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
			if ((i == 0) && (j == 0))
				printf("%c%c%8.2lf", a6, a3, ppM[i][j]);
			else if ((i == 0) && (j == col_size - 1))
				printf("%8.2lf %c%c", ppM[i][j], a6, a4); //  �� ǥ���ϱ� 
			else if ((i > 0) && (i < row_size - 1) && (j == 0))
				printf("%c%c%8.2lf", a6, a2, ppM[i][j]); // �� ǥ���ϱ�  
			else if ((i > 0) && (i < row_size - 1) && (j == col_size - 1))
				printf("%8.2lf %c%c", ppM[i][j], a6, a2); // �� ǥ���ϱ�
			else if ((i == row_size - 1) && (j == 0))
				printf("%c%c%8.2lf", a6, a6, ppM[i][j]); // �� ǥ���ϱ�
			else if ((i == row_size - 1) && (j == col_size - 1))
				printf("%8.2lf %c%c", ppM[i][j], a6, a5); // �� ǥ���ϱ�
			else
				printf("%8.2lf", ppM[i][j]);
	
		printf("\n");
	}
	

}

double **addMtrx(double** A, double** B, int row_size, int col_size)//����� ��
{
	double** C;

	C = creat(row_size, col_size);
	
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			C[i][j] = A[i][j] + B[i][j];

	return C;
}

double **subMtrx(double** A, double** B,  int row_size, int col_size)//����� ��
{
	
	double** C;
	
	C = creat(row_size, col_size);
	
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			C[i][j] = A[i][j] - B[i][j];

	return C;
}

double** mulMtrx(double** A, double** B, int row_size, int col_size)//����� ����
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