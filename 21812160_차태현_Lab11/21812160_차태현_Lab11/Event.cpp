#include<stdio.h>
#include<stdlib.h>
#include"Event.h"

void printEvent(Event* pEv)
{
	printf("Ev(no:%3d,pri:%2d", pEv->event_no, pEv->event_pri);//event_no와event_pri출력
}

void fprintEvent(FILE* fout, Event* pEv)
{
	fprintf(fout,"Ev(no:%3d,pri:%2d)", pEv->event_no, pEv->event_pri);//파일에 event_no와event_pri출력
}

Event* genEvent(Event* pEvent, int event_Gen_ID, int event_no, int event_pri)//이벤트 값 정의
{
	pEvent = (Event*)malloc(sizeof(Event));//동적할당

	pEvent->event_gen_addr = event_Gen_ID;//구조체 값정의
	pEvent->event_no = event_no;
	pEvent->event_pri = event_pri;

	return pEvent;//구조체 반환
}