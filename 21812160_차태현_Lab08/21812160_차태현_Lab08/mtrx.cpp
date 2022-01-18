#include <stdio.h>
#include <stdlib.h>


double** fGetMtrx_double(FILE* fin, int* row_size, int* col_size)//���Ϸ� ���� ��İ��޾ƿ��� 
{
	double** dM;
	double data = 0;
	fscanf(fin, "%d %d", &*row_size, &*col_size);
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
void deleteMtrx(double** dM, int row_size, int col_size)//�����迭 ��ȯ
{
	for (int i = 0; i < row_size; i++)
	{
		free(dM[i]); //��ȯ�� �Ųٷ� �׳� �����ͺ��� ��ȯ
	}
	free(dM);
}
void printMtrx_double(double** dM, int row_size, int col_size)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2; //Ȯ�� �ϼ����ڵ�
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
			if (col_size == 1)//���� ���� 1�Ͻä�  ǥ��
				printf("%c%c", a6, a4);
		}
			
		else if ((i == 0) && (j == col_size - 1))
		{
			if(row_size==1)
			printf("%8.2lf", dM[i][j]);
			else 
			printf("%8.2lf %c%c", dM[i][j], a6, a4); //  �� ǥ���ϱ�
		
		}
		else if ((i > 0) && (i < row_size - 1) && (j == 0))
		{
			printf("%c%c%8.2lf", a6, a2, dM[i][j]); // �� ǥ���ϱ�  
			if (col_size == 1)//���� ���� 1�Ͻ� ���� lǥ��
				printf("%c%c", a6, a2);
		}
		else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1)))
			printf("%8.2lf %c%c", dM[i][j], a6, a2); // �� ǥ���ϱ�
		else if ((i == (row_size - 1)) && (j == 0))
		{
			printf("%c%c%8.2lf", a6, a6, dM[i][j]); // �� ǥ���ϱ�
			if (col_size == 1)//���� ���� 1�ϰ�� ��ǥ��
				printf("%c%c", a6, a5);
		}
		else if ((i == (row_size - 1)) && (j == (col_size - 1)))
			printf("%8.2lf %c%c", dM[i][j], a6, a5); // �� ǥ���ϱ�
		else
			printf("%8.2lf", dM[i][j]);
		}
		printf("\n");
	}

}

void fprintMtrx_double(FILE* fout, double** dM, int row_size, int col_size)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2; //Ȯ�� �ϼ����ڵ�
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
					fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a4); //  �� ǥ���ϱ�

			}
			else if ((i > 0) && (i < row_size - 1) && (j == 0))
			{
				fprintf(fout,"%c%c%8.2lf", a6, a2, dM[i][j]); // �� ǥ���ϱ�  
				if (col_size == 1)
					fprintf(fout,"%c%c", a6, a2);
			}
			else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1)))
				fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a2); // �� ǥ���ϱ�
			else if ((i == (row_size - 1)) && (j == 0))
			{
				fprintf(fout,"%c%c%8.2lf", a6, a6, dM[i][j]); // �� ǥ���ϱ�
				if (col_size == 1)
					fprintf(fout,"%c%c", a6, a5);
			}
			else if ((i == (row_size - 1)) && (j == (col_size - 1)))
				fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a5); // �� ǥ���ϱ�
			else
				fprintf(fout,"%8.2lf", dM[i][j]);
		}
		fprintf(fout,"\n");
	}
}

double** creat(int row_size, int col_size)// 2���� �����迭 �����Լ�
{
	double** dM;

	dM = (double**)calloc(row_size, sizeof(double*)+1);
	for (int i = 0; i < col_size; i++)
	{
		dM[i] = (double*)calloc(col_size, sizeof(double));
	}
	return dM;
}

double** addMtrx_double(double** A, double** B, int row_size, int col_size)//����� ��
{
	double** C;

	C = creat(row_size, col_size);

	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)//������ġ�� ���鳢�� ���ϱ�
			C[i][j] = A[i][j] + B[i][j];

	return C;
}

double** subtractMtrx_double(double** A, double** B, int row_size, int col_size)//����� ��
{

	double** C;

	C = creat(row_size, col_size);

	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)//���� ��ġ�� ���鳢�� ����
			C[i][j] = A[i][j] - B[i][j];

	return C;
}

double** multiplyMtrx_double(double** A, double** B, int row_size, int col_size, int bcol_size)//����� ����
{
	double** C;

	C = creat(row_size, col_size);

	for (int i = 0; i < row_size; i++)//a����� ��
	{
		for (int j = 0; j < bcol_size; j++)//b����� ��
		{
			for (int k = 0; k < col_size; k++)//a����� ��
				C[i][j] += A[i][k] * B[k][j];
		}
	}

	return C;
}
