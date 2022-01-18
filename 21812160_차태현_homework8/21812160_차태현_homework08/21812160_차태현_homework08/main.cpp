/**
*�����̸�"21812160_������_homework08 ��
*���α׷��� ���� �� �⺻ ���:
* ���Ϸκ��� ����� �Է¹޾� �⺻������ �ϰ� �� ������� ���ϴ� ���α׷�
*
*���α׷� �ۼ���: 21812160 ������(2021�� 4��28��),
*���� ���� �� ����: 2021�� 4�� 28�� (������)
*/
#include<stdio.h>
#include<stdlib.h>
#include"mtrx.h"//����� �������

int main()
{
	double** mA=NULL, ** mB=NULL, ** mC=NULL, ** mD = NULL, ** mF = NULL, ** mE = NULL, ** mI = NULL, ** inv_mA=NULL;//����� �Է¹��� 2���������迭�� ���� ����
	double** A;
	
	int a_row,a_col,size_N;//������ ����� ũ��
	int b_row, b_col;
	int c_row, c_col;
	int d_row, d_col;
	int e_row, e_col; 
	int f_row, f_col;
	int i_row, i_col;

	FILE* fout;
	FILE* fin;
	FILE* A_fin;

	fout = fopen("Array_2D_input.txt", "r");//�б���� ���Ͽ���
	fin = fopen("output.txt", "w");//������� ���Ͽ���
	A_fin = fopen("nxn_mtrx.txt", "r");

	printf(" A=\n");
	mA=fGetMtrx(fout, &a_row, &a_col);//���Ϸκ��� ��Ĺ޾ƿ���
	printMtrx(mA, a_row,a_col);//������
	printf("\n ");

	printf(" B=\n");
	mB = fGetMtrx(fout, &b_row, &b_col);
	printMtrx(mB, b_row, b_col);
	printf("\n ");

	printf(" C=\n");
	mC = fGetMtrx(fout, &c_row, &c_col);
	printMtrx(mC, c_row, c_col);
	printf("\n");

	d_row = a_row;//����� ���ʱ�ȭ
	d_col = b_col;//����� ���ʱ�ȭ
	mD=creat(d_row, d_col);//2���� �����迭����
	addMtrx(mA, mB, mD, d_row, d_col);//����� ��
	printf(" A+B = D =\n");
	printMtrx(mD, d_row, d_col);
	printf("\n");

	e_row = a_row;//����� ���ʱ�ȭ
	e_col = b_col;//����� ���ʱ�ȭ
	mE = creat(e_row, e_col);//2���� �����迭����
	subMtrx(mA, mB, mE, e_row, e_col);//����� ��
	printf(" A-B = E =\n");
	printMtrx(mE, e_row, e_col);
	printf("\n");

	f_row = a_row;
	f_col = c_col;
	mF = creat(f_row, f_col);
	mutiplyMtrx(mA, mC, mF, a_row, a_col, c_col);//����� ��
	printf(" A*C = F =\n");
	printMtrx(mF, f_row, f_col);

	A = fGetMtrx(A_fin, &size_N, &size_N);

	inv_mA = creat(size_N, size_N);// �����迭����
	inverseMtrx(A, inv_mA, size_N);	//����� ���ϱ�
	printf("inv_A =  \n");
	printMtrx(inv_mA, size_N, size_N);
	i_row = size_N;
	i_col = size_N;
	mI = creat(i_row, i_col);
	mutiplyMtrx(A, inv_mA,mI,size_N, size_N,size_N);//����İ� ����� ��
	fprintf(fin, " A*inv_A = I =\n");
	fprintMtrx(fin, mI, i_row, i_col);//���Ͽ� ���


	deleteMtrx(mA, a_row, a_col);//�����迭 ��ȯ
	deleteMtrx(mB, b_row, b_col);
	deleteMtrx(mC, c_row, c_col);
	deleteMtrx(mD, d_row, d_col);
	deleteMtrx(mE, e_row, e_col);
	deleteMtrx(mF, f_row, f_col);
	deleteMtrx(mI, i_row, i_col);
	deleteMtrx(A, size_N, size_N);

	fclose(fout);//���ϴݱ�
	fclose(fin);
	fclose(A_fin);
}