#ifndef M_H
#define M_H

double** fGetMtrx_double(FILE* fin, int* row_size, int* col_size);//��� ���Ϸκ��� �޾ƿ���
void deleteMtrx(double** dM, int row_size, int col_size);//�����迭 ��ȯ
void printMtrx_double(double** dM, int row_size, int col_size);//��� ���
void fprintMtrx_double(FILE* fout, double** dM, int row_size, int col_size);//���Ͽ� ������
double** creat(int row_size, int col_size);//�����迭����
double** addMtrx_double(double** A, double** B, int row_size, int col_size);//����� ��
double** subtractMtrx_double(double** A, double** B, int row_size, int col_size);//����� ��
double** multiplyMtrx_double(double** A, double** B, int row_size, int col_size, int bcol_size);//����� ��


#endif // !M_H
