/**
*�����̸�"21812160_������_homework10-2 ��
*���α׷��� ���� �� �⺻ ���:
*  ���ڿ��� �Է¹޾� 10������ ��ȯ���ְ� �ٽ� 16������ ��ȯ�ϴ� ���α׷�
*
*���α׷� �ۼ���: 21812160 ������(2021�� 5��15��),
*���� ���� �� ����: 2021�� 5�� 15�� (������)
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hexadecimal.h"//����� �������

void main()
{
	char* hexStr;
	char* hexConvertStr;
	unsigned int value_int;
	
	hexStr = (char*)calloc(MAX_HEX_STR_LEN + 1, sizeof(char));//�����Ҵ�
	hexConvertStr = (char*)calloc(MAX_HEX_STR_LEN + 1, sizeof(char));
	while (true)
	{
		printf("input hexadecimal number : ");
		scanf("%s", hexStr);//�Է� ���ڿ�
		if (strcmp(hexStr, ".") == 0)//.�Ͻ� ����
			break;
		value_int = atox(hexStr);//10�����ޱ�
		printf("hexadecimal (%s) = %d (decimal)\n", hexStr, value_int);
		xtoa(hexConvertStr,value_int);//16�����ޱ�
		printf("hexadecimal (%s) = %d (decimal) = %#0X (hexadecimal) =re - converted hexadecimal string(% s)\n",	hexStr, value_int, value_int, hexConvertStr);
	}

	free(hexStr);
	free(hexConvertStr);
}
