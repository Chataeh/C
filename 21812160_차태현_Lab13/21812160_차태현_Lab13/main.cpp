/**
*파일이름"21812160_차태현_Lab13 "
*프로그램의 목적 및 기본 기능:
*  멀티스레드를 이용하여 연결리스트큐에 있는이벤트들 처리.
*
*프로그램 작성자: 21812160 차태현(2021년 6월3일),
*최종 수정 및 보완: 2021년 6월 3일 (차태현)
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
	DLL_EvQ dll_EvQ_PriH, dll_EvQ_PriL;//연결리스트 큐
	Event* pEvent;//이벤트
	int myAddr = 0;
	int event_handler_addr, eventPriority;
	LARGE_INTEGER pc_freq;

	fout = fopen("SimOutput.txt", "w");
	if (fout == NULL)
	{
		printf("Error in opening SimOutput.txt file in write mode !!\n");
		exit;
	}

	initDLL_EvQ(&dll_EvQ_PriH, 0);//연결리스트 큐 초기화
	initDLL_EvQ(&dll_EvQ_PriL, 1);
	srand(time(NULL));
	ThreadParam_Ev thrdParam_EventGen[NUM_EVENT_GENERATORS],thrdParam_EventHndlr[NUM_EVENT_HANDLERS];//생성할 스레드의 구조체
	thread thread_evHandlers[NUM_EVENT_HANDLERS];//join을 위한 스레드 배열생성
	thread thread_evGens[NUM_EVENT_GENERATORS];
	mutex cs_main;//메인에서 임계구역
	mutex cs_thrd_mon;//모니터링 임계구역
	ThreadStatMon thrdMon;//스레드 모니터링 구조체
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventProcessed;
	Event eventProcessed[TOTAL_NUM_EVENTS];//전체 생성이벤트

	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&pc_freq);//주파수 기록
	/*스레드 모니터링관련값 초기화*/
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGen = 0;//생성된 이벤트수
	thrdMon.totalEventProc = 0;//처리된 이벤트 수
	thrdMon.numEventProcs_priH = 0;//high 에서 처리된 이벤트 수
	thrdMon.numEventProcs_priL = 0;//low 에서 처리된 이벤트 수
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].event_no = -1; // mark as not-processed
		thrdMon.eventProcessed[ev].event_pri = -1;
		
	}
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)//두개의 이벤트 처리 스레드 생성
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
		thread_evHandlers[p] = thread(Thread_EventHandler, &thrdParam_EventHndlr[p]);//스레드 생성
		cs_main.lock();
		printf("%d-th thread_EventHandler is created and activated (id: %d)\n", p,	thread_evHandlers[p].get_id());
		cs_main.unlock();
	}
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)//세개의 이벤트 처리스레드 생성
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
		thread_evGens[g] = thread(Thread_EventGenerator, &thrdParam_EventGen[g]);//스레드 생성
		cs_main.lock();
		printf("%d-th thread_EventGen is created and activated (id: )\n", g, thread_evGens[g].get_id());
		cs_main.unlock();
	}
	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();
		system("cls");//콘솔창 화면 비우기
		gotoxy(consHndlr, 0, 0);//콘솔창에서 커서 처음으로 옮기기
		printf("Thread monitoring by main() :: round(%2d): \n", round);
		printf("Event_Generators have generated total %2d events\n", thrdMon.totalEventGen);
		for (int i = 0; i < NUM_EVENT_GENERATORS; i++)
		{
			printf(" Event_Genr[%d] generated %2d events.\n", i, thrdMon.eventsGen[i]);//스레드별 생성이벤트 수 출력
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
		printf("Event_Handlers have processed total %2d events ", thrdMon.totalEventProc);//스레드처리자들이 처리한 이벤트수
		printf("(event__PriH (%2d), event_PriL (%2d))\n", thrdMon.numEventProcs_priH,	thrdMon.numEventProcs_priL);//각각의 처리스레드가 처리한 이벤트 수
		for (int i = 0; i < NUM_EVENT_HANDLERS; i++)
		{
			printf(" Event_Proc[%d] processed %2d events.\n", i, thrdMon.eventsProc[i]);//스레드별 처리이벤트 수 출력
		}
		printf("\nDLL_EvQ_PriH(% 3d events) :\n ", dll_EvQ_PriH.num_event);	//high pri처리자가 처리한 이벤트수
		printDLL_EvQ(&dll_EvQ_PriH);
		printf("\nDLL_EvQ_PriL(% 3d events) :\n ", dll_EvQ_PriL.num_event);//low pri처리자가 처리한 이벤트수
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
		if (numEventProcessed >= TOTAL_NUM_EVENTS)//처리된이벤트 수가 전체 이벤트 수보다 많거나 같을경우 정지를 위한 플래그 변경
		{
			eventThreadFlag = TERMINATE; 
			cs_main.unlock();
			break;
		}
		cs_main.unlock(); Sleep(100);
	} 
	for (int g = 0; g < NUM_EVENT_GENERATORS; g++)
	{
		thread_evGens[g].join();//이벤트 처리스레드가 다끝날때 까지 기다림
	}
	printf("All threads of event generators are terminated !!\n");
	for (int p = 0; p < NUM_EVENT_HANDLERS; p++)
	{
		thread_evHandlers[p].join();//이벤트 생성 스레드가 다 끝날때까지 기다림
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
