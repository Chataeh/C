#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "array.h"
void genBigRandArray(int* array, int size, int offset)//ū���� ���� �Լ�
{
	char* repeat;
	unsigned int big;
	unsigned int uint = 0;
	int num = 0;

	repeat = (char*)calloc(size, sizeof(char));//�ߺ����������� �����迭 ����

	srand((unsigned int)time(0));
	while (num < size)
	{
		uint = (rand() << 15) | rand();//30��Ʈ ����
		big = uint % size; //size-1�� ����

		if (repeat[big] == 1) //�ߺ��� �����ϱ����� ���� Ȯ��
			continue;
		else
		{
			repeat[big] = 1;//�ߺ� ���Ÿ� ���� �̹̳��� ���� �� ����
			array[num++] = big + offset;
		}

	}
}

void printBigArraySample(int* array, int size, int line_size, int sample_lines)//�迭�� ȭ������ ���
{
	int num = 0;
	
		for (int i = 0; i < line_size * sample_lines; i++)
		{
			printf("%8d", array[num]);
			num++;
			if (num % 10 == 0)
				printf("\n");

		}
		num = size - line_size * sample_lines;
		printf("  .....\n");//ù�� ���ٰ� ���� ���ٻ��� ���ǥ��
		for (int j = num; j < size; j++)
		{
			printf("%8d", array[num]);
			num++;
			if (num % 10 == 0)
				printf("\n");

		}
		printf("\n");
	
}

void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int sample_lines)//�迭�� ȭ������ ���
{
	int num = 0;
	

		for (int i = 0; i < line_size * sample_lines; i++)
		{
			fprintf(fout, "%8d", array[num]);
			num++;
			if (num % 10 == 0)
				fprintf(fout, "\n");

		}
		num = size - line_size * sample_lines;
		fprintf(fout, "  .....\n");//ù�� ���ٰ� ���� ���ٻ��� ���ǥ��
		for (int j = num; j < size; j++)
		{
			fprintf(fout, "%8d", array[num]);
			num++;
			if (num % 10 == 0)
				fprintf(fout, "\n");

		}
		fprintf(fout, "\n");
	
}

void _quick(int* array, int size, int left, int right)
{
	int value, newpi, temp;
	int pivot = (left + right) / 2; //���ذ��� �迭�� �߰�������

	value = array[pivot];


	temp = array[pivot];//���ذ��� �� ���������� ����
	array[pivot] = array[right];
	array[right] = temp;

	newpi = left;//���ʿ� ���ذ����� �������� �־��ֱ� ����
	for (int i = left; i <= (right - 1); i++)
	{
		if (array[i] <= value)
		{
			temp = array[i];
			array[i] = array[newpi];
			array[newpi] = temp;
			newpi = newpi + 1; //�������� ������ �״���ĭ���� �̵�
		}
	}

	temp = array[newpi];//�ǿ��������� ���´� ���ذ��� �翷�� ������ ���� newpi������ �̵�
	array[newpi] = array[right]; 
	array[right] = temp;

	
	
	if (left < (newpi - 1)) // ���ذ��� ���� �������� ����
	{
		_quick(array, size, left, newpi - 1);
	}
	if (newpi + 1 < right)//���ذ��� ���� ū ������ ����
	{
		_quick(array, size, newpi + 1, right);
	}

}



void hyQuick(int* array, int size,int left,int right)
{  
	if ((right-left+1) <= QUICK) //QUICK���� �����ų� ������ ��������
	{
		int index;
		int min;

		for (int i = left; i <= (right - 1); i++)
		{
			index = i;
			min = array[i];


			for (int j = i + 1; j <= right ; j++)
			{
				if (array[j] < min)
				{
					min = array[j];
					index = j;
				}
			}
			if (index != i)
			{
				array[index] = array[i];
				array[i] = min;
			}
		}
		return;
	}

	int value, newpi, temp;
	int pivot = (left + right) / 2; //���ذ��� �迭�� �߰�������

	value = array[pivot];


	temp = array[pivot];//���ذ��� �� ���������� ����
	array[pivot] = array[right];
	array[right] = temp;

	newpi = left;//���ʿ� ���ذ����� �������� �־��ֱ� ����
	for (int i = left; i <= (right - 1); i++)
	{
		if (array[i] <= value)
		{
			temp = array[i];
			array[i] = array[newpi];
			array[newpi] = temp;
			newpi = newpi + 1; //�������� ������ �״���ĭ���� �̵�
		}
	}

	temp = array[newpi];//�ǿ��������� ���´� ���ذ��� �翷�� ������ ���� newpi������ �̵�
	array[newpi] = array[right];
	array[right] = temp;

	if(left<(newpi-1))
		hyQuick(array, size,left,newpi-1); 
	if  ((newpi+1)<right)
		hyQuick(array, size, newpi+1,right);


}
void Quick(int* array, int size)
{
	_quick(array, size, 0, size - 1);
}



void select(int* array, int size) //��������
{
	int index;
	int min;

	for (int i = 0; i < size - 1; i++)
	{
		index = i;
		min = array[i];

		for (int j = i + 1; j < size; j++)
		{
			if (array[j] < min)
			{
				min = array[j];
				index = j;
			}
		}
		if (index != i) //i��° ���� �ּҰ����� ����
		{
			array[index] = array[i];
			array[i] = min;
		}
	}
}

