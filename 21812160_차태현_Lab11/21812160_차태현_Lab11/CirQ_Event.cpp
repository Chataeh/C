#include<stdio.h>
#include<stdlib.h>
#include"CirQ_Event.h"


CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity)//환영큐공간 초기화
{
	Event* pEv;

	pEv = (Event*)calloc(capacity, sizeof(Event));//동적할당

	pCirQ->CirBuff_Ev = pEv;//동적할당된 pEv를 입력
	pCirQ->capacity = capacity;//용량은 입력한 용량
	pCirQ->front = pCirQ->end = pCirQ->num_elements = 0;//나머지 요소들은 0

	return pCirQ;
}

bool isCirQFull(CirQ_Event* pCirQ)
{
	if (pCirQ->num_elements == pCirQ->capacity)//용량이 다 찼을경우
		return true;
	else
		return false;
}

bool isCirQEmpty(CirQ_Event* pCirQ)
{
	if (pCirQ->num_elements == 0)//용량이 다 비어있는경우
		return true;
	else
		return false;
}

void printCirQ_Event(CirQ_Event* CirQ)
{
	Event ev;
	int index;

	printf(" %2d Elements in CirQ_Event(index_front:%2d):\n", CirQ->num_elements, CirQ->front);
	if (isCirQEmpty(CirQ))
	{
		printf("pCirQ_Event is Empty");
	}
	else
	{
		for (int i = 0; i < CirQ->num_elements; i++)
		{
			index = CirQ->front + i;
			if (index >= CirQ->capacity)
				index = index % CirQ->capacity;//환영이기때문에 공간을 넘어갔을시 앞으로 돌아옴
			ev = CirQ->CirBuff_Ev[index];
			printEvent(&ev);
			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != CirQ->num_elements))//원소가 남아있고 5개를 썻을경우 줄바꿈
				printf("\n   ");

		}
	}
	printf("\n");
}

void fprintCirQ_Event(FILE* fout,CirQ_Event* CirQ)
{
	Event ev;
	int index;

	fprintf(fout," %2d Elements in CirQ_Event(index_front:%2d):\n", CirQ->num_elements, CirQ->front);
	if (isCirQEmpty(CirQ))
	{
		fprintf(fout,"pCirQ_Event is Empty");
	}
	else
	{
		for (int i = 0; i < CirQ->num_elements; i++)
		{
			index = CirQ->front + i;
			if (index >= CirQ->capacity)
				index = index % CirQ->capacity;//환영이기때문에 공간을 넘어갔을시 앞으로 돌아옴
			ev = CirQ->CirBuff_Ev[index];//인덱스 위치의값을 ev에 넣어줌
			fprintEvent(fout,&ev);
			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != CirQ->num_elements))
				fprintf(fout,"\n   ");

		}
	}
	fprintf(fout,"\n");
}

Event* enCirQ(CirQ_Event* CirQ, Event ev)//구조체 추가
{
	if (isCirQFull(CirQ))
	{
		return NULL;
	}
	CirQ->CirBuff_Ev[CirQ->end] = ev;//end위치의 구조체값
	CirQ->num_elements++;//이벤트 수 더하기
	CirQ->end++;//end위치 더하기
	if (CirQ->end >= CirQ->capacity)
		CirQ->end = CirQ->end % CirQ->capacity;//환영이기때문에 계속입력해주어 end값이 용량을 넘어갔을시에 다시 처음으로 돌아옴

	return &(CirQ->CirBuff_Ev[CirQ->end]);
}

Event* deCirQ(CirQ_Event* CirQ)//구조체 내보내기
{
	if (isCirQEmpty(CirQ))
		return NULL;

	Event* pEv = &(CirQ->CirBuff_Ev[CirQ->front]);//front위치의 구조체값 
	CirQ->front++;//front값 더하기
	if (CirQ->front >= CirQ->capacity)
		CirQ->front = CirQ->front % CirQ->capacity;//환영큐기때문에 front값이 용량을 넘어갔을시
	CirQ->num_elements--;//이벤트 수 빼주기

	return pEv;
}

void delCirQ(CirQ_Event* CirQ)//초기화
{
	if (CirQ->CirBuff_Ev != NULL)
		free(CirQ->CirBuff_Ev);//동적할당 반환
	CirQ->CirBuff_Ev = NULL;//NULL로 초기화
	CirQ->capacity = 0;//0으로 초기화
	CirQ->front = CirQ->end = CirQ->num_elements = 0;//0으로 초기화
}