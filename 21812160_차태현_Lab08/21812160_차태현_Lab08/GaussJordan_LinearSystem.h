#ifndef G_H
#define G_H

void pivoting(double** augMtrx, int size_N, int p, int* piv_found);//���� ��ġ��ȯ
void diagonalize_FileOut(FILE* fout, double** mtrxAug, int size_N, int* solExist);//���콺 �ҰŹ�
void getAugmentedMtrx(FILE* fin,double**dM, int size_N);//������Ϸκ��� �޾ƿ���
void invMtrxGaussJordanElim_FileOut(FILE* fout, double** mA, double** inv_A, int size_N);//������� �̿��� ���콺�ҰŹ�

#endif // !G_H
