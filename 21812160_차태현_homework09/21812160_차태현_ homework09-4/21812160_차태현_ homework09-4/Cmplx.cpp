#include<stdio.h>
#include<math.h>
#include"Cmplx.h"

void printCmplx(const Cmplx c)//복소수 출력
{
	if (c.imag >= 0)
		printf("(%3.3lf +j%3.3lf(magnitude %3.3lf))", c.real, c.imag, c.magnitude);
	else
		printf("(%3.3lf -j%3.3lf(magnitude %3.3lf))", c.real, c.imag*-1, c.magnitude);
}

Cmplx cmplxAdd(const Cmplx c1, const Cmplx c2)//복소수의 덧셈
{
	Cmplx c3;
	c3.real = c1.real + c2.real;//실수부분 덧셈
	c3.imag = c1.imag + c2.imag;// 허수부분 덧셈
	c3.magnitude = sqrt((c3.real * c3.real) + (c3.imag * c3.imag));

	return c3;
}

Cmplx complxSubtract(const Cmplx c1, const Cmplx c2)//복소수의 뺄셈
{
	Cmplx c3;
	c3.real = c1.real - c2.real;//실수부분 덧셈
	c3.imag = c1.imag - c2.imag;//허수부분 뺄셈
	c3.magnitude = sqrt((c3.real * c3.real) + (c3.imag * c3.imag));
	
	return c3;
}

Cmplx complxMultiply(const Cmplx c1, const Cmplx c2)//복소수의 곱셈
{
	Cmplx c3;
	c3.real = c1.real * c2.real - c1.imag * c2.imag;//(a + jb)(d + je) = (ad - be) + j(ae + bd)
	c3.imag = c1.real * c2.imag + c1.imag * c2.real;
	c3.magnitude = sqrt((c3.real * c3.real) + (c3.imag * c3.imag));

	return c3;
}

Cmplx cmplxDivide(const Cmplx c1, const Cmplx c2)//복소수 나눗셈
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
	scanf("%lf %lf", &c.real, &c.imag);//복소수의 실수 허수 값 입력
	c.magnitude = sqrt((c.real * c.real) + (c.imag * c.imag));

	return c;
}

double compareCmplx(const Cmplx c1, const Cmplx c2)
{
	if (c1.magnitude > c2.magnitude)//c1의 magnitude가 클경우 1
		return 1;
	else if (c1.magnitude < c2.magnitude)//c2의 magnitude가 클경우 -1
		return -1;
	else//같을경우
		return 0;
}

void _quickSortCmplx(Cmplx cmplxs[], int size,int left,int right)
{
	int  newpi;
	int pivot = (left + right) / 2;
	Cmplx temp;

	temp = cmplxs[pivot];//기준값을 맨 오른쪽으로 보내줌
	cmplxs[pivot] = cmplxs[right];
	cmplxs[right] = temp;

	newpi = left;

	for (int i = left; i <= right - 1; i++)
	{
		if (compareCmplx(cmplxs[i], cmplxs[right]) < 0)//magnitude 값이 더 작을경우 newpi위치 구조체와 i위치 구조체를 바꿈
		{
			temp = cmplxs[i];
			cmplxs[i] = cmplxs[newpi];
			cmplxs[newpi] = temp;
			newpi++;
		}
	}
	temp = cmplxs[newpi];//기준위치와 newpi 위치의 구조체를 바꿈
	cmplxs[newpi] = cmplxs[right];
	cmplxs[right] = temp;

	if (left < newpi - 1)//왼쪽에대해 재귀함수 실행
	{
		_quickSortCmplx(cmplxs, size, left, newpi - 1);
	}
	if (newpi + 1 < right)//오른쪽에 대해 재귀함수실행
	{
		_quickSortCmplx(cmplxs, size, newpi + 1, right);
	}

}
void quickSortCmplx(Cmplx cmplxs[], int size)
{
	_quickSortCmplx(cmplxs, size, 0, size - 1);
}
