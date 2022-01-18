#include<stdio.h>
#include<stdlib.h>
#include "hexadecimal.h"

unsigned int atox(char* hexStr)
{
	unsigned char hexChar;
	unsigned int hexVal = 0, hexSum = 0;

	for (int i = 0; i < MAX_HEX_STR_LEN; i++)
	{
		hexChar = hexStr[i];//�����ϳ��� �޾ƿ� ���ڿ��� ����
		
		if (hexChar == NULL)
			break;
		if ((hexChar >= '0') && (hexChar <= '9'))//���ڰ� 0~9�����ΰ��
			hexVal=hexChar-'0'; //0~9�� ��ȯ
		else if ((hexChar >= 'A') && (hexChar <= 'F'))
			hexVal = hexChar - 'A'+10; //A~F�� ��ȯ
		else if ((hexChar >= 'a') && (hexChar <= 'f'))
			hexVal = hexChar - 'a' + 10; //a~f�� ��ȯ
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
		mod = hxd % 16;//��������
		if (mod >9)
			temp[i] = mod + 'A'-10;//10������A~F������ ǥ��
		else
			temp[i] = mod + '0';//10������ 0~9�� ǥ��
		hxd /= 16;
		if (hxd == 0)//0�Ͻ� ����
			break;
		i++;//����ĭ�� �Է¹ޱ����� ����
	}
	
	
	for (int j = 0; j<=i; j++)//���ڿ��� ���̸�ŭ�ݺ�
	{
		strBuf[j] = temp[i-j];//�������� ���
	}
	
	free(temp);
}
