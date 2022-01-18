#ifndef MTRX_H
#define MTRX_H
#include<stdio.h>
#include<stdlib.h>

double** inputMtrx(FILE* fin, int* row_size, int* col_size);//행렬을 파일로부터 받아오는 함수 
double** creat(int row_size, int col_size); // 2차원 동적배열 생성함수
void deleteMtrx(double** ppM, int row_size, int col_size);//동적배열 반환
void pirintMtrx(double** ppM, int row_size, int col_size);//행렬 출력
double **addMtrx(double** A, double** B, int row_size, int col_size);// 행렬의 합
double **subMtrx(double** A, double** B, int row_size, int col_size);//행렬의 차
double** mulMtrx(double** A, double** B, int row_size, int col_size);//행렬의 곱셈

#endif 
