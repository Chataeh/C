#include<Windows.h>
#include<time.h>
#include"Thread.h"
#include"PriQ_Event.h"
#include"Event.h"

void Thread_EventGenerator(ThreadParam_Event* pParam)//스레드 이벤트 생성
{
	PriQ_Event* pPriQ_Event = pParam->pPriQ_Event;//큐의 주소 저장
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int event_gen_count = 0;
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon;
	pPriQ_Event = pParam->pPriQ_Event;
	int targetEventGen = pParam->targetEventGen;
	
	Event* pEv;

	srand(time(NULL));
	for (int round = 0; round < maxRound; round++)//라운드 반복
	{
		if (event_gen_count >= targetEventGen)//생성한 이벤트가 목표로하는 이벤트 생성수와 같거나 클경우 
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)//터미네이트 상태일때 종료
				break;

			else
			{
				Sleep(500);//터미네이트 상태일때까지 대기
				continue;
			}
		}
		pEv = (Event*)calloc(1, sizeof(Event));//동적할당
		pEv->ev_generator = myAddr;
		pEv->ev_no = -1;
		pEv->ev_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;//각각의 스레드가 발생시키는 값 중복방지
		pEv->ev_pri = targetEventGen - event_gen_count - 1;//우선순위는 작은값이 첫번째기때문에 역순으로 설정
		pEv->ev_handler = -1;
		QueryPerformanceCounter(&pEv->ev_t_gen);//시간 측정
		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = *pEv;
		while (enPriQ_Event(pPriQ_Event, *pEv) == NULL)//우선순위큐에 인큐해줌
		{
			Sleep(500);
		}
		free(pEv);//동적반환
		pParam->pMTX_thrd_mon->lock();//임계구역 설정
		pThrdMon->numEventGenerated++;
		pThrdMon->totalEventGenerated++;
		pParam->pMTX_thrd_mon->unlock();//임계구역 설정
		event_gen_count++;
		Sleep(10);
	}
}

void Thread_EventHandler(ThreadParam_Event* pParam)
{
	Event* pEv, * pEvProc, ev;
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	PriQ_Event* pPriQ_Event = pParam->pPriQ_Event;
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon;
	int maxRound = pParam->maxRound;
	int targetEventGen = pParam->targetEventGen;//전달되어온 값들로 초기화


	srand(time(NULL));
	for (int round = 0; round < maxRound; round++)//라운드 반복
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)//터미네이트 상태일때 종료
			break;

		if ((pEv = dePriQ_Event(pPriQ_Event)) != NULL)
		{
			pParam->pMTX_thrd_mon->lock();//임계구역 설정
			QueryPerformanceCounter(&pEv->ev_t_handle);//시간측정
			pEv->ev_handler = myAddr;
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = *pEv;
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			pParam->pMTX_thrd_mon->unlock();//임계구역설정
			free(pEv);//메모리 반환
		}
		Sleep(100 + rand() % 300);	
	}
}