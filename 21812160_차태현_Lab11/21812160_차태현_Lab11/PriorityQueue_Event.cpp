#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"PriorityQueue_Event.h"
#include"Event.h"

bool hasLeftchild(int pos, PriQ_Event* pPriQ_Ev)//�����ڽ��� �ִ��� �Ǻ�
{
	if (pos * 2 <= pPriQ_Ev->num_entry)//�����ڽ��� pos*2
		return TRUE;
	else
		return FALSE;
}

bool hasRightchild(int pos, PriQ_Event* pPriQ_Ev)//�������ڽ��� �ִ��� �Ǻ�
{
	if (pos * 2+1 <= pPriQ_Ev->num_entry)//�������ڽ��� pos*2+1
		return TRUE;
	else
		return FALSE;
}

PriQ_Event* initPriQ_Event(PriQ_Event* pPriQ_Ev,const char* name, int capacity = 1)//�켱���� ť �ʱ�ȭ
{
	strcpy(pPriQ_Ev->name, name);
	pPriQ_Ev->capacity = capacity;
	pPriQ_Ev->pCBT_Event = (CBTN_Event*)calloc((capacity + 1), sizeof(CBTN_Event));//1������ ��ġ�ϱ⶧���� �뷮+1
	pPriQ_Ev->num_entry = 0;
	pPriQ_Ev->pos_last = 0;

	return pPriQ_Ev;
}

void deletePriQ_Event(PriQ_Event* pPriQ_Ev)//�����޸� ��ȯ
{
	CBTN_Event* pCBTN_Ev;
	for (int i = 0; i < pPriQ_Ev->num_entry; i++)
	{
		pCBTN_Ev = &pPriQ_Ev->pCBT_Event[i];
		if (pCBTN_Ev != NULL)//�̺�Ʈ�� �����ϴ� �޸𸮰�������
		{
			if(pCBTN_Ev->pEvent != NULL)//�̺�Ʈ��ü�� ����Ǿ��ִ� �޸𸮰� ������
				free(pCBTN_Ev->pEvent);//������ȯ
			free(pCBTN_Ev);//������ȯ
		}
	}
}

void insertPriQ_Event(PriQ_Event* pPriQ_Ev, Event* pEv)//���ο� ����߰�
{
	int pos, pos_parent;
	CBTN_Event CBTN_Ev_tmp;

	if (pPriQ_Ev->num_entry >= pPriQ_Ev->capacity)//�켱���� ť������á����
	{
		CBTN_Event* newCBT_Event;
		int newcapcity;

		newcapcity = 2 * pPriQ_Ev->capacity;//���ο� �뷮
		newCBT_Event = (CBTN_Event*)malloc((newcapcity + 1) * sizeof(CBTN_Event));//1������ ��ġ�ϱ⶧���� �뷮+1

		for (int pos = 1; pos <= pPriQ_Ev->num_entry; pos++)
		{
			newCBT_Event[pos] = pPriQ_Ev->pCBT_Event[pos];//���������� ��������
		}
		free(pPriQ_Ev->pCBT_Event);//������ ����ߴ� �����޸� ��ȯ
		pPriQ_Ev->pCBT_Event = newCBT_Event;//���ο���� ����
		pPriQ_Ev->capacity = newcapcity;//�뷮����
	}

	pos = ++pPriQ_Ev->num_entry;
	pPriQ_Ev->pCBT_Event[pos].priority = pEv->event_pri;//���ο� ��忡�߰�
	pPriQ_Ev->pCBT_Event[pos].pEvent = pEv;//���ο� ��尪�߰�

	while (pos != POS_ROOT)//root���� �ƴҶ� ����
	{
		pos_parent = pos / 2;//�θ��� �ε���=�ڽĳ�� �ε���/2
		if (pPriQ_Ev->pCBT_Event[pos].priority >= pPriQ_Ev->pCBT_Event[pos_parent].priority)//�θ���� �ڽĳ�� �켱���� �� 
			break;
		else
		{
			CBTN_Ev_tmp = pPriQ_Ev->pCBT_Event[pos_parent];//up-heap bubbling�� ���� ��ġ��ȯ
			pPriQ_Ev->pCBT_Event[pos_parent] = pPriQ_Ev->pCBT_Event[pos];
			pPriQ_Ev->pCBT_Event[pos] = CBTN_Ev_tmp;
			pos = pos_parent;
		}
	}
	
}


Event* removeMinPriQ_Event(PriQ_Event* pPriQ_Ev)//�켱������ �������� ������ ������
{
	Event* pEv;
	CBTN_Event CBT_Event_tmp;
	int pos, pos_root = 1, pos_last, pos_child;

	if (pPriQ_Ev->num_entry <= 0)//��������� ��ȯ�ҰԾ���
		return NULL;

	pEv = pPriQ_Ev->pCBT_Event[1].pEvent;//�켱������ ������� �̺�Ʈ ����(��ȯ�� ���)
	pos_last = pPriQ_Ev->num_entry;//��� ���� �����������ġ
	--pPriQ_Ev->num_entry;//������ ��尡 ��Ʈ���� ���鼭 ���� �پ��

	if (pPriQ_Ev->num_entry > 0)
	{
		pPriQ_Ev->pCBT_Event[pos_root] = pPriQ_Ev->pCBT_Event[pos_last];//��������带 ��Ʈ��ġ�� ����
		pos_last--;


		pos = pos_root;
		while (hasLeftchild(pos, pPriQ_Ev))//�����ڽ��� ������
		{
			pos_child = pos * 2;//���� �ڽ�
			if (hasRightchild(pos, pPriQ_Ev))//������ �ڽĵ� �ִ°�� 
			{
				if (pPriQ_Ev->pCBT_Event[pos_child].priority > pPriQ_Ev->pCBT_Event[pos_child + 1].priority)//������ �ڽ��� �켱������ �������
					pos_child = pos * 2 + 1;//������ �ڽ��� �켱������ �� ����
			}
			if (pPriQ_Ev->pCBT_Event[pos_child].priority < pPriQ_Ev->pCBT_Event[pos].priority)//�ڽ��� �켱������ �� �������
			{
				CBT_Event_tmp = pPriQ_Ev->pCBT_Event[pos];//down-heap bubbling�� ���� ��ġ��ȯ
				pPriQ_Ev->pCBT_Event[pos] = pPriQ_Ev->pCBT_Event[pos_child];
				pPriQ_Ev->pCBT_Event[pos_child] = CBT_Event_tmp;
			}
			else
				break;
			pos = pos_child;
		}
	}
	return pEv;
}

void fprintPriQ_Event(FILE* fout, PriQ_Event* pPriQ_Event)
{
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;

	if (pPriQ_Event->num_entry == 0)//������ ������ 0�Ͻ�
	{
		fprintf(fout, "PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;

	fprintf(fout, "\n CompBinTree :\n", level);
	while (count <= pPriQ_Event->num_entry)
	{
		fprintf(fout, " level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count)
		{
			pEv = pPriQ_Event->pCBT_Event[pos].pEvent;//������ ��ġ�� �̺�Ʈ�� �Է�
			eventPriority = pPriQ_Event->pCBT_Event[pos].priority;//�켱���� ����
			fprintEvent(fout, pEv);//�̺�Ʈ ���
			pos++;
			count++;
			if (count > pPriQ_Event->num_entry)//������ �������� ū��� ��³�
				break;
			count_per_line++;
			if ((count_per_line % EVENT_PER_LINE) == 0)//���ٿ� 5�� ���
			{
				if (count_per_line < level_count)
					fprintf(fout, "\n ");
				else
					fprintf(fout, "\n");
			}
		}
		if ((count_per_line % EVENT_PER_LINE) != 0)
			fprintf(fout, "\n");
		level++;
		level_count *= 2;
	}
	fprintf(fout, "\n");
}

void printPriQ_Event(PriQ_Event* pPriQ_Event)
{
	int pos, count, count_per_line;
	int eventPriority;
	int level = 0, level_count = 1;
	Event* pEv;

	if (pPriQ_Event->num_entry == 0)//������ ������ 0�Ͻ�
	{
		printf("PriorityQueue_Event is empty !!\n");
		return;
	}
	pos = 1;
	count = 1;

	printf("\n CompBinTree :\n", level);
	while (count <= pPriQ_Event->num_entry)
	{
		printf(" level%2d : ", level);
		count_per_line = 0;
		while (count_per_line < level_count)
		{
			pEv = pPriQ_Event->pCBT_Event[pos].pEvent;//������ ��ġ�� �̺�Ʈ�� �Է�
			eventPriority = pPriQ_Event->pCBT_Event[pos].priority;//�켱���� ����
			printEvent(pEv);//�̺�Ʈ ���
			pos++;
			count++;
			if (count > pPriQ_Event->num_entry)//������ �������� ū��� ��³�
				break;
			count_per_line++;
			if ((count_per_line % EVENT_PER_LINE) == 0)//���ٿ� 5�� ���
			{
				if (count_per_line < level_count)
					printf("\n ");
				else
					printf("\n");
			}
		}
		if ((count_per_line % EVENT_PER_LINE) != 0)
			printf("\n");
		level++;
		level_count *= 2;
	}
	printf("\n");
}

