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
	int eventsGen[NUM_EVENT_GENERATORS];//���� ������
	int eventsProc[NUM_EVENT_HANDLERS];//ó�� ������
	int totalEventGen;//������ �̺�Ʈ ��
	int totalEventProc;//ó���� �̺�Ʈ��
	int numEventProcs_priH;//high����ó���ȼ�
	int numEventProcs_priL;//low���� ó���� ��
	THREAD_FLAG* pFlagThreadTerminate;
	Event eventProcessed[TOTAL_NUM_EVENTS];
	Event eventsGenerated[TOTAL_NUM_EVENTS];

} ThreadStatMon;//����͸� ����ü

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
	int targetEventGen;//������ �̺� Ʈ ��
	LARGE_INTEGER PC_freq;//���ļ�
	ThreadStatMon* pThrdMon;
} ThreadParam_Ev;

void Thread_EventHandler(ThreadParam_Ev* pThrdParam);//�̺�Ʈ ó��
void Thread_EventGenerator(ThreadParam_Ev* pThrdParam);//�̺�Ʈ ����

#endif