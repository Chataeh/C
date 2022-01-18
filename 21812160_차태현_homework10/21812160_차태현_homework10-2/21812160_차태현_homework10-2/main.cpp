/**
*파일이름"21812160_차태현_homework10-2 ”
*프로그램의 목적 및 기본 기능:
*  문자열을 입력받아 10진수로 변환해주고 다시 16진수로 변환하는 프로그램
*
*프로그램 작성자: 21812160 차태현(2021년 5월15일),
*최종 수정 및 보완: 2021년 5월 15일 (차태현)
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hexadecimal.h"//사용자 정의헤더

void main()
{
	char* hexStr;
	char* hexConvertStr;
	unsigned int value_int;
	
	hexStr = (char*)calloc(MAX_HEX_STR_LEN + 1, sizeof(char));//동적할당
	hexConvertStr = (char*)calloc(MAX_HEX_STR_LEN + 1, sizeof(char));
	while (true)
	{
		printf("input hexadecimal number : ");
		scanf("%s", hexStr);//입력 문자열
		if (strcmp(hexStr, ".") == 0)//.일시 종료
			break;
		value_int = atox(hexStr);//10진수받기
		printf("hexadecimal (%s) = %d (decimal)\n", hexStr, value_int);
		xtoa(hexConvertStr,value_int);//16진수받기
		printf("hexadecimal (%s) = %d (decimal) = %#0X (hexadecimal) =re - converted hexadecimal string(% s)\n",	hexStr, value_int, value_int, hexConvertStr);
	}

	free(hexStr);
	free(hexConvertStr);
}
