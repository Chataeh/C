#ifndef WORD_H
#define WORD_H
#define MAX_WORD_LEN 15
#define MAX_NUM_WORDS 500000


void genRandWordArray(char word[][MAX_WORD_LEN], int size);//���� ���ڿ�����
void fprintfBigWordArray(FILE* fout, char wordList[][MAX_WORD_LEN], int size, int words_per_lines = 10, int sample_lines = 5);//���ڿ� ���Ͽ� ���
void sectionsorting(char wordlist[][MAX_WORD_LEN], int num_words);//��������
void _quicksorting(char word[][MAX_WORD_LEN], int size, int left, int right);
void quicksorting(char wordlist[][MAX_WORD_LEN], int num_words);//������
void suffleArray(char wordlist[][MAX_WORD_LEN], int size);//�迭 �ڸ� ����

#endif