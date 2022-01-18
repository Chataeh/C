/**
*파일명:“다중소스파일”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 소스파일을 여러개 생성하고 파일입출력을 사용하며 헤더파일을 사용하여 배열의 통계정보를 구하는 프로그램이다.
*
*프로그램 작성자: 21812160 차태현(2021년 3월30일),
*최종 수정 및 보완: 2021년 3월 30일 (차태현)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완 내용
*차태현               2021/03/30   콘솔창에만 출력되고 텍스트파일에 출력되지않는 오류 수정
*============================================================================
*/
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Array.h"// 사용자 정의 헤더함수



void arrayStatistics_basicArray(FILE* fout);
void arrayStatistics_externArray(FILE* fout);
void arrayStatistics_fileDataArray(FILE* fout);
void arrayStatistics_inputArray(FILE* fout);
void arrayStatistics_genBigRandArray(FILE* fout);

#define Data_Input_File "Data_input.txt" //가져올 파일
#define Data_Output_File "Data_output.txt"//작성할 파일
#define MAX_NUM_DATA 100


int main()
{
	FILE* fout;
	char menu;
	fout = fopen(Data_Output_File, "w"); //쓰기모드로 파일열기

	if (fout == NULL)//파일이 제대로 열리지 않을시
	{
		printf("Error in creation of %s!!\n", Data_Output_File);
		return -1;
	}

	while (1)
	{
		printf("\nTest Array Handling(1:data_array; 2:extern_array; 3:data_file; 4:data_input; 5:genBigRandArray; Esc:terminate):");
		menu = _getche();//입력값을 에코해줌
		if (menu == 27)//ESC입력시 종료
			break;
		switch (menu) //번호에 따라 실행할 함수 지정
		{
		case'1':
			arrayStatistics_basicArray(fout);
			break;
		case'2':
			arrayStatistics_externArray(fout);
			break;
		case'3':
			arrayStatistics_fileDataArray(fout);
			break;
		case'4':
			arrayStatistics_inputArray(fout);
			break;
		case'5':
			arrayStatistics_genBigRandArray(fout);
			break;
		default:
			break;
		}
	}
	fclose(fout);//파일 닫기
	return 0;
}
void arrayStatistics_basicArray(FILE* fout) //정의된 배열 출력 후 통계정보계산
{
	int num_data = 10;
	int data_array[MAX_NUM_DATA] = { 11,12,13,14,15,16,17,18,19,20 };

	printf("\nArrayStatistics_basicArray .....\n");
	fprintf(fout, "\nArrayStatistics_basicArray .....\n");
	printf("Total(10) integer data:\n");
	fprintf(fout, "Total(10) integer data:\n");
	for (int i = 0; i < num_data; i++)
	{
		printf("%8d", data_array[i]);//콘솔창에 출력
		fprintf(fout, "%8d", data_array[i]);//파일에 출력
	}
	printf("\n\n");
	fprintf(fout, "\n\n");
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("arrayStatistics_basicArray-completed. Result is also stored in output file(%s).\n", Data_Output_File);
}

void arrayStatistics_externArray(FILE* fout)
{
	int num_data = 0;

	printf("\nArrayStatistics_externArray .....\n");
	fprintf(fout, "\nArrayStatistics_externArray .....\n");

	extern int data_array[MAX_NUM_DATA]; //다른 소스파일의 데이터 받아옴
	printf("Total(35) integer data:\n");
	fprintf(fout, "Total(35) integer data:\n");
	for (int i = 0; i < MAX_NUM_DATA; i++)
	{

		if (data_array[i] == -1)
			break;
		else
			num_data++;
		if ((i % 10 == 0) || (i % 20 == 0))
			printf("\n");
		printf("%8d", data_array[i]);
		fprintf(fout, "%8d", data_array[i]);
	}
	printf("\n");
	fprintf(fout, "\n");
	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("arrayStatistics_basicArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);
}

void arrayStatistics_fileDataArray(FILE* fout) // Data_input에서 파일을 읽어옴
{
	FILE* Fin;
	int data, num_data = 0;
	int data_array[MAX_NUM_DATA] = { 0 };

	printf("\nArrayStatistics_fileDataArray .....\n");
	fprintf(fout, "\nArrayStatistics_fileDataArray .....\n");

	Fin = fopen("Data_input.txt", "r");//파일열기
	if (Fin == NULL)//파일이 제대로 열리지 않았을시 실행
	{
		printf("Error in opening input data file !!\n");
		return;
	}
	while (fscanf_s(Fin, "%d", &data) != EOF)
	{
		if (data == -1)// data 값이 -1일시 정지
			break;
		data_array[num_data] = data;
		num_data++;
	}
	printf("Total(%d) integer data:\n", num_data);
	fprintf(fout, "Total(%d) integer data:\n", num_data);
	for (int i = 0; i < num_data; i++)
	{
		if (i % 10 == 0)
			printf("\n");
		printf("%8d", data_array[i]);
		if (i % 10 == 0)
			fprintf(fout, "\n");
		fprintf(fout, "%8d", data_array[i]);
	}
	fclose(Fin);//파일닫기
	printf("\n");
	fprintf(fout, "\n");

	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("arrayStatistics_fileDataArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);

}

void arrayStatistics_inputArray(FILE* fout)//배열값 입력후 그에따른 통계정보계산
{
	int num, data;
	int data_array[MAX_NUM_DATA] = { 0 };
	printf("\nArrayStatistics_inputArray .....\n");
	fprintf(fout, "\nArrayStatistics_inputArray .....\n");
	printf("Please input the number of integers (less than %d) = ", MAX_NUM_DATA);
	scanf_s("%d", &num);
	printf("Input %d integer data : ", num);
	for (int i = 0; i < num; i++)
	{
		scanf_s("%d", &data);
		data_array[i] = data;
		

	}
	printf("Total(%d) integer data:\n", num);
	fprintf(fout, "Total(%d) integer data:\n", num);
	
	for (int i = 0; i < num; i++)
	{
		printf("%8d", data_array[i]);
		fprintf(fout, "%8d", data_array[i]);
		
	}
	printf("\n");
	fprintf(fout, "\n");

	getArrayStatistics(data_array, num);
	fgetArrayStatistics(fout, data_array, num);
	printf("arrayStatistics_inputArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);
}

void arrayStatistics_genBigRandArray(FILE* fout)
{
	int* array;
	int size;
	printf("\n ArrayStatistics_genBigRandArray .....\n");
	fprintf(fout, "\n ArrayStatistics_genBigRandArray .....\n");
	printf("Size of big array(bigger than 50000)=");
	scanf_s("%d", &size);
	printf("Creating big random Integer array(size:%d)\n", size);
	printf("Total(%d) integer data", size);
	fprintf(fout, "Total(%d) integer data", size);
	array = (int*)calloc(size, sizeof(int));//동적배열 생성
	printf("\n");
	fprintf(fout,"\n");
	
	genBigRandArray(array, size);
	selecttionsort(array,size);
	printBigArraySample(array, size, 10, 2);
	fprintBigArraySample(fout, array, size, 10, 2);
	
	
	getArrayStatistics(array, size);
	fgetArrayStatistics(fout, array, size);

	free(array);//동적배열반환
	printf("arrayStatistics_genBigRandArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);

}