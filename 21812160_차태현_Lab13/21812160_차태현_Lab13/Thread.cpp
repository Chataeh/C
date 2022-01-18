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
	DLL_EvQ* pPriH_LLQ = pThrdParam->EvQ_PriH;//�켱������ ����ť
	DLL_EvQ* pPriL_LLQ = pThrdParam->EvQ_PriL;//�켱������ ����ť
	int maxRound = pThrdParam->maxRound;
	int targetEventGen = pThrdParam->targetEventGen;
	ThreadStatMon* pThrdMon = pThrdParam->pThrdMon;
	
	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen)//������ �̺�Ʈ ���� �����ҷ��� �̺�Ʈ ������ ũ�ų� ���� ��� ����
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			else {
				Sleep(500);
				continue;
			}
		}
		pEv = (Event*)calloc(1, sizeof(Event));//�����Ҵ�
		pEv->event_gen_addr = myAddr;
		pEv->event_handler_addr = -1;
		pEv->event_no = event_gen_count+(NUM_EVENTS_PER_GEN*myAddr);
		pEv->event_pri = event_pri = rand() % NUM_PRIORITY;//�켱���� 0~9
		
		QueryPerformanceCounter(&pEv->t_gen);//������ �ð� 
		pEvQ = (event_pri < PRIORITY_THRESHOLD) ? pPriH_LLQ : pPriL_LLQ;//�켱������ 3���������� high �ƴϸ� low
		while (enDLL_EvQ(pEvQ, pEv) == NULL)//�̺�Ʈ �߰� ��ť����
		{
			Sleep(100);
		} // end while
		pThrdParam->pCS_thrd_mon->lock();		
		pThrdMon->eventsGenerated[pThrdMon->totalEventGen] = *pEv;
		pThrdMon->totalEventGen++;//�����忡�� ������ �̺�Ʈ�� 
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
			while ((pEvent = deDLL_EvQ(pPriH_LLQ)) != NULL)//��ť���� ����
			{
				pThrdParam->pCS_thrd_mon->lock();	
				pEvent->event_handler_addr = myAddr; 
				QueryPerformanceCounter(&pEvent->t_proc);
				calc_elapsed_time(pEvent,pThrdParam->PC_freq);//ó���� �ð�
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