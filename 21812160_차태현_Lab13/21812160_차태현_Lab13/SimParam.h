#pragma once
#ifndef SIMULATION_PARAMETERS_H
#define SIMULATION_PARAMETERS_H

#define NUM_EVENT_GENERATORS 3// �̺�Ʈ ���� ������ ��
#define NUM_EVENTS_PER_GEN 50//������� ������ �̺�Ʈ
#define NUM_EVENT_HANDLERS 2// �̺�Ʈ ó���� ������ ��
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS)// ��ü �����̺�Ʈ
#define PLUS_INF INT_MAX
#define MAX_ROUND 1000//�ִ� ����
#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3 // 0~2���� high Pri 3~9 low Pri
#define EVENT_PER_LINE 5
#define NUM_ROUTERS 3
#define NUM_PRIORITY 10
#define PRIORITY_THRESHOLD 3
#define EVENT_PER_LINE 5

#endif