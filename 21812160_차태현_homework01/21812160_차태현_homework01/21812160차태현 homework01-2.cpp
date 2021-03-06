#include <stdio.h>
#define PI 3.141592
/**
*파일명:“homework01-2.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 원기둥의 반지름과 높이를 입력받아 원기둥의 부피와 겉넓이는 구하는 프로그램입니다.
*
*프로그램 작성자: 21812160 차태현(2021년 3월5일),
*최종 수정 및 보완: 2021년 3월 일 (차태현)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완 내용
*차태현               2021/03/0   
*============================================================================
*/
int main(void)
{
	double radius, height;
	double Volume = 0;
	double Surfacearea = 0;

	printf("원기둥의 반지름과 높이를 입력하시오:\n");
	scanf_s("%lf%lf", &radius, &height);

	Volume= PI * radius * radius * height;
	Surfacearea = 2 * PI * radius * height + 2 * PI * radius * radius;

	printf("원기둥의 부피는%.2lf이고 겉넓이는%.2lf이다", Volume, Surfacearea);


	return 0;
}