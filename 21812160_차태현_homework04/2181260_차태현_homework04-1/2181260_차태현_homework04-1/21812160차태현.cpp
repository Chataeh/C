/**
*파일명:“32767보다 더큰 난수의 생성.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 32767이상의 난수를  출력하는프로그램입니다.
*
*프로그램 작성자: 21812160 차태현(2021년 3월26일),
*최종 수정 및 보완: 2021년 3월 26일 (차태현)
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LINE_SIZE 10

void genBigRandArray(int mA[], int size)
{
	char* flag;
	unsigned long uint_32,bigRand;
	int count = 0;

	srand(time(0));

	flag = (char*)malloc(sizeof(char) * size);

	while (count < size)
	{
		uint_32 = ((unsigned long)rand() << 15) | rand();
		bigRand = uint_32 % size;

		if (flag[bigRand] == 1)
			continue;
		else
		{
			flag[bigRand] = 1;
			mA[count++] = bigRand;
		}
	}
	
}

void printArraySample(int mA[], int size, int line_size)
{
	int i;

	for (i = 0; i < 30; i++)
	{
		printf("%8d", mA[i]);
		if ((i == 9) || (i == 19) || (i == 29))
			printf("\n");
	}
	for (i = size; i < size-30; i--)
	{
		printf("%8d", mA[i]);
		if ((i == size-9) || (i == size-19) || (i == size-29))
			printf("\n");
	}
	
}
int main()
{
	
	int* array;
	
	for (int size = 200000; size <= 1000000; size += 200000)
	{
		printf("Testing generation of dynamic array of random numbers (size:%d)\n", size);
		array = (int*)calloc(size, sizeof(int));
	    
		if (array == NULL)//동적할당 실패시 
		{
			printf("Error in dynamic memory allocation for integer array of size(%d)\n");
			exit(-1);
		}
	
		genBigRandArray(array, size);
		printArraySample(array, size, LINE_SIZE);
	}


	return 0;
}