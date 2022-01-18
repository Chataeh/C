#ifndef M_H
#define M_H

double** fGetMtrx_double(FILE* fin, int* row_size, int* col_size);//행렬 파일로부터 받아오기
void deleteMtrx(double** dM, int row_size, int col_size);//동적배열 반환
void printMtrx_double(double** dM, int row_size, int col_size);//행렬 출력
void fprintMtrx_double(FILE* fout, double** dM, int row_size, int col_size);//파일에 행렬출력
double** creat(int row_size, int col_size);//동적배열생성
double** addMtrx_double(double** A, double** B, int row_size, int col_size);//행렬의 합
double** subtractMtrx_double(double** A, double** B, int row_size, int col_size);//행렬을 차
double** multiplyMtrx_double(double** A, double** B, int row_size, int col_size, int bcol_size);//행렬의 곱


#endif // !M_H
