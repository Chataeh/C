/*Array.h �����Լ����� �����Լ����� ����ϱ����� �������*/
#ifndef ARRAY_H //������� �ߺ�����
#define ARRAY_H

#include <stdio.h>

void printBigArraySample(int* array, int size, int line_size, int num_sample_lines); //�ֿܼ� ���
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_sample_lines);//���Ͽ� ���
void genBigRandArray(int* array, int size);//ū ��������
void getArrayStatistics(int* array, int size);//������� ��� �� ȭ�鿡 ���
void fgetArrayStatistics(FILE* fout, int* array, int size);//���Ͽ� ����������
void selecttionsort(int* array, int size);

#endif