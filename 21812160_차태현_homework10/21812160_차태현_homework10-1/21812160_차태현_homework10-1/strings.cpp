#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void selectionsort(char** word, int word_num, int word_len)//��������
{
	char* temp;
	int min;

	temp = (char*)calloc(word_len, sizeof(char));//�����Ҵ�

	for (int i = 0; i < word_num; i++)
	{
		strcpy(temp, word[i]);//�ʱⰪ����
		min = i;
		for (int j = i + 1; j < word_num; j++)
		{
			if (strcmp(word[j],temp) < 0)//�ʱⰪ�� ���Ͽ� �ּڰ�����
			{
				min = j;
				strcpy(temp, word[j]);
				
			}
		}
		if (min != i)
		{
			strcpy(word[min], word[i]);//�ʱ� �ּڰ��� �ٸ��� ��ġ��ȯ
			strcpy(word[i], temp);
		}
	}
}