#ifndef Mtrx_H
#define MTrx_H

double** createDoubleMtrx(int row_size, int col_size);
void checkAddr_2D_Array(double** dM, int row_size, int col_size);
double** fgetDoubleMtrx(FILE* fin, int row_size, int col_size);
void deleteDoubleMtrx(double** dM, int row_size, int col_size);
void printMtrx(double** dM, int size_row, int size_col);
void addMtrx(double** mA, double** mB, double** mR, int row_size, int col_size);
void subMtrx(double** mA, double** mB, double** mR, int row_size, int col_size);
void mutiplyMtrx(double** mA, double** mB, double** mR, int row_size, int col_size, int col_size2);

#endif Mtrx_H