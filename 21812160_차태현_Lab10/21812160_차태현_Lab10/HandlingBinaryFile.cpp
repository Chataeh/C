#include<stdio.h>
#include <ctype.h>
#define BUFFER_LEN 16


void dumpBinaryFile(FILE* fin, FILE* fout)//2������ �����
{
	int nbytes;
	unsigned char buffer[BUFFER_LEN] = " ";//���ٿ� 16���� ó���ϱ�����
	
	for (int i = 0; i <300; i += BUFFER_LEN)
	{
		nbytes = fread(buffer, sizeof(unsigned char), BUFFER_LEN, fin);
		fprintf(fout, "%08X: ",i);//16������ ���
		for (int i = 0; i < nbytes; i++)
		{
			if (i == (BUFFER_LEN / 2))
			{
				fprintf(fout, " ");
			}
			fprintf(fout, "%02X ", buffer[i]);// ������ ����Ʈ�� 16������ǥ��
		}
		fprintf(fout, " ");
		for (int j = 0; j < nbytes; j++)
		{
			if (isprint(buffer[j]))//��°��� �ҽ�
				fprintf(fout, "%c", buffer[j]);
			else
				fprintf(fout, ".");//���� ���ϴ������Ͻ� .���� ���
		}
		fprintf(fout, "\n");
	}
}