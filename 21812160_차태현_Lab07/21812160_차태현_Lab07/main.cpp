/**
*파일명:행렬연산
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 2차원동적배열을 생성하여 행렬을 출력하고 연산하는 프로그램.
*
*프로그램 작성자: 21812160 차태현(2021년 4월13일),
*최종 수정 및 보완: 2021년 4월 13일 (차태현)
*============================================================================
*프로그램 수정/보완 이력
*/

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"//사용자 정의 헤더 

void checkAddress_2DimArray_for_Matrix(); //2차원 배열주소값출력
void test_2D_DynamicArray_FIleIO();// 파일로부터 받아온 데이터로 2차원배열 출력
void test_Matrix_Addition_Subtraction();//행렬의 덧셈뺄셈
void test_Matrix_Multiplication();//행렬의 곱셈
void test_Matrix_avg();

int main()
{
	int num;//1,2,3,4 골라주기위한 변수

	while (1)
	{
		printf("Testing Matrix Operations with 2-Dimensional Dynamic Array\n");
		printf("1: Check addresses of 2-Dim array for Matrix\n");
		printf("2:Test 2-D Dynamic Array creation for Matrix with FileI/O\n");
		printf("3:Test Matrix Addition,Subtraction\n");
		printf("-1:Quit\n");
		printf("Input num(-1 to quit):");
		scanf("%d", &num);

		if (num == -1)//-1입력될시 종료
			break;
		printf("\n");

		switch (num)
		{
		case 1: 
			checkAddress_2DimArray_for_Matrix();//자리별 주소출력
			break;

		case 2:
			test_2D_DynamicArray_FIleIO();//파일로부터 행렬 두개 받아오기
			break;
		
		case 3:
			test_Matrix_Addition_Subtraction();//파일로 받아온 행렬 덧셈뺄셈
			break;
			
		case 4:
			test_Matrix_Multiplication();//파일로 받아온 행렬 곱셈
			break;
		case 5:
			test_Matrix_avg();
			break;

		default :
			break;
		}
	}
}

void checkAddress_2DimArray_for_Matrix()//2차원배열 자리별 주솟값 확인
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

void test_2D_DynamicArray_FIleIO() //파일로부터 행렬두개출력
{
	FILE* fout;
	int a_row, a_col;
	int b_row, b_col;
	double** dMA, ** dMB;

	fout = fopen("datafile.txt", "r"); //읽기전용 파일열기
	fscanf(fout, "%d %d", &a_row, &a_col);// 몇 곱하기 몇 행렬인지받음
	dMA = fgetDoubleMtrx(fout,a_row, a_col);// dMA에 행렬받아옴
	printf("Input Matrix_A(%d x %d):\n", a_row, a_col);
	printMtrx(dMA, a_row, a_col);//행렬출력
	printf("\n");

	fscanf(fout, "%d %d", &b_row, &b_col);
	dMB = fgetDoubleMtrx(fout, b_row, b_col);
	printf("Input Matrix_B(%d x %d):\n", b_row, b_col);
	printMtrx(dMB, b_row, b_col);
	printf("\n");

	deleteDoubleMtrx(dMA, a_row, a_col);//동적배열 반환
	deleteDoubleMtrx(dMB, b_row, b_col);
	
	fclose(fout);//파일닫기
}

void test_Matrix_Addition_Subtraction()
{
	FILE* fout;
	int a_row, a_col;
	int b_row, b_col;
	int c_row, c_col;
	int d_row, d_col;
	double** dMA, ** dMB,**dMC,**dMD; //행렬의 연산 값을 위한 C,D 지정

	fout = fopen("datafile2.txt","r");//읽기모드 파일열기
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

	c_row = a_row;// 행렬 연산의 특징으로 ex) 2x3 행렬과 3x2행렬연산시 2x2행렬이 나옴
	c_col = b_col;
	dMC=createDoubleMtrx(c_row, c_col);// 동적배열생성
	addMtrx(dMA, dMB, dMC, c_row, c_col);//행렬의 덧셈
	printf("Matrix_C(%d x %d)=Matrix A + Matrix B:\n", c_row, c_col);
	printMtrx(dMC, c_row, c_col);
	printf("\n");

	d_row = a_row;
	d_col = b_col;
	dMD = createDoubleMtrx(d_row, d_col);//동적배열 생성
	subMtrx(dMA, dMB, dMD, d_row, d_col);//행렬의 뺄셈
	printf("Matrix_D(%d x %d)=Matrix A - Matrix B:\n", d_row, d_col);
	printMtrx(dMD, d_row, d_col);
	printf("\n");


	deleteDoubleMtrx(dMA, a_row, a_col);//동적배열 반환
	deleteDoubleMtrx(dMB, b_row, b_col);
	deleteDoubleMtrx(dMC, c_row, c_col);
	deleteDoubleMtrx(dMD, d_row, d_col);

	fclose(fout);//파일닫기
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

	c_row = a_row;// 행렬 연산의 특징으로 ex) 2x3 행렬과 3x2행렬연산시 2x2행렬이 나옴
	c_col = b_col;
	dMC = createDoubleMtrx(c_row, c_col);// 동적배열생성
	mutiplyMtrx(dMA, dMB, dMC, a_row, a_col,b_col);//행렬의 곱셈
	printf("Matrix_C(%d x %d)=Matrix A x Matrix B:\n", c_row, c_col);
	printMtrx(dMC, c_row, c_col);
	printf("\n");


	deleteDoubleMtrx(dMA, a_row, a_col);//동적배열 반환
	deleteDoubleMtrx(dMB, b_row, b_col);
	deleteDoubleMtrx(dMC, c_row, c_col);

	fclose(fout);//파일닫기
}

void test_Matrix_avg()
{
	FILE* fout;
	int a_row, a_col;
	double** dMA,**dMB;
	double avg=0,avg2=0,avg3=0;
	double num=0,num2=0,num3=0;

	fout = fopen("datafile2.txt", "r"); //읽기전용 파일열기
	fscanf(fout, "%d %d", &a_row, &a_col);// 몇 곱하기 몇 행렬인지받음
	dMA = fgetDoubleMtrx(fout, a_row, a_col);// dMA에 행렬받아옴
	printf("Input Matrix_A(%d x %d):\n", a_row, a_col);
	printMtrx(dMA, a_row, a_col);//행렬출력
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