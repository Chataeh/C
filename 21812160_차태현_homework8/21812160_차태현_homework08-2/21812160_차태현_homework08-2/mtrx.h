#ifndef M_H
#define M_H

void printMtrx(double** dM, int row_size, int col_size);//������
void mutiplyMtrx(double** mA, double** mB, double** mR, int arow_size, int acol_size, int bcol_size);//����� ��void inverseMtrx(double** mA, double** invA, int size_N);
double** creat(int row_size, int col_size);//�����޸𸮻���
void deleteMtrx(double** dM, int row_size, int col_size);//�����޸� ��ȯ
void fprintMtrx(FILE* fout, double** dM, int row_size, int col_size);//���Ͽ� ������
void inverseMtrx(double** mA, double** invA, int size_N);//����� ���ϱ�
#endif // !M_H
