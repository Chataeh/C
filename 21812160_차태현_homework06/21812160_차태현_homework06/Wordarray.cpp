#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"wordarray.h"
void genword(char word[], int min_word_len, int max_word_len)
{ 
	int len;
	len = len = (rand() % (max_word_len - min_word_len + 1)) + min_word_len;// 5~15범위의 난수생성
	for (int i = 0; i <len; i++)
	{
		if (i == 0)
			word[i] = rand() % 26 + 'A';//첫문자는 대문자
		else if (i == len)
			word[i] == NULL;//마지막문자는 NULL
		else
			word[i] = rand() % 26 + 'a';//다른자리는 다 소문자
	}
}


void genRandWordArray(char word[][MAX_WORD_LEN], int num_words)
{	
	for (int i = 0; i < num_words; i++)//생성하고하는 개수만큼 난수생성
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
		if (num % words_per_lines == 0)//10줄마다 띄어쓰기
			fprintf(fout, "\n");
	}

	fprintf(fout,"....\n");
	num = size - words_per_lines * sample_lines;//마지막 50줄 출력을 위한  num정의
	for (int j = num; j < size; j++)
	{
		fprintf(fout, "%-20s", wordList[j]);
		num++;
		if (num % words_per_lines == 0)
			fprintf(fout, "\n");
	}

}

void sectionsorting(char word[][MAX_WORD_LEN], int num_words)//선택정렬
{
	char temp[MAX_WORD_LEN];
	int index;

	for (int i = 0; i < num_words; i++) //처음값을 기준으로 실행
	{
		index = i;
		for (int j = i + 1; j < num_words; j++)
		{
			if (strcmp(word[index], word[j]) > 0)//처음값보다 작은값을 탐색
			{
				index = j;
			}
		}
			if (index != i)//처음값과 가장작은 값이 같지않다면 위치교환
			{
				strcpy(temp, word[i]);
				strcpy(word[i], word[index]);
				strcpy(word[index], temp);
			}
	
	}
}


void _quicksorting(char word[][MAX_WORD_LEN], int size, int left, int right)//퀵
{
	char temp[MAX_WORD_LEN];
	int pivot=(left+right)/2; //기준 피벗설정
	int newpi;

	strcpy(temp, word[pivot]);        // 기준 피봇값을 맨오른쪽으로 보내줌
	strcpy(word[pivot], word[right]);
	strcpy(word[right], temp);

	newpi = left;
	for (int i = left; i < right; i++)
	{
		if (strcmp(word[i], word[right]) < 0) //기준값 왼쪽에 기준값보다 더 작은값들을 넣어주기위함.
		{
			strcpy(temp, word[i]);
			strcpy(word[i], word[newpi]);
			strcpy(word[newpi],temp);
			newpi++;
		}
	}
	strcpy(temp, word[newpi]);//맨오른쪽으로 보냈던 기준값 새로찾아낸 양옆을 구분하는 newpi값과 교환
	strcpy(word[newpi], word[right]);
	strcpy(word[right], temp);


	if (left < newpi - 1)//기준갑에 대해 작은 왼쪽재귀함수실해
	{
		_quicksorting(word, size, left,newpi-1);
	}
	if (newpi+1 < right) //기준값에 대해 큰 오른쪽재귀실행
	{
		_quicksorting(word, size, newpi+1, right);
	}


	
}

void quicksorting(char wordlist[][MAX_WORD_LEN], int num_words)//퀵정렬
{
	_quicksorting(wordlist, num_words, 0, num_words - 1);
}

void suffleArray(char wordlist[][MAX_WORD_LEN], int size)// 문자열을 다시 섞는 함수
{
	char temp[MAX_WORD_LEN];
	int index;

	srand((unsigned)time(0));
	for (int i = 0; i < size; i++)
	{
		index = (rand() % size);//size-1 만큼의 난수생성 

		strcpy(temp, wordlist[i]);
		strcpy(wordlist[i], wordlist[index]);
		strcpy(wordlist[index], temp);
	}
}