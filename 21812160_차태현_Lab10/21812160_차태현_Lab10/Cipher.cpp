#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void xtoa(unsigned char uc)
{
	printf("%c", uc);
}
void cipherchar(unsigned char ch, unsigned char* pCC_u, unsigned char* pCC_l)
{
	char c[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };//문자배열선언
	int num = ch;//문자uc를 10진수로 받아옴
	int up, low;
	up = num / 16;//상위비트값을 위한 나눗셈
	low = num % 16;//하위비트값을 위한 모듈러
	
	*pCC_u=c[up];//상위비트 값
	*pCC_l=c[low];// 하위비트값

}

void cipherText(FILE* fp_msg, FILE* fp_tx,unsigned char cipher_code)
{
	char* sp;
	unsigned char pCC_u = {};
	unsigned char pCC_l = {};
	int num=0;

	sp = (char*)calloc(300, sizeof(char));
	
	while (fscanf(fp_msg, "%c", &sp[num])!=EOF)//파일로부터 문자를 받아옴
	{
		sp[num] ^= cipher_code;//XOR연산을 통한 암호화
		cipherchar(sp[num], &pCC_u,&pCC_l);//상위비트와 하위비트각각표시
		fprintf(fp_tx, "%c%c", pCC_u, pCC_l);//파일에 출력
		if (sp[num] == '\n')//띄어쓰기일시 띄어쓰기
			fprintf(fp_tx, "\n");
		num++;
	}
	
	free(sp);
}
unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l)
{
	unsigned char uc, hexChar;
	unsigned int hexVal = 0, hexSum = 0;
	
	char hexstr[3]=" ";
	hexstr[0] = rc_u;
	hexstr[1] = rc_l;
	
	for (int i = 0; i < 2; i++)
	{
		hexChar = hexstr[i];//문자를 문자열로 만들어줌
		if (hexChar == NULL)
			break;
		if ((hexChar >= '0') && (hexChar <= '9'))
			hexVal = hexChar - '0';
		else if ((hexChar >= 'A') && (hexChar <= 'F'))
			hexVal = hexChar - 'A' + 10;
		else if ((hexChar >= 'a') && (hexChar <= 'f'))
			hexVal = hexChar - 'a' + 10;

		hexSum = hexSum * 16 + hexVal;
	}
	

	return hexSum;
}

void deCipherText(FILE* fp_tx, FILE* fp_out, unsigned char cipher_code)
{
	char up, low;
	int num;
	char sp;
	
	while (fscanf(fp_tx, "%c",&up)!=EOF)//상위비트의 문자 하나 받아옴
	{
		if (up == '\n')
			continue;
		fscanf(fp_tx, "%c", &low);//하위비트의 문자 하나받아옴
		
		sp=deCipherChar(up, low);//합해서 반환
		sp ^= cipher_code;//XOR을 통한 복호화실행
		fprintf(fp_out, "%c", sp);
	}
}