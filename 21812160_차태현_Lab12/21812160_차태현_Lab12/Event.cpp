#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include"Event.h"

void printEvent(Event* pEv)//�̺�Ʈ ���
{
	printf("Ev(id:%3d, pri:%2d, gen:%2d, proc:%2d) ", pEv->ev_no, pEv->ev_pri,	pEv->ev_generator, pEv->ev_handler);
}

Event* genEvent(Event* pEv, int event_Gen_ID, int ev_no, int ev_pri)//�̺�Ʈ ����
{
	pEv = (Event*)calloc(1, sizeof(Event));//�����޸� �Ҵ�
	if (pEv == NULL)
		return NULL;// �����Ҵ� ����� �ȵǾ�����
	pEv->ev_generator = event_Gen_ID;
	pEv->ev_handler = -1;//���� ������������
	pEv->ev_no = ev_no;
	pEv->ev_pri = ev_pri;

	return pEv;
}
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)//�ð��� ���
{
	LONGLONG t_diff;
	t_diff = pEv->ev_t_handle.QuadPart - pEv->ev_t_gen.QuadPart;//�̺�Ʈ ����Ƚð� - �̺�Ʈ �߰��Ƚð�
	pEv->elap_time = (double)t_diff / freq.QuadPart; //�ð���/���ļ�
}

void printEvent_withTime(Event* pEv)//�ɸ��ð��� �̺�Ʈ ���
{
	printf("Ev(no:%2d,pri:%2d,elap_t:%6.0lf[ms]", pEv->ev_no, pEv->ev_pri, pEv->elap_time*1000);
}