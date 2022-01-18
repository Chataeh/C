/**
*파일이름"21812160_차태현_homework08 ”
*프로그램의 목적 및 기본 기능:
* 파일로부터 행렬을 입력받아 기본연산을 하고 그 역행렬을 구하는 프로그램
*
*프로그램 작성자: 21812160 차태현(2021년 4월28일),
*최종 수정 및 보완: 2021년 4월 28일 (차태현)
*/
#include<stdio.h>
#include<stdlib.h>
#include"mtrx.h"//사용자 정의헤더

int main()
{
	double** mA=NULL, ** mB=NULL, ** mC=NULL, ** mD = NULL, ** mF = NULL, ** mE = NULL, ** mI = NULL, ** inv_mA=NULL;//행렬을 입력받을 2차원동적배열을 위한 정의
	double** A;
	
	int a_row,a_col,size_N;//각각의 행렬을 크기
	int b_row, b_col;
	int c_row, c_col;
	int d_row, d_col;
	int e_row, e_col; 
	int f_row, f_col;
	int i_row, i_col;

	FILE* fout;
	FILE* fin;
	FILE* A_fin;

	fout = fopen("Array_2D_input.txt", "r");//읽기모드로 파일열기
	fin = fopen("output.txt", "w");//쓰기모드로 파일열기
	A_fin = fopen("nxn_mtrx.txt", "r");

	printf(" A=\n");
	mA=fGetMtrx(fout, &a_row, &a_col);//파일로부터 행렬받아오기
	printMtrx(mA, a_row,a_col);//행렬출력
	printf("\n ");

	printf(" B=\n");
	mB = fGetMtrx(fout, &b_row, &b_col);
	printMtrx(mB, b_row, b_col);
	printf("\n ");

	printf(" C=\n");
	mC = fGetMtrx(fout, &c_row, &c_col);
	printMtrx(mC, c_row, c_col);
	printf("\n");

	d_row = a_row;//행렬의 행초기화
	d_col = b_col;//행렬의 열초기화
	mD=creat(d_row, d_col);//2차원 동적배열생성
	addMtrx(mA, mB, mD, d_row, d_col);//행렬의 합
	printf(" A+B = D =\n");
	printMtrx(mD, d_row, d_col);
	printf("\n");

	e_row = a_row;//행렬의 행초기화
	e_col = b_col;//행렬의 열초기화
	mE = creat(e_row, e_col);//2차원 동적배열생성
	subMtrx(mA, mB, mE, e_row, e_col);//행렬의 차
	printf(" A-B = E =\n");
	printMtrx(mE, e_row, e_col);
	printf("\n");

	f_row = a_row;
	f_col = c_col;
	mF = creat(f_row, f_col);
	mutiplyMtrx(mA, mC, mF, a_row, a_col, c_col);//행렬의 곱
	printf(" A*C = F =\n");
	printMtrx(mF, f_row, f_col);

	A = fGetMtrx(A_fin, &size_N, &size_N);

	inv_mA = creat(size_N, size_N);// 동적배열생성
	inverseMtrx(A, inv_mA, size_N);	//역행렬 구하기
	printf("inv_A =  \n");
	printMtrx(inv_mA, size_N, size_N);
	i_row = size_N;
	i_col = size_N;
	mI = creat(i_row, i_col);
	mutiplyMtrx(A, inv_mA,mI,size_N, size_N,size_N);//역행렬과 행렬의 곱
	fprintf(fin, " A*inv_A = I =\n");
	fprintMtrx(fin, mI, i_row, i_col);//파일에 출력


	deleteMtrx(mA, a_row, a_col);//동적배열 반환
	deleteMtrx(mB, b_row, b_col);
	deleteMtrx(mC, c_row, c_col);
	deleteMtrx(mD, d_row, d_col);
	deleteMtrx(mE, e_row, e_col);
	deleteMtrx(mF, f_row, f_col);
	deleteMtrx(mI, i_row, i_col);
	deleteMtrx(A, size_N, size_N);

	fclose(fout);//파일닫기
	fclose(fin);
	fclose(A_fin);
}