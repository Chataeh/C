/**
*���ϸ�:���ŵ��������ϱ�.cpp��
*���α׷��� ���� �� �⺻ ���:
* -�� ���α׷��� �ŵ������� ���� ���ϱ� ���� ���Ǵµ� ���� �ɸ��½ð��� ��û�ϴ� ���α׷��Դϴ�.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 3��26��),
*���� ���� �� ����: 2021�� 3�� 26�� (������)

*/
#include <stdio.h>
#include <time.h>
#include <Windows.h>

double powerIter(double base, int exponet)
{
	int i;
	double a = base;
	for (i = 2; i <= exponet; i++)
		base =base*a;

	return base;
}
double powerRecur(double base, int exponent)
{
	
	if (exponent == 0)
		return 1;
	else
		return base * powerRecur(base, exponent - 1);
}

int main()
{
	double base = 1.015;
	int exponent;
	double result_i = 0;
	double result_r = 0;

	time_t t_before, t_after;
	int t_diff;// time�� ����� �ð� ��
	long long t_diff_pc; //QueryPerformanceCounter�� ����� �ð���
	LARGE_INTEGER freq,t1, t2;//QueryPerformanceCounter ������ϱ����� ��������
	
	double t_elapse_ms;
	QueryPerformanceFrequency(&freq);
	for (exponent = 1000; exponent <= 4000; exponent += 1000)
	{
		time(&t_before);
		QueryPerformanceCounter(&t1);
		result_i = powerIter(base, exponent);
		QueryPerformanceCounter(&t2);
		time(&t_after);
		t_diff = difftime(t_after, t_before);
		t_diff_pc = t2.QuadPart - t1.QuadPart;
		t_elapse_ms = ((double)t_diff_pc /(double)freq.QuadPart) * 1000;// 1ms�� ��Ȯ�������� ���
		printf("PowerRecur(1.015,%d)by recursive=%40.5lf,took(%3d)sec,(%10.2lf)milli-second\n", exponent, result_i, t_diff, t_elapse_ms);


		time(&t_before);
		QueryPerformanceCounter(&t1);
		result_r = powerRecur(base, exponent);
		QueryPerformanceCounter(&t2);
		time(&t_after);
		t_diff = difftime(t_after, t_before);
		t_diff_pc = t2.QuadPart - t1.QuadPart;
		t_elapse_ms = ((double)t_diff_pc / (double)freq.QuadPart) * 1000;// 1ms�� ��Ȯ�������� ���
		printf("PowerRecur(1.015,%d)by recursive=%40.5lf,took(%3d)sec,(%10.2lf)milli-second\n", exponent, result_r, t_diff, t_elapse_ms);

	}
	
	return 0;
}