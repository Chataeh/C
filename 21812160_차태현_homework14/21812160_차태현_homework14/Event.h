#pragma once
#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#include <Windows.h>
#include "ConsoleDisplay.h"
#include "SimParam.h"

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
extern const char* strEventStatus[];

typedef struct
{
	int seqNO;
	int genAddr;//���� ������
	int handlerAddr;//ó�� ������
	int priority; // event_priority
	LARGE_INTEGER t_gen;//������ �ð�
	LARGE_INTEGER t_proc;//ó���� �ð�
	double t_elapsed;
	EventStatus eventStatus;
} Event;
void printEvent(Event* pEvt);//�̺�Ʈ ���
void printEvent_withTime(Event* pEv);//�̺�Ʈ �� �̺�Ʈ �����ð� ���
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);//�̺�Ʈ �����ð����
void fprintEvent(FILE* fout,Event* pEvt);//���Ͽ� �̺�Ʈ ���
void initEvent(Event* pEv, unsigned int sAddr, unsigned int sN);//�̺�Ʈ ����
#endif