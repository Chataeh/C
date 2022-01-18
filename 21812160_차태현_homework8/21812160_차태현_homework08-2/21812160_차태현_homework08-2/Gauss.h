#ifndef G_H
#define G_H

void fgetAugmentedMtrx(FILE* fin, double** dM, int size_N);//파일로부터 행렬값 받아오기
void pivoting(double** augMtrx, int size_N, int p, int* piv);
void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist);//가우스 소거법

#endif