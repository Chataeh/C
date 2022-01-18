#ifndef S_H
#define S_H

#define NUM_EVENT_GENERATORS 1 //생성하는 스레드
#define NUM_EVENTS_PER_GEN 50//발생시킬 이벤트 수
#define NUM_EVENT_HANDLERS 1//처리하는 이벤트
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)//전체 생성할 이벤트 수
#define PRI_QUEUE_CAPACITY 1
#define PLUS_INF INT_MAX
#define MAX_ROUND 1000

#endif