#ifndef M_H
#define M_H

double** fGetMtrx(FILE* fin, int* row_size, int* col_size);
void printMtrx(double** dM, int row_size, int col_size);
void addMtrx(double** mA, double** mB, double** mR, int row_size, int col_size);
void subMtrx(double** mA, double** mB, double** mR, int row_size, int col_size);
void mutiplyMtrx(double** mA, double** mB, double** mR, int arow_size, int acol_size, int bcol_size);
void inverseMtrx(double** mA, double** invA, int size_N);
double** creat(int row_size, int col_size);
void deleteMtrx(double** dM, int row_size, int col_size);
void fprintMtrx(FILE* fout, double** dM, int row_size, int col_size);

#endif // !M_H
