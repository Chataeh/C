#include "DLL_EvQ.h"
void initDLL_EvQ(DLL_EvQ* pEvQ, int pri)//���Ḯ��Ʈ ť �ʱ�ȭ
{
	pEvQ->cs_EvQ.lock();//�Ӱ豸��
	pEvQ->priority = pri;
	pEvQ->front = pEvQ->back = NULL;//ó���� ������ �������ּ� NULL�� �ʱ�ȭ
	pEvQ->num_event = 0;//�̺�Ʈ�� 0���� �ʱ�ȭ
	pEvQ->cs_EvQ.unlock();//�Ӱ豸��
}

Event* enDLL_EvQ(DLL_EvQ* pEvQ, Event* pEv)//��ť �̺�Ʈ ����
{
	DLLN_Ev* pLN_Ev;
	if (pEv == NULL)
	{
		printf("Error in enDLL_EvQ :: DLL_EvQ is NULL !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev = (DLLN_Ev*)calloc(1, sizeof(DLLN_Ev));//�����޸� ����
	if (pLN_Ev == NULL)
	{
		printf("Error in enDLL_EvQ :: memory allocation for new DLLN failed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return NULL;
	}
	pLN_Ev->pEv = pEv;//������ �ޱ�
	pEvQ->cs_EvQ.lock();//�Ӱ豸�� ����
	if (pEvQ->num_event == 0) //���Ḯ��Ʈ ť�� ����ִٸ�
	{
		pEvQ->front = pEvQ->back = pLN_Ev;//ó���� ���� �־��� �̺�Ʈ�� ���� �̺�Ʈ�� �ϳ����̱⶧��
		pLN_Ev->prev = pLN_Ev->next = NULL;//������ �̺�Ʈ�� �����̺�Ʈ�� ���� �̺�Ʈ�� �������� NULL
		pEvQ->num_event = 1;//��� ������ �̺�Ʈ ��
	}
	else
	{
		pLN_Ev->prev = pEvQ->back;//�������ڸ� �ڿ� ��ť�ǹǷ� ��ť�� �̺�Ʈ���� �̺�Ʈ�� ������ �������̺�Ʈ
		pEvQ->back->next = pLN_Ev;//���� �������̺�Ʈ�� ������ġ�� ��ť��
		pEvQ->back = pLN_Ev;//������ �̺�Ʈ�� ��� ��ť���� �̺�Ʈ�� ��
		pLN_Ev->next = NULL;//������ �̺�Ʈ �����̺�Ʈ�� ����
		pEvQ->num_event++;//�̺�Ʈ �� �߰�
	}
	pEvQ->cs_EvQ.unlock();//�Ӱ豸��
	return pLN_Ev->pEv;
}

Event* deDLL_EvQ(DLL_EvQ* pEvQ)//��ť �̺�Ʈ����
{
	Event* pEv;
	DLLN_Ev* pLN_Ev_OldFront;
	pEvQ->cs_EvQ.lock();//�Ӱ豸�� ����
	if (pEvQ->num_event <= 0)//ť������ �ƹ��͵� �������
	{
		pEvQ->cs_EvQ.unlock();//������ �������� ����Ǳ⶧���� �Ӱ豸���� �����������
		return NULL; // DLL_EvQ is Empty
	}
	else
	{
		pLN_Ev_OldFront = pEvQ->front;
		pEv = pEvQ->front->pEv;//ó����ġ���� �����ϱ⶧���� �̺�Ʈ�� pEv�� ����
		pEvQ->front = pEvQ->front->next;//ó����ġ�� ������ġ�� �̺�Ʈ�� ó���̺�Ʈ�� ��
		if (pEvQ->front != NULL)//ó����ġ�� �̺�Ʈ�� �������
			pEvQ->front->prev = NULL;
		pEvQ->num_event--;//��ť �� �� �̺�Ʈ ���� �پ��
		free(pLN_Ev_OldFront); // release memory for the current front DLLN
		pEvQ->cs_EvQ.unlock();//�Ӱ豸��
		return pEv;
	}
}
void printDLL_EvQ(DLL_EvQ* pEvQ)//���
{
	int index = 0;
	int count;
	Event* pEv;
	DLLN_Ev* pLN_Ev;
	if (pEvQ == NULL)//����Ұ��� �������
	{
		printf("Error in printDLL_EvQ :: DLL_EvQ is NULL !!");
		printf("Press any key to continue ...\n");
		getc(stdin);
	}
	//printf("DLL_EvQ(num_event: %2d):\n ", pEvQ->num_event);
	if (pEvQ->num_event <= 0)
		return;
	pLN_Ev = pEvQ->front;
	count = 0;
	while (pLN_Ev != NULL)//ť�� ù��° �ڸ��� �ִ°��
	{
		pEv = pLN_Ev->pEv;
		if (pEv == NULL)
			break;
		printEvent(pEv); printf(" ");
		count++;
		if ((count % 5) == 0)
			printf("\n ");
		pLN_Ev = pLN_Ev->next;//������ġ�� ù��° ��ġ����
	}
}