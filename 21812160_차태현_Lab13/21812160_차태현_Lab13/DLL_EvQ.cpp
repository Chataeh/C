#include "DLL_EvQ.h"
void initDLL_EvQ(DLL_EvQ* pEvQ, int pri)//연결리스트 큐 초기화
{
	pEvQ->cs_EvQ.lock();//임계구역
	pEvQ->priority = pri;
	pEvQ->front = pEvQ->back = NULL;//처음과 마지막 데이터주소 NULL로 초기화
	pEvQ->num_event = 0;//이벤트수 0으로 초기화
	pEvQ->cs_EvQ.unlock();//임계구역
}

Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv)//인큐 이벤트 생성
{
	DLLN_Ev* pLN_Ev;
	if (pEv == NULL)
	{
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev));//동적메모리 생성
	if (pLN_Ev == NULL)
	{
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev->pEv = pEv;//데이터 받기
	pEvQ->cs_EvQ.lock();//임계구역 생성
	if (pEvQ->num_event == 0) //연결리스트 큐가 비어있다면
	{
		pEvQ->front = pEvQ->back = pLN_Ev;//처음과 끝은 넣어준 이벤트와 같음 이벤트가 하나뿐이기때문
		pLN_Ev->prev = pLN_Ev->next = NULL;//생성된 이벤트의 이전이벤트와 이후 이벤트는 없음으로 NULL
		pEvQ->num_event = 1;//방금 생성된 이벤트 뿐
	}
	else
	{
		pLN_Ev->prev = pEvQ->back;//마지막자리 뒤에 인큐되므로 인큐된 이벤트앞의 이벤트는 원래의 마지막이벤트
		pEvQ->back->next = pLN_Ev;//원래 마지막이벤트의 다음위치로 인큐됨
		pEvQ->back = pLN_Ev;//마지막 이벤트가 방금 인큐해준 이벤트가 됨
		pLN_Ev->next = NULL;//마지막 이벤트 다음이벤트는 없음
		pEvQ->num_event++;//이벤트 수 추가
	}
	pEvQ->cs_EvQ.unlock();//임계구역
	return pLN_Ev->pEv;
}

Event* deDLL_EvQ(DLL_EvQ* pEvQ)//디큐 이벤트추출
{
	Event* pEv;
	DLLN_Ev* pLN_Ev_OldFront;
	pEvQ->cs_EvQ.lock();//임계구역 설정
	if (pEvQ->num_event <= 0)//큐공간에 아무것도 없을경우
	{
		pEvQ->cs_EvQ.unlock();//공간이 비었을경우 종료되기때문에 임계구역을 설정해줘야함
		return NULL; // DLL_EvQ is Empty
	}
	else
	{
		pLN_Ev_OldFront = pEvQ->front;
		pEv = pEvQ->front->pEv;//처음위치부터 추출하기때문에 이벤트를 pEv에 저장
		pEvQ->front = pEvQ->front->next;//처음위치의 다음위치의 이벤트가 처음이벤트로 됨
		if (pEvQ->front != NULL)//처음위치에 이벤트가 있을경우
			pEvQ->front->prev = NULL;
		pEvQ->num_event--;//디큐 후 총 이벤트 수는 줄어듬
		free(pLN_Ev_OldFront); // release memory for the current front DLLN
		pEvQ->cs_EvQ.unlock();//임계구역
		return pEv;
	}
}
void printDLL_EvQ(DLL_EvQ* pEvQ)//출력
{
	int index = 0;
	int count;
	Event* pEv;
	DLLN_Ev* pLN_Ev;
	if (pEvQ == NULL)//출력할것이 없을경우
	{
		printf("Error in printDLL_EvQ :: DLL_EvQ is NULL !!");
		printf("Press any key to continue ...\n");
		getc(stdin);
	}
	//printf("DLL_EvQ(num_event: %2d):\n ", pEvQ->num_event);
	if (pEvQ->num_event <= 0)
		return;
	pLN_Ev = pEvQ->front;
	count = 0;
	while (pLN_Ev != NULL)//큐의 첫번째 자리가 있는경우
	{
		pEv = pLN_Ev->pEv;
		if (pEv == NULL)
			break;
		printEvent(pEv); printf(" ");
		count++;
		if ((count % 5) == 0)
			printf("\n ");
		pLN_Ev = pLN_Ev->next;//다음위치가 첫번째 위치가됨
	}
}