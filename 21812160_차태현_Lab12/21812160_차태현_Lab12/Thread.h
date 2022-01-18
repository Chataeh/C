#ifndef T_H
#define T_H

#include"PriQ_Event.h"
#include"SimParam.h"

using namespace std;

enum ROLE {
	EVENT_GENERATOR,
	EVENT_HANDLER
};
enum THREAD_FLAG {
	INITIALIZE, RUN,
	TERMINATE
};


typedef struct
{
	int numEventGenerated;//������ �̺�Ʈ ��
	int numEventProcessed;//ó���� �̺�Ʈ ��
	int totalEventGenerated;
	int totalEventProcessed;
	Event eventGenerated[TOTAL_NUM_EVENTS]; //������ �̺�Ʈ
	Event eventProcessed[TOTAL_NUM_EVENTS]; //ó���� �̺�Ʈ
	THREAD_FLAG* pFlagThreadTerminate;
} ThreadStatusMonitor;//����͸��ؼ� ������ ����ü

typedef struct
{
	mutex* pMTX_main;//�Ӱ豸������
	mutex* pMTX_thrd_mon;//����͸��Ҷ� �Ӱ豸�� ����
	PriQ_Event* pPriQ_Event;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;//�������̺�Ʈ ��
	ThreadStatusMonitor* pThrdMon;

} ThreadParam_Event;//������ ������ �μ��� ��������

void Thread_EventHandler(ThreadParam_Event* pParam);
void Thread_EventGenerator(ThreadParam_Event* pParam);

#endif // !