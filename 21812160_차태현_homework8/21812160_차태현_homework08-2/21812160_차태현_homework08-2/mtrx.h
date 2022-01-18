#ifndef M_H
#define M_H

void printMtrx(double** dM, int row_size, int col_size);//행렬출력
void mutiplyMtrx(double** mA, double** mB, double** mR, int arow_size, int acol_size, int bcol_size);//행렬의 곱void inverseMtrx(double** mA, double** invA, int size_N);
double** creat(int row_size, int col_size);//동적메모리생성
void deleteMtrx(double** dM, int row_size, int col_size);//동적메모리 반환
void fprintMtrx(FILE* fout, double** dM, int row_size, int col_size);//파일에 행렬출력
void inverseMtrx(double** mA, double** invA, int size_N);//역행렬 구하기
#endif // !M_H
