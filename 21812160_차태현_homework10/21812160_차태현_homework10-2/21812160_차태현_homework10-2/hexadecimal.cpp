#include<stdio.h>
#include<stdlib.h>
#include "hexadecimal.h"

unsigned int atox(char* hexStr)
{
	unsigned char hexChar;
	unsigned int hexVal = 0, hexSum = 0;

	for (int i = 0; i < MAX_HEX_STR_LEN; i++)
	{
		hexChar = hexStr[i];//문자하나씩 받아와 문자열을 만듦
		
		if (hexChar == NULL)
			break;
		if ((hexChar >= '0') && (hexChar <= '9'))//문자가 0~9사이인경우
			hexVal=hexChar-'0'; //0~9로 변환
		else if ((hexChar >= 'A') && (hexChar <= 'F'))
			hexVal = hexChar - 'A'+10; //A~F로 변환
		else if ((hexChar >= 'a') && (hexChar <= 'f'))
			hexVal = hexChar - 'a' + 10; //a~f로 변환
		hexSum = hexSum * 16 + hexVal;
	}
	return hexSum;
}

void xtoa(char* strBuf,unsigned int hxd)
{
	char* temp;
	int len;
	int mod;
	int i = 0;
	temp = (char*)calloc(MAX_HEX_STR_LEN, sizeof(char)+1);
	
	while(1)
	{
		mod = hxd % 16;//나머지값
		if (mod >9)
			temp[i] = mod + 'A'-10;//10진수를A~F까지로 표현
		else
			temp[i] = mod + '0';//10진수를 0~9로 표현
		hxd /= 16;
		if (hxd == 0)//0일시 종료
			break;
		i++;//다음칸을 입력받기위한 덧셈
	}
	
	
	for (int j = 0; j<=i; j++)//문자열의 길이만큼반복
	{
		strBuf[j] = temp[i-j];//역순으로 출력
	}
	
	free(temp);
}
