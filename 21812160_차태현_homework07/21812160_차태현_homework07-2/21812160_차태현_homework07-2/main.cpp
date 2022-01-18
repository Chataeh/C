/**
*파일이름"행렬연산”
*프로그램의 목적 및 기본 기능:
*  2차원 동적배열을 생성해 행렬을 입력하고 그행렬을 연산하는 프로그램.
*
*프로그램 작성자: 21812160 차태현(2021년 4월16일),
*최종 수정 및 보완: 2021년 4월 16일 (차태현)
*/
#include<stdio.h>
#include<stdlib.h>
#include "Mtrx.h"//사용자 정의헤더

int main()
{
	FILE* fin;
	double** A, ** B, ** C, ** D,**E;// 출력할 행렬을 위해 초기화
	int arow_size, acol_size,brow_size,bcol_size;
	
	
	fin = fopen("input_data.txt", "r");//파일 읽기모드로 열기
	fscanf(fin, "%d %d", &arow_size, &acol_size); //파일에서 행과 열의 값받아옴
	printf("Matrix A:\n");
	A = inputMtrx(fin, &arow_size, &acol_size);//행렬에 파일로부터 받아온 데이터입력
	pirintMtrx(A, arow_size, acol_size);//행렬 출력
	printf("\n");

	fscanf(fin, "%d %d", &brow_size, &bcol_size);
	printf("Matrix B:\n");
	B = inputMtrx(fin, &brow_size, &bcol_size);
	pirintMtrx(B, brow_size, bcol_size);
	printf("\n");
	
	printf("Matrix C = A+B:\n");
	C = addMtrx(A, B, arow_size, bcol_size);//행렬의 덧셈연산
	pirintMtrx(C, arow_size, bcol_size);
	printf("\n");

	printf("Matrix D = A-B:\n");
	D = subMtrx(A, B, arow_size, bcol_size);//행렬의 뺄셈연산
	pirintMtrx(D, arow_size, bcol_size);
	printf("\n");

	printf("Matrix E = A*B:\n");
	E = mulMtrx(A, B, arow_size, bcol_size);//행렬의 곱셈연산
	pirintMtrx(E, arow_size, bcol_size);
	printf("\n");




	deleteMtrx(A,arow_size,acol_size);//동적배열 반환
	deleteMtrx(B, brow_size, bcol_size);
	deleteMtrx(C, arow_size, bcol_size);
	deleteMtrx(D, arow_size, bcol_size);
	deleteMtrx(E, arow_size, bcol_size);

	fclose(fin);//파일닫기


	return 0;
}