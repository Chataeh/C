#include"PriQ_Event.h"
#include "Event.h"


bool hasLeftChild(int pos, PriQ_Event* pPriQ_Event)// 왼쪽자식 존재여부
{
	if (pos * 2 <= pPriQ_Event->priQ_size)//왼쪽자식= pos*2
		return TRUE;
	else
		return FALSE;
}
bool hasRightChild(int pos, PriQ_Event* pPriQ_Event)//오른쪽자식 존재여부
{
	if (pos * 2 + 1 <= pPriQ_Event->priQ_size)//오른쪽자식 = pos*2+1
		return TRUE;
	else
		return FALSE;
}

PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Event, const char* name, int capacity)//큐 생성
{
	pPriQ_Event->cs_PriQ.lock();//스레드 실행할때 하나의 스레드만 동작하게 하기위함
	strcpy(pPriQ_Event->PriQ_name, name);//이름입력
	pPriQ_Event->priQ_capacity = capacity;//용량 입력
	pPriQ_Event->pCBT_Event = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event));//1부터시작하기위해 용량+1 동적메모리생성
	pPriQ_Event->priQ_size = 0;
	pPriQ_Event->pos_last = 0;
	pPriQ_Event->cs_PriQ.unlock();//스레드 실행할때 하나의 스레드만 동작하게 하기위함
	
	return pPriQ_Event;
}

void deletePriQ_Event(PriQ_Event* pPriQ_Event)//큐공간 반환
{
	pPriQ_Event->cs_PriQ.lock();//스레드 실행할때 하나의 스레드만 동작하게 하기위함
	if (pPriQ_Event->pCBT_Event != NULL)//큐공간이 있을경우
		free(pPriQ_Event->pCBT_Event);//메모리반환	
	pPriQ_Event->cs_PriQ.unlock();//스레드 실행할때 하나의 스레드만 동작하게 하기위함
}
Event* enPriQ_Event(PriQ_Event* pPriQ_Event, Event ev)//이벤트 추가
{
	int pos, pos_parent;
	CBTN_Event CBTN_Ev_tmp;

	pPriQ_Event->cs_PriQ.lock();//스레드 실행할때 하나의 스레드만 동작하게 하기위함
	if (pPriQ_Event->priQ_size >= pPriQ_Event->priQ_capacity)//우선순위 큐가가득찼을시
	{
		CBTN_Event* newCBT_Event;
		int newcapcity;

		newcapcity = 2 * pPriQ_Event->priQ_capacity;//새로운 용량
		newCBT_Event = (CBTN_Event*)malloc((newcapcity + 1) * sizeof(CBTN_Event));//1번부터 배치하기때문에 용량+1

		for (int pos = 1; pos <= pPriQ_Event->priQ_size;pos++)
		{
			newCBT_Event[pos] = pPriQ_Event->pCBT_Event[pos];//기존값들을 복사해줌
		}
		free(pPriQ_Event->pCBT_Event);//이전에 사용했던 동적메모리 반환
		pPriQ_Event->pCBT_Event = newCBT_Event;//새로운값으로 정의
		pPriQ_Event->priQ_capacity = newcapcity;//새로운 용량정의
	}
	pos = ++pPriQ_Event->priQ_size;// 추가된 값의 위치는 size+1
	pPriQ_Event->pCBT_Event[pos].priority = ev.ev_pri;//새로운노드 값정의
	pPriQ_Event->pCBT_Event[pos].event = ev;;

	/*up heap bubbling*/
	while (pos != POS_ROOT)//root노드가 아닐때경우 반복
	{
		pos_parent = pos / 2;//완전2진트리에서 부모노드=자식노드/2
		if (pPriQ_Event->pCBT_Event[pos].priority >= pPriQ_Event->pCBT_Event[pos_parent].priority)//부모노드가 우선순위가 높을시 종료
			break;
		else//자식노드의 우선순위가 더 높은경우
		{
			CBTN_Ev_tmp = pPriQ_Event->pCBT_Event[pos_parent];//부모노드와 자식노드의 위치변환
			pPriQ_Event->pCBT_Event[pos_parent] = pPriQ_Event->pCBT_Event[pos];
			pPriQ_Event->pCBT_Event[pos] = CBTN_Ev_tmp;
			pos = pos_parent;//원래의 위치가 부모노드가 됨
		}
	}
	pPriQ_Event->cs_PriQ.unlock();//스레드 실행할때 하나의 스레드만 동작하게 하기위함
	
	return &(pPriQ_Event->pCBT_Event[pPriQ_Event->pos_last].event);
}

Event* dePriQ_Event(PriQ_Event* pPriQ_Event)//이벤트 추출
{
	Event* pEv, ev;
	CBTN_Event CBTN_Ev_tmp;
	int pos, pos_root = 1, pos_last, pos_child;

	if (pPriQ_Event->priQ_size <= 0)//큐공간이 비어있을경우
		return NULL;

	pPriQ_Event->cs_PriQ.lock();//스레드 실행할때 하나의 스레드만 동작하게 하기위함
	pEv = (Event*)calloc(1, sizeof(Event));//동적할당
	*pEv = pPriQ_Event->pCBT_Event[1].event;//루트노드에있는 값 추출을 위해 주소저장
	pos_last = pPriQ_Event->priQ_size;//노드수가 즉 마지막노드위치
	pPriQ_Event->priQ_size--;//이벤트 추출후 노드 수는 줄어듦

	if (pPriQ_Event->priQ_size > 0)//추출할 노드가 있는경우
	{
		pPriQ_Event->pCBT_Event[pos_root] = pPriQ_Event->pCBT_Event[pos_last];//마지막 위치에있던노드 루트노드위치로 옮김

		pos = pos_root;
		while (hasLeftChild(pos, pPriQ_Event))//왼쪽자식이 있는경우 반복
		{
			pos_child = pos * 2;//왼쪽자식노드 pos*2
			if (hasRightChild(pos, pPriQ_Event))
			{
				if (pPriQ_Event->pCBT_Event[pos_child].priority > pPriQ_Event->pCBT_Event[pos_child + 1].priority)//오른쪽 자식의 우선순위가 더 높다면
					pos_child = pos * 2 + 1; //오른쪽자식의 pos값
			}
			if (pPriQ_Event->pCBT_Event[pos_child].priority >= pPriQ_Event->pCBT_Event[pos].priority)//부모의 우선순위가 더 높다면 정지
				break;
			else//자식의 우선순위가 더 높은경우
			{
				CBTN_Ev_tmp = pPriQ_Event->pCBT_Event[pos];//다운힙 버블링에 의한 위치변환
				pPriQ_Event->pCBT_Event[pos] = pPriQ_Event->pCBT_Event[pos_child];
				pPriQ_Event->pCBT_Event[pos_child] = CBTN_Ev_tmp;
			}
			pos = pos_child;//자식노드가 부모노드가 됨
		}
	}
	pPriQ_Event->cs_PriQ.unlock();//스레드 실행할때 하나의 스레드만 동작하게 하기위함
	return pEv;
}

void printPriQ_Event(PriQ_Event* pPriQ_Event)//이벤트 출력
{
	int pos, count;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;

	if (pPriQ_Event->priQ_size == 0)//추출할 것이 없음 큐가 비었음
	{
		printf(" PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;
	printf("\nCompBinTree:\n ");
	while (count <= pPriQ_Event->priQ_size)//카운트가 사이즈보다 작거나 같을때까지반복
	{
		printf("level%2d :", level);
		for (int i = 0; i < level_count; i++)
		{
			pEv = &(pPriQ_Event->pCBT_Event[pos].event);
			eventPriority = pEv->ev_pri;
			printEvent(pEv);
			if ((count % EVENT_PER_LINE) == 0)//한줄에 5개만출력
				printf("\n ");
					count++;
			if (count > pPriQ_Event->priQ_size)//카운트가 사이즈보다 크면 종료
				break;
		}
		printf("\n");
		level++;//층수 더해짐
		level_count *= 2;//각층은 2의n승개만큼의 노드를 가짐
	}
	printf("\n");
}