#include<stdio.h>
#include<stdlib.h>
#include"Event.h"

const char* strEventStatus[] = { "GENERATED", "ENQUED", "PROCESSED", "UNDEFINED" };

void printEvent(Event* pEvt)
{
	printf("Ev(no:%3d,pri:%2d,gen:%3d, proc:%3d)", pEvt->seqNO, pEvt->priority, pEvt->genAddr, pEvt->handlerAddr);//�̺�Ʈ ���
}

void printEvent_withTime(Event* pEv)
{
	printf("Ev(no:%3d,pri:%2d,%6.0lf[ms])", pEv->seqNO, pEv->priority, pEv->t_elapsed * 1000);//�̺�Ʈ �����ϴµ� �ɸ��ð� �� �̺�Ʈ ���
}
void calc_elapsed_time(Event* pEv, LARGE_INTEGER freq)
{
	LONGLONG t_diff_LL;
	double t_elapsed;

	t_diff_LL = pEv->t_proc.QuadPart - pEv->t_gen.QuadPart;//ó���� �ð�-�����Ƚð�
	t_elapsed = (double)t_diff_LL / (double)freq.QuadPart;//�ð���/���ļ�
	pEv->t_elapsed = t_elapsed;
}
void fprintEvent(FILE* fout, Event* pEvt)
{
	fprintf(fout,"Ev(no:%3d,pri:%2d,gen:%3d, proc:%3d)", pEvt->seqNO, pEvt->priority, pEvt->genAddr, pEvt->handlerAddr);//�̺�Ʈ ���

}
void initEvent(Event* pEv, unsigned int sAddr,unsigned int sN)//�̺�Ʈ ����
{
	

	pEv = (Event*)calloc(1, sizeof(Event));//�����޸� �Ҵ�
	pEv->genAddr = sAddr;
	pEv->handlerAddr = -1;//���� ������������
	pEv->seqNO = sN;
	pEv->priority = -1;

	
}