/**
*�����̸�"21812160_������_Lab13 "
*���α׷��� ���� �� �⺻ ���:
*  ��Ƽ�����带 �̿��Ͽ� ���Ḯ��Ʈť�� �ִ��̺�Ʈ�� ó��.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 6��3��),
*���� ���� �� ����: 2021�� 6�� 3�� (������)
*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "Thread.h"
#include "DLL_EvQ.h"
#include "Event.h"
#include "ConsoleDisplay.h"

using namespace std;

int main()
{
	FILE* fout;
	DLL_EvQ dll_EvQ_PriH, dll_EvQ_PriL;//���Ḯ��Ʈ ť
	Event* pEvent;//�̺�Ʈ
	int myAddr = 0;
	int event_handler_addr, eventPriority;
	LARGE_INTEGER pc_freq;

	fout = fopen("SimOutput.txt", "w");
	if (fout == NULL)
	{
		printf("Error in opening SimOutput.txt file in write mode !!\n");
		exit;
	}

	initDLL_EvQ(&dll_EvQ_PriH, 0);//���Ḯ��Ʈ ť �ʱ�ȭ
	initDLL_EvQ(&dll_EvQ_PriL, 1);
	srand(time(NULL));
	ThreadParam_Ev thrdParam_EventGen[NUM_EVENT_GENERATORS],thrdParam_EventHndlr[NUM_EVENT_HANDLERS];//������ �������� ����ü
	thread thread_evHandlers[NUM_EVENT_HANDLERS];//join�� ���� ������ �迭����
	thread thread_evGens[NUM_EVENT_GENERATORS];
	mutex cs_main;//���ο��� �Ӱ豸��
	mutex cs_thrd_mon;//����͸� �Ӱ豸��
	ThreadStatMon thrdMon;//������ ����͸� ����ü
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventProcessed;
	Event eventProcessed[TOTAL_NUM_EVENTS];//��ü �����̺�Ʈ

	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&pc_freq);//���ļ� ���
	/*������ ����͸����ð� �ʱ�ȭ*/
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGen = 0;//������ �̺�Ʈ��
	thrdMon.totalEventProc = 0;//ó���� �̺�Ʈ ��
	thrdMon.numEventProcs_priH = 0;//high ���� ó���� �̺�Ʈ ��
	thrdMon.numEventProcs_priL = 0;//low ���� ó���� �̺�Ʈ ��
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].event_no = -1; // mark as not-processed
		thrdMon.eventProcessed[ev].event_pri = -1;
		
	}
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)//�ΰ��� �̺�Ʈ ó�� ������ ����
	{
		thrdMon.eventsProc[p] = 0;
		thrdParam_EventHndlr[p].fout = fout;
		thrdParam_EventHndlr[p].role = EVENT_HANDLER;
		thrdParam_EventHndlr[p].myAddr = p; // Event handler address
		thrdParam_EventHndlr[p].pCS_main = &cs_main;
		thrdParam_EventHndlr[p].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EventHndlr[p].EvQ_PriH = &dll_EvQ_PriH;
		thrdParam_EventHndlr[p].EvQ_PriL = &dll_EvQ_PriL;
		thrdParam_EventHndlr[p].maxRound = MAX_ROUND;
		thrdParam_EventHndlr[p].pThrdMon = &thrdMon;
		thrdParam_EventHndlr[p].PC_freq = pc_freq;
		thread_evHandlers[p] = thread(Thread_EventHandler, &thrdParam_EventHndlr[p]);//������ ����
		cs_main.lock();
		printf("%d-th thread_EventHandler is created and activated (id: %d)\n", p,	thread_evHandlers[p].get_id());
		cs_main.unlock();
	}
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)//������ �̺�Ʈ ó�������� ����
	{
		thrdMon.eventsGen[g] = 0;
		thrdParam_EventGen[g].role = EVENT_GENERATOR;
		thrdParam_EventGen[g].myAddr = g; // my Address of event generator
		thrdParam_EventGen[g].pCS_main = &cs_main;
		thrdParam_EventGen[g].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EventGen[g].EvQ_PriH = &dll_EvQ_PriH;
		thrdParam_EventGen[g].EvQ_PriL = &dll_EvQ_PriL;
		thrdParam_EventGen[g].targetEventGen = NUM_EVENTS_PER_GEN;
		thrdParam_EventGen[g].maxRound = MAX_ROUND;
		thrdParam_EventGen[g].pThrdMon = &thrdMon;
		thrdParam_EventGen[g].PC_freq = pc_freq;
		thread_evGens[g] = thread(Thread_EventGenerator, &thrdParam_EventGen[g]);//������ ����
		cs_main.lock();
		printf("%d-th thread_EventGen is created and activated (id: )\n", g, thread_evGens[g].get_id());
		cs_main.unlock();
	}
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();
		system("cls");//�ܼ�â ȭ�� ����
		gotoxy(consHndlr, 0, 0);//�ܼ�â���� Ŀ�� ó������ �ű��
		printf("Thread monitoring by main() :: round(%2d): \n", round);
		printf("Event_Generators have generated total %2d events\n", thrdMon.totalEventGen);
		for (int i = 0; i < NUM_EVENT_GENERATORS; i++)
		{
			printf(" Event_Genr[%d] generated %2d events.\n", i, thrdMon.eventsGen[i]);//�����庰 �����̺�Ʈ �� ���
		}
		printf("Event_Generators have generated total %2d events\n", thrdMon.totalEventGen);
		int totalEventGenerated = thrdMon.totalEventGen;
		printf("\nTotal Generated Events (current total %d events)\n ", totalEventGenerated);
		for (int ev = 0; ev < totalEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventsGenerated[ev];
			if (pEvent != NULL)
			{
				printEvent(pEvent);
				if (((ev + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
		}
		printf("\n");
		printf("Event_Handlers have processed total %2d events ", thrdMon.totalEventProc);//������ó���ڵ��� ó���� �̺�Ʈ��
		printf("(event__PriH (%2d), event_PriL (%2d))\n", thrdMon.numEventProcs_priH,	thrdMon.numEventProcs_priL);//������ ó�������尡 ó���� �̺�Ʈ ��
		for (int i = 0; i < NUM_EVENT_HANDLERS; i++)
		{
			printf(" Event_Proc[%d] processed %2d events.\n", i, thrdMon.eventsProc[i]);//�����庰 ó���̺�Ʈ �� ���
		}
		printf("\nDLL_EvQ_PriH(% 3d events) :\n ", dll_EvQ_PriH.num_event);	//high prió���ڰ� ó���� �̺�Ʈ��
		printDLL_EvQ(&dll_EvQ_PriH);
		printf("\nDLL_EvQ_PriL(% 3d events) :\n ", dll_EvQ_PriL.num_event);//low prió���ڰ� ó���� �̺�Ʈ��
		printDLL_EvQ(&dll_EvQ_PriL);
		printf("\n");
		printf("Events processed:\n ");
		count = 0;
		numEventProcessed = thrdMon.totalEventProc;
		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev];
			if (pEvent != NULL)
			{
				printEvent(pEvent);
				if (((ev + 1) % EVENT_PER_LINE) == 0) 
					printf("\n ");
			}
		}
		printf("\n");
		if (numEventProcessed >= TOTAL_NUM_EVENTS)//ó�����̺�Ʈ ���� ��ü �̺�Ʈ ������ ���ų� ������� ������ ���� �÷��� ����
		{
			eventThreadFlag = TERMINATE; 
			cs_main.unlock();
			break;
		}
		cs_main.unlock(); Sleep(100);
	} 
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thread_evGens[g].join();//�̺�Ʈ ó�������尡 �ٳ����� ���� ��ٸ�
	}
	printf("All threads of event generators are terminated !!\n");
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thread_evHandlers[p].join();//�̺�Ʈ ���� �����尡 �� ���������� ��ٸ�
	}
	printf("All threads of event handlers are terminated !!\n");


	double min, max, avg, sum;
	int min_event, max_event;
	min = max = sum = thrdMon.eventProcessed[0].t_elapsed;
	min_event = max_event = 0;
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++)
	{
		sum += thrdMon.eventProcessed[i].t_elapsed;
		if (min > thrdMon.eventProcessed[i].t_elapsed)
		{
			min = thrdMon.eventProcessed[i].t_elapsed;
			min_event = i;
		}
		if (max < thrdMon.eventProcessed[i].t_elapsed)
		{
			max = thrdMon.eventProcessed[i].t_elapsed;
			max_event = i;
		}
	}
	avg = sum / (double)TOTAL_NUM_EVENTS;
	printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[min_event]); printf("\n");
	printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000);
	printEvent_withTime(&thrdMon.eventProcessed[max_event]); printf("\n");
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000,	TOTAL_NUM_EVENTS);
	printf("\n");

	return 0;
}
