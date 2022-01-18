#ifndef E_H
#define E_H
#include<stdio.h>
#include<Windows.h>
#define NUM _PROPROTY 100
#define EVENT_PER_LINE 5

typedef struct {
	int ev_no;
	int ev_generator;
	int ev_handler;
	int ev_pri;//�켱����
	LARGE_INTEGER ev_t_gen;// �ð������ ���� ����
	LARGE_INTEGER ev_t_handle;// �ð������ ���Ѻ���
	double elap_time; //�ð���

}Event; //�̺�Ʈ ����ü����

void printEvent(Event* pEvt);//�̺�Ʈ ���
Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri);//�̺�Ʈ����
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq);//�ð��� ���
void printEvent_withTime(Event* pEv);//�ð����� �Բ� �̺�Ʈ ���

#endif