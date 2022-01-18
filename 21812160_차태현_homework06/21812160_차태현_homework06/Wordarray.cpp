#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"wordarray.h"
void genword(char word[], int min_word_len, int max_word_len)
{ 
	int len;
	len = len = (rand() % (max_word_len - min_word_len + 1)) + min_word_len;// 5~15������ ��������
	for (int i = 0; i <len; i++)
	{
		if (i == 0)
			word[i] = rand() % 26 + 'A';//ù���ڴ� �빮��
		else if (i == len)
			word[i] == NULL;//���������ڴ� NULL
		else
			word[i] = rand() % 26 + 'a';//�ٸ��ڸ��� �� �ҹ���
	}
}


void genRandWordArray(char word[][MAX_WORD_LEN], int num_words)
{	
	for (int i = 0; i < num_words; i++)//�����ϰ��ϴ� ������ŭ ��������
	{
		genword(word[i], 5, 10);

	}
}

void fprintfBigWordArray(FILE* fout, char wordList[][MAX_WORD_LEN], int size, int words_per_lines , int sample_lines )
{
	int num = 0;
	for (int i = 0; i < words_per_lines*sample_lines; i++)
	{
		fprintf(fout, "%-20s", wordList[i]);
		num++;
		if (num % words_per_lines == 0)//10�ٸ��� ����
			fprintf(fout, "\n");
	}

	fprintf(fout,"....\n");
	num = size - words_per_lines * sample_lines;//������ 50�� ����� ����  num����
	for (int j = num; j < size; j++)
	{
		fprintf(fout, "%-20s", wordList[j]);
		num++;
		if (num % words_per_lines == 0)
			fprintf(fout, "\n");
	}

}

void sectionsorting(char word[][MAX_WORD_LEN], int num_words)//��������
{
	char temp[MAX_WORD_LEN];
	int index;

	for (int i = 0; i < num_words; i++) //ó������ �������� ����
	{
		index = i;
		for (int j = i + 1; j < num_words; j++)
		{
			if (strcmp(word[index], word[j]) > 0)//ó�������� �������� Ž��
			{
				index = j;
			}
		}
			if (index != i)//ó������ �������� ���� �����ʴٸ� ��ġ��ȯ
			{
				strcpy(temp, word[i]);
				strcpy(word[i], word[index]);
				strcpy(word[index], temp);
			}
	
	}
}


void _quicksorting(char word[][MAX_WORD_LEN], int size, int left, int right)//��
{
	char temp[MAX_WORD_LEN];
	int pivot=(left+right)/2; //���� �ǹ�����
	int newpi;

	strcpy(temp, word[pivot]);        // ���� �Ǻ����� �ǿ��������� ������
	strcpy(word[pivot], word[right]);
	strcpy(word[right], temp);

	newpi = left;
	for (int i = left; i < right; i++)
	{
		if (strcmp(word[i], word[right]) < 0) //���ذ� ���ʿ� ���ذ����� �� ���������� �־��ֱ�����.
		{
			strcpy(temp, word[i]);
			strcpy(word[i], word[newpi]);
			strcpy(word[newpi],temp);
			newpi++;
		}
	}
	strcpy(temp, word[newpi]);//�ǿ��������� ���´� ���ذ� ����ã�Ƴ� �翷�� �����ϴ� newpi���� ��ȯ
	strcpy(word[newpi], word[right]);
	strcpy(word[right], temp);


	if (left < newpi - 1)//���ذ��� ���� ���� ��������Լ�����
	{
		_quicksorting(word, size, left,newpi-1);
	}
	if (newpi+1 < right) //���ذ��� ���� ū ��������ͽ���
	{
		_quicksorting(word, size, newpi+1, right);
	}


	
}

void quicksorting(char wordlist[][MAX_WORD_LEN], int num_words)//������
{
	_quicksorting(wordlist, num_words, 0, num_words - 1);
}

void suffleArray(char wordlist[][MAX_WORD_LEN], int size)// ���ڿ��� �ٽ� ���� �Լ�
{
	char temp[MAX_WORD_LEN];
	int index;

	srand((unsigned)time(0));
	for (int i = 0; i < size; i++)
	{
		index = (rand() % size);//size-1 ��ŭ�� �������� 

		strcpy(temp, wordlist[i]);
		strcpy(wordlist[i], wordlist[index]);
		strcpy(wordlist[index], temp);
	}
}