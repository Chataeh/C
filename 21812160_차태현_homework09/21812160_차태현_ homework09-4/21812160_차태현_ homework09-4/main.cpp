/**
*파일이름" 21812160_차태현_homework09-4”
*프로그램의 목적 및 기본 기능:
*  복소수의 값을 입력받은 후 연산 및 값에따른 정렬.
*
*프로그램 작성자: 21812160 차태현(2021년 5월7일),
*최종 수정 및 보완: 2021년 5월 7일 (차태현)
*/
#include <stdio.h>
#include "Cmplx.h"//사용자 정의헤더
void main()
{
	Cmplx cmplxs[7]; // 구조체 배열정의
	cmplxs[0] = inputCmplx();//배열 0에 복소수값입력
	cmplxs[1] = inputCmplx();//배열 1에 복소수값입력
	printf("cmplxs[0] = "); printCmplx(cmplxs[0]); printf("\n");
	printf("cmplxs[1] = "); printCmplx(cmplxs[1]); printf("\n");
	cmplxs[2] = cmplxAdd(cmplxs[0], cmplxs[1]);//복소수 더하기
	printf("cmplxs[2] = cmplxs[0] + cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" + "); printCmplx(cmplxs[1]); printf(" = "); printCmplx(cmplxs[2]); printf("\n");
	cmplxs[3] = complxSubtract(cmplxs[0], cmplxs[1]);//복소수 뺄셈
	printf("cmplxs[3] = cmplxs[0] - cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" - "); printCmplx(cmplxs[1]); printf(" = "); printCmplx(cmplxs[3]); printf("\n");
	cmplxs[4] = complxMultiply(cmplxs[0], cmplxs[1]);//복소수 곱셈
	printf("cmplxs[4] = cmplxs[0] * cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" * "); printCmplx(cmplxs[1]); printf(" = "); printCmplx(cmplxs[4]); printf("\n");
	cmplxs[5] = cmplxDivide(cmplxs[0], cmplxs[1]);//복소수 나눗셈
	printf("cmplxs[5] = cmplxs[0] / cmplxs[1] = \n ");
	printCmplx(cmplxs[0]); printf(" / "); printCmplx(cmplxs[1]); printf(" = "); printCmplx(cmplxs[5]); printf("\n");
	cmplxs[6] = complxMultiply(cmplxs[1], cmplxs[5]);
	printf("cmplxs[6] = cmplxs[1] * cmplxs[5] = \n ");
	printCmplx(cmplxs[1]); printf(" * "); printCmplx(cmplxs[5]); printf(" = "); printCmplx(cmplxs[6]); printf("\n");
	printf("Before sorting complexs: \n");
	for (int i = 0; i < 7; i++)//복소수 출력
	{
		printf("cmplxs[%d] = ", i); printCmplx(cmplxs[i]);
		printf("\n");
	}
	quickSortCmplx(cmplxs, 7);//퀵소팅으로 정렬
	printf("Sorted complexs: \n");
	for (int i = 0; i < 7; i++)//정렬후 출력
	{
		printf("cmplxs[%d] = ", i); printCmplx(cmplxs[i]);
		printf("\n");
	}
}