/**
*�����̸�"21812160_������_homework08-2��
*���α׷��� ���� �� �⺻ ���:
* ����� ���콺�ҰŹ��� ������������ ���콺�ҰŹ����� �ظ����Ͽ� ��
*
*���α׷� �ۼ���: 21812160 ������(2021�� 4��29��),
*���� ���� �� ����: 2021�� 4�� 29�� (������)
*/
#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include"mtrx.h"//����� ���� ���
#include"Gauss.h"//����� ���� ���

int main()
{
	FILE* fout;
	FILE* fin;
	FILE* A_fin;

	int size_N, size_N2;
	double* solution;//�ظ� ����� �ַ��
	double** augMtrx,**mX,**mI,**res,**mA;//�������
	int solExist = 1;
	double data;

	fin = fopen("input_data.txt", "r");//�����б���� ����
	fout = fopen("output.txt", "w");//���� ������� ����
	A_fin = fopen("A_data.txt", "r");

	fscanf(fin, "%d", &size_N);//���Ϸκ��� size_N�޾ƿ���
	augMtrx = creat(size_N+1, size_N+1);//�����޸� ����
	mA = creat(size_N, size_N);
	mX = creat(size_N, size_N);
	mI = creat(size_N, size_N);
	res = creat(size_N, size_N);

	fgetAugmentedMtrx(fin, augMtrx, size_N);//���Ϸκ��� ��� �� �޾ƿ���
	solution=(double*)calloc(size_N, sizeof(double));//�����޸𸮻���
	fprintf(fout, "Augmented Matrix : \n");
	fprintMtrx(fout, augMtrx, size_N, size_N + 1);
	printf("Augmented Matrix : \n");
	printMtrx(augMtrx, size_N, size_N + 1);//������

	diagonalize_FileOut(fout, augMtrx, size_N, &solExist);//���콺�ҰŹ�����
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


	for (int m = 0; m < size_N; m++) //��İ� �޾ƿ���
	{
		for (int n = 0; n < size_N; n++)
		{
			fscanf(A_fin, "%lf", &data);
			mA[m][n] = data;
		}
	}
	for (int i = 0; i < size_N; i++)
	{
		fscanf(A_fin, "%lf", &data);
		mX[i][0] = data;
	}
	

	inverseMtrx(mA, mI, size_N);//����ı��ϱ�
	printf(" Inverse : \n");
	printMtrx(mI, size_N, size_N);

	printf(" mX: \n");
	printMtrx(mX, size_N, 1);

	mutiplyMtrx(mI,mX,res,size_N,size_N,1);//����� ��
	printf(" Res = mI x mX: \n");
	printMtrx(res, size_N, 1);

	deleteMtrx(augMtrx, size_N, 1);//�����޸� ��ȯ
	deleteMtrx(mI, size_N, 1);
	deleteMtrx(mX, size_N, 1);
	deleteMtrx(res, size_N, 1);

	fclose(fout);//���ϴݱ�
	fclose(fin);
	fclose(A_fin);
}
