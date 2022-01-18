/**
*파일이름"21812160_차태현_homework10-1 ”
*프로그램의 목적 및 기본 기능:
*  파일로부터 문자열을 받고 문자열의 길이와 문자열의 정렬
*
*프로그램 작성자: 21812160 차태현(2021년 5월14일),
*최종 수정 및 보완: 2021년 5월 14일 (차태현)
*/#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"strings.h"//사용자정의헤더
#define WORD_MAX 10
#define LEN 15

int main()
{
	FILE* fin;
	FILE* fout;
	int* word_len;//문자열의 길이
	char** word;//문자열
	char words[WORD_MAX];//파일에서 받아올 문자
	int num = 0;

	fin = fopen("words_input.txt", "r");
	fout = fopen("words_output.txt", "w");

	word_len = (int*)calloc(WORD_MAX, sizeof(int));//동적배열할당
	word = (char**)calloc(WORD_MAX, sizeof(char*));
	for (int i = 0; i < WORD_MAX; i++)
	{
		word[i] = (char*)calloc(LEN, sizeof(char));
	}
	
	while (fscanf(fin, "%s", &words) != EOF)
	{
		strcpy(word[num], words);//파일로부터 문자를 받아옴
		num++;
		
	}
	for (int j = 0; j < WORD_MAX; j++)
	{
		word_len[j]=strlen(word[j]);//문자열길이 계산
	}

	fprintf(fout, "Input word list:\n");
	for (int k = 0; k < WORD_MAX; k++)
	{
		fprintf(fout, "(%2d)th-word : %-10s (word_length : %2d)\n", k, word[k], word_len[k]);
	}
	selectionsort(word, WORD_MAX, LEN);//문자열 선택정렬
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
