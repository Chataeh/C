#ifndef Array_H
#define Array_H
#define QUICK 60

void genBigRandArray(int* array, int size, int offset); //큰 수의 난수 생성
void printBigArraySample(int* array, int size, int line_size, int sample_lines);//배열 출력
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int sample_lines);//파일에 배열출력
void hyQuick(int* array, int size,int left,int right);//배열수에따른 퀵정렬또는 선택정렬
void _quick(int* array, int size, int left, int right);
void select(int* array, int size);//선택정렬
void Quick(int* array, int size);// 퀵정렬


#endif