/**
*�����̸�"��Ŀ��ꡱ
*���α׷��� ���� �� �⺻ ���:
*  2���� �����迭�� ������ ����� �Է��ϰ� ������� �����ϴ� ���α׷�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 4��16��),
*���� ���� �� ����: 2021�� 4�� 16�� (������)
*/
#include<stdio.h>
#include<stdlib.h>
#include "Mtrx.h"//����� �������

int main()
{
	FILE* fin;
	double** A, ** B, ** C, ** D,**E;// ����� ����� ���� �ʱ�ȭ
	int arow_size, acol_size,brow_size,bcol_size;
	
	
	fin = fopen("input_data.txt", "r");//���� �б���� ����
	fscanf(fin, "%d %d", &arow_size, &acol_size); //���Ͽ��� ��� ���� ���޾ƿ�
	printf("Matrix A:\n");
	A = inputMtrx(fin, &arow_size, &acol_size);//��Ŀ� ���Ϸκ��� �޾ƿ� �������Է�
	pirintMtrx(A, arow_size, acol_size);//��� ���
	printf("\n");

	fscanf(fin, "%d %d", &brow_size, &bcol_size);
	printf("Matrix B:\n");
	B = inputMtrx(fin, &brow_size, &bcol_size);
	pirintMtrx(B, brow_size, bcol_size);
	printf("\n");
	
	printf("Matrix C = A+B:\n");
	C = addMtrx(A, B, arow_size, bcol_size);//����� ��������
	pirintMtrx(C, arow_size, bcol_size);
	printf("\n");

	printf("Matrix D = A-B:\n");
	D = subMtrx(A, B, arow_size, bcol_size);//����� ��������
	pirintMtrx(D, arow_size, bcol_size);
	printf("\n");

	printf("Matrix E = A*B:\n");
	E = mulMtrx(A, B, arow_size, bcol_size);//����� ��������
	pirintMtrx(E, arow_size, bcol_size);
	printf("\n");




	deleteMtrx(A,arow_size,acol_size);//�����迭 ��ȯ
	deleteMtrx(B, brow_size, bcol_size);
	deleteMtrx(C, arow_size, bcol_size);
	deleteMtrx(D, arow_size, bcol_size);
	deleteMtrx(E, arow_size, bcol_size);

	fclose(fin);//���ϴݱ�


	return 0;
}