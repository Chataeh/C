/**
*파일이름"21812160_차태현_homework09-5 ”
*프로그램의 목적 및 기본 기능:
* 구조체 시간배열을 선택정렬하는 프로그램.
*
*프로그램 작성자: 21812160 차태현(2021년 5월7일),
*최종 수정 및 보완: 2021년 5월 7일 (차태현)
*/
#include <stdio.h>
#include "Time.h"//사용자 정의헤더
#define NUM_TIMES 5
void main()
{
	Time t1, t2;
	Time times[NUM_TIMES];
	int incr_secs, diff_sec;
	t1 = t2 = inputTime();//시간 입력
	printf("Input time t1 = "); printTime(&t1); printf("\n");
	printf("input seconds to increment : ");
	scanf("%d", &incr_secs);//증가 된 시간입력
	incrementTime(&t2, incr_secs);//증가된 초에 따른 새로운 시간값
	printf("After incrementing %d secs, t2 = ", incr_secs); printTime(&t2); printf("\n");
	diff_sec = compareTime(&t1, &t2);//두 시간의 시간 차
	printf("Difference between t1 and t2 is %d secs\n", diff_sec);
	times[0] = initTime(23, 59, 59);
	times[1] = initTime(9, 0, 5);
	times[2] = initTime(13, 30, 0);
	times[3] = initTime(3, 59, 59);
	times[4] = initTime(0, 0, 0);
	printf("\nBefore sorting times : \n");
	for (int i = 0; i < NUM_TIMES; i++)
	{
		printf("times[%d] = ", i); printTime(&times[i]); printf("\n");
	}
	selectSortTime(times, NUM_TIMES);//선택정렬후 출력
	printf("After selection sorting of times : \n");
	for (int i = 0; i < NUM_TIMES; i++)
	{
		printf("times[%d] = ", i); printTime(&times[i]); printf("\n");
	}
}