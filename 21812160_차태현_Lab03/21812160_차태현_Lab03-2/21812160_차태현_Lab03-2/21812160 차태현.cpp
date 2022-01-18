/**
*파일명:“행렬연산.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 초기화된 행렬에 관한 연산을실행하는 프로그램.
*
*프로그램 작성자: 21812160 차태현(2021년 3월17일),
*최종 수정 및 보완: 2021년 3월 18일 (차태현)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완 내용
*차태현               2021/03/18   ㄱ 표시하는게 한칸앞에 나오는 걸 수정
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
                printf("%c%c%7.2lf", a6, a3, A[i][j]); // 「 표시하기
            else if ((i == 0) && (j == size -1))
                printf("%7.2lf%c%c", A[i][j], a6, a4); //  ㄱ 표시하기 
            else if ((i > 0) && (i < size - 1) && (j == 0))
                printf("%c%c%7.2lf", a6, a2, A[i][j]); // ㅣ 표시하기  
            else if ((i > 0) && (i < size - 1) && (j == size - 1))
                printf("%7.2lf%c%c", A[i][j], a6, a2); // ㅣ 표시하기
            else if ((i == size - 1) && (j == 0))  
                printf("%c%c%7.2lf", a6, a6, A[i][j]); // ㄴ 표시하기
            else if ((i == size - 1) && (j == size - 1))
                printf("%7.2lf%c%c", A[i][j], a6, a5); // 」 표시하기
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