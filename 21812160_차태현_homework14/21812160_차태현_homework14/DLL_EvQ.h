#pragma once
#ifndef DLL_EvQ_H
#define DLL_EvQ_H
#include <Windows.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include "Event.h"
using namespace std;
// doubly linked list node (DLLN)
typedef struct DLLN
{
	struct DLLN* prev;//이전 데이터 주소
	struct DLLN* next;//다음 데이터주소
	Event* pEv;//이벤트
} DLLN_Ev;
typedef struct
{
	mutex cs_EvQ;//임계구역
	int priority;
	DLLN_Ev* front;//시작 데이터 주소
	DLLN_Ev* back;//마지막 데이터 주소
	int num_event;//이벤트수
} DLL_EvQ;
void initDLL_EvQ(DLL_EvQ* DLL_EvQ, int priority);//연결리스트 큐 초기화
Event* enDLL_EvQ(DLL_EvQ* DLL_EvQ, Event* pEv);//인큐
Event* deDLL_EvQ(DLL_EvQ* DLL_EvQ);//디큐
void printDLL_EvQ(DLL_EvQ* DLL_EvQ);//출력
void fprintDLL_EvQ(FILE* fout, DLL_EvQ* pEvQ);//파일에출력
#endif