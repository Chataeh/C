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
	char c[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };//���ڹ迭����
	int num = ch;//����uc�� 10������ �޾ƿ�
	int up, low;
	up = num / 16;//������Ʈ���� ���� ������
	low = num % 16;//������Ʈ���� ���� ��ⷯ
	
	*pCC_u=c[up];//������Ʈ ��
	*pCC_l=c[low];// ������Ʈ��

}

void cipherText(FILE* fp_msg, FILE* fp_tx,unsigned char cipher_code)
{
	char* sp;
	unsigned char pCC_u = {};
	unsigned char pCC_l = {};
	int num=0;

	sp = (char*)calloc(300, sizeof(char));
	
	while (fscanf(fp_msg, "%c", &sp[num])!=EOF)//���Ϸκ��� ���ڸ� �޾ƿ�
	{
		sp[num] ^= cipher_code;//XOR������ ���� ��ȣȭ
		cipherchar(sp[num], &pCC_u,&pCC_l);//������Ʈ�� ������Ʈ����ǥ��
		fprintf(fp_tx, "%c%c", pCC_u, pCC_l);//���Ͽ� ���
		if (sp[num] == '\n')//�����Ͻ� ����
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
		hexChar = hexstr[i];//���ڸ� ���ڿ��� �������
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
	
	while (fscanf(fp_tx, "%c",&up)!=EOF)//������Ʈ�� ���� �ϳ� �޾ƿ�
	{
		if (up == '\n')
			continue;
		fscanf(fp_tx, "%c", &low);//������Ʈ�� ���� �ϳ��޾ƿ�
		
		sp=deCipherChar(up, low);//���ؼ� ��ȯ
		sp ^= cipher_code;//XOR�� ���� ��ȣȭ����
		fprintf(fp_out, "%c", sp);
	}
}