/**
*���ϸ�:���߼ҽ�����
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� ��������� ����� ���߼ҽ������� �����ϰ� ȭ��Ӹ��ƴ϶� ���Ͽ��� ����ϴ� ���α׷�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 4��2��),
*���� ���� �� ����: 2021�� 4�� 2�� (������)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BigArray.h"//����� �������


int main()
{
	FILE* fout;
	int* array;
	int size;//�Է¹��� �迭�� ũ��

	fout = fopen("out.txt", "w");//���� ������������ ���� out.txt�� ����� ����
	printf("Input size of big array(more than 100000)=");
	
	scanf_s("%d", &size);
	fprintf(fout, "Input size of big array(more than 100000)=%d\n",size);
	
	array = (int*)calloc(sizeof(int), size);//array �迭�� ũ��Ȯ���� ���� �����迭 ����
	genBigRandArray(array, size);//���� �����Լ�
	printBigArraySample(array, size);//�迭����Լ�
	fprintBigArraySample(fout,array, size);//���Ͽ� �迭���

	fclose(fout);//���ϴݱ�
	free(array);//�����迭��ȯ

	return 0;
}