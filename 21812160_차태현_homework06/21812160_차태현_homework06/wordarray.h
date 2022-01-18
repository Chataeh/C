#ifndef WORD_H
#define WORD_H
#define MAX_WORD_LEN 15
#define MAX_NUM_WORDS 500000


void genRandWordArray(char word[][MAX_WORD_LEN], int size);//랜덤 문자열생성
void fprintfBigWordArray(FILE* fout, char wordList[][MAX_WORD_LEN], int size, int words_per_lines = 10, int sample_lines = 5);//문자열 파일에 출력
void sectionsorting(char wordlist[][MAX_WORD_LEN], int num_words);//선택정렬
void _quicksorting(char word[][MAX_WORD_LEN], int size, int left, int right);
void quicksorting(char wordlist[][MAX_WORD_LEN], int num_words);//퀵정렬
void suffleArray(char wordlist[][MAX_WORD_LEN], int size);//배열 자리 셔플

#endif