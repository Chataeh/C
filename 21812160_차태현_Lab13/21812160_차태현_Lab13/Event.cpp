#include<stdio.h>
#include<stdlib.h>
#include"Event.h"

const char* strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" };

void printEvent(Event* pEvt)
{
	printf("Ev(no:%3d,pri:%2d,gen:%3d, proc:%3d)", pEvt->event_no, pEvt->event_pri, pEvt->event_gen_addr, pEvt->event_handler_addr);//이벤트 출력
}

void printEvent_withTime(Event* pEv)
{
	printf("Ev(no:%3d,pri:%2d,%6.0lf[ms])", pEv->event_no, pEv->event_pri,pEv->t_elapsed*1000);//이벤트 생성하는데 걸린시간 과 이벤트 출력
}
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)
{
	LONGLONG t_diff_LL;
	double t_elapsed;

	t_diff_LL = pEv->t_proc.QuadPart - pEv->t_gen.QuadPart;//처리된 시간-생성된시간
	t_elapsed = (double)t_diff_LL / (double)freq.QuadPart;//시간차/주파수
	pEv->t_elapsed = t_elapsed;
}