/**
*�����̸�"21812160_������_Lab12 "
*���α׷��� ���� �� �⺻ ���:
*  �켱����ť�� ��Ƽ������� ����.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 5��26��),
*���� ���� �� ����: 2021�� 5�� 26�� (������)
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
	initPriQ_Event(&priQ_Event, "PriQ_Event", 1);//�켱���� ť �ʱ�ȭ

	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;
	mutex cs_main;//�Ӱ豸�� ������ ����
	mutex cs_thrd_mon;//�Ӱ豸�� ������ ����
	ThreadStatusMonitor thrdMon;
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventGenerated, numEventProcessed;
	LARGE_INTEGER freq;//�ð������ ����

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

	/*�̺�Ʈ �ڵ鷯 ���������*/
	thrdMon.numEventProcessed = 0;
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = 1;
	thrdParam_EventHndlr.pMTX_main = &cs_main; //���ο��� �Ӱ豸��
	thrdParam_EventHndlr.pMTX_thrd_mon = &cs_thrd_mon;// �����忡���� �Ӱ豸��
	thrdParam_EventHndlr.pPriQ_Event = &priQ_Event;//�����ڿ� �켱����ť
	thrdParam_EventHndlr.maxRound = MAX_ROUND;//�ִ� ����
	thrdParam_EventHndlr.pThrdMon = &thrdMon;

	thread thrd_ev_handler(Thread_EventHandler, &thrdParam_EventHndlr);//������ ����
	cs_main.lock();//������� ����ߺ������� ���� �Ӱ豸������
	printf("Thread_EventHandler is created and activated ...\n");
	cs_main.unlock();//������� ����ߺ������� ���� �Ӱ豸������

	/*�̺�Ʈ ���� ������ ����*/
	thrdMon.numEventGenerated = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = 0; 
	thrdParam_EventGen.pMTX_main = &cs_main;//���ο��� �Ӱ豸��
	thrdParam_EventGen.pMTX_thrd_mon = &cs_thrd_mon;// �����忡���� �Ӱ豸��
	thrdParam_EventGen.pPriQ_Event = &priQ_Event;//�����ڿ� �켱����ť
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;//������ �̺�Ʈ 
	thrdParam_EventGen.maxRound = MAX_ROUND;//�ִ� ����
	thrdParam_EventGen.pThrdMon = &thrdMon;
	
	thread thrd_ev_generator(Thread_EventGenerator, &thrdParam_EventGen);
	cs_main.lock();//������� ����ߺ������� ���� �Ӱ豸������
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();//������� ����ߺ������� ���� �Ӱ豸������

	for (int round = 0; round < MAX_ROUND; round++)
	{
		system("cls");//�ܼ�â ����
		gotoxy(consHndlr, 0, 0);//�ܼ�â���� Ŀ�� �ű�� 0,0 �� ó������ �ű��
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n",round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		printf("\n");
		printf("Events generated: \n ");

		count = 0;
		numEventGenerated = thrdMon.totalEventGenerated;//��ü������ ������ �̺�Ʈ��
		for (int i = 0; i < numEventGenerated; i++)//������ �̺�Ʈ���
		{
			pEv = &thrdMon.eventGenerated[i];//������ �̺�Ʈ
			if (pEv != NULL)//�迭�� �������
			{
				printEvent(pEv);//�̺�Ʈ ���
				if (((i + 1) % EVENT_PER_LINE) == 0)//���ٿ�5�������
					printf("\n ");
			}
		}
		printf("\n");
		printf("Event_Gen generated %2d events\n", thrdMon.numEventGenerated);
		printf("Event_Handler processed %2d events\n", thrdMon.numEventProcessed);
		printf("\n");
		printf("PriQ_Event::");
		printPriQ_Event(&priQ_Event);//����Ʈ�� ���
		printf("\n");
		printf("Events processed: \n ");
		
		count = 0;
		numEventProcessed = thrdMon.totalEventProcessed;//��ü������ ó���� �̺�Ʈ ��
		for (int i = 0; i < numEventProcessed; i++)//�̺�Ʈ ó��
		{
			pEv = &thrdMon.eventProcessed[i];//ó���� �̺�Ʈ
			if (pEv != NULL)
			{
				calc_elapsed_time(pEv, freq);//ó���Ƚð�-�����Ƚð�
				printEvent_withTime(pEv);//�ɸ��ð��� �Բ� �̺�Ʈ���
				if (((i + 1) % EVENT_PER_LINE) == 0)//���ٿ� 5�������
					printf("\n ");
			}
		}
		printf("\n ");
		
		if (numEventProcessed >= TOTAL_NUM_EVENTS)//ó���� �Ϸ�Ǿ�����
		{
			eventThreadFlag = TERMINATE;//������ ����
			break;
		}
		Sleep(100);
	}
	double min, max, avg, sum;
	int min_ev, max_ev;
	min = max = sum = thrdMon.eventProcessed[0].elap_time;//�ִ��ּ���հ��� �ʱⰪ���� ����
	min_ev = max_ev = 0;
	
	for (int i = 1; i < TOTAL_NUM_EVENTS; i++)
	{
		sum += thrdMon.eventProcessed[i].elap_time;//ó���� ���ð� ������
		if (min > thrdMon.eventProcessed[i].elap_time)//�ʱ⼳���� �ּҰ����� �� �������� �������
		{
			min = thrdMon.eventProcessed[i].elap_time;//�װ��� �ּڰ�
			min_ev = i;
		}
		if (max < thrdMon.eventProcessed[i].elap_time)//�ʱ⼳���� �ִ밪���� �� ū ���� ������� 
		{
			max = thrdMon.eventProcessed[i].elap_time;//�װ��� �ִ밪
			max_ev = i;
		}
	}
	avg = sum / TOTAL_NUM_EVENTS;//�ɸ��ð��� ��հ����
	printf("Minimum event processing time: %8.2lf[ms] for ", min * 1000);//�ּҽð� �ɸ��̺�Ʈ
	printEvent_withTime(&thrdMon.eventProcessed[min_ev]); printf("\n");//�ð��� �̺�Ʈ���
	printf("Maximum event processing time: %8.2lf[ms] for ", max * 1000);//�ִ�ð� �ɸ��̺�Ʈ
	printEvent_withTime(&thrdMon.eventProcessed[max_ev]); printf("\n");//�ð��� �̺�Ʈ ���
	printf("Average event processing time: %8.2lf[ms] for total %d events\n", avg * 1000,TOTAL_NUM_EVENTS);//�̺�Ʈ ó���ð��� ���
	printf("\n");

	thrd_ev_generator.join();//������ ���ᰡ�ɶ����� ��ٸ�
	printf("Thread_EventGenerator is terminated !!\n");
	thrd_ev_handler.join();//ó���� ������������ٸ�
	printf("Thread_EventHandler is terminated !!\n");
}