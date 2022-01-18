/**
*�����̸�" �Լ��μ����޹�� ��
*���α׷��� ���� �� �⺻ ���:
*  �Լ��� �μ��� ���� ���� �޾ƿ� ��������ϴ����α׷�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 4��16��),
*���� ���� �� ����: 2021�� 4�� 16�� (������)
*/
#include <stdio.h>

double average_value(double x, double y);//�������� ȣ��
void average_pointer(double* px, double* py, double* pavg);//�����Ϳ����� ȣ��
void average_reference(double& px, double& py, double& pavg);//���������� ȣ��

int main()
{
	double x, y;
	double avg=0;

	scanf("%lf %lf", &x, &y);
	printf("call-by-value\n");
	avg=average_value(x, y);//�μ����� ����
	printf("avg=%.2lf\n", avg);
	
	
	scanf("%lf %lf", &x, &y);
	printf("\ncall-by-pointer\navg=");
	average_pointer(&x, &y, &avg);//�ּ����� ����
	printf("\n");

	scanf("%lf %lf", &x, &y);
	printf("\ncall-by-reference\navg=");
	average_reference(x, y, avg);//������ �ּ�����

}

double average_value(double x, double y)//�������� ȣ��
{
	double avg;
	avg = (x + y) / 2;
	
	return avg;
}

void average_pointer(double* px, double* py, double* pavg)//�����Ϳ� ���� ȣ��*��� �ּ����� ����
{

	*pavg = (*px + *py) / 2;

	printf("%.2lf", *pavg);
}
void average_reference(double& px, double& py, double& pavg)//���������� ȣ�� &���
{
	pavg = (px + py) / 2;

	printf("%.2lf", pavg);

}