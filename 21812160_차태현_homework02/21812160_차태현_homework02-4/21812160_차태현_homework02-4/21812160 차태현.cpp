/**
*���ϸ�:��realnumberarithmetics.cpp��
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� 2���� �Ǽ��� �Է¹޾� �� �Ǽ����� ����,����,����,�������� ���ϴ� ���α׷��Դϴ�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 3��12��),
*���� ���� �� ����: 2021�� 3�� 12�� (������)
*/
#include <stdio.h>

int main()
{
	double x, y;

	printf("�� �Ǽ��� �Է��Ͻÿ�:");
	scanf_s("%lf %lf", &x, &y);

	printf("%.2lf+%.2lf=%.2lf\n", x, y, x + y);

	printf("%.2lf-%.2lf=%.2lf\n", x, y, x - y);

	printf("%.2lf*%.2lf=%.2lf\n", x, y, x * y);

	printf("%.2lf/%.2lf=%.2lf\n", x, y, x / y);



	return 0;
}