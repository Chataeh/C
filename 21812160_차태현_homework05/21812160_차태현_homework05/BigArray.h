#ifndef ARRAY_H  //������� �ߺ����Ÿ� ���� ��ó����
#define ARRAY_H

void genBigRandArray(int* array, int size);
void suffleBigArray(int* array, int size);
void printBigArraySample(int* array, int size, int line_size = 10, int sample_lines = 2);
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size = 10, int sample_lines = 2);



#endif // !ARRAY_H
