/**
*파일명:“퀵정렬과 선택정렬”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 매우 큰 크기의 배열을 퀵정렬을 통해 정렬 후 걸린시간을 측정하는 프로그램이다.
*
*프로그램 작성자: 21812160 차태현(2021년 4월6일),
*최종 수정 및 보완: 2021년 4월 6일 (차태현)
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "array.h"//사용자 정의 헤더

void compare(FILE* fout);
void bigrand(FILE* fout);
void hybird(FILE* fout);

int main()
{
    FILE* fout;
    int num;
    

    fout = fopen("output.txt", "w");//파일 읽기전용으로 열기

    while (1)
    {
        printf("\nTest Array Algorithms :\n");
        printf("    1:Performance Comparison of Selection Sort and Quick Sort fo Small Integer Array\n");
        printf("    2:Test Big Rand Array (Array Size:1,000,000~10,000,000)\n");
        printf("    3:Performance Measurements of hybird_QS_SS for Integer Array\n");
        printf("Input num(-1 to terminate):");
        scanf_s("%d", &num);
        printf("\n");

        if (num == -1)
            break;

        switch (num)
        {
        case 1:
            compare(fout);
            break;

        case 2:
            bigrand(fout);
            break;
        case 3:
            hybird(fout);
            break;
        default:
            break;
        }

        fflush(fout); //파일의 버퍼 비우기
    }
    fclose(fout);// 파일닫기
    
    
    return 0;
}

void compare(FILE* fout) // 퀵정렬과 선택정렬 시간비교
{
    LARGE_INTEGER freq, t1, t2,t3,t4;  
    long long t_diff,t_diff2;
    double elapsed_time,elapsed_time2;
    int* array;

    array = (int*)calloc(100, sizeof(int));
    

    QueryPerformanceFrequency(&freq); //cpu clock 주파수 
    
    for(int i=5; i<QUICK; i+=5) 
    {
        genBigRandArray(array, i, 0);
        QueryPerformanceCounter(&t1);
        Quick(array, i);
        QueryPerformanceCounter(&t2);
        t_diff = t2.QuadPart - t1.QuadPart;
        elapsed_time = (double)t_diff / freq.QuadPart;

        genBigRandArray(array, i, 0);
        QueryPerformanceCounter(&t3);
        select(array, i);
        QueryPerformanceCounter(&t4);
        t_diff2 = t4.QuadPart - t3.QuadPart;
        elapsed_time2 = (double)t_diff2 / freq.QuadPart;

        printf("Sortion of an iteger array (size:%8d): Quick_Sort took%8.2lf [micro-seconds],   Selection_Sort took%8.2lf[micro-seconds]\n", i, elapsed_time * 1000000, elapsed_time2 * 1000000);
       fprintf(fout,"Sortion of an iteger array (size:%8d): Quick_Sort took%8.2lf [micro-seconds],   Selection_Sort took%8.2lf[micro-seconds]\n", i, elapsed_time * 1000000, elapsed_time2 * 1000000);
    }

}

void bigrand(FILE* fout)
{
    int* array;
    
   
    printf("Testing Big integer Random arrays(size= 1,000,000~10,000,000):\n");
    fprintf(fout,"Testing Big integer Random arrays(size= 1,000,000~10,000,000):\n");

    for (int i = 1000000; i <= 10000000; i += 1000000)
    {
        array = (int*)calloc(i, sizeof(int));
        genBigRandArray(array, i, 0);
        printf("Generation Big integer array (size =%3d)....\n", i);
        fprintf(fout,"Generation Big integer array (size =%3d)....\n", i);
        printf("Generation Big integer array (size =%3d):\n", i);
        fprintf(fout,"Generation Big integer array (size =%3d):", i);
        printBigArraySample(array, i, 10, 2);
        fprintBigArraySample(fout,array, i, 10, 2);
     
        Quick(array, i);
        printf("Sorted Big Integer array (size= %3d):\n", i);
        fprintf(fout,"\nSorted Big Integer array (size= %3d):\n", i);
        printBigArraySample(array, i, 10, 2);
        fprintBigArraySample(fout,array, i, 10, 2);


    }
    
    
}

void hybird(FILE* fout)
{
    LARGE_INTEGER freq, t1, t2;
    long long t_diff;
    double elapsed_time;
    int* array;

    QueryPerformanceFrequency(&freq); //cpu clock 주파수 
    
    for (int i = 1000000; i <= 10000000; i += 1000000)
    {
        array = (int*)calloc(i, sizeof(int));//동적배열 생성
       
        genBigRandArray(array, i,0);
        QueryPerformanceCounter(&t1);
        hyQuick(array, i,0,i-1);//배열의 수의 따른 정렬방법 선택 후 정렬
        QueryPerformanceCounter(&t2);
        t_diff = t2.QuadPart - t1.QuadPart;
        elapsed_time = (double)t_diff / freq.QuadPart;
        printBigArraySample(array, i,10,2); //실제함수가 정렬되어있는지 확인하였음.


        
        printf("hybird_QS_SS sorting of an iteger array(size:  %d): hybird_QS_SS sorting took %8.2lf[milli-seconds]\n", i, elapsed_time * 1000);
        fprintf(fout,"hybird_QS_SS sorting of an iteger array(size:  %d): hybird_QS_SS sorting took %8.2lf[milli-seconds]\n", i, elapsed_time * 1000);
    }

}