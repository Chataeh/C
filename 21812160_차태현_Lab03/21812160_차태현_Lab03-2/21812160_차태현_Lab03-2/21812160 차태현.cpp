/**
*���ϸ�:����Ŀ���.cpp��
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� �ʱ�ȭ�� ��Ŀ� ���� �����������ϴ� ���α׷�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 3��17��),
*���� ���� �� ����: 2021�� 3�� 18�� (������)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���� ����
*������               2021/03/18   �� ǥ���ϴ°� ��ĭ�տ� ������ �� ����
*============================================================================
*/
#include <stdio.h>

#define size 5
void printMtrx(double A[size][size], int extend)
{
    unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
    unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if ((i == 0) && (j == 0))
                printf("%c%c%7.2lf", a6, a3, A[i][j]); // �� ǥ���ϱ�
            else if ((i == 0) && (j == size -1))
                printf("%7.2lf%c%c", A[i][j], a6, a4); //  �� ǥ���ϱ� 
            else if ((i > 0) && (i < size - 1) && (j == 0))
                printf("%c%c%7.2lf", a6, a2, A[i][j]); // �� ǥ���ϱ�  
            else if ((i > 0) && (i < size - 1) && (j == size - 1))
                printf("%7.2lf%c%c", A[i][j], a6, a2); // �� ǥ���ϱ�
            else if ((i == size - 1) && (j == 0))  
                printf("%c%c%7.2lf", a6, a6, A[i][j]); // �� ǥ���ϱ�
            else if ((i == size - 1) && (j == size - 1))
                printf("%7.2lf%c%c", A[i][j], a6, a5); // �� ǥ���ϱ�
            else
                printf("%7.2lf", A[i][j]);

        }

    printf("\n");
}
}
void addmtrx(double A[size][size], double B[size][size], double C[size][size])
{
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtractMtrx(double A[size][size], double B[size][size], double D[size][size])
{
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            D[i][j] = A[i][j] - B[i][j];
}

void multiplyMtrx(double A[size][size], double B[size][size], double E[size][size])
{
    int i, j,k;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
        {
            E[i][j] = 0;
            for (k = 0; k < size; k++)
                E[i][j] += A[i][k] * B[k][j];
        }
}

int main()
{
    double A[size][size] = { {5.00,4.00,3.00,2.00,1.00},
        {6.00,7.00,8.00,9.00,10.00},{11.00,12.00,13.00,14.00,15.00},
        {16.00,17.00,18.00,19.00,20.00},{21.00,22.00,23.00,24.00,25.00}
    };

    double B[size][size] = { {1.00,0.00,0.00,0.00,0.00},
        {0.00,1.00,0.00,0.00,0.00},{0.00,0.00,1.00,0.00,0.00},
        {0.00,0.00,0.00,1.00,0.00},{0.00,0.00,0.00,0.00,1.00}
    };
    double C[size][size];
    double D[size][size];
    double E[size][size];
   
    printf("Matrix A:\n");
    printMtrx(A, size);
    

    printf("Matrix B:\n");
    printMtrx(B, size);
   

    addmtrx(A, B, C);
    printf("Matrix C= A + B:\n");
    printMtrx(C, size);
   
    
    subtractMtrx(A, B, D);
    printf("Matrix D= A - B:\n");
    printMtrx(D, size);
    
    multiplyMtrx(A, B, E);
    printf("Matrix E= A * B:\n");
    printMtrx(E, size);
    
    return 0;
}