/**
*파일명:“거듭제곱구하기.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 거듭제곱의 값을 구하기 식이 계산되는데 까지 걸리는시간을 측청하는 프로그램입니다.
*
*프로그램 작성자: 21812160 차태현(2021년 3월26일),
*최종 수정 및 보완: 2021년 3월 26일 (차태현)

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
	int t_diff;// time을 사용한 시간 차
	long long t_diff_pc; //QueryPerformanceCounter를 사용한 시간차
	LARGE_INTEGER freq,t1, t2;//QueryPerformanceCounter 를사용하기위한 지역변수
	
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
		t_elapse_ms = ((double)t_diff_pc /(double)freq.QuadPart) * 1000;// 1ms의 정확도까지의 계산
		printf("PowerRecur(1.015,%d)by recursive=%40.5lf,took(%3d)sec,(%10.2lf)milli-second\n", exponent, result_i, t_diff, t_elapse_ms);


		time(&t_before);
		QueryPerformanceCounter(&t1);
		result_r = powerRecur(base, exponent);
		QueryPerformanceCounter(&t2);
		time(&t_after);
		t_diff = difftime(t_after, t_before);
		t_diff_pc = t2.QuadPart - t1.QuadPart;
		t_elapse_ms = ((double)t_diff_pc / (double)freq.QuadPart) * 1000;// 1ms의 정확도까지의 계산
		printf("PowerRecur(1.015,%d)by recursive=%40.5lf,took(%3d)sec,(%10.2lf)milli-second\n", exponent, result_r, t_diff, t_elapse_ms);

	}
	
	return 0;
}