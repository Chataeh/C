/**
*�����̸�"21812160_������_Lab08 ��
*���α׷��� ���� �� �⺻ ���:
*  ���Ϸι޾ƿ� ����� �⺻����� ���콺���� �ҰŹ����
*
*���α׷� �ۼ���: 21812160 ������(2021�� 4��28��),
*���� ���� �� ����: 2021�� 4�� 28�� (������)
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Mtrx.h"//������������
#include "GaussJordan_LinearSystem.h"//������������

void test_2D_DynamicArray_FileIO(FILE* fout);
void test_MatrixAdditionSubtraction(FILE* fout);
void test_MatrixMultiplication(FILE* fout);
void test_GaussJordanElimination_LinearSystem(FILE* fout);
void test_InvMtrx_GaussJordanElimination_LinearSystem(FILE* fout);
int main(void)
{
	FILE* fin, * fout;
	int num;
	fout = fopen("out_put.txt", "w");//���� ������� ����
	if (fout == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	while (1)
	{
		printf("Testing Matrix Operations with 2-Dimensional Dynamic Array\n");
		printf(" 1: Test 2-D Dynamic Array Creation for Matrix with File I/O\n");
		printf(" 2: Test Matrix Addition, Subtraction\n");
		printf(" 3: Test Matrix Multiplication\n");
		printf(" 4: Test Gauss-Jordan Elimination for Linear System\n");
		printf(" 5: Test Inverse Matrix with Gauss-Jordan Elimination for Linear System\n");
		printf(" 0: Quit\n");
		printf("Input menu (0 to quit) : ");
		scanf("%d", &num);
		if (num == 0)
			break;
		printf("\n");
		switch (num)
		{
		case 1:
			test_2D_DynamicArray_FileIO(fout);//���Ϸκ��� ��� ���
			break;
		case 2:
			test_MatrixAdditionSubtraction(fout);// ����� ��������
			break;
		case 3:
			test_MatrixMultiplication(fout);//����� ����
			break;
		case 4:
			test_GaussJordanElimination_LinearSystem(fout);//���콺���ܼҰŹ��� ���� ���������
			break;
		case 5:
			test_InvMtrx_GaussJordanElimination_LinearSystem(fout);//������� ����� ���콺���ܼҰŹ�
			break;
		default:
			break;
		}
	}
	fclose(fout);
}

void test_2D_DynamicArray_FileIO(FILE* fout)//2���� ������
{
	FILE* fin;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	double** dMA, **dMB;

	fin = fopen("mtrx_input.txt", "r");//���� �б��忭��

	dMA = fGetMtrx_double(fin, &a_row_size, &a_col_size);//��� ���Ϸκ��� �޾ƿ���
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx_double(dMA, a_row_size, a_col_size);//������
	printf("\n");

	dMB = fGetMtrx_double(fin, &b_row_size, &b_col_size);
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx_double(dMB, b_row_size, b_col_size);
	printf("\n");

	deleteMtrx(dMA, a_row_size, a_col_size);//�����迭��ȯ
	deleteMtrx(dMB, b_row_size, b_col_size);

	fclose(fin);//���ϴݱ�
}

void test_MatrixAdditionSubtraction(FILE* fout)//����� ��������
{
	FILE* fin;

	double** dMA, ** dMB, ** dMC, ** dMD;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	int d_row_size, d_col_size;

	fin = fopen("mtrx_input2.txt", "r");//���� �б���ο���

	dMA = fGetMtrx_double(fin, &a_row_size, &a_col_size);//���Ϸκ��� ��Ĺ޾ƿ���
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx_double(dMA, a_row_size, a_col_size);//������
	printf("\n");

	dMB = fGetMtrx_double(fin, &b_row_size, &b_col_size);
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx_double(dMA, b_row_size, b_col_size);
	printf("\n");

	c_row_size = a_row_size;
	c_col_size = b_col_size;
	
	dMC = addMtrx_double(dMA, dMB, c_row_size, c_col_size);//����� ����
	printf("Matrix_C (%d x %d) = Matrix_A + Matrix_B : \n", c_row_size, c_col_size);
	printMtrx_double(dMC, c_row_size, c_col_size);
	printf("\n");

	d_row_size = a_row_size;
	d_col_size = b_col_size;


	dMD = subtractMtrx_double(dMA, dMB, d_row_size, d_col_size);//����� ����
	printf("Matrix_D (%d x %d) = Matrix_A - Matrix_B : \n", d_row_size, d_col_size);
	printMtrx_double(dMD, d_row_size, d_col_size);
	printf("\n");

	deleteMtrx(dMA, a_row_size, a_col_size);
	deleteMtrx(dMB, b_row_size, b_col_size);
	deleteMtrx(dMC, c_row_size, c_col_size);
	deleteMtrx(dMD, d_row_size, d_col_size);

	fclose(fin);
}

void test_MatrixMultiplication(FILE* fout)//����� ����
{
	FILE* fin;
	int a_row_size, a_col_size;
	int b_row_size, b_col_size;
	int c_row_size, c_col_size;
	double** dMA, ** dMB,**dMC;

	fin = fopen("mtrx_input.txt", "r");//�б���� ���Ͽ���

	dMA = fGetMtrx_double(fin, &a_row_size, &a_col_size);//���Ϸκ��� ��Ĺ޾ƿ���
	printf("Input Matrix_A ( %d x %d) : \n", a_row_size, a_col_size);
	printMtrx_double(dMA, a_row_size, a_col_size);//������
	printf("\n");

	dMB = fGetMtrx_double(fin, &b_row_size, &b_col_size);
	printf("Input Matrix_B ( %d x %d) : \n", b_row_size, b_col_size);
	printMtrx_double(dMB, b_row_size, b_col_size);
	printf("\n");

	c_row_size = a_row_size;
	c_col_size = b_col_size;
	
	dMC = multiplyMtrx_double(dMA, dMB, a_row_size, a_col_size, b_col_size);//����� ����
	printf("Matrix_C (%d x %d) = Matrix_A x Matrix_B : \n", c_row_size, c_col_size);
	printMtrx_double(dMC, c_row_size, c_col_size);
	printf("\n");


	
	deleteMtrx(dMA, a_row_size, a_col_size);
	deleteMtrx(dMB, b_row_size, b_col_size);
	deleteMtrx(dMC, c_row_size, c_col_size);

	fclose(fin);
}

void test_GaussJordanElimination_LinearSystem(FILE* fout)
{
	FILE* fin;
	int size_N;
	double* solution;
	double** augMtrx = NULL;
	int solExist = 1;
	double data;

	fin = fopen("Jordan_input.txt", "r");//�б���� ���Ͽ���
	fscanf(fin, "%d", &size_N);//���Ͽ��� size �޾ƿ���
	augMtrx = creat(size_N+1, size_N+1 );//�����迭 ����
	getAugmentedMtrx(fin, augMtrx, size_N);//������ �����迭�� ��Ĺ޾ƿ���
	solution = (double*)calloc(size_N, sizeof(double));//�����迭����
	fprintf(fout, "Augmented Matrix : \n");
	fprintMtrx_double(fout,augMtrx, size_N, size_N +1);
	printf("Augmented Matrix : \n");
	printMtrx_double(augMtrx, size_N, size_N +1);//������

	diagonalize_FileOut(fout,augMtrx, size_N,&solExist);//���콺�ҰŹ�����
	if (solExist)
	{
		fprintf(fout, "The solution of the given linear system:\n");
		printf("The solution of the given linear system:\n");
		for (int i = 0; i < size_N; i++)
		{
			solution[i] = augMtrx[i][size_N];//�ַ�ǿ� ���������� ������ �Է�
			fprintf(fout, " x[%d] : %4f\n", i, solution[i]);
			printf(" x[%d] : %4f\n", i, solution[i]);
		}
	}
	else
	{
		fprintf(fout, "No unique solution\n");
		printf("No unique solution\n");
	}
	
	deleteMtrx(augMtrx, size_N + 1, size_N + 1);//�����迭��ȯ
	free(solution);
	fclose(fin);
}

void test_InvMtrx_GaussJordanElimination_LinearSystem(FILE* fout)//������� ����� ���콺�ҰŹ�
{
	FILE* fin;
	double** mA, ** inv_A, ** res, ** mE;
	int size_N;
	double data;

	fin = fopen("inv_input.txt", "r");//���� �б���� ����

	fscanf(fin, "%d", &size_N);//���Ϸκ��� size�޾ƿ���
	
	mA =creat(size_N,size_N);		// �����迭����
	inv_A = creat(size_N, size_N);
	mE = creat(size_N, size_N);
	res = creat(size_N, size_N);
	
	for (int m=0; m < size_N; m++) //��İ� �޾ƿ���
	{
		for (int n = 0; n < size_N; n++)
		{
			fscanf(fin, "%lf", &data);
			mA[m][n] = data;
		}
	}
	for (int i = 0; i < size_N; i++) 
	{
		fscanf(fin, "%lf", &data);
		mE[i][0] = data;
	}
	
	

	fprintf(fout, "Matrix A: \n");
	fprintMtrx_double(fout, mA, size_N, size_N);
	printf("Matrix A: \n");
	printMtrx_double(mA, size_N, size_N);

	invMtrxGaussJordanElim_FileOut(fout, mA, inv_A, size_N);//����İ��콺 �ҰŹ�����
	fprintf(fout, " Inverse A: \n");
	fprintMtrx_double(fout,inv_A, size_N, size_N);
	printf(" Inverse A: \n");
	printMtrx_double(inv_A, size_N, size_N);

	fprintf(fout, " mE: \n");
	fprintMtrx_double(fout, mE, size_N, 1);
	printf(" mE: \n");
	printMtrx_double(mE, size_N, 1);

	res = multiplyMtrx_double(inv_A, mE, size_N, size_N, 1);//����� ��
	fprintf(fout, " Res = Inv_A x mE: \n");
	fprintMtrx_double(fout, res, size_N,1 );
	printf(" Res = Inv_A x mE: \n");
	printMtrx_double(res, size_N,1 );

	fprintf(fout, "\n");
	deleteMtrx(mA, size_N, size_N);//�����迭��ȯ
	deleteMtrx(inv_A, size_N, size_N);
	deleteMtrx(mE, size_N,1);
	deleteMtrx(res, size_N, 1);

	fclose(fin);//���ϴݱ�
}