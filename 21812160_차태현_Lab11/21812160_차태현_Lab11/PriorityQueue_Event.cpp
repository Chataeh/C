#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"PriorityQueue_Event.h"
#include"Event.h"

bool hasLeftchild(int pos, PriQ_Event* pPriQ_Ev)//왼쪽자식이 있는지 판별
{
	if (pos * 2 <= pPriQ_Ev->num_entry)//왼쪽자식은 pos*2
		return TRUE;
	else
		return FALSE;
}

bool hasRightchild(int pos, PriQ_Event* pPriQ_Ev)//오른쪽자식이 있는지 판별
{
	if (pos * 2+1 <= pPriQ_Ev->num_entry)//오른쪽자식은 pos*2+1
		return TRUE;
	else
		return FALSE;
}

PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Ev,const char* name, int capacity = 1)//우선순위 큐 초기화
{
	strcpy(pPriQ_Ev->name, name);
	pPriQ_Ev->capacity = capacity;
	pPriQ_Ev->pCBT_Event = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event));//1번부터 배치하기때문에 용량+1
	pPriQ_Ev->num_entry = 0;
	pPriQ_Ev->pos_last = 0;

	return pPriQ_Ev;
}

void deletePriQ_Event(PriQ_Event* pPriQ_Ev)//동적메모리 반환
{
	CBTN_Event* pCBTN_Ev;
	for (int i = 0; i < pPriQ_Ev->num_entry; i++)
	{
		pCBTN_Ev = &pPriQ_Ev->pCBT_Event[i];
		if (pCBTN_Ev != NULL)//이벤트를 저장하는 메모리가있을시
		{
			if(pCBTN_Ev->pEvent != NULL)//이벤트자체가 저장되어있는 메모리가 있을시
				free(pCBTN_Ev->pEvent);//동적반환
			free(pCBTN_Ev);//동적반환
		}
	}
}

void insertPriQ_Event(PriQ_Event* pPriQ_Ev, Event* pEv)//새로운 노드추가
{
	int pos, pos_parent;
	CBTN_Event CBTN_Ev_tmp;

	if (pPriQ_Ev->num_entry >= pPriQ_Ev->capacity)//우선순위 큐가가득찼을시
	{
		CBTN_Event* newCBT_Event;
		int newcapcity;

		newcapcity = 2 * pPriQ_Ev->capacity;//새로운 용량
		newCBT_Event = (CBTN_Event*)malloc((newcapcity + 1) * sizeof(CBTN_Event));//1번부터 배치하기때문에 용량+1

		for (int pos = 1; pos <= pPriQ_Ev->num_entry; pos++)
		{
			newCBT_Event[pos] = pPriQ_Ev->pCBT_Event[pos];//기존값들을 복사해줌
		}
		free(pPriQ_Ev->pCBT_Event);//이전에 사용했던 동적메모리 반환
		pPriQ_Ev->pCBT_Event = newCBT_Event;//새로운값으로 설정
		pPriQ_Ev->capacity = newcapcity;//용량설정
	}

	pos = ++pPriQ_Ev->num_entry;
	pPriQ_Ev->pCBT_Event[pos].priority = pEv->event_pri;//새로운 노드에추가
	pPriQ_Ev->pCBT_Event[pos].pEvent = pEv;//새로운 노드값추가

	while (pos != POS_ROOT)//root값이 아닐때 까지
	{
		pos_parent = pos / 2;//부모노드 인덱스=자식노드 인덱스/2
		if (pPriQ_Ev->pCBT_Event[pos].priority >= pPriQ_Ev->pCBT_Event[pos_parent].priority)//부모노드와 자식노드 우선순위 비교 
			break;
		else
		{
			CBTN_Ev_tmp = pPriQ_Ev->pCBT_Event[pos_parent];//up-heap bubbling에 의한 위치변환
			pPriQ_Ev->pCBT_Event[pos_parent] = pPriQ_Ev->pCBT_Event[pos];
			pPriQ_Ev->pCBT_Event[pos] = CBTN_Ev_tmp;
			pos = pos_parent;
		}
	}
	
}


Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Ev)//우선순위가 높은값을 추출후 재조정
{
	Event* pEv;
	CBTN_Event CBT_Event_tmp;
	int pos, pos_root = 1, pos_last, pos_child;

	if (pPriQ_Ev->num_entry <= 0)//비어있으면 반환할게없음
		return NULL;

	pEv = pPriQ_Ev->pCBT_Event[1].pEvent;//우선순위가 가장높은 이벤트 저장(반환할 노드)
	pos_last = pPriQ_Ev->num_entry;//노드 수가 마지막노드위치
	--pPriQ_Ev->num_entry;//마지막 노드가 루트노드로 가면서 수가 줄어듦

	if (pPriQ_Ev->num_entry > 0)
	{
		pPriQ_Ev->pCBT_Event[pos_root] = pPriQ_Ev->pCBT_Event[pos_last];//마지막노드를 루트위치로 대입
		pos_last--;


		pos = pos_root;
		while (hasLeftchild(pos, pPriQ_Ev))//왼쪽자식이 있으면
		{
			pos_child = pos * 2;//왼쪽 자식
			if (hasRightchild(pos, pPriQ_Ev))//오른쪽 자식도 있는경우 
			{
				if (pPriQ_Ev->pCBT_Event[pos_child].priority > pPriQ_Ev->pCBT_Event[pos_child + 1].priority)//오른쪽 자식의 우선순위가 높을경우
					pos_child = pos * 2 + 1;//오른쪽 자식의 우선순위가 더 높다
			}
			if (pPriQ_Ev->pCBT_Event[pos_child].priority < pPriQ_Ev->pCBT_Event[pos].priority)//자식의 우선순위가 더 높은경우
			{
				CBT_Event_tmp = pPriQ_Ev->pCBT_Event[pos];//down-heap bubbling에 의한 위치변환
				pPriQ_Ev->pCBT_Event[pos] = pPriQ_Ev->pCBT_Event[pos_child];
				pPriQ_Ev->pCBT_Event[pos_child] = CBT_Event_tmp;
			}
			else
				break;
			pos = pos_child;
		}
	}
	return pEv;
}

void fprintPriQ_Event(FILE* fout, PriQ_Event* pPriQ_Event)
{
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;

	if (pPriQ_Event->num_entry == 0)//원소의 개수가 0일시
	{
		fprintf(fout, "PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;

	fprintf(fout, "\n CompBinTree :\n", level);
	while (count <= pPriQ_Event->num_entry)
	{
		fprintf(fout, " level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count)
		{
			pEv = pPriQ_Event->pCBT_Event[pos].pEvent;//포지션 위치의 이벤트값 입력
			eventPriority = pPriQ_Event->pCBT_Event[pos].priority;//우선순위 설정
			fprintEvent(fout, pEv);//이벤트 출력
			pos++;
			count++;
			if (count > pPriQ_Event->num_entry)//원소의 개수보다 큰경우 출력끝
				break;
			count_per_line++;
			if ((count_per_line % EVENT_PER_LINE) == 0)//한줄에 5개 출력
			{
				if (count_per_line < level_count)
					fprintf(fout, "\n ");
				else
					fprintf(fout, "\n");
			}
		}
		if ((count_per_line % EVENT_PER_LINE) != 0)
			fprintf(fout, "\n");
		level++;
		level_count *= 2;
	}
	fprintf(fout, "\n");
}

void printPriQ_Event(PriQ_Event* pPriQ_Event)
{
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;

	if (pPriQ_Event->num_entry == 0)//원소의 개수가 0일시
	{
		printf("PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;

	printf("\n CompBinTree :\n", level);
	while (count <= pPriQ_Event->num_entry)
	{
		printf(" level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count)
		{
			pEv = pPriQ_Event->pCBT_Event[pos].pEvent;//포지션 위치의 이벤트값 입력
			eventPriority = pPriQ_Event->pCBT_Event[pos].priority;//우선순위 설정
			printEvent(pEv);//이벤트 출력
			pos++;
			count++;
			if (count > pPriQ_Event->num_entry)//원소의 개수보다 큰경우 출력끝
				break;
			count_per_line++;
			if ((count_per_line % EVENT_PER_LINE) == 0)//한줄에 5개 출력
			{
				if (count_per_line < level_count)
					printf("\n ");
				else
					printf("\n");
			}
		}
		if ((count_per_line % EVENT_PER_LINE) != 0)
			printf("\n");
		level++;
		level_count *= 2;
	}
	printf("\n");
}

