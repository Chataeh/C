/**
*파일명:“trans second.cpp”
*프로그램의 목적 및 기본 기능:
* -이 프로그램은 초를 입력받아 시간 분 초로 변환하는프로그램입니다.
*
*프로그램 작성자: 21812160 차태현(2021년 3월11일),
*최종 수정 및 보완: 2021년 3월 11일 (차태현)
*
*/
#include <stdio.h>

int main()
{
	int sec;
	int min, hour,trans;
	
	
	printf("초를 입력하시오:");
	scanf_s("%d", &sec);
	

	trans = sec % 60;// 초 구하기
	min = (sec / 60) % 60;//분 구하기
	hour = (sec / 60) / 60; //시간 구하기
	
	printf("%d초는 %d시간%d분%d초입니다", sec, hour, min, trans);


	return 0;
}