#ifndef Array_H
#define Array_H
#define QUICK 60

void genBigRandArray(int* array, int size, int offset); //ū ���� ���� ����
void printBigArraySample(int* array, int size, int line_size, int sample_lines);//�迭 ���
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int sample_lines);//���Ͽ� �迭���
void hyQuick(int* array, int size,int left,int right);//�迭�������� �����ĶǴ� ��������
void _quick(int* array, int size, int left, int right);
void select(int* array, int size);//��������
void Quick(int* array, int size);// ������


#endif