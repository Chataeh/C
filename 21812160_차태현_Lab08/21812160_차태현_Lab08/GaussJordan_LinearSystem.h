#ifndef G_H
#define G_H

void pivoting(double** augMtrx, int size_N, int p, int* piv_found);//행의 위치변환
void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist);//가우스 소거법
void getAugmentedMtrx(FILE* fin,double**dM, int size_N);//행렬파일로부터 받아오기
void invMtrxGaussJordanElim_FileOut(FILE* fout, double** mA, double** inv_A, int size_N);//역행렬을 이용한 가우스소거법

#endif // !G_H
