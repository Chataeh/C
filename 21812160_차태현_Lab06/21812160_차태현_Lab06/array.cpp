#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "array.h"
void genBigRandArray(int* array, int size, int offset)//큰난수 생성 함수
{
	char* repeat;
	unsigned int big;
	unsigned int uint = 0;
	int num = 0;

	repeat = (char*)calloc(size, sizeof(char));//중복방지를위한 동적배열 생성

	srand((unsigned int)time(0));
	while (num < size)
	{
		uint = (rand() << 15) | rand();//30비트 난수
		big = uint % size; //size-1의 난수

		if (repeat[big] == 1) //중복을 제거하기위해 값을 확인
			continue;
		else
		{
			repeat[big] = 1;//중복 제거를 위한 이미나온 수의 값 정의
			array[num++] = big + offset;
		}

	}
}

void printBigArraySample(int* array, int size, int line_size, int sample_lines)//배열을 화면으로 출력
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
		printf("  .....\n");//첫줄 두줄과 끝줄 두줄사이 경계표시
		for (int j = num; j < size; j++)
		{
			printf("%8d", array[num]);
			num++;
			if (num % 10 == 0)
				printf("\n");

		}
		printf("\n");
	
}

void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int sample_lines)//배열을 화면으로 출력
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
		fprintf(fout, "  .....\n");//첫줄 두줄과 끝줄 두줄사이 경계표시
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
	int pivot = (left + right) / 2; //기준값은 배열의 중간정수값

	value = array[pivot];


	temp = array[pivot];//기준값을 맨 오른쪽으로 보냄
	array[pivot] = array[right];
	array[right] = temp;

	newpi = left;//왼쪽에 기준값보다 작은값을 넣어주기 위함
	for (int i = left; i <= (right - 1); i++)
	{
		if (array[i] <= value)
		{
			temp = array[i];
			array[i] = array[newpi];
			array[newpi] = temp;
			newpi = newpi + 1; //작은값이 들어갔을시 그다음칸으로 이동
		}
	}

	temp = array[newpi];//맨오른쪽으로 보냈던 기준값을 양옆을 나누는 기준 newpi값으로 이동
	array[newpi] = array[right]; 
	array[right] = temp;

	
	
	if (left < (newpi - 1)) // 기준값에 비해 작은왼쪽 실행
	{
		_quick(array, size, left, newpi - 1);
	}
	if (newpi + 1 < right)//기준값에 비해 큰 오른쪽 실행
	{
		_quick(array, size, newpi + 1, right);
	}

}



void hyQuick(int* array, int size,int left,int right)
{  
	if ((right-left+1) <= QUICK) //QUICK보다 작을거나 같을시 선택정렬
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
	int pivot = (left + right) / 2; //기준값은 배열의 중간정수값

	value = array[pivot];


	temp = array[pivot];//기준값을 맨 오른쪽으로 보냄
	array[pivot] = array[right];
	array[right] = temp;

	newpi = left;//왼쪽에 기준값보다 작은값을 넣어주기 위함
	for (int i = left; i <= (right - 1); i++)
	{
		if (array[i] <= value)
		{
			temp = array[i];
			array[i] = array[newpi];
			array[newpi] = temp;
			newpi = newpi + 1; //작은값이 들어갔을시 그다음칸으로 이동
		}
	}

	temp = array[newpi];//맨오른쪽으로 보냈던 기준값을 양옆을 나누는 기준 newpi값으로 이동
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



void select(int* array, int size) //선택정렬
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
		if (index != i) //i번째 값을 최소값으로 변경
		{
			array[index] = array[i];
			array[i] = min;
		}
	}
}

