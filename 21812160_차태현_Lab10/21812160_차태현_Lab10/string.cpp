#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void selectionSortWords(char** word_array, int num_words, int max_word_len)//��������
{
	char* temp;
	int min;

	temp = (char*)calloc(max_word_len, sizeof(char));//���ڿ��ޱ����� �����迭����

	for (int i = 0; i < num_words; i++)
	{
		strcpy(temp, word_array[i]);//�ʱⰪ����
		min = i;
		for (int j = i + 1; j < num_words; j++)
		{
			if (strcmp(word_array[j], temp) < 0)//�ּҰ� ����
			{
				min = j;
				strcpy(temp, word_array[j]);
			}
		}
		if (min != i)//�ʱ��� �ּڰ��� �ٸ��� ��ġ��ȯ
		{
			strcpy(word_array[min], word_array[i]);
			strcpy(word_array[i], temp);
		}
	}	
}