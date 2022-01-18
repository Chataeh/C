#pragma once
#ifndef SIMULATION_PARAMETERS_H
#define SIMULATION_PARAMETERS_H

#define NUM_EVENT_GENERATORS 3// 이벤트 생성 스레드 수
#define NUM_EVENTS_PER_GEN 50//스레드당 생성할 이벤트
#define NUM_EVENT_HANDLERS 2// 이벤트 처리할 스레드 수
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)// 전체 생성이벤트
#define PLUS_INF INT_MAX
#define MAX_ROUND 1000//최대 라운드
#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3 // 0~2까지 high Pri 3~9 low Pri
#define EVENT_PER_LINE 5
#define NUM_ROUTERS 3
#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3
#define EVENT_PER_LINE 5

#endif