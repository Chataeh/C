#ifndef PRI_H
#define PRI_H

#include"Event.h"
#define POS_ROOT 1
#define MAX_NAME_LEN 80
#define TRUE 1
#define FALSE 0

typedef struct
{
	int priority;//�켱����
	Event* pEvent;
}CBTN_Event;

typedef struct
{
	char name[MAX_NAME_LEN];//���ڿ�����
	int capacity;//�� �뷮
	int num_entry;// ������ ����
	int pos_last;//������ ������ �ε���
	CBTN_Event* pCBT_Event;
}PriQ_Event;


void insertPriQ_Event(PriQ_Event* pPriQ_Event, Event* pEvent);
Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Event);
void printPriQ_Event(PriQ_Event* pPriQ_Event);
void fprintPriQ_Event(FILE* fout, PriQ_Event* pPriQ_Event);
void deletePriQ_Event(PriQ_Event* pPriQ_Event);
PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Ev,const char* name,int capacity);
#endif // !PRI_H

