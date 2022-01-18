#include<Windows.h>
#include<time.h>
#include"Thread.h"
#include"PriQ_Event.h"
#include"Event.h"

void Thread_EventGenerator(ThreadParam_Event* pParam)//������ �̺�Ʈ ����
{
	PriQ_Event* pPriQ_Event = pParam->pPriQ_Event;//ť�� �ּ� ����
	int myRole = pParam->role;
	int myAddr = pParam->myAddr;
	int maxRound = pParam->maxRound;
	int event_gen_count = 0;
	ThreadStatusMonitor* pThrdMon = pParam->pThrdMon;
	pPriQ_Event = pParam->pPriQ_Event;
	int targetEventGen = pParam->targetEventGen;
	
	Event* pEv;

	srand(time(NULL));
	for (int round = 0; round < maxRound; round++)//���� �ݺ�
	{
		if (event_gen_count >= targetEventGen)//������ �̺�Ʈ�� ��ǥ���ϴ� �̺�Ʈ �������� ���ų� Ŭ��� 
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)//�͹̳���Ʈ �����϶� ����
				break;

			else
			{
				Sleep(500);//�͹̳���Ʈ �����϶����� ���
				continue;
			}
		}
		pEv = (Event*)calloc(1, sizeof(Event));//�����Ҵ�
		pEv->ev_generator = myAddr;
		pEv->ev_no = -1;
		pEv->ev_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;//������ �����尡 �߻���Ű�� �� �ߺ�����
		pEv->ev_pri = targetEventGen - event_gen_count - 1;//�켱������ �������� ù��°�⶧���� �������� ����
		pEv->ev_handler = -1;
		QueryPerformanceCounter(&pEv->ev_t_gen);//�ð� ����
		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = *pEv;
		while (enPriQ_Event(pPriQ_Event, *pEv) == NULL)//�켱����ť�� ��ť����
		{
			Sleep(500);
		}
		free(pEv);//������ȯ
		pParam->pMTX_thrd_mon->lock();//�Ӱ豸�� ����
		pThrdMon->numEventGenerated++;
		pThrdMon->totalEventGenerated++;
		pParam->pMTX_thrd_mon->unlock();//�Ӱ豸�� ����
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
	int targetEventGen = pParam->targetEventGen;//���޵Ǿ�� ����� �ʱ�ȭ


	srand(time(NULL));
	for (int round = 0; round < maxRound; round++)//���� �ݺ�
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)//�͹̳���Ʈ �����϶� ����
			break;

		if ((pEv = dePriQ_Event(pPriQ_Event)) != NULL)
		{
			pParam->pMTX_thrd_mon->lock();//�Ӱ豸�� ����
			QueryPerformanceCounter(&pEv->ev_t_handle);//�ð�����
			pEv->ev_handler = myAddr;
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = *pEv;
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			pParam->pMTX_thrd_mon->unlock();//�Ӱ豸������
			free(pEv);//�޸� ��ȯ
		}
		Sleep(100 + rand() % 300);	
	}
}