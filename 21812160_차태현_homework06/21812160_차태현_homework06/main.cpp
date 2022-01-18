/**
*파일명:“문자열난수”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 랜덤문자열을 생성해 알파벳순으로 정렬하는 프로그램.
*
*프로그램 작성자: 21812160 차태현(2021년 4월10일),
*최종 수정 및 보완: 2021년 4월 10일 (차태현)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*
*/
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include "wordarray.h"

int main()
{
	extern char words[][MAX_WORD_LEN];//전역변수로 다른소스파일의 변수가져옴
	FILE* fout;
	LARGE_INTEGER freq, t1, t2,t3,t4; //시간을 재기위함
	long long diff,diff2; //시간 차
	double elapsed_time,elapsed_time2;
	

	fout = fopen("output.txt", "w");//파일쓰기모드로 생성
	srand((unsigned int)time(0));//계속변화하도록 시간변경
	QueryPerformanceFrequency(&freq);// 주파수 기록
    
	printf("Performance Analysis of Sorting Algorithms\n");
	for (int num_words = 10000; num_words <= 100000; num_words +=10000)
	{
		printf("Word array(size: %8d):", num_words);
		genRandWordArray(words, num_words);//랜덤 문자열생성
		fprintf(fout, "Randomly generated Word Array (size: %d)\n", num_words);
		fprintfBigWordArray(fout, words, num_words,10,5 );//파일에 배열출력
		fprintf(fout,"\nQuick sorting for Word Array (size: %d) .....\n", num_words);
	   
		QueryPerformanceCounter(&t1);//시간측정
		quicksorting(words, num_words);
		QueryPerformanceCounter(&t2);//시간측정
		diff = t2.QuadPart - t1.QuadPart;//시간 차계산을 통해 걸린시간계산
		elapsed_time = (double)diff / freq.QuadPart; //걸린시간 나누기 주파수

		fprintf(fout, "QuickSort_WordArray(size: %d) took %10.3f [millisecond]\n", num_words,elapsed_time * 1000.0);
		fprintf(fout, "\nAfter sorting word array (size : %d)\n", num_words);
		fprintfBigWordArray(fout, words, num_words, 10, 5);
		fprintf(fout, "\n");
		
		fprintf(fout,"WordArray(size:%8d) after suffling\n",num_words);
		suffleArray(words, num_words);//퀵정렬과 선택정렬의 시간차 확인을 위한 배열셔플
		fprintfBigWordArray(fout, words, num_words, 10, 5);

		QueryPerformanceCounter(&t3);
		sectionsorting(words, num_words);
		QueryPerformanceCounter(&t4);
		diff2 = t4.QuadPart - t3.QuadPart;
		elapsed_time2 = (double)diff2 / freq.QuadPart;

		fprintf(fout,"Selection sorting for Word Array (size:%d)\n", num_words);
		fprintf(fout, "SelectionSort_WordArray(size: %d) took %10.3f [millisecond]\n", num_words, elapsed_time2 * 1000.0);
		fprintf(fout, "\nAfter sorting word array (size : %d)\n", num_words);
		fprintfBigWordArray(fout, words, num_words, 10, 5);
		fprintf(fout, "\n");



		printf("Quick_Sort (%10.3lf ms),Select_Sort(%10.3lf ms) \n", elapsed_time * 1000.0, elapsed_time2 * 1000.0);
	}
	fclose(fout);//파일닫기
}