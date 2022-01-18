#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"Event.h"

void printEvent(Event* pEv)//이벤트 출력
{
	printf("Ev(id:%3d, pri:%2d, gen:%2d, proc:%2d) ", pEv->ev_no, pEv->ev_pri,	pEv->ev_generator, pEv->ev_handler);
}

Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri)//이벤트 생성
{
	pEv = (Event*)calloc(1, sizeof(Event));//동적메모리 할당
	if (pEv == NULL)
		return NULL;// 동적할당 제대로 안되었을시
	pEv->ev_generator = event_Gen_ID;
	pEv->ev_handler = -1;//아직 정해지지않음
	pEv->ev_no = ev_no;
	pEv->ev_pri = ev_pri;

	return pEv;
}
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)//시간차 계산
{
	LONGLONG t_diff;
	t_diff = pEv->ev_t_handle.QuadPart - pEv->ev_t_gen.QuadPart;//이벤트 추출된시간 - 이벤트 추가된시간
	pEv->elap_time = (double)t_diff / freq.QuadPart; //시간차/주파수
}

void printEvent_withTime(Event* pEv)//걸린시간과 이벤트 출력
{
	printf("Ev(no:%2d,pri:%2d,elap_t:%6.0lf[ms]", pEv->ev_no, pEv->ev_pri, pEv->elap_time*1000);
}