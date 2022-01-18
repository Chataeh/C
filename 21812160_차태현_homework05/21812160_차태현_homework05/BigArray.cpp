#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void genBigRandArray(int* array, int size)//큰난수 생성 함수
{
	char* repeat;
	unsigned int big;
	unsigned int uint = 0;
	int num = 0;

	repeat = (char*)calloc(size, sizeof(char));//중복방지를위한 동적배열 생성

	srand(time(0));
	while (num < size)
	{
		uint = (rand() << 15) | rand();//30비트 난수
		big = uint % size; //size-1의 난수

		if (repeat[big] == 1) //중복을 제거하기위해 값을 확인
			continue;
		else
		{
			repeat[big] = 1;//중복 제거를 위한 이미나온 수의 값 정의
			array[num++] = big;
		}

	}
}
void suffleBigArray(int* array, int size)//두 배열의 값의 위치를 변환
{
	int temp,a,b;//temp는 위치를 변환하기 위하여 필요한 버퍼
	srand(time(0));
	for(int i=0;i<size;i++)
		
	{
		a = (((unsigned long)rand() << 15) | rand())% size; // 두개의난수 생성
		b = (((unsigned long)rand() << 15) | rand())% size;


		temp = array[a];
		array[a] = array[b];	
		array[b] = temp;
	}


}
void printBigArraySample(int* array, int size, int line_size = 10, int sample_lines = 2)//배열을 화면으로 출력
{
	int num=0;
	if (size > 50)//배열의 크기가 50초과일시 처음과 끝 두줄씩 출력
	{
		for (int i = 0; i < line_size * sample_lines; i++)
		{
			printf("%8d", array[num]);
			num++;
			if (num % 10 == 0)
				printf("\n");
			
		}
		num = size - line_size * sample_lines; 
		printf("\n....\n");//첫줄 두줄과 끝줄 두줄사이 경계표시
		for (int j = num; j < size; j++)
		{
			printf("%8d", array[num]);
			num++;
			if (num % 10 == 0)
				printf("\n");
			
		}
		printf("\n");
	}
	


	else//배열의 크기가 50이하일시 한줄에 10개의 배열 출력
	{
		for (int i = 0; i < size; i++)
		{
			if (i %10  == 0)
				printf("\n");
			printf("%8d", array[i]);
		}
	}
	
}
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size = 10, int sample_lines = 2)//주어진 배열을 파일에 출력
{
	int num = 0;
	if (size > 50)//배열의 크기가 50초과일시 처음과 끝 두줄씩 출력
	{
		for (int i = 0; i < line_size * sample_lines; i++)
		{
			fprintf(fout,"%8d", array[num]);
			num++;
			if(num % 10 == 0)
				fprintf(fout,"\n");
			
		}
		num = size - line_size * sample_lines;
		fprintf(fout,"\n....\n");//첫줄 두줄과 끝줄 두줄사이 경계표시
		for (int j = num; j < size; j++)
		{
			fprintf(fout,"%8d", array[num]);
			num++;
			if (num % 10 == 0)
				fprintf(fout,"\n");
			
		}
		fprintf(fout, "\n");
	}



	else//배열의 크기가 50이하일시 한줄에 10개의 배열 출력
	{
		for (int i = 0; i < size; i++)
		{
			
			if (i % 10 == 0)
				fprintf(fout,"\n");

			fprintf(fout, "%d", array[i]);
		}
	}
}

