//BigArray.cpp
//�迭�� ��°� ���ó���� ���� �Լ���
#include <stdio.h>
#include<limits.h>
#include<math.h> 
#include<time.h>
#include<stdlib.h>
void printBigArraySample(int* array, int size, int line_size, int num_sample_lines) //�迭���
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
		num = size - line_size * num_sample_lines; //num= (��üũ��)-(����ҷ��� �� �迭�� ��)

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

void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_sample_lines)// �迭�� ���Ͽ� ���
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



void getArrayStatistics(int* array, int size)//���������� �� ���
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

void fgetArrayStatistics(FILE* fout, int* array, int size)//  ������� ��� �� ���Ͽ� ���
{
	int min = INT_MAX;
	int max = INT_MIN;
	int sum = 0;
	double avg = 0;
	double diff, var, sq_diff_sum = 0, std_dev;

	for (int i = 0; i < size; i++)
	{

		if (array[i] < min)//�ּҰ� ���ϱ�
			min = array[i];

		if (array[i] > max)//�ִ밪 ���ϱ�
			max = array[i];

		sum += array[i];
	}
	avg = sum / (double)size; //��հ� ���

	for (int i = 0; i < size; i++)
	{
		diff = array[i] - avg;
		sq_diff_sum += diff * diff;
	}
	var = sq_diff_sum / (double)size;//�л���
	std_dev = sqrt(var);//ǥ������ ���
	fprintf(fout, "min(%8d), max(%8d), sum(%8d), average(%8.2lf), variance(%8.2lf), standard deviation(%8.2lf)\n", min, max, sum, avg, var, std_dev);

}

void genBigRandArray(int* array, int size)//���� ����
{
	char* flag;
	unsigned int uint_32, bigRand;
	int num=0;

	srand(time(0));// �ð�����
	
	flag = (char*)malloc(sizeof(char) * size);//�����迭 ����

	while (num < size)
	{
		uint_32 = (rand() << 15) | rand(); //30��Ʈ ��������
		bigRand = uint_32 % size; //size-1ũ���� ��������


		if (flag[bigRand] == 1) //�ߺ��˻�
			continue;
		else
		{
			flag[bigRand] = 1;
			array[num++] = bigRand;
		}
	}
}