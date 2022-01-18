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
	struct DLLN* prev;//���� ������ �ּ�
	struct DLLN* next;//���� �������ּ�
	Event* pEv;//�̺�Ʈ
} DLLN_Ev;
typedef struct
{
	mutex cs_EvQ;//�Ӱ豸��
	int priority;
	DLLN_Ev* front;//���� ������ �ּ�
	DLLN_Ev* back;//������ ������ �ּ�
	int num_event;//�̺�Ʈ��
} DLL_EvQ;
void initDLL_EvQ(DLL_EvQ* DLL_EvQ, int priority);//���Ḯ��Ʈ ť �ʱ�ȭ
Event* enDLL_EvQ(DLL_EvQ* DLL_EvQ, Event* pEv);//��ť
Event* deDLL_EvQ(DLL_EvQ* DLL_EvQ);//��ť
void printDLL_EvQ(DLL_EvQ* DLL_EvQ);//���
void fprintDLL_EvQ(FILE* fout, DLL_EvQ* pEvQ);//���Ͽ����
#endif