#ifndef P_H
#define P_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Event.h"
#include<mutex>

using namespace std; //mutex �������

#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TURE 1
#define FALSE 0

typedef struct
{
	int priority;
	Event event;
}CBTN_Event; //2��Ʈ��

typedef struct
{
	char PriQ_name[MAX_NAME_LEN];//�̸�
	int priQ_capacity;//ť�� �뷮
	int priQ_size;//ũ��
	int pos_last;//������ �����ġ
	CBTN_Event* pCBT_Event;
	mutex cs_PriQ;
}PriQ_Event;// �켱���� ť

PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Event, const char* name, int capacity);//ť���� ����
Event* enPriQ_Event(PriQ_Event* pPriQ_Event, Event ev);//�̺�Ʈ �߰�
Event* dePriQ_Event(PriQ_Event* pPriQ_Event);//�̺�Ʈ ����
void printPriQ_Event(PriQ_Event* pPriQ_Event);//�̺�Ʈ ���
//void fprintPriQ_Event(FILE* fout, PriQ_Event* pPriQ_Event);//���Ͽ� �̺�Ʈ���
void deletePriQ_Event(PriQ_Event* pPriQ_Event);//ť���� ��ȯ

#endif // !P_H
