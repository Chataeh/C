#ifndef C_H
#define C_H

typedef struct //±¸Á¶Ã¼ Á¤ÀÇ
{
	double real;
	double imag;
	double magnitude;
}Cmplx;
void printCmplx(const Cmplx c);//±¸Á¶Ã¼ Ãâ·Â
Cmplx cmplxAdd(const Cmplx c1, const Cmplx c2);//º¹¼Ò¼ö µ¡¼À
Cmplx complxSubtract(const Cmplx c1, const Cmplx c2);//º¹¼Ò¼ö »¬¼À
Cmplx complxMultiply(const Cmplx c1, const Cmplx c2);//º¹¼Ò¼ö °ö¼À
Cmplx cmplxDivide(const Cmplx c1, const Cmplx c2);//º¹¼Ò¼ö ³ª´°¼À
Cmplx inputCmplx(void);//º¹¼Ò¼ö ÀÔ·Â
void quickSortCmplx(Cmplx cmplxs[], int size);//ÄüÁ¤·Ä

#endif // !C_H
