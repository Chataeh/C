/**
*���ϸ�:�����ڿ�������
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� �������ڿ��� ������ ���ĺ������� �����ϴ� ���α׷�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 4��10��),
*���� ���� �� ����: 2021�� 4�� 10�� (������)
*============================================================================
*���α׷� ����/���� �̷�
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
	extern char words[][MAX_WORD_LEN];//���������� �ٸ��ҽ������� ����������
	FILE* fout;
	LARGE_INTEGER freq, t1, t2,t3,t4; //�ð��� �������
	long long diff,diff2; //�ð� ��
	double elapsed_time,elapsed_time2;
	

	fout = fopen("output.txt", "w");//���Ͼ������ ����
	srand((unsigned int)time(0));//��Ӻ�ȭ�ϵ��� �ð�����
	QueryPerformanceFrequency(&freq);// ���ļ� ���
    
	printf("Performance Analysis of Sorting Algorithms\n");
	for (int num_words = 10000; num_words <= 100000; num_words +=10000)
	{
		printf("Word array(size: %8d):", num_words);
		genRandWordArray(words, num_words);//���� ���ڿ�����
		fprintf(fout, "Randomly generated Word Array (size: %d)\n", num_words);
		fprintfBigWordArray(fout, words, num_words,10,5 );//���Ͽ� �迭���
		fprintf(fout,"\nQuick sorting for Word Array (size: %d) .....\n", num_words);
	   
		QueryPerformanceCounter(&t1);//�ð�����
		quicksorting(words, num_words);
		QueryPerformanceCounter(&t2);//�ð�����
		diff = t2.QuadPart - t1.QuadPart;//�ð� ������� ���� �ɸ��ð����
		elapsed_time = (double)diff / freq.QuadPart; //�ɸ��ð� ������ ���ļ�

		fprintf(fout, "QuickSort_WordArray(size: %d) took %10.3f [millisecond]\n", num_words,elapsed_time * 1000.0);
		fprintf(fout, "\nAfter sorting word array (size : %d)\n", num_words);
		fprintfBigWordArray(fout, words, num_words, 10, 5);
		fprintf(fout, "\n");
		
		fprintf(fout,"WordArray(size:%8d) after suffling\n",num_words);
		suffleArray(words, num_words);//�����İ� ���������� �ð��� Ȯ���� ���� �迭����
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
	fclose(fout);//���ϴݱ�
}