#include <Windows.h>
#include <time.h>
#include <thread>
#include <mutex>
#include "Thread.h"
#include "DLL_EvQ.h"
#include "Event.h"
#include "Simparam.h"

using namespace std;

void Thread_EventGenerator(ThreadParam_Ev* pThrdParam)
{
	DLL_EvQ* pEvQ;
	Event* pEv;
	int event_id = 0, event_pri = 0, event_gen_count = 0;
	int event_handlerAddr;
	int myRole = pThrdParam->role;
	int myAddr = pThrdParam->myAddr;
	DLL_EvQ* pPriH_LLQ = pThrdParam->EvQ_PriH;//우선순위가 높은큐
	DLL_EvQ* pPriL_LLQ = pThrdParam->EvQ_PriL;//우선순위가 낮은큐
	int maxRound = pThrdParam->maxRound;
	int targetEventGen = pThrdParam->targetEventGen;
	ThreadStatMon* pThrdMon = pThrdParam->pThrdMon;
	
	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen)//생성된 이벤트 수가 생성할려는 이벤트 수보다 크거나 같을 경우 종료
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			else {
				Sleep(500);
				continue;
			}
		}
		pEv = (Event*)calloc(1, sizeof(Event));//동적할당
		pEv->event_gen_addr = myAddr;
		pEv->event_handler_addr = -1;
		pEv->event_no = event_gen_count+(NUM_EVENTS_PER_GEN*myAddr);
		pEv->event_pri = event_pri = rand() % NUM_PRIORITY;//우선순위 0~9
		
		QueryPerformanceCounter(&pEv->t_gen);//생성된 시간 
		pEvQ = (event_pri < PRIORITY_THRESHOLD) ? pPriH_LLQ : pPriL_LLQ;//우선순위가 3보다작으면 high 아니면 low
		while (enDLL_EvQ(pEvQ, pEv) == NULL)//이벤트 추가 인큐과정
		{
			Sleep(100);
		} // end while
		pThrdParam->pCS_thrd_mon->lock();		
		pThrdMon->eventsGenerated[pThrdMon->totalEventGen] = *pEv;
		pThrdMon->totalEventGen++;//스레드에서 생성된 이벤트수 
		pThrdMon->eventsGen[myAddr]++;
		pThrdParam->pCS_thrd_mon->unlock();
		event_gen_count++;
		Sleep(100 + rand() % 300);
	} 
}

	void Thread_EventHandler(ThreadParam_Ev * pThrdParam)
	{
		DLL_EvQ* pEvQ;
		THREAD_FLAG* pFlagThreadTerminate;
		Event* pEvent;
		int event_id = 0, event_pri = 0, pkt_gen_count = 0;
		int num_event_processed = 0;
		int myRole = pThrdParam->role;
		int myAddr = pThrdParam->myAddr;
		DLL_EvQ* pPriH_LLQ = pThrdParam->EvQ_PriH;
		DLL_EvQ* pPriL_LLQ = pThrdParam->EvQ_PriL;
		ThreadStatMon* pThrdMon = pThrdParam->pThrdMon;
		int maxRound = pThrdParam->maxRound;
		Event* pEventProc = pThrdParam->pThrdMon->eventProcessed;
		int targetEventGen = pThrdParam->targetEventGen;
		
		for (int round = 0; round < maxRound; round++)
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			while ((pEvent = deDLL_EvQ(pPriH_LLQ)) != NULL)//디큐과정 실행
			{
				pThrdParam->pCS_thrd_mon->lock();	
				pEvent->event_handler_addr = myAddr; 
				QueryPerformanceCounter(&pEvent->t_proc);
				calc_elapsed_time(pEvent,pThrdParam->PC_freq);//처리된 시간
				pEventProc[pThrdMon->totalEventProc] = *pEvent;
				pThrdMon->totalEventProc++;
				pThrdMon->numEventProcs_priH++;
				pThrdMon->eventsProc[myAddr]++;
				free(pEvent); 
				pThrdParam->pCS_thrd_mon->unlock();
				Sleep(100 + rand() % 300);
			} // end while
			if ((pEvent = deDLL_EvQ(pPriL_LLQ)) != NULL)
			{
				pThrdParam->pCS_thrd_mon->lock();
				pEvent->event_handler_addr = myAddr;
				QueryPerformanceCounter(&pEvent->t_proc);
				calc_elapsed_time(pEvent, pThrdParam->PC_freq);
				pEventProc[pThrdMon->totalEventProc] = *pEvent;
				pThrdMon->totalEventProc++;
				pThrdMon->numEventProcs_priL++;
				pThrdMon->eventsProc[myAddr]++;
				
				free(pEvent);
				pThrdParam->pCS_thrd_mon->unlock();
			} // end if
			Sleep(100 + rand() % 300);
		} // end for
	}