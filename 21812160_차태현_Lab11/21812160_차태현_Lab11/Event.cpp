#include<stdio.h>
#include<stdlib.h>
#include"Event.h"

void printEvent(Event* pEv)
{
	printf("Ev(no:%3d,pri:%2d", pEv->event_no, pEv->event_pri);//event_no��event_pri���
}

void fprintEvent(FILE* fout, Event* pEv)
{
	fprintf(fout,"Ev(no:%3d,pri:%2d)", pEv->event_no, pEv->event_pri);//���Ͽ� event_no��event_pri���
}

Event* genEvent(Event* pEvent, int event_Gen_ID, int event_no, int event_pri)//�̺�Ʈ �� ����
{
	pEvent = (Event*)malloc(sizeof(Event));//�����Ҵ�

	pEvent->event_gen_addr = event_Gen_ID;//����ü ������
	pEvent->event_no = event_no;
	pEvent->event_pri = event_pri;

	return pEvent;//����ü ��ȯ
}