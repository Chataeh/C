/**
*�����̸�"21812160_������_homework12��
*���α׷��� ���� �� �⺻ ���:
*  ȯ��ť�� �켱����ť�� ����.
*
*���α׷� �ۼ���: 21812160 ������(2021�� 5��21��),
*���� ���� �� ����: 2021�� 5�� 21�� (������)
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Event.h"
#include"CirQ_Event.h"
#include"PriorityQueue_Event.h"

#define EVENT_GENERATOR 0
#define TOTAL_NUM_EVENTS 128
#define MAX_ROUND 100
#define INIT_PriQ_SIZE 1

void test_FIFO_CirQ_Event(FILE* fout, int max_events_per_round);
void test_PriQ_Event(FILE* fout, int max_events_per_round);

void main()
{
	FILE* fout;
	int num;
	int max_events_per_round;

	fout = fopen("output.txt", "w");//������� ���Ͽ���
	while (1)
	{
		printf("\nAvailable Menu : \n");
		printf(" 1. Test FIFO/CirQ Event.\n");
		printf(" 2. Test PriQ Event.\n");
		printf("Input menu (0 to quit) : ");
		scanf("%d", &num);//ó���� �̺�Ʈ ���� �ޱ�
		if (num == 0)
			break;
		printf("Input num_events per round :");
		scanf("%d", &max_events_per_round);//round ����
		switch (num)
		{
		case 1:
			test_FIFO_CirQ_Event(fout, max_events_per_round);
			break;
		case 2:
			test_PriQ_Event(fout, max_events_per_round);
			break;
		default:
			break;
		}
	}
	fclose(fout);
}

void test_FIFO_CirQ_Event(FILE* fout, int max_events_per_round)
{
	CirQ_Event* pCirQ_Event;
	Event ev, * pEv = NULL;
	Event processed_events[TOTAL_NUM_EVENTS];
	int total_processed_events = 0;//ó���� �̺�Ʈ ����
	int total_generated_events = 0;//������ �̺�Ʈ ����
	int num_events = 0;
	int num_generated_round = 0;//���帶���� ������ �̺�Ʈ
	int num_processed_round = 0;//���帶���� ó���� �̺�Ʈ

	fprintf(fout, "Testing Event Handling with FIFO Circular Queue\n");
	pCirQ_Event = (CirQ_Event*)calloc(1, sizeof(CirQ_Event));//�����Ҵ�
	printf("Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);
	fprintf(fout, "Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);
	pCirQ_Event = initCirQ(pCirQ_Event, max_events_per_round);//ȯ��ť �ʱ�ȭ

	for (int round = 0; round < MAX_ROUND; round++)
	{
		fprintf(fout, "start of Round(%2d) ****\n", round);
		if (total_generated_events < TOTAL_NUM_EVENTS)
		{
			num_events = max_events_per_round;//�̺�Ʈ ������ų ����
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS)
				num_events = TOTAL_NUM_EVENTS - total_generated_events;//���������� ����
			fprintf(fout, "generate and enque %2d events\n", num_events);
			num_generated_round = 0;
			for (int i = 0; i < num_events; i++)
			{
				if (isCirQFull(pCirQ_Event))//ȯ��ť ������ ����á���� 
				{
					fprintf(fout, " !!! CirQ_Event is full --> skip generation and enqueueing ofevent. \n");
					break;
				}
				pEv = genEvent(pEv, EVENT_GENERATOR, total_generated_events,TOTAL_NUM_EVENTS - total_generated_events - 1);//�̺�Ʈ ����
				fprintf(fout, ">>> Enqueue event = ");
				fprintEvent(fout, pEv);//event_no,event_pri ���Ͽ� ���
				fprintf(fout, "\n");
				enCirQ(pCirQ_Event, *pEv);//����ü �߰�
				fprintCirQ_Event(fout, pCirQ_Event);
				free(pEv);//�����޸� ��ȯ
				total_generated_events++;//������ �̺�Ʈ����
				num_generated_round++;
			}
		}
		num_events = max_events_per_round;//�ѹ��� ó���� ����
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS)
			num_events = TOTAL_NUM_EVENTS - total_processed_events;//���� ������ ó��
		fprintf(fout, "dequeue %2d events\n", num_events);
		num_processed_round = 0;
		for (int i = 0; i < num_events; i++)
		{
			if (isCirQEmpty(pCirQ_Event))//ȯ��ť ������ ������� 
				break;
			pEv = deCirQ(pCirQ_Event);//����ü ��������
			if (pEv != NULL)//����ü�� �����ҽ�
			{
				fprintf(fout, "<<< Dequed event = ");
				fprintEvent(fout, pEv);
				fprintf(fout, "\n");
				processed_events[total_processed_events] = *pEv;//�迭�� �̺�Ʈ ����
				total_processed_events++;//ó���� �̺�Ʈ���� ����
				num_processed_round++;//���� ó���� �̺�Ʈ ���� ����
			}
			fprintCirQ_Event(fout, pCirQ_Event);
		} 
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d),	processed_in_this_round(% 3d), total_processed_events(% 3d),	events_in_queue(% 3d)\n\n", round, num_generated_round, total_generated_events,	num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d),processed_in_this_round(% 3d), total_processed_events(% 3d),	events_in_queue(% 3d)\n", round, num_generated_round, total_generated_events,num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		if (total_processed_events >= TOTAL_NUM_EVENTS)//�� ����������
			break;
	} 
	printf("Processed Events :\n");
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++)
	{
		printf("Ev(id:%3d, pri:%3d), ", processed_events[i].event_no,processed_events[i].event_pri);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
	delCirQ(pCirQ_Event);//0���� �ʱ�ȭ
}

void test_PriQ_Event(FILE* fout, int max_events_per_round)
{
	PriQ_Event* pPriQ_Ev;
	Event* pEv = NULL;
	Event processed_events[TOTAL_NUM_EVENTS];
	int total_processed_events = 0;//ó���� �̺�Ʈ
	int total_generated_events = 0;//������ �̺�Ʈ
	int num_events = 0;
	int num_generated_round = 0;//���帶���� ������ �̺�Ʈ
	int num_processed_round = 0;//���帶���� ó���� �̺�Ʈ

	fprintf(fout, "Testing Event Handling with Priority Queue\n");
	pPriQ_Ev = (PriQ_Event*)malloc(sizeof(PriQ_Event));//���� �޸� ����

	printf("Initializing PriorityQueue_Event of capacity (%d)\n", INIT_PriQ_SIZE);
	initPriQ_Event(pPriQ_Ev, "PriorityQueue_Event", INIT_PriQ_SIZE);//�켱���� ť �ʱ�ȭ

	for (int round = 0; round < MAX_ROUND; round++)
	{
		
		fprintf(fout, "\n*** Start of round(%2d)...\n", round);
		if (total_generated_events < TOTAL_NUM_EVENTS)
		{
			num_events = max_events_per_round;//ó���� �̺�Ʈ �� ����
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS)
				num_events = TOTAL_NUM_EVENTS - total_generated_events;//�ִ밪 �ʰ��� �����ִ� �̺�Ʈ�� ó��
			fprintf(fout, ">>> enque %2d events\n", num_events);
			num_generated_round = 0;
			for (int i = 0; i < num_events; i++)
			{
				pEv = genEvent(pEv, 0, total_generated_events, TOTAL_NUM_EVENTS - total_generated_events - 1);//�̺�Ʈ �� ����

				fprintf(fout, " *** enqued event : ");
				fprintEvent(fout, pEv);
				insertPriQ_Event(pPriQ_Ev, pEv);//�̺�Ʈ�� �߰���
				total_generated_events++;
				num_generated_round++;
				fprintPriQ_Event(fout, pPriQ_Ev);
			}
		}
		num_events = max_events_per_round;//ó���� �̺�Ʈ �� ����
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS)//�ִ밪 �ʰ��� �����ִ� �̺�Ʈ�� ó��
			num_events = TOTAL_NUM_EVENTS - total_processed_events;
		fprintf(fout, "<<< dequeue %2d events\n", num_events);
		num_processed_round = 0;
		for (int i = 0; i < num_events; i++)
		{
			pEv = removeMinPriQ_Event(pPriQ_Ev);//�̺�Ʈ ����
			if (pEv == NULL)//����ִٸ�
			{
				fprintf(fout, " PriQ is empty\n");
				break;
			}
			fprintf(fout, " *** dequeued event : ");
			fprintEvent(fout, pEv);
			fprintPriQ_Event(fout, pPriQ_Ev);
			processed_events[total_processed_events] = *pEv;
			total_processed_events++;//ó���� �̺�Ʈ ����
			num_processed_round++;//���忡�� ó���� �̺�Ʈ ����
		}
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d),processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n\n", round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pPriQ_Ev->num_entry);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d),processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n", round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pPriQ_Ev->num_entry);
		fflush(fout);//���ۿ� �ִ��� ����
		if (total_processed_events >= TOTAL_NUM_EVENTS)//ó���� �̺�Ʈ�� ��ü�̺�Ʈ�� ���ų� ũ��
			break;
	}
	printf("Processed Events :\n");
	for (int i = 0; i < TOTAL_NUM_EVENTS; i++)
	{
		printf("Ev(id:%3d, pri:%3d), ", processed_events[i].event_no, processed_events[i].event_pri);
		if ((i + 1) % 5 == 0)
			printf("\n");
	}
	printf("\n");
	deletePriQ_Event(pPriQ_Ev);
	fprintf(fout, "\n");
}