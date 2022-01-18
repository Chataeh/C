/**
*파일명:다중소스파일
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 헤더파일을 사용해 다중소스파일을 구성하고 화면뿐만아니라 파일에도 출력하는 프로그램.
*
*프로그램 작성자: 21812160 차태현(2021년 4월2일),
*최종 수정 및 보완: 2021년 4월 2일 (차태현)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BigArray.h"//사용자 정의헤더


int main()
{
	FILE* fout;
	int* array;
	int size;//입력받을 배열의 크기

	fout = fopen("out.txt", "w");//파일 쓰기전용으로 열기 out.txt에 출력을 위함
	printf("Input size of big array(more than 100000)=");
	
	scanf_s("%d", &size);
	fprintf(fout, "Input size of big array(more than 100000)=%d\n",size);
	
	array = (int*)calloc(sizeof(int), size);//array 배열에 크기확장을 위해 동적배열 생성
	genBigRandArray(array, size);//난수 생성함수
	printBigArraySample(array, size);//배열출력함수
	fprintBigArraySample(fout,array, size);//파일에 배열출력

	fclose(fout);//파일닫기
	free(array);//동적배열반환

	return 0;
}