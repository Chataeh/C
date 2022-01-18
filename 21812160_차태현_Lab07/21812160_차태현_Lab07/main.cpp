/**
*���ϸ�:��Ŀ���
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� 2���������迭�� �����Ͽ� ����� ����ϰ� �����ϴ� ���α׷�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 4��13��),
*���� ���� �� ����: 2021�� 4�� 13�� (������)
*============================================================================
*���α׷� ����/���� �̷�
*/

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"//����� ���� ��� 

void checkAddress_2DimArray_for_Matrix(); //2���� �迭�ּҰ����
void test_2D_DynamicArray_FIleIO();// ���Ϸκ��� �޾ƿ� �����ͷ� 2�����迭 ���
void test_Matrix_Addition_Subtraction();//����� ��������
void test_Matrix_Multiplication();//����� ����
void test_Matrix_avg();

int main()
{
	int num;//1,2,3,4 ����ֱ����� ����

	while (1)
	{
		printf("Testing Matrix Operations with 2-Dimensional Dynamic Array\n");
		printf("1: Check addresses of 2-Dim array for Matrix\n");
		printf("2:Test 2-D Dynamic Array creation for Matrix with FileI/O\n");
		printf("3:Test Matrix Addition,Subtraction\n");
		printf("-1:Quit\n");
		printf("Input num(-1 to quit):");
		scanf("%d", &num);

		if (num == -1)//-1�Էµɽ� ����
			break;
		printf("\n");

		switch (num)
		{
		case 1: 
			checkAddress_2DimArray_for_Matrix();//�ڸ��� �ּ����
			break;

		case 2:
			test_2D_DynamicArray_FIleIO();//���Ϸκ��� ��� �ΰ� �޾ƿ���
			break;
		
		case 3:
			test_Matrix_Addition_Subtraction();//���Ϸ� �޾ƿ� ��� ��������
			break;
			
		case 4:
			test_Matrix_Multiplication();//���Ϸ� �޾ƿ� ��� ����
			break;
		case 5:
			test_Matrix_avg();
			break;

		default :
			break;
		}
	}
}

void checkAddress_2DimArray_for_Matrix()//2�����迭 �ڸ��� �ּڰ� Ȯ��
{
	int m[3][3] = { {10,20,30},{40,50,60},{70,80,90} };

	printf("m       =%p\n", m);
	printf("m[0]    =%p\n", m[0]);
	printf("m[1]    =%p\n", m[1]);
	printf("m[2]    =%p\n", m[2]);
	printf("&m[0][0]=%p\n", &m[0][0]);
	printf("&m[1][0]=%p\n", &m[1][0]);
	printf("&m[2][0]=%p\n", &m[2][0]);
}

void test_2D_DynamicArray_FIleIO() //���Ϸκ��� ��ĵΰ����
{
	FILE* fout;
	int a_row, a_col;
	int b_row, b_col;
	double** dMA, ** dMB;

	fout = fopen("datafile.txt", "r"); //�б����� ���Ͽ���
	fscanf(fout, "%d %d", &a_row, &a_col);// �� ���ϱ� �� �����������
	dMA = fgetDoubleMtrx(fout,a_row, a_col);// dMA�� ��Ĺ޾ƿ�
	printf("Input Matrix_A(%d x %d):\n", a_row, a_col);
	printMtrx(dMA, a_row, a_col);//������
	printf("\n");

	fscanf(fout, "%d %d", &b_row, &b_col);
	dMB = fgetDoubleMtrx(fout, b_row, b_col);
	printf("Input Matrix_B(%d x %d):\n", b_row, b_col);
	printMtrx(dMB, b_row, b_col);
	printf("\n");

	deleteDoubleMtrx(dMA, a_row, a_col);//�����迭 ��ȯ
	deleteDoubleMtrx(dMB, b_row, b_col);
	
	fclose(fout);//���ϴݱ�
}

void test_Matrix_Addition_Subtraction()
{
	FILE* fout;
	int a_row, a_col;
	int b_row, b_col;
	int c_row, c_col;
	int d_row, d_col;
	double** dMA, ** dMB,**dMC,**dMD; //����� ���� ���� ���� C,D ����

	fout = fopen("datafile2.txt","r");//�б��� ���Ͽ���
	fscanf(fout, "%d %d", &a_row, &a_col);
	dMA = fgetDoubleMtrx(fout, a_row, a_col);
	printf("Input Matrix_A(%d x %d):\n", a_row, a_col);
	printMtrx(dMA, a_row, a_col);
	printf("\n");

	fscanf(fout, "%d %d", &b_row, &b_col);
	dMB = fgetDoubleMtrx(fout, b_row, b_col);
	printf("Input Matrix_B(%d x %d):\n", b_row, b_col);
	printMtrx(dMB, b_row, b_col);
	printf("\n");

	c_row = a_row;// ��� ������ Ư¡���� ex) 2x3 ��İ� 3x2��Ŀ���� 2x2����� ����
	c_col = b_col;
	dMC=createDoubleMtrx(c_row, c_col);// �����迭����
	addMtrx(dMA, dMB, dMC, c_row, c_col);//����� ����
	printf("Matrix_C(%d x %d)=Matrix A + Matrix B:\n", c_row, c_col);
	printMtrx(dMC, c_row, c_col);
	printf("\n");

	d_row = a_row;
	d_col = b_col;
	dMD = createDoubleMtrx(d_row, d_col);//�����迭 ����
	subMtrx(dMA, dMB, dMD, d_row, d_col);//����� ����
	printf("Matrix_D(%d x %d)=Matrix A - Matrix B:\n", d_row, d_col);
	printMtrx(dMD, d_row, d_col);
	printf("\n");


	deleteDoubleMtrx(dMA, a_row, a_col);//�����迭 ��ȯ
	deleteDoubleMtrx(dMB, b_row, b_col);
	deleteDoubleMtrx(dMC, c_row, c_col);
	deleteDoubleMtrx(dMD, d_row, d_col);

	fclose(fout);//���ϴݱ�
}

void test_Matrix_Multiplication()
{
	FILE* fout;
	int a_row, a_col;
	int b_row, b_col;
	int c_row, c_col;
	double** dMA, ** dMB, ** dMC;

	fout = fopen("datafile.txt", "r");
	fscanf(fout, "%d %d", &a_row, &a_col);
	dMA=fgetDoubleMtrx(fout, a_row, a_col);
	printf("Input Matrix_A(%d x %d):\n", a_row, a_col);
	printMtrx(dMA, a_row, a_col);
	printf("\n");

	fscanf(fout, "%d %d", &b_row, &b_col);
	dMB = fgetDoubleMtrx(fout, b_row, b_col);
	printf("Input Matrix_B(%d x %d):\n", b_row, b_col);
	printMtrx(dMB, b_row, b_col);
	printf("\n");

	c_row = a_row;// ��� ������ Ư¡���� ex) 2x3 ��İ� 3x2��Ŀ���� 2x2����� ����
	c_col = b_col;
	dMC = createDoubleMtrx(c_row, c_col);// �����迭����
	mutiplyMtrx(dMA, dMB, dMC, a_row, a_col,b_col);//����� ����
	printf("Matrix_C(%d x %d)=Matrix A x Matrix B:\n", c_row, c_col);
	printMtrx(dMC, c_row, c_col);
	printf("\n");


	deleteDoubleMtrx(dMA, a_row, a_col);//�����迭 ��ȯ
	deleteDoubleMtrx(dMB, b_row, b_col);
	deleteDoubleMtrx(dMC, c_row, c_col);

	fclose(fout);//���ϴݱ�
}

void test_Matrix_avg()
{
	FILE* fout;
	int a_row, a_col;
	double** dMA,**dMB;
	double avg=0,avg2=0,avg3=0;
	double num=0,num2=0,num3=0;

	fout = fopen("datafile2.txt", "r"); //�б����� ���Ͽ���
	fscanf(fout, "%d %d", &a_row, &a_col);// �� ���ϱ� �� �����������
	dMA = fgetDoubleMtrx(fout, a_row, a_col);// dMA�� ��Ĺ޾ƿ�
	printf("Input Matrix_A(%d x %d):\n", a_row, a_col);
	printMtrx(dMA, a_row, a_col);//������
	printf("\n");


	dMB = createDoubleMtrx(a_row + 1, a_col + 1);
	for (int i = 0; i < a_row; i++)
	{
		num = 0;
		for (int j = 0; j < a_col; j++)
		{
			dMB[i][j] = dMA[i][j];
			num += dMA[i][j];
		}
		avg = num / a_col;
		dMB[i][a_col] = avg;
	}
	

	for (int i = 0; i < a_col; i++)
	{
		num2 = 0;
		for (int j = 0; j < a_row; j++)
		{
			num2 += dMA[j][i];
		}
		avg2 = num2/ a_row;
		dMB[a_row][i] = avg2;
	}

	for (int i = 0; i < a_col; i++)
	{
		for (int j = 0; j < a_row; j++)
		{
			num3 += dMA[i][j];
		}

	}
	avg3 = num3 /(a_col * a_row);

	dMB[a_row][a_col] = avg3;


	printMtrx(dMB, a_row+1, a_col+1);

	deleteDoubleMtrx(dMA, a_row, a_col);
	deleteDoubleMtrx(dMB, a_row+1, a_col+1);

	fclose(fout);
}