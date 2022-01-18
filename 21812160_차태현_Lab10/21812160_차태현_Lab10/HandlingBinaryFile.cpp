#include<stdio.h>
#include <ctype.h>
#define BUFFER_LEN 16


void dumpBinaryFile(FILE* fin, FILE* fout)//2진파일 입출력
{
	int nbytes;
	unsigned char buffer[BUFFER_LEN] = " ";//한줄에 16개씩 처리하기위함
	
	for (int i = 0; i <300; i += BUFFER_LEN)
	{
		nbytes = fread(buffer, sizeof(unsigned char), BUFFER_LEN, fin);
		fprintf(fout, "%08X: ",i);//16진수로 출력
		for (int i = 0; i < nbytes; i++)
		{
			if (i == (BUFFER_LEN / 2))
			{
				fprintf(fout, " ");
			}
			fprintf(fout, "%02X ", buffer[i]);// 각각의 바이트를 16진수로표현
		}
		fprintf(fout, " ");
		for (int j = 0; j < nbytes; j++)
		{
			if (isprint(buffer[j]))//출력가능 할시
				fprintf(fout, "%c", buffer[j]);
			else
				fprintf(fout, ".");//참고 못하는정보일시 .으로 출력
		}
		fprintf(fout, "\n");
	}
}