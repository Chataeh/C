//BigArray.cpp
//배열의 출력과 통계처리를 위한 함수들
#include <stdio.h>
#include<limits.h>
#include<math.h> 
#include<time.h>
#include<stdlib.h>
void printBigArraySample(int* array, int size, int line_size, int num_sample_lines) //배열출력
{
	int num = 0;

	for (int i = 0; i < num_sample_lines; i++)
	{
		for (int j = 0; j < line_size; j++)
		{
			if (num > size)
			{
				printf("\n");
				return;
			}
			printf("%8d", array[num]);
			num++;
			if (num%10==0)
				printf("\n");
		}
	}
	printf("\n");

	if (num < (size - line_size * num_sample_lines))
		num = size - line_size * num_sample_lines; //num= (전체크기)-(출력할려는 총 배열의 수)

	if (num >= size)
		return;
	printf("\n   .....\n");

	for (int i = 0; i < num_sample_lines; i++)
	{
		for (int j = 0; j < line_size; j++)
		{
			if (num > size)
			{
				printf("\n");
				return;
			}
			printf("%8d", array[num]);
			num++;
		}
		printf("\n");
	}
	printf("\n");
}

void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_sample_lines)// 배열을 파일에 출력
{
	int num = 0;

	for (int i = 0; i < num_sample_lines; i++)
	{
		for (int j = 0; j < line_size; j++)
		{
			if (num > size)
			{
				fprintf(fout, "\n");
				return;
			}
			fprintf(fout, "%8d", array[num]);
			num++;
		}
	}
	fprintf(fout, "\n");

	if (num < (size - line_size * num_sample_lines))
		num = size - line_size * num_sample_lines;

	if (num >= size)
		return;
	fprintf(fout, "\n   .....\n");

	for (int i = 0; i < num_sample_lines; i++)
	{
		for (int j = 0; j < line_size; j++)
		{
			if (num > size)
			{
				fprintf(fout, "\n");
				return;
			}
			fprintf(fout, "%8d", array[num]);
			num++;
		}
		fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
}



void getArrayStatistics(int* array, int size)//통계정보계산 후 출력
{
	int min = INT_MAX;
	int max = INT_MIN;
	int sum = 0;
	double avg = 0;
	double diff, var, sq_diff_sum = 0, std_dev;

	for (int i = 0; i < size; i++)
	{

		if (array[i] < min)
			min = array[i];

		if (array[i] > max)
			max = array[i];

		sum += array[i];
	}
	avg = sum / (double)size;

	for (int i = 0; i < size; i++)
	{
		diff = array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / (double)size;
	std_dev = sqrt(var);

	printf("min(%8d), max(%8d), sum(%8d), average(%8.2lf), variance(%8.2lf), standard deviation(%8.2lf)\n", min, max, sum, avg, var, std_dev);

}

void fgetArrayStatistics(FILE* fout, int* array, int size)//  통계정보 계산 후 파일에 출력
{
	int min = INT_MAX;
	int max = INT_MIN;
	int sum = 0;
	double avg = 0;
	double diff, var, sq_diff_sum = 0, std_dev;

	for (int i = 0; i < size; i++)
	{

		if (array[i] < min)//최소값 구하기
			min = array[i];

		if (array[i] > max)//최대값 구하기
			max = array[i];

		sum += array[i];
	}
	avg = sum / (double)size; //평균값 계산

	for (int i = 0; i < size; i++)
	{
		diff = array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / (double)size;//분산계산
	std_dev = sqrt(var);//표준편차 계산
	fprintf(fout, "min(%8d), max(%8d), sum(%8d), average(%8.2lf), variance(%8.2lf), standard deviation(%8.2lf)\n", min, max, sum, avg, var, std_dev);

}

void genBigRandArray(int* array, int size)//난수 생성
{
	char* flag;
	unsigned int uint_32, bigRand;
	int num=0;

	srand(time(0));// 시간변경
	
	flag = (char*)malloc(sizeof(char) * size);//동적배열 생성

	while (num < size)
	{
		uint_32 = (rand() << 15) | rand(); //30비트 난수생성
		bigRand = uint_32 % size; //size-1크기의 난수생성


		if (flag[bigRand] == 1) //중복검사
			continue;
		else
		{
			flag[bigRand] = 1;
			array[num++] = bigRand;
		}
	}
}