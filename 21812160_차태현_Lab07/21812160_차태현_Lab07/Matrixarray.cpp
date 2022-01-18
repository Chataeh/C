#include <stdio.h>
#include <stdlib.h>

double **createDoubleMtrx(int row_size, int col_size)// 2���� �����迭 ����
{
	double** array;

	array = (double**)calloc(row_size, sizeof(double*));//���������� �������ش�
	for (int i = 0; i < row_size; i++)
	{
		array[i] = (double*)calloc(col_size, sizeof(double));
	}

	return array;
}

void checkAddr_2D_Array(double** dM, int row_size, int col_size)// 2�����迭�� �ּڰ�Ȯ��
{
	printf("dM=%p\n", dM);
	printf("dM[0]=%p\n", dM[0]);
	printf("&dM[0][0]=%p", &dM[0][0]);

}

void deleteDoubleMtrx(double** dM, int row_size, int col_size)//�����迭 ��ȯ
{
	for (int i = 0; i < row_size; i++)
	{
		free(dM[i]); //��ȯ�� �Ųٷ� �׳� �����ͺ��� ��ȯ
	}
	free(dM);
}

double** fgetDoubleMtrx(FILE* fin, int row_size, int col_size)// ���Ϸκ��� �� �޾ƿ���(���)
{
	double** array;
	double data = 0;

	
	array = createDoubleMtrx(row_size, col_size);//2���� �����迭 ����

	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
		{
			if (fscanf(fin,"%lf",&data)!= EOF)
				array[i][j]=data;
		}
	}
	return array;
}

void printMtrx(double** dM, int size_row, int size_col)//����������� ���
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	
	

	for (int i = 0; i < size_row; i++)
	{
		for (int j = 0; j < size_col; j++)
		{
			if ((i == 0) && (j == 0))
				printf("%c%c%8.2lf", a6, a3, dM[i][j]); // �� ǥ���ϱ�
			else if ((i == 0) && (j == size_col - 1))
				printf("%8.2lf %c%c", dM[i][j], a6, a4); //  �� ǥ���ϱ� 
			else if ((i > 0) && (i < size_row - 1) && (j == 0))
				printf("%c%c%8.2lf", a6, a2, dM[i][j]); // �� ǥ���ϱ�  
			else if ((i > 0) && (i < size_row - 1) && (j == size_col - 1))
				printf("%8.2lf %c%c", dM[i][j], a6, a2); // �� ǥ���ϱ�
			else if ((i == size_row - 1) && (j == 0))
				printf("%c%c%8.2lf", a6, a6, dM[i][j]); // �� ǥ���ϱ�
			else if ((i == size_row - 1) && (j == size_col - 1))
				printf("%8.2lf %c%c", dM[i][j], a6, a5); // �� ǥ���ϱ�
			else
				printf("%8.2lf",dM[i][j]);
		}
		printf("\n");
	}
}

void fprintMtrx(FILE *fout,double** dM, int size_row, int size_col)//���Ͽ� ����������� ���
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;



	for (int i = 0; i < size_row; i++)
	{
		for (int j = 0; j < size_col; j++)
		{
			if ((i == 0) && (j == 0))
				fprintf(fout,"%c%c%8.2lf", a6, a3, dM[i][j]); // �� ǥ���ϱ�
			else if ((i == 0) && (j == size_col - 1))
				fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a4); //  �� ǥ���ϱ� 
			else if ((i > 0) && (i < size_row - 1) && (j == 0))
				fprintf(fout,"%c%c%8.2lf", a6, a2, dM[i][j]); // �� ǥ���ϱ�  
			else if ((i > 0) && (i < size_row - 1) && (j == size_col - 1))
				fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a2); // �� ǥ���ϱ�
			else if ((i == size_row - 1) && (j == 0))
				fprintf(fout,"%c%c%8.2lf", a6, a6, dM[i][j]); // �� ǥ���ϱ�
			else if ((i == size_row - 1) && (j == size_col - 1))
				fprintf(fout,"%8.2lf %c%c", dM[i][j], a6, a5); // �� ǥ���ϱ�
			else
				fprintf(fout,"%8.2lf", dM[i][j]);
		}
		fprintf(fout,"\n");
	}
}



void addMtrx(double** mA, double** mB,double** mR, int row_size, int col_size)//����� ��
{
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			mR[i][j] = mA[i][j] + mB[i][j];

}

void subMtrx(double** mA, double** mB, double** mR, int row_size, int col_size)//����� ��
{
	for (int i = 0; i < row_size; i++)
		for (int j = 0; j < col_size; j++)
			mR[i][j] = mA[i][j] - mB[i][j];

}

void mutiplyMtrx(double** mA, double** mB, double** mR, int arow_size, int acol_size,int bcol_size)//����� ��
{
	for (int i = 0; i < arow_size; i++)
		for (int j = 0; j < bcol_size; j++)
		{
			mR[i][j] = 0;
			for (int k = 0; k < acol_size; k++)//3�� �ݺ��� ��� (����� �� Ư����)
				mR[i][j] += mA[i][k] * mB[k][j];

		}
	
}