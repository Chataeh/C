#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#include <Windows.h>
#include "ConsoleDisplay.h"
#include "SimParam.h"

enum EventStatus {GENERATED, ENQUEUED,	PROCESSED, UNDEFINED};
extern const char* strEventStatus[];

typedef struct
{
	int event_no;
	int event_gen_addr;//���� ������
	int event_handler_addr;//ó�� ������
	int event_pri; // event_priority
	LARGE_INTEGER t_gen;//������ �ð�
	LARGE_INTEGER t_proc;//ó���� �ð�
	double t_elapsed;
	EventStatus eventStatus;
} Event;
void printEvent(Event* pEvt);//�̺�Ʈ ���
void printEvent_withTime(Event* pEv);//�̺�Ʈ �� �̺�Ʈ �����ð� ���
void calc_elapsed_time(Event* pEv,LARGE_INTEGER freq);//�̺�Ʈ �����ð����
#endif