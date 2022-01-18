#include<stdio.h>
#include<math.h>
#include"Cmplx.h"

void printCmplx(const Cmplx c)//���Ҽ� ���
{
	if (c.imag >= 0)
		printf("(%3.3lf +j%3.3lf(magnitude %3.3lf))", c.real, c.imag, c.magnitude);
	else
		printf("(%3.3lf -j%3.3lf(magnitude %3.3lf))", c.real, c.imag*-1, c.magnitude);
}

Cmplx cmplxAdd(const Cmplx c1, const Cmplx c2)//���Ҽ��� ����
{
	Cmplx c3;
	c3.real = c1.real + c2.real;//�Ǽ��κ� ����
	c3.imag = c1.imag + c2.imag;// ����κ� ����
	c3.magnitude = sqrt((c3.real * c3.real) + (c3.imag * c3.imag));

	return c3;
}

Cmplx complxSubtract(const Cmplx c1, const Cmplx c2)//���Ҽ��� ����
{
	Cmplx c3;
	c3.real = c1.real - c2.real;//�Ǽ��κ� ����
	c3.imag = c1.imag - c2.imag;//����κ� ����
	c3.magnitude = sqrt((c3.real * c3.real) + (c3.imag * c3.imag));
	
	return c3;
}

Cmplx complxMultiply(const Cmplx c1, const Cmplx c2)//���Ҽ��� ����
{
	Cmplx c3;
	c3.real = c1.real * c2.real - c1.imag * c2.imag;//(a + jb)(d + je) = (ad - be) + j(ae + bd)
	c3.imag = c1.real * c2.imag + c1.imag * c2.real;
	c3.magnitude = sqrt((c3.real * c3.real) + (c3.imag * c3.imag));

	return c3;
}

Cmplx cmplxDivide(const Cmplx c1, const Cmplx c2)//���Ҽ� ������
{
	Cmplx c3;
	c3.real = (c1.real * c2.real + c1.imag * c2.imag) / (c2.real * c2.real + c2.imag * c2.imag);//(a + jb) / (d + je) = (ad + be) / (d^2+e^2) + j (bd - ae) / (d^2+e^2)
	c3.imag= (c1.imag * c2.real - c1.real * c2.imag) / (c2.real * c2.real + c2.imag * c2.imag);
	c3.magnitude = sqrt((c3.real * c3.real) + (c3.imag * c3.imag));

	return c3;
}

Cmplx inputCmplx(void)
{
	Cmplx c;

	printf("Input complex number (rrr.ddd iii.ddd) : ");
	scanf("%lf %lf", &c.real, &c.imag);//���Ҽ��� �Ǽ� ��� �� �Է�
	c.magnitude = sqrt((c.real * c.real) + (c.imag * c.imag));

	return c;
}

double compareCmplx(const Cmplx c1, const Cmplx c2)
{
	if (c1.magnitude > c2.magnitude)//c1�� magnitude�� Ŭ��� 1
		return 1;
	else if (c1.magnitude < c2.magnitude)//c2�� magnitude�� Ŭ��� -1
		return -1;
	else//�������
		return 0;
}

void _quickSortCmplx(Cmplx cmplxs[], int size,int left,int right)
{
	int  newpi;
	int pivot = (left + right) / 2;
	Cmplx temp;

	temp = cmplxs[pivot];//���ذ��� �� ���������� ������
	cmplxs[pivot] = cmplxs[right];
	cmplxs[right] = temp;

	newpi = left;

	for (int i = left; i <= right - 1; i++)
	{
		if (compareCmplx(cmplxs[i], cmplxs[right]) < 0)//magnitude ���� �� ������� newpi��ġ ����ü�� i��ġ ����ü�� �ٲ�
		{
			temp = cmplxs[i];
			cmplxs[i] = cmplxs[newpi];
			cmplxs[newpi] = temp;
			newpi++;
		}
	}
	temp = cmplxs[newpi];//������ġ�� newpi ��ġ�� ����ü�� �ٲ�
	cmplxs[newpi] = cmplxs[right];
	cmplxs[right] = temp;

	if (left < newpi - 1)//���ʿ����� ����Լ� ����
	{
		_quickSortCmplx(cmplxs, size, left, newpi - 1);
	}
	if (newpi + 1 < right)//�����ʿ� ���� ����Լ�����
	{
		_quickSortCmplx(cmplxs, size, newpi + 1, right);
	}

}
void quickSortCmplx(Cmplx cmplxs[], int size)
{
	_quickSortCmplx(cmplxs, size, 0, size - 1);
}
