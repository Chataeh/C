/**
*���ϸ�:�����߼ҽ����ϡ�
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� �ҽ������� ������ �����ϰ� ����������� ����ϸ� ��������� ����Ͽ� �迭�� ��������� ���ϴ� ���α׷��̴�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 3��30��),
*���� ���� �� ����: 2021�� 3�� 30�� (������)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���� ����
*������               2021/03/30   �ܼ�â���� ��µǰ� �ؽ�Ʈ���Ͽ� ��µ����ʴ� ���� ����
*============================================================================
*/
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Array.h"// ����� ���� ����Լ�



void arrayStatistics_basicArray(FILE* fout);
void arrayStatistics_externArray(FILE* fout);
void arrayStatistics_fileDataArray(FILE* fout);
void arrayStatistics_inputArray(FILE* fout);
void arrayStatistics_genBigRandArray(FILE* fout);

#define Data_Input_File "Data_input.txt" //������ ����
#define Data_Output_File "Data_output.txt"//�ۼ��� ����
#define MAX_NUM_DATA 100


int main()
{
	FILE* fout;
	char menu;
	fout = fopen(Data_Output_File, "w"); //������� ���Ͽ���

	if (fout == NULL)//������ ����� ������ ������
	{
		printf("Error in creation of %s!!\n", Data_Output_File);
		return -1;
	}

	while (1)
	{
		printf("\nTest Array Handling(1:data_array; 2:extern_array; 3:data_file; 4:data_input; 5:genBigRandArray; Esc:terminate):");
		menu = _getche();//�Է°��� ��������
		if (menu == 27)//ESC�Է½� ����
			break;
		switch (menu) //��ȣ�� ���� ������ �Լ� ����
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
	fclose(fout);//���� �ݱ�
	return 0;
}
void arrayStatistics_basicArray(FILE* fout) //���ǵ� �迭 ��� �� ����������
{
	int num_data = 10;
	int data_array[MAX_NUM_DATA] = { 11,12,13,14,15,16,17,18,19,20 };

	printf("\nArrayStatistics_basicArray .....\n");
	fprintf(fout, "\nArrayStatistics_basicArray .....\n");
	printf("Total(10) integer data:\n");
	fprintf(fout, "Total(10) integer data:\n");
	for (int i = 0; i < num_data; i++)
	{
		printf("%8d", data_array[i]);//�ܼ�â�� ���
		fprintf(fout, "%8d", data_array[i]);//���Ͽ� ���
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

	extern int data_array[MAX_NUM_DATA]; //�ٸ� �ҽ������� ������ �޾ƿ�
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

void arrayStatistics_fileDataArray(FILE* fout) // Data_input���� ������ �о��
{
	FILE* Fin;
	int data, num_data = 0;
	int data_array[MAX_NUM_DATA] = { 0 };

	printf("\nArrayStatistics_fileDataArray .....\n");
	fprintf(fout, "\nArrayStatistics_fileDataArray .....\n");

	Fin = fopen("Data_input.txt", "r");//���Ͽ���
	if (Fin == NULL)//������ ����� ������ �ʾ����� ����
	{
		printf("Error in opening input data file !!\n");
		return;
	}
	while (fscanf_s(Fin, "%d", &data) != EOF)
	{
		if (data == -1)// data ���� -1�Ͻ� ����
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
	fclose(Fin);//���ϴݱ�
	printf("\n");
	fprintf(fout, "\n");

	getArrayStatistics(data_array, num_data);
	fgetArrayStatistics(fout, data_array, num_data);
	printf("arrayStatistics_fileDataArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);

}

void arrayStatistics_inputArray(FILE* fout)//�迭�� �Է��� �׿����� ����������
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
	array = (int*)calloc(size, sizeof(int));//�����迭 ����
	printf("\n");
	fprintf(fout,"\n");
	
	genBigRandArray(array, size);
	selecttionsort(array,size);
	printBigArraySample(array, size, 10, 2);
	fprintBigArraySample(fout, array, size, 10, 2);
	
	
	getArrayStatistics(array, size);
	fgetArrayStatistics(fout, array, size);

	free(array);//�����迭��ȯ
	printf("arrayStatistics_genBigRandArray - completed. Result is also stored in output file(%s).\n", Data_Output_File);

}