#ifndef G_H
#define G_H

void fgetAugmentedMtrx(FILE* fin, double** dM, int size_N);//���Ϸκ��� ��İ� �޾ƿ���
void pivoting(double** augMtrx, int size_N, int p, int* piv);
void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist);//���콺 �ҰŹ�

#endif