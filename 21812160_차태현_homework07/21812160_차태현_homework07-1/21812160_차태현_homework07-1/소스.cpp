/**
*파일이름" 함수인수전달방식 ”
*프로그램의 목적 및 기본 기능:
*  함수의 인수를 여러 경우로 받아와 평균을구하는프로그램.
*
*프로그램 작성자: 21812160 차태현(2021년 4월16일),
*최종 수정 및 보완: 2021년 4월 16일 (차태현)
*/
#include <stdio.h>

double average_value(double x, double y);//값에의한 호출
void average_pointer(double* px, double* py, double* pavg);//포인터에의한 호출
void average_reference(double& px, double& py, double& pavg);//참조에의한 호출

int main()
{
	double x, y;
	double avg=0;

	scanf("%lf %lf", &x, &y);
	printf("call-by-value\n");
	avg=average_value(x, y);//인수복사 전달
	printf("avg=%.2lf\n", avg);
	
	
	scanf("%lf %lf", &x, &y);
	printf("\ncall-by-pointer\navg=");
	average_pointer(&x, &y, &avg);//주소정보 전달
	printf("\n");

	scanf("%lf %lf", &x, &y);
	printf("\ncall-by-reference\navg=");
	average_reference(x, y, avg);//변수의 주소정보

}

double average_value(double x, double y)//값에의한 호출
{
	double avg;
	avg = (x + y) / 2;
	
	return avg;
}

void average_pointer(double* px, double* py, double* pavg)//포인터에 의한 호출*사용 주소정보 전달
{

	*pavg = (*px + *py) / 2;

	printf("%.2lf", *pavg);
}
void average_reference(double& px, double& py, double& pavg)//참조에의한 호출 &사용
{
	pavg = (px + py) / 2;

	printf("%.2lf", pavg);

}