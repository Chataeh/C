#ifndef C_H
#define C_H
#include"Event.h"

typedef struct {
	Event* CirBuff_Ev;
	int capacity;//�뷮
	int front;//ó��
	int end;//������
	int num_elements;
}CirQ_Event;

CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity);//ȯ��ť���� �ʱ�ȭ
bool isCirQFull(CirQ_Event* pCirQ);//ȯ�� ť������ ����á���� �Ǻ�
bool isCirQEmpty(CirQ_Event* pCirQ);//ȯ�� ť ������ ����ִ��� �Ǻ�
void printCirQ_Event(CirQ_Event* CirQ);//�̺�Ʈ ���
void fprintCirQ_Event(FILE* fout, CirQ_Event* CirQ);//���Ͽ� �̺�Ʈ ���
Event* enCirQ(CirQ_Event* CirQ, Event ev);//�̺�Ʈ�߰�
Event* deCirQ(CirQ_Event* CirQ);//�̺�Ʈ ����
void delCirQ(CirQ_Event* CirQ);//�ʱ�ȭ

#endif // !C_H
