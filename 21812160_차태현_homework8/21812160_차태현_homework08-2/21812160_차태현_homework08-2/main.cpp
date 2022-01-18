/**
*파일이름"21812160_차태현_homework08-2”
*프로그램의 목적 및 기본 기능:
* 행렬을 가우스소거법과 역행렬을사용한 가우스소거법으로 해를구하여 비교
*
*프로그램 작성자: 21812160 차태현(2021년 4월29일),
*최종 수정 및 보완: 2021년 4월 29일 (차태현)
*/
#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include"mtrx.h"//사용자 정의 헤더
#include"Gauss.h"//사용자 정의 헤더

int main()
{
	FILE* fout;
	FILE* fin;
	FILE* A_fin;

	int size_N, size_N2;
	double* solution;//해를 출력할 솔루션
	double** augMtrx,**mX,**mI,**res,**mA;//행렬저장
	int solExist = 1;
	double data;

	fin = fopen("input_data.txt", "r");//파일읽기모드로 열기
	fout = fopen("output.txt", "w");//파일 쓰기모드로 열기
	A_fin = fopen("A_data.txt", "r");

	fscanf(fin, "%d", &size_N);//파일로부터 size_N받아오기
	augMtrx = creat(size_N+1, size_N+1);//동적메모리 생성
	mA = creat(size_N, size_N);
	mX = creat(size_N, size_N);
	mI = creat(size_N, size_N);
	res = creat(size_N, size_N);

	fgetAugmentedMtrx(fin, augMtrx, size_N);//파일로부터 행렬 값 받아오기
	solution=(double*)calloc(size_N, sizeof(double));//동적메모리생성
	fprintf(fout, "Augmented Matrix : \n");
	fprintMtrx(fout, augMtrx, size_N, size_N + 1);
	printf("Augmented Matrix : \n");
	printMtrx(augMtrx, size_N, size_N + 1);//행렬출력

	diagonalize_FileOut(fout, augMtrx, size_N, &solExist);//가우스소거법실행
	if (solExist)
	{
		fprintf(fout, "The solution of the given linear system:\n");
		printf("The solution of the given linear system:\n");
		for (int i = 0; i < size_N; i++)
		{
			solution[i] = augMtrx[i][size_N];//솔루션에 마지막열의 값들을 입력
			fprintf(fout, " x[%d] : %4f\n", i, solution[i]);
			printf(" x[%d] : %4f\n", i, solution[i]);
		}
	}
	else
	{
		fprintf(fout, "No unique solution\n");
		printf("No unique solution\n");
	}


	for (int m = 0; m < size_N; m++) //행렬값 받아오기
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
	

	inverseMtrx(mA, mI, size_N);//역행렬구하기
	printf(" Inverse : \n");
	printMtrx(mI, size_N, size_N);

	printf(" mX: \n");
	printMtrx(mX, size_N, 1);

	mutiplyMtrx(mI,mX,res,size_N,size_N,1);//행렬의 곱
	printf(" Res = mI x mX: \n");
	printMtrx(res, size_N, 1);

	deleteMtrx(augMtrx, size_N, 1);//동적메모리 반환
	deleteMtrx(mI, size_N, 1);
	deleteMtrx(mX, size_N, 1);
	deleteMtrx(res, size_N, 1);

	fclose(fout);//파일닫기
	fclose(fin);
	fclose(A_fin);
}
