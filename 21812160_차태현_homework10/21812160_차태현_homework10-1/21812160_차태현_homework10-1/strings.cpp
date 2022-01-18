#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void selectionsort(char** word, int word_num, int word_len)//선택정렬
{
	char* temp;
	int min;

	temp = (char*)calloc(word_len, sizeof(char));//동적할당

	for (int i = 0; i < word_num; i++)
	{
		strcpy(temp, word[i]);//초기값설정
		min = i;
		for (int j = i + 1; j < word_num; j++)
		{
			if (strcmp(word[j],temp) < 0)//초기값과 비교하여 최솟값설정
			{
				min = j;
				strcpy(temp, word[j]);
				
			}
		}
		if (min != i)
		{
			strcpy(word[min], word[i]);//초기 최솟값이 다를시 위치교환
			strcpy(word[i], temp);
		}
	}
}