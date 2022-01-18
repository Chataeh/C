#ifndef C_H
#define C_H
#include"Event.h"

typedef struct {
	Event* CirBuff_Ev;
	int capacity;//용량
	int front;//처음
	int end;//마지막
	int num_elements;
}CirQ_Event;

CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity);//환영큐공간 초기화
bool isCirQFull(CirQ_Event* pCirQ);//환영 큐공간이 가득찼는지 판별
bool isCirQEmpty(CirQ_Event* pCirQ);//환영 큐 공간이 비어있는지 판별
void printCirQ_Event(CirQ_Event* CirQ);//이벤트 출력
void fprintCirQ_Event(FILE* fout, CirQ_Event* CirQ);//파일에 이벤트 출력
Event* enCirQ(CirQ_Event* CirQ, Event ev);//이벤트추가
Event* deCirQ(CirQ_Event* CirQ);//이벤트 추출
void delCirQ(CirQ_Event* CirQ);//초기화

#endif // !C_H
