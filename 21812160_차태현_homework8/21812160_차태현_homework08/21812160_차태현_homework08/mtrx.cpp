#include <stdio.h>
#include <stdlib.h>


double** fGetMtrx(FILE* fin, int* row_size, int* col_size)//���Ϸ� ���� ��İ��޾ƿ��� 
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
double** creat(int row_size, int col_size)// 2���� �����迭 �����Լ�
{
	double** dM;

	dM = (double**)calloc(row_size, sizeof(double*) + 1);
	for (int i = 0; i < col_size; i++)
	{
		dM[i] = (double*)calloc(col_size, sizeof(double));
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
void printMtrx(double** dM, int row_size, int col_size)
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
					if (row_size == 1)
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
void fprintMtrx(FILE* fout,double** dM, int row_size, int col_size)
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
				if (col_size == 1)//���� ���� 1�Ͻä�  ǥ��
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
				if (col_size == 1)//���� ���� 1�Ͻ� ���� lǥ��
					fprintf(fout,"%c%c", a6, a2);
			}
			else if ((i > 0) && (i < row_size - 1) && (j == (col_size - 1)))
				fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a2); // �� ǥ���ϱ�
			else if ((i == (row_size - 1)) && (j == 0))
			{
				fprintf(fout,"%c%c%8.2lf", a6, a6, dM[i][j]); // �� ǥ���ϱ�
				if (col_size == 1)//���� ���� 1�ϰ�� ��ǥ��
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

void addMtrx(double** mA, double** mB, double** mD, int row_size, int col_size)//����� ��
{
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			mD[i][j] = mA[i][j] + mB[i][j];

}

void subMtrx(double** mA, double** mB, double** mR, int row_size, int col_size)//����� ��
{
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			mR[i][j] = mA[i][j] - mB[i][j];

}

void mutiplyMtrx(double** mA, double** mB, double** mR, int arow_size, int acol_size, int bcol_size)//����� ��
{
	for (int i = 0; i < arow_size; i++)
		for (int j = 0; j < bcol_size; j++)
		{
			mR[i][j] = 0;
			for (int k = 0; k < acol_size; k++)//3�� �ݺ��� ��� (����� �� Ư����)
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

	}
	for (int i = 0; i < size_N; i++)
	{
		for (int j = 0; j < size_N; j++)
			invA[i][j] = mAUG[i][j + size_N];//���� ��������ڸ����ִ� ����� ����ķ�����
	}
}