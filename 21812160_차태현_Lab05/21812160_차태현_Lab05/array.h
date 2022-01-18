/*Array.h 메인함수에서 다음함수들을 사용하기위한 헤더파일*/
#ifndef ARRAY_H //헤더파일 중복제거
#define ARRAY_H

#include <stdio.h>

void printBigArraySample(int* array, int size, int line_size, int num_sample_lines); //콘솔에 출력
void fprintBigArraySample(FILE* fout, int* array, int size, int line_size, int num_sample_lines);//파일에 출력
void genBigRandArray(int* array, int size);//큰 난수생성
void getArrayStatistics(int* array, int size);//통계정보 계산 후 화면에 출력
void fgetArrayStatistics(FILE* fout, int* array, int size);//파일에 통계정보계산
void selecttionsort(int* array, int size);

#endif