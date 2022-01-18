/**
*파일명:“realnumberarithmetics.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 2개의 실수를 입력받아 두 실수값의 덧셈,뺄셈,곱셈,나눗셈을 구하는 프로그램입니다.
*
*프로그램 작성자: 21812160 차태현(2021년 3월12일),
*최종 수정 및 보완: 2021년 3월 12일 (차태현)
*/
#include <stdio.h>

int main()
{
	double x, y;

	printf("두 실수를 입력하시오:");
	scanf_s("%lf %lf", &x, &y);

	printf("%.2lf+%.2lf=%.2lf\n", x, y, x + y);

	printf("%.2lf-%.2lf=%.2lf\n", x, y, x - y);

	printf("%.2lf*%.2lf=%.2lf\n", x, y, x * y);

	printf("%.2lf/%.2lf=%.2lf\n", x, y, x / y);



	return 0;
}