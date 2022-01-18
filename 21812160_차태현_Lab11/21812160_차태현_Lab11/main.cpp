/**
*파일이름"21812160_차태현_homework12”
*프로그램의 목적 및 기본 기능:
*  환형큐와 우선순위큐의 실행.
*
*프로그램 작성자: 21812160 차태현(2021년 5월21일),
*최종 수정 및 보완: 2021년 5월 21일 (차태현)
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

	fout = fopen("output.txt", "w");//쓰기모드로 파일열기
	while (1)
	{
		printf("\nAvailable Menu : \n");
		printf(" 1. Test FIFO/CirQ Event.\n");
		printf(" 2. Test PriQ Event.\n");
		printf("Input menu (0 to quit) : ");
		scanf("%d", &num);//처리할 이벤트 개수 받기
		if (num == 0)
			break;
		printf("Input num_events per round :");
		scanf("%d", &max_events_per_round);//round 지정
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
	int total_processed_events = 0;//처리된 이벤트 개수
	int total_generated_events = 0;//생성된 이벤트 개수
	int num_events = 0;
	int num_generated_round = 0;//라운드마다의 생성된 이벤트
	int num_processed_round = 0;//라운드마다의 처리된 이벤트

	fprintf(fout, "Testing Event Handling with FIFO Circular Queue\n");
	pCirQ_Event = (CirQ_Event*)calloc(1, sizeof(CirQ_Event));//동적할당
	printf("Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);
	fprintf(fout, "Initializing FIFO_CirQ of capacity (%d)\n", max_events_per_round);
	pCirQ_Event = initCirQ(pCirQ_Event, max_events_per_round);//환영큐 초기화

	for (int round = 0; round < MAX_ROUND; round++)
	{
		fprintf(fout, "start of Round(%2d) ****\n", round);
		if (total_generated_events < TOTAL_NUM_EVENTS)
		{
			num_events = max_events_per_round;//이벤트 생성시킬 개수
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS)
				num_events = TOTAL_NUM_EVENTS - total_generated_events;//남은개수만 생성
			fprintf(fout, "generate and enque %2d events\n", num_events);
			num_generated_round = 0;
			for (int i = 0; i < num_events; i++)
			{
				if (isCirQFull(pCirQ_Event))//환영큐 공간이 가득찼을시 
				{
					fprintf(fout, " !!! CirQ_Event is full --> skip generation and enqueueing ofevent. \n");
					break;
				}
				pEv = genEvent(pEv, EVENT_GENERATOR, total_generated_events,TOTAL_NUM_EVENTS - total_generated_events - 1);//이벤트 생성
				fprintf(fout, ">>> Enqueue event = ");
				fprintEvent(fout, pEv);//event_no,event_pri 파일에 출력
				fprintf(fout, "\n");
				enCirQ(pCirQ_Event, *pEv);//구조체 추가
				fprintCirQ_Event(fout, pCirQ_Event);
				free(pEv);//동적메모리 반환
				total_generated_events++;//생성된 이벤트개수
				num_generated_round++;
			}
		}
		num_events = max_events_per_round;//한번에 처리할 개수
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS)
			num_events = TOTAL_NUM_EVENTS - total_processed_events;//남은 개수만 처리
		fprintf(fout, "dequeue %2d events\n", num_events);
		num_processed_round = 0;
		for (int i = 0; i < num_events; i++)
		{
			if (isCirQEmpty(pCirQ_Event))//환영큐 공간이 비었을시 
				break;
			pEv = deCirQ(pCirQ_Event);//구조체 내보내기
			if (pEv != NULL)//구조체가 존재할시
			{
				fprintf(fout, "<<< Dequed event = ");
				fprintEvent(fout, pEv);
				fprintf(fout, "\n");
				processed_events[total_processed_events] = *pEv;//배열에 이벤트 저장
				total_processed_events++;//처리된 이벤트개수 증가
				num_processed_round++;//라운드 처리된 이벤트 개수 증가
			}
			fprintCirQ_Event(fout, pCirQ_Event);
		} 
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d),	processed_in_this_round(% 3d), total_processed_events(% 3d),	events_in_queue(% 3d)\n\n", round, num_generated_round, total_generated_events,	num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d),processed_in_this_round(% 3d), total_processed_events(% 3d),	events_in_queue(% 3d)\n", round, num_generated_round, total_generated_events,num_processed_round, total_processed_events, pCirQ_Event->num_elements);
		if (total_processed_events >= TOTAL_NUM_EVENTS)//다 실행했을시
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
	delCirQ(pCirQ_Event);//0으로 초기화
}

void test_PriQ_Event(FILE* fout, int max_events_per_round)
{
	PriQ_Event* pPriQ_Ev;
	Event* pEv = NULL;
	Event processed_events[TOTAL_NUM_EVENTS];
	int total_processed_events = 0;//처리된 이벤트
	int total_generated_events = 0;//생성된 이벤트
	int num_events = 0;
	int num_generated_round = 0;//라운드마다의 생성된 이벤트
	int num_processed_round = 0;//라운드마다의 처리된 이벤트

	fprintf(fout, "Testing Event Handling with Priority Queue\n");
	pPriQ_Ev = (PriQ_Event*)malloc(sizeof(PriQ_Event));//동적 메모리 생성

	printf("Initializing PriorityQueue_Event of capacity (%d)\n", INIT_PriQ_SIZE);
	initPriQ_Event(pPriQ_Ev, "PriorityQueue_Event", INIT_PriQ_SIZE);//우선순위 큐 초기화

	for (int round = 0; round < MAX_ROUND; round++)
	{
		
		fprintf(fout, "\n*** Start of round(%2d)...\n", round);
		if (total_generated_events < TOTAL_NUM_EVENTS)
		{
			num_events = max_events_per_round;//처리할 이벤트 값 설정
			if ((total_generated_events + num_events) > TOTAL_NUM_EVENTS)
				num_events = TOTAL_NUM_EVENTS - total_generated_events;//최대값 초과시 남아있는 이벤트만 처리
			fprintf(fout, ">>> enque %2d events\n", num_events);
			num_generated_round = 0;
			for (int i = 0; i < num_events; i++)
			{
				pEv = genEvent(pEv, 0, total_generated_events, TOTAL_NUM_EVENTS - total_generated_events - 1);//이벤트 값 설정

				fprintf(fout, " *** enqued event : ");
				fprintEvent(fout, pEv);
				insertPriQ_Event(pPriQ_Ev, pEv);//이벤트를 추가함
				total_generated_events++;
				num_generated_round++;
				fprintPriQ_Event(fout, pPriQ_Ev);
			}
		}
		num_events = max_events_per_round;//처리할 이벤트 값 설정
		if ((total_processed_events + num_events) > TOTAL_NUM_EVENTS)//최대값 초과시 남아있는 이벤트만 처리
			num_events = TOTAL_NUM_EVENTS - total_processed_events;
		fprintf(fout, "<<< dequeue %2d events\n", num_events);
		num_processed_round = 0;
		for (int i = 0; i < num_events; i++)
		{
			pEv = removeMinPriQ_Event(pPriQ_Ev);//이벤트 추출
			if (pEv == NULL)//비어있다면
			{
				fprintf(fout, " PriQ is empty\n");
				break;
			}
			fprintf(fout, " *** dequeued event : ");
			fprintEvent(fout, pEv);
			fprintPriQ_Event(fout, pPriQ_Ev);
			processed_events[total_processed_events] = *pEv;
			total_processed_events++;//처리된 이벤트 증가
			num_processed_round++;//라운드에서 처리된 이벤트 증가
		}
		fprintf(fout, "Round(%2d): generated_in_this_round(%3d), total_generated_events(%3d),processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n\n", round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pPriQ_Ev->num_entry);
		printf("Round(%2d): generated_in_this_round(%3d), total_generated(%3d),processed_in_this_round(% 3d), total_processed_events(% 3d), events_in_queue(% 3d)\n", round, num_generated_round, total_generated_events, num_processed_round, total_processed_events, pPriQ_Ev->num_entry);
		fflush(fout);//버퍼에 있던것 전달
		if (total_processed_events >= TOTAL_NUM_EVENTS)//처리한 이벤트가 전체이벤트와 같거나 크면
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