#ifndef MTRX_H
#define MTRX_H
#include<stdio.h>
#include<stdlib.h>

double** inputMtrx(FILE* fin, int* row_size, int* col_size);//����� ���Ϸκ��� �޾ƿ��� �Լ� 
double** creat(int row_size, int col_size); // 2���� �����迭 �����Լ�
void deleteMtrx(double** ppM, int row_size, int col_size);//�����迭 ��ȯ
void pirintMtrx(double** ppM, int row_size, int col_size);//��� ���
double **addMtrx(double** A, double** B, int row_size, int col_size);// ����� ��
double **subMtrx(double** A, double** B, int row_size, int col_size);//����� ��
double** mulMtrx(double** A, double** B, int row_size, int col_size);//����� ����

#endif 
