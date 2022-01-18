#ifndef E_H
#define E_H
#include<stdio.h>
#include<Windows.h>
#define NUM _PROPROTY 100
#define EVENT_PER_LINE 5

typedef struct {
	int ev_no;
	int ev_generator;
	int ev_handler;
	int ev_pri;//우선순위
	LARGE_INTEGER ev_t_gen;// 시간계산을 위한 변수
	LARGE_INTEGER ev_t_handle;// 시간계산을 위한변수
	double elap_time; //시간차

}Event; //이벤트 구조체정의

void printEvent(Event* pEvt);//이벤트 출력
Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri);//이벤트생성
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);//시간차 계산
void printEvent_withTime(Event* pEv);//시간차와 함께 이벤트 출력

#endif