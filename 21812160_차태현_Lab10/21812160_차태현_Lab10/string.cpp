#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void selectionSortWords(char** word_array, int num_words, int max_word_len)//선택정렬
{
	char* temp;
	int min;

	temp = (char*)calloc(max_word_len, sizeof(char));//문자열받기위한 동적배열생성

	for (int i = 0; i < num_words; i++)
	{
		strcpy(temp, word_array[i]);//초기값설정
		min = i;
		for (int j = i + 1; j < num_words; j++)
		{
			if (strcmp(word_array[j], temp) < 0)//최소값 결정
			{
				min = j;
				strcpy(temp, word_array[j]);
			}
		}
		if (min != i)//초기의 최솟값과 다를시 위치변환
		{
			strcpy(word_array[min], word_array[i]);
			strcpy(word_array[i], temp);
		}
	}	
}