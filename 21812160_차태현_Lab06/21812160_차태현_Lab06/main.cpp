/**
*���ϸ�:�������İ� �������ġ�
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� �ſ� ū ũ���� �迭�� �������� ���� ���� �� �ɸ��ð��� �����ϴ� ���α׷��̴�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 4��6��),
*���� ���� �� ����: 2021�� 4�� 6�� (������)
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "array.h"//����� ���� ���

void compare(FILE* fout);
void bigrand(FILE* fout);
void hybird(FILE* fout);

int main()
{
    FILE* fout;
    int num;
    

    fout = fopen("output.txt", "w");//���� �б��������� ����

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

        fflush(fout); //������ ���� ����
    }
    fclose(fout);// ���ϴݱ�
    
    
    return 0;
}

void compare(FILE* fout) // �����İ� �������� �ð���
{
    LARGE_INTEGER freq, t1, t2,t3,t4;  
    long long t_diff,t_diff2;
    double elapsed_time,elapsed_time2;
    int* array;

    array = (int*)calloc(100, sizeof(int));
    

    QueryPerformanceFrequency(&freq); //cpu clock ���ļ� 
    
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

    QueryPerformanceFrequency(&freq); //cpu clock ���ļ� 
    
    for (int i = 1000000; i <= 10000000; i += 1000000)
    {
        array = (int*)calloc(i, sizeof(int));//�����迭 ����
       
        genBigRandArray(array, i,0);
        QueryPerformanceCounter(&t1);
        hyQuick(array, i,0,i-1);//�迭�� ���� ���� ���Ĺ�� ���� �� ����
        QueryPerformanceCounter(&t2);
        t_diff = t2.QuadPart - t1.QuadPart;
        elapsed_time = (double)t_diff / freq.QuadPart;
        printBigArraySample(array, i,10,2); //�����Լ��� ���ĵǾ��ִ��� Ȯ���Ͽ���.


        
        printf("hybird_QS_SS sorting of an iteger array(size:  %d): hybird_QS_SS sorting took %8.2lf[milli-seconds]\n", i, elapsed_time * 1000);
        fprintf(fout,"hybird_QS_SS sorting of an iteger array(size:  %d): hybird_QS_SS sorting took %8.2lf[milli-seconds]\n", i, elapsed_time * 1000);
    }

}