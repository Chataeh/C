#pragma once
#ifndef THREAD_H
#define THREAD_H
#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include "Event.h"
#include "SimParam.h"
#include "DLL_EvQ.h"

using namespace std;

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

typedef struct
{
	int eventsGen[NUM_EVENT_GENERATORS];//생성 스레드
	int eventsProc[NUM_EVENT_HANDLERS];//처리 스레드
	int totalEventGen;//생성된 이벤트 수
	int totalEventProc;//처리된 이벤트수
	int numEventProcs_priH;//high에서처리된수
	int numEventProcs_priL;//low에서 처리된 수
	THREAD_FLAG* pFlagThreadTerminate;
	Event eventProcessed[TOTAL_NUM_EVENTS];
	Event eventsGenerated[TOTAL_NUM_EVENTS];

} ThreadStatMon;//모니터링 구조체

typedef struct
{
	FILE* fout;
	mutex* pCS_main;
	mutex* pCS_thrd_mon;
	DLL_EvQ* EvQ_PriH;//high pri
	DLL_EvQ* EvQ_PriL;//low pri
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;//생성할 이벤 트 수
	LARGE_INTEGER PC_freq;//주파수
	ThreadStatMon* pThrdMon;
} ThreadParam_Ev;

void Thread_EventHandler(ThreadParam_Ev* pThrdParam);//이벤트 처리
void Thread_EventGenerator(ThreadParam_Ev* pThrdParam);//이벤트 생성

#endif