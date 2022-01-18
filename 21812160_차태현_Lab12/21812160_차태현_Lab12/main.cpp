/**
*파일이름"21812160_차태현_Lab12 "
*프로그램의 목적 및 기본 기능:
*  우선순위큐를 멀티스레드로 실행.
*
*프로그램 작성자: 21812160 차태현(2021년 5월26일),
*최종 수정 및 보완: 2021년 5월 26일 (차태현)
*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mutex>
#include "Thread.h"
#include "PriQ_Event.h"
#include "Event.h"
#include "ConsoleDisplay.h"

using namespace std;

int main()
{
	PriQ_Event priQ_Event;
	Event* pEv;
	int myAddr = 0;
	int ev_handler, eventPriority;

	srand(time(NULL));
	initPriQ_Event(&priQ_Event, "PriQ_Event", 1);//우선순위 큐 초기화

	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;
	mutex cs_main;//임계구역 설정을 위함
	mutex cs_thrd_mon;//임계구역 설정을 위함
	ThreadStatusMonitor thrdMon;
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventGenerated, numEventProcessed;
	LARGE_INTEGER freq;//시간계산을 위함

	consHndlr = initConsoleHandler();

	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++)
	{
		thrdMon.eventProcessed[i].ev_no = -1;
		thrdMon.eventProcessed[i].ev_pri = -1;
	}
	QueryPerformanceFrequency(&freq);

	/*이벤트 핸들러 스레드생성*/
	thrdMon.numEventProcessed = 0;
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = 1;
	thrdParam_EventHndlr.pMTX_main = &cs_main; //메인에서 임계구역
	thrdParam_EventHndlr.pMTX_thrd_mon = &cs_thrd_mon;// 스레드에서의 임계구역
	thrdParam_EventHndlr.pPriQ_Event = &priQ_Event;//공유자원 우선순위큐
	thrdParam_EventHndlr.maxRound = MAX_ROUND;//최대 라운드
	thrdParam_EventHndlr.pThrdMon = &thrdMon;

	thread thrd_ev_handler(Thread_EventHandler, &thrdParam_EventHndlr);//스레드 생성
	cs_main.lock();//스레드와 출력중복방지를 위한 임계구역설정
	printf("Thread_EventHandler is created and activated ...\n");
	cs_main.unlock();//스레드와 출력중복방지를 위한 임계구역설정

	/*이벤트 생성 스레드 생성*/
	thrdMon.numEventGenerated = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = 0; 
	thrdParam_EventGen.pMTX_main = &cs_main;//메인에서 임계구역
	thrdParam_EventGen.pMTX_thrd_mon = &cs_thrd_mon;// 스레드에서의 임계구역
	thrdParam_EventGen.pPriQ_Event = &priQ_Event;//공유자원 우선순위큐
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;//생성할 이벤트 
	thrdParam_EventGen.maxRound = MAX_ROUND;//최대 라운드
	thrdParam_EventGen.pThrdMon = &thrdMon;
	
	thread thrd_ev_generator(Thread_EventGenerator, &thrdParam_EventGen);
	cs_main.lock();//스레드와 출력중복방지를 위한 임계구역설정
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();//스레드와 출력중복방지를 위한 임계구역설정

	for (int round = 0; round < MAX_ROUND; round++)
	{
		system("cls");//콘솔창 비우기
		gotoxy(consHndlr, 0, 0);//콘솔창에서 커서 옮기기 0,0 즉 처음으로 옮기기
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n",round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		printf("\n");
		printf("Events generated: \n ");

		count = 0;
		numEventGenerated = thrdMon.totalEventGenerated;//전체적으로 생성된 이벤트수
		for (int i = 0; i < numEventGenerated; i++)//생성된 이벤트출력
		{
			pEv = &thrdMon.eventGenerated[i];//생성된 이벤트
			if (pEv != NULL)//배열이 있을경우
			{
				printEvent(pEv);//이벤트 출력
				if (((i + 1) % EVENT_PER_LINE) == 0)//한줄에5개씩출력
					printf("\n ");
			}
		}
		printf("\n");
		printf("Event_Gen generated %2d events\n", thrdMon.numEventGenerated);
		printf("Event_Handler processed %2d events\n", thrdMon.numEventProcessed);
		printf("\n");
		printf("PriQ_Event::");
		printPriQ_Event(&priQ_Event);//이진트리 출력
		printf("\n");
		printf("Events processed: \n ");
		
		count = 0;
		numEventProcessed = thrdMon.totalEventProcessed;//전체적으로 처리된 이벤트 수
		for (int i = 0; i < numEventProcessed; i++)//이벤트 처리
		{
			pEv = &thrdMon.eventProcessed[i];//처리될 이벤트
			if (pEv != NULL)
			{
				calc_elapsed_time(pEv, freq);//처리된시간-생성된시간
				printEvent_withTime(pEv);//걸린시간과 함께 이벤트출력
				if (((i + 1) % EVENT_PER_LINE) == 0)//한줄에 5개씩출력
					printf("\n ");
			}
		}
		printf("\n ");
		
		if (numEventProcessed >= TOTAL_NUM_EVENTS)//처리가 완료되었을시
		{
			eventThreadFlag = TERMINATE;//스레드 종료
			break;
		}
		Sleep(100);
	}
	double min, max, avg, sum;
	int min_ev, max_ev;
	min = max = sum = thrdMon.eventProcessed[0].elap_time;//최대최소평균값을 초기값으로 설정
	min_ev = max_ev = 0;
	
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++)
	{
		sum += thrdMon.eventProcessed[i].elap_time;//처리된 모든시간 더해줌
		if (min > thrdMon.eventProcessed[i].elap_time)//초기설정된 최소값보다 더 작은값이 있을경우
		{
			min = thrdMon.eventProcessed[i].elap_time;//그값이 최솟값
			min_ev = i;
		}
		if (max < thrdMon.eventProcessed[i].elap_time)//초기설정된 최대값보다 더 큰 값이 있을경우 
		{
			max = thrdMon.eventProcessed[i].elap_time;//그값이 최대값
			max_ev = i;
		}
	}
	avg = sum / TOTAL_NUM_EVENTS;//걸린시간의 평균값계산
	printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);//최소시간 걸린이벤트
	printEvent_withTime(&thrdMon.eventProcessed[min_ev]); printf("\n");//시간과 이벤트출력
	printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000);//최대시간 걸린이벤트
	printEvent_withTime(&thrdMon.eventProcessed[max_ev]); printf("\n");//시간과 이벤트 출력
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000,TOTAL_NUM_EVENTS);//이벤트 처리시간의 평균
	printf("\n");

	thrd_ev_generator.join();//생성이 종료가될때까지 기다림
	printf("Thread_EventGenerator is terminated !!\n");
	thrd_ev_handler.join();//처리가 끝날때까지기다림
	printf("Thread_EventHandler is terminated !!\n");
}