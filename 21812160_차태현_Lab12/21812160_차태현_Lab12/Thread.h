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
	int numEventGenerated;//생성된 이벤트 수
	int numEventProcessed;//처리된 이벤트 수
	int totalEventGenerated;
	int totalEventProcessed;
	Event eventGenerated[TOTAL_NUM_EVENTS]; //생성된 이벤트
	Event eventProcessed[TOTAL_NUM_EVENTS]; //처리된 이벤트
	THREAD_FLAG* pFlagThreadTerminate;
} ThreadStatusMonitor;//모니터링해서 관찰할 구조체

typedef struct
{
	mutex* pMTX_main;//임계구역설정
	mutex* pMTX_thrd_mon;//모니터링할때 임계구역 설정
	PriQ_Event* pPriQ_Event;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;//생성할이벤트 수
	ThreadStatusMonitor* pThrdMon;

} ThreadParam_Event;//스레드 생성시 인수를 전달위함

void Thread_EventHandler(ThreadParam_Event* pParam);
void Thread_EventGenerator(ThreadParam_Event* pParam);

#endif // !