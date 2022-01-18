/**
*�����̸�"21812160_������_homework10-1 ��
*���α׷��� ���� �� �⺻ ���:
*  ���Ϸκ��� ���ڿ��� �ް� ���ڿ��� ���̿� ���ڿ��� ����
*
*���α׷� �ۼ���: 21812160 ������(2021�� 5��14��),
*���� ���� �� ����: 2021�� 5�� 14�� (������)
*/#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"strings.h"//������������
#define WORD_MAX 10
#define LEN 15

int main()
{
	FILE* fin;
	FILE* fout;
	int* word_len;//���ڿ��� ����
	char** word;//���ڿ�
	char words[WORD_MAX];//���Ͽ��� �޾ƿ� ����
	int num = 0;

	fin = fopen("words_input.txt", "r");
	fout = fopen("words_output.txt", "w");

	word_len = (int*)calloc(WORD_MAX, sizeof(int));//�����迭�Ҵ�
	word = (char**)calloc(WORD_MAX, sizeof(char*));
	for (int i = 0; i < WORD_MAX; i++)
	{
		word[i] = (char*)calloc(LEN, sizeof(char));
	}
	
	while (fscanf(fin, "%s", &words) != EOF)
	{
		strcpy(word[num], words);//���Ϸκ��� ���ڸ� �޾ƿ�
		num++;
		
	}
	for (int j = 0; j < WORD_MAX; j++)
	{
		word_len[j]=strlen(word[j]);//���ڿ����� ���
	}

	fprintf(fout, "Input word list:\n");
	for (int k = 0; k < WORD_MAX; k++)
	{
		fprintf(fout, "(%2d)th-word : %-10s (word_length : %2d)\n", k, word[k], word_len[k]);
	}
	selectionsort(word, WORD_MAX, LEN);//���ڿ� ��������
	fprintf(fout,"Sorted word list:");
	num = 0;
	for (int k = 0; k < WORD_MAX; k++)
	{
		if (num % 5 == 0)
			fprintf(fout, "\n");
		fprintf(fout, "%-10s", word[k]);
		
		num++;
	}

	fclose(fin);
	fclose(fout);
	free(word_len);
	free(word);

	return 0;
}
