#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void genBigRandArray(int* array, int size)//ū���� ���� �Լ�
{
	char* repeat;
	unsigned int big;
	unsigned int uint = 0;
	int num = 0;

	repeat = (char*)calloc(size, sizeof(char));//�ߺ����������� �����迭 ����

	srand(time(0));
	while (num < size)
	{
		uint = (rand() << 15) | rand();//30��Ʈ ����
		big = uint % size; //size-1�� ����

		if (repeat[big] == 1) //�ߺ��� �����ϱ����� ���� Ȯ��
			continue;
		else
		{
			repeat[big] = 1;//�ߺ� ���Ÿ� ���� �̹̳��� ���� �� ����
			array[num++] = big;
		}

	}
}
void suffleBigArray(int* array, int size)//�� �迭�� ���� ��ġ�� ��ȯ
{
	int temp,a,b;//temp�� ��ġ�� ��ȯ�ϱ� ���Ͽ� �ʿ��� ����
	srand(time(0));
	for(int i=0;i<size;i++)
		
	{
		a = (((unsigned long)rand() << 15) | rand())% size; // �ΰ��ǳ��� ����
		b = (((unsigned long)rand() << 15) | rand())% size;


		temp = array[a];
		array[a] = array[b];	
		array[b] = temp;
	}


}
void printBigArraySample(int* array, int size, int line_size = 10, int sample_lines = 2)//�迭�� ȭ������ ���
{
	int num=0;
	if (size > 50)//�迭�� ũ�Ⱑ 50�ʰ��Ͻ� ó���� �� ���پ� ���
	{
		for (int i = 0; i < line_size * sample_lines; i++)
		{
			printf("%8d", array[num]);
			num++;
			if (num % 10 == 0)
				printf("\n");
			
		}
		num = size - line_size * sample_lines; 
		printf("\n....\n");//ù�� ���ٰ� ���� ���ٻ��� ���ǥ��
		for (int j = num; j < size; j++)
		{
			printf("%8d", array[num]);
			num++;
			if (num % 10 == 0)
				printf("\n");
			
		}
		printf("\n");
	}
	


	else//�迭�� ũ�Ⱑ 50�����Ͻ� ���ٿ� 10���� �迭 ���
	{
		for (int i = 0; i < size; i++)
		{
			if (i %10  == 0)
				printf("\n");
			printf("%8d", array[i]);
		}
	}
	
}
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size = 10, int sample_lines = 2)//�־��� �迭�� ���Ͽ� ���
{
	int num = 0;
	if (size > 50)//�迭�� ũ�Ⱑ 50�ʰ��Ͻ� ó���� �� ���پ� ���
	{
		for (int i = 0; i < line_size * sample_lines; i++)
		{
			fprintf(fout,"%8d", array[num]);
			num++;
			if(num % 10 == 0)
				fprintf(fout,"\n");
			
		}
		num = size - line_size * sample_lines;
		fprintf(fout,"\n....\n");//ù�� ���ٰ� ���� ���ٻ��� ���ǥ��
		for (int j = num; j < size; j++)
		{
			fprintf(fout,"%8d", array[num]);
			num++;
			if (num % 10 == 0)
				fprintf(fout,"\n");
			
		}
		fprintf(fout, "\n");
	}



	else//�迭�� ũ�Ⱑ 50�����Ͻ� ���ٿ� 10���� �迭 ���
	{
		for (int i = 0; i < size; i++)
		{
			
			if (i % 10 == 0)
				fprintf(fout,"\n");

			fprintf(fout, "%d", array[i]);
		}
	}
}

