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
	int genAddr;//생성 스레드
	int handlerAddr;//처리 스레드
	int priority; // event_priority
	LARGE_INTEGER t_gen;//생성된 시간
	LARGE_INTEGER t_proc;//처리된 시간
	double t_elapsed;
	EventStatus eventStatus;
} Event;
void printEvent(Event* pEvt);//이벤트 출력
void printEvent_withTime(Event* pEv);//이벤트 및 이벤트 생성시간 출력
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);//이벤트 생성시간계산
void fprintEvent(FILE* fout,Event* pEvt);//파일에 이벤트 출력
void initEvent(Event* pEv, unsigned int sAddr, unsigned int sN);//이벤트 생성
#endif