#include<stdio.h>
#include<stdlib.h>
#include"CirQ_Event.h"


CirQ_Event* initCirQ(CirQ_Event* pCirQ, int capacity)//ȯ��ť���� �ʱ�ȭ
{
	Event* pEv;

	pEv = (Event*)calloc(capacity, sizeof(Event));//�����Ҵ�

	pCirQ->CirBuff_Ev = pEv;//�����Ҵ�� pEv�� �Է�
	pCirQ->capacity = capacity;//�뷮�� �Է��� �뷮
	pCirQ->front = pCirQ->end = pCirQ->num_elements = 0;//������ ��ҵ��� 0

	return pCirQ;
}

bool isCirQFull(CirQ_Event* pCirQ)
{
	if (pCirQ->num_elements == pCirQ->capacity)//�뷮�� �� á�����
		return true;
	else
		return false;
}

bool isCirQEmpty(CirQ_Event* pCirQ)
{
	if (pCirQ->num_elements == 0)//�뷮�� �� ����ִ°��
		return true;
	else
		return false;
}

void printCirQ_Event(CirQ_Event* CirQ)
{
	Event ev;
	int index;

	printf(" %2d Elements in CirQ_Event(index_front:%2d):\n", CirQ->num_elements, CirQ->front);
	if (isCirQEmpty(CirQ))
	{
		printf("pCirQ_Event is Empty");
	}
	else
	{
		for (int i = 0; i < CirQ->num_elements; i++)
		{
			index = CirQ->front + i;
			if (index >= CirQ->capacity)
				index = index % CirQ->capacity;//ȯ���̱⶧���� ������ �Ѿ���� ������ ���ƿ�
			ev = CirQ->CirBuff_Ev[index];
			printEvent(&ev);
			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != CirQ->num_elements))//���Ұ� �����ְ� 5���� ������� �ٹٲ�
				printf("\n   ");

		}
	}
	printf("\n");
}

void fprintCirQ_Event(FILE* fout,CirQ_Event* CirQ)
{
	Event ev;
	int index;

	fprintf(fout," %2d Elements in CirQ_Event(index_front:%2d):\n", CirQ->num_elements, CirQ->front);
	if (isCirQEmpty(CirQ))
	{
		fprintf(fout,"pCirQ_Event is Empty");
	}
	else
	{
		for (int i = 0; i < CirQ->num_elements; i++)
		{
			index = CirQ->front + i;
			if (index >= CirQ->capacity)
				index = index % CirQ->capacity;//ȯ���̱⶧���� ������ �Ѿ���� ������ ���ƿ�
			ev = CirQ->CirBuff_Ev[index];//�ε��� ��ġ�ǰ��� ev�� �־���
			fprintEvent(fout,&ev);
			if ((((i + 1) % EVENT_PER_LINE) == 0) && ((i + 1) != CirQ->num_elements))
				fprintf(fout,"\n   ");

		}
	}
	fprintf(fout,"\n");
}

Event* enCirQ(CirQ_Event* CirQ, Event ev)//����ü �߰�
{
	if (isCirQFull(CirQ))
	{
		return NULL;
	}
	CirQ->CirBuff_Ev[CirQ->end] = ev;//end��ġ�� ����ü��
	CirQ->num_elements++;//�̺�Ʈ �� ���ϱ�
	CirQ->end++;//end��ġ ���ϱ�
	if (CirQ->end >= CirQ->capacity)
		CirQ->end = CirQ->end % CirQ->capacity;//ȯ���̱⶧���� ����Է����־� end���� �뷮�� �Ѿ���ÿ� �ٽ� ó������ ���ƿ�

	return &(CirQ->CirBuff_Ev[CirQ->end]);
}

Event* deCirQ(CirQ_Event* CirQ)//����ü ��������
{
	if (isCirQEmpty(CirQ))
		return NULL;

	Event* pEv = &(CirQ->CirBuff_Ev[CirQ->front]);//front��ġ�� ����ü�� 
	CirQ->front++;//front�� ���ϱ�
	if (CirQ->front >= CirQ->capacity)
		CirQ->front = CirQ->front % CirQ->capacity;//ȯ��ť�⶧���� front���� �뷮�� �Ѿ����
	CirQ->num_elements--;//�̺�Ʈ �� ���ֱ�

	return pEv;
}

void delCirQ(CirQ_Event* CirQ)//�ʱ�ȭ
{
	if (CirQ->CirBuff_Ev != NULL)
		free(CirQ->CirBuff_Ev);//�����Ҵ� ��ȯ
	CirQ->CirBuff_Ev = NULL;//NULL�� �ʱ�ȭ
	CirQ->capacity = 0;//0���� �ʱ�ȭ
	CirQ->front = CirQ->end = CirQ->num_elements = 0;//0���� �ʱ�ȭ
}