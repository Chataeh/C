#ifndef C_H
#define C_H

typedef struct //����ü ����
{
	double real;
	double imag;
	double magnitude;
}Cmplx;
void printCmplx(const Cmplx c);//����ü ���
Cmplx cmplxAdd(const Cmplx c1, const Cmplx c2);//���Ҽ� ����
Cmplx complxSubtract(const Cmplx c1, const Cmplx c2);//���Ҽ� ����
Cmplx complxMultiply(const Cmplx c1, const Cmplx c2);//���Ҽ� ����
Cmplx cmplxDivide(const Cmplx c1, const Cmplx c2);//���Ҽ� ������
Cmplx inputCmplx(void);//���Ҽ� �Է�
void quickSortCmplx(Cmplx cmplxs[], int size);//������

#endif // !C_H
