#ifndef P_H
#define P_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Event.h"
#include<mutex>

using namespace std; //mutex 사용위함

#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TURE 1
#define FALSE 0

typedef struct
{
	int priority;
	Event event;
}CBTN_Event; //2진트리

typedef struct
{
	char PriQ_name[MAX_NAME_LEN];//이름
	int priQ_capacity;//큐의 용량
	int priQ_size;//크기
	int pos_last;//마지막 노드위치
	CBTN_Event* pCBT_Event;
	mutex cs_PriQ;
}PriQ_Event;// 우선순위 큐

PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Event, const char* name, int capacity);//큐공간 생성
Event* enPriQ_Event(PriQ_Event* pPriQ_Event, Event ev);//이벤트 추가
Event* dePriQ_Event(PriQ_Event* pPriQ_Event);//이벤트 추출
void printPriQ_Event(PriQ_Event* pPriQ_Event);//이벤트 출력
//void fprintPriQ_Event(FILE* fout, PriQ_Event* pPriQ_Event);//파일에 이벤트출력
void deletePriQ_Event(PriQ_Event* pPriQ_Event);//큐공간 반환

#endif // !P_H
